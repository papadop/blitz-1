SET(blitz_LIB_SRCS ../src/globals.cpp)

ADD_LIBRARY(blitz SHARED ${blitz_LIB_SRCS})
ADD_DEPENDENCIES(blitz generated-headers)

SET_TARGET_PROPERTIES(blitz PROPERTIES
                      VERSION 0.9.0
                      SOVERSION 0
                      CLEAN_DIRECT_OUTPUT 1)

SET(BLITZ_LIBS blitz)
IF (NOT WIN32)
    ADD_LIBRARY(blitz-static STATIC ${blitz_LIB_SRCS})
    ADD_DEPENDENCIES(blitz-static generated-headers)
    SET(BLITZ_LIBS ${BLITZ_LIBS} blitz-static)

    #SET(BLITZ-STATIC-DEFS)
    #IF (NOT WIN32)
    #    GET_TARGET_PROPERTY(BLITZ-STATIC-DEFS blitz-static COMPILE_DEFINITIONS)
    #    IF (NOT BLITZ-STATIC-DEFS)
    #        SET(BLITZ-STATIC-DEFS)
    #    ENDIF()
    #    SET(BLITZ-STATIC-DEFS COMPILE_DEFINITIONS "${BLITZ-STATIC-DEFS};BLITZ_STATIC_LIBRARY")
    #ENDIF()

    SET_TARGET_PROPERTIES(blitz-static PROPERTIES
                          OUTPUT_NAME blitz
                          ${BLITZ-STATIC-DEFS}
                          CLEAN_DIRECT_OUTPUT 1)
ENDIF()

INSTALL(TARGETS ${BLITZ_LIBS}
        EXPORT  blitz
        #RUNTIME DESTINATION bin COMPONENT runtime
        ARCHIVE DESTINATION lib COMPONENT devel
        LIBRARY DESTINATION lib COMPONENT devel
)
