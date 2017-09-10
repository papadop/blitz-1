INCLUDE(ParseArguments.cmake)

MACRO(STENCIL_DOC texi define)
    GET_FILENAME_COMPONENT(name ${texi} NAME_WE)
    SET(source ${name}.cpp)
    SET(stenciltoapply ${name})
    SET(stencilargs ${define})
    CONFIGURE_FILE(dump-stencil.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/${source} @ONLY)
    ADD_EXECUTABLE(${name} ${CMAKE_CURRENT_BINARY_DIR}/${source})
    GET_TARGET_PROPERTY(PROG_EXE ${name} LOCATION)
    TARGET_LINK_LIBRARIES(${name} blitz)
    ADD_CUSTOM_TARGET(${texi} ALL DEPENDS ${name}
                      COMMAND ${PROG_EXE} > ${texi} 2>&1)
ENDMACRO()
    
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

MACRO(GENERATE_STENCILS_DOC)
    SET(args ${ARGN})
    PARSE_ARGUMENTS(STENCIL "NORMAL;LAPLACIAN" "" ${args})
    FOREACH (texi ${STENCIL_NORMAL})
        STENCIL_DOC(${texi} "A,1")
    ENDFOREACH()
    ADD_DEFINITIONS(-Dstencilargs=A)
    FOREACH (texi ${STENCIL_LAPLACIAN})
        STENCIL_DOC(${texi} "A")
    ENDFOREACH()
    SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${STENCIL_NORMAL};${STENCIL_LAPLACIAN}")
ENDMACRO()

SET(NORMAL_STENCILS
    central12.texi central22.texi central32.texi central42.texi central14.texi central24.texi central34.texi central44.texi
    forward11.texi forward21.texi forward31.texi forward41.texi forward12.texi forward22.texi forward32.texi forward42.texi
    backward11.texi backward21.texi backward31.texi backward41.texi backward12.texi backward22.texi backward32.texi backward42.texi)

SET(LAPLACIAN_STENCILS Laplacian2D.texi Laplacian2D4.texi)

GENERATE_STENCILS_DOC(NORMAL ${NORMAL_STENCILS} LAPLACIAN ${LAPLACIAN_STENCILS})

SOURCE_GROUP(Stencils FILES ${NORMAL_STENCILS} ${LAPLACIAN_STENCILS})

########### install files ###############

#EXTRA_DIST = dump-stencil.cpp
#
#clean-local:
#	-rm -rf *.ii *.ti cxx_repository Template.dir ii_files ti_files dump-stencil *.texi
