CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

PROJECT(Blitz++ CXX)

#   Blitz version and release date.

SET(Blitz++_MAJOR 0)
SET(Blitz++_MINOR 9)
SET(Blitz++_PATCH 0)
SET(Blitz++_VERSION ${Blitz++_MAJOR}.${Blitz++_MINOR}.${Blitz++_PATCH})
SET(Blitz++_Release "2010-05-24")

#   Packaging

SET(CPACK_GENERATOR "TGZ")
SET(CPACK_PACKAGE_VERSION_MAJOR ${Blitz++_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${Blitz++_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${Blitz++_PATCH})
SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME Blitz++-${Blitz++_VERSION})
SET(CPACK_SOURCE_IGNORE_FILES ".*.swp$" ".*.swo$" "~$" ".bz2$" ".gz$")

INCLUDE(CPack)
INCLUDE(UnitTests)
INCLUDE(BlitzConfigFileName)
INCLUDE(Win32Compat)

INCLUDE_DIRECTORIES(BEFORE SYSTEM ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

ADD_CUSTOM_TARGET(generated-headers ALL)

#Makeinfo, texi2html, doxygen
# blas

SET(GENERATED_HEADERS)
ADD_SUBDIRECTORY(bin) 
ADD_SUBDIRECTORY(blitz) 
ADD_SUBDIRECTORY(random) 
ADD_SUBDIRECTORY(lib) 
ADD_SUBDIRECTORY(doc) 

IF (BUILD_TESTING)
    ADD_SUBDIRECTORY(testsuite) 
    ADD_SUBDIRECTORY(examples) 
ENDIF()

OPTION(FORTRAN "Enable Fortran benchmarks")
IF (Fortran)
    ENABLE_LANGUAGE(Fortran OPTIONAL)
    ADD_SUBDIRECTORY(benchmarks) 
ELSE()
    MESSAGE(STATUS "${CMAKE_CURRENT_SOURCE_DIR}: skipped subdir $(FORTRAN_DIRS)")
ENDIF()

########### install files ###############

INSTALL(EXPORT blitz DESTINATION lib/pkgconfig)
INSTALL(FILES blitz.pc DESTINATION lib/pkgconfig)

#original (partial) Makefile.am contents follow:

#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = blitz.pc
#
#DISTCLEANFILES = blitz.pc blitz.pc.in blitz-uninstalled.pc
#
#lib: blitz-library
#
#blitz-library:
#	@(cd lib && $(MAKE) $(AM_MAKEFLAGS)) || exit 1;
#
#check-testsuite: lib
#	@(cd testsuite && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;
#
#check-examples: lib
#	@(cd examples && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;
#
#check-benchmarks: lib
#	@(cd benchmarks && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;
