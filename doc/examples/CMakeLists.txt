MACRO(TEXI_FROM_SOURCE source)
    GET_FILENAME_COMPONENT(name ${source} NAME_WE)
    SET(texi ${name}.texi)
    ADD_CUSTOM_COMMAND(OUTPUT ${texi}
                       COMMAND sed -e 's/{/@{/' -e 's/}/@}/' ${CMAKE_CURRENT_SOURCE_DIR}/${source} | fold -s -w 80 > ${texi}
                       DEPENDS ${source})
ENDMACRO(TEXI_FROM_SOURCE source)

MACRO(OUTPUT_FROM_SOURCE source)
    GET_FILENAME_COMPONENT(name ${source} NAME_WE)
    ADD_EXECUTABLE(${name} ${source})
    SET(out ${name}.out)
    ADD_CUSTOM_COMMAND(OUTPUT ${out}
                       COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${source} 2>&1 | fold -s -w 80 > ${out}
                       DEPENDS ${name})
ENDMACRO(OUTPUT_FROM_SOURCE source)

MACRO(GENERATE_EXAMPLES var)
    IF (NOT "${var}" STREQUAL "texi" AND NOT "${var}" STREQUAL "out")
       MESSAGE(ERROR,"Unknown output type: ${var}") 
    ENDIF (NOT "${var}" STREQUAL "texi" AND NOT "${var}" STREQUAL "out")
    FOREACH (source ${ARGN})
        IF ("${var}" STREQUAL "texi")
            TEXI_FROM_SOURCE(${source})
        ELSE ("${var}" STREQUAL "texi")
            OUTPUT_FROM_SOURCE(${source})
        ENDIF ("${var}" STREQUAL "texi")
        GET_FILENAME_COMPONENT(name ${source} NAME_WE)
        LIST(APPEND ll ${name}.${var})
    ENDFOREACH (source)
    ADD_CUSTOM_TARGET(${var} DEPENDS ${ll})
    #   Per the documentation this should not be needed as OUTPUT of
    #   ADD_CUSTOM_COMMAND should be automatucally cleaned...
    SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${ll}")
ENDMACRO(GENERATE_EXAMPLES)

SET(EXAMPLES simple.cpp storage.cpp outer.cpp strideslice.cpp slicing.cpp debug.cpp
             output.cpp io.cpp dump.cpp xor.cpp cast.cpp range.cpp fixed.cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

GENERATE_EXAMPLES(texi ${EXAMPLES} fixed-point.h)
GENERATE_EXAMPLES(out  ${EXAMPLES})

TARGET_LINK_LIBRARIES(io blitz)

########### install files ###############

#EXTRA_DIST = fixed-class.cpp fixed-point.h makefile.example io.data
