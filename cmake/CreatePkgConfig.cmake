FUNCTION(INSTALL)
    
ENDFUNCTION()

FUNCTION (CreatePkgConfigInfo)
    SET(pkgconfig_prefix ${CMAKE_INSTALL_PREFIX})
    SET(pkgconfig_version ${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}.${PACKAGE_VERSION_PATCH})
    SET(pkgconfig_execprefix "\${prefix}")
    SET(pkgconfig_libdir "\${exec_prefix}/lib")
    SET(pkgconfig_includedir "\${prefix}/include")
    SET(pkgconfig_package_name "${CMAKE_PROJECT_NAME}")
    SET(pkgconfig_


CMAKE_LIBRARY_PATH_FLAG
CMAKE_LINK_LIBRARY_FLAG
INCLUDE_DIRECTORIES
LINK_DIRECTORIES
CPACK_PACKAGE_DESCRIPTION_FILE
CPACK_PACKAGE_DESCRIPTION_SUMMARY
ENDFUNCTION()
