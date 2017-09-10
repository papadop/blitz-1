INCLUDE(CheckCXXFeatures)

OPTION(BZ_FULLY64BIT "Enable 64 dimensions with > 2^31 elements (NOT IMPLEMENTED)")
OPTION(BZ_THREADSAFE "Enable Blitz thread-safety features")

IF (NOT CHECKED_COMPILER_CXX_FEATURES)
    CHECK_ALL_CXX_FEATURES(BZ_)
    CHECK_HEADER(HAVE_INTTYPES_H inttypes.h)
    SET(BZ_MATH_ABSINT_IN_NAMESPACE_STD ${BZ_HAVE_MATH_ABSINT_IN_NAMESPACE_STD})
    SET(BZ_MATH_FN_IN_NAMESPACE_STD     ${BZ_HAVE_MATH_FN_IN_NAMESPACE_STD})
    SET(BZ_ISNAN_IN_NAMESPACE_STD       ${BZ_HAVE_ISNAN_IN_NAMESPACE_STD})
    SET(BZ_HAVE_NCEG_RESTRICT_EGCS      ${BZ_HAVE_RESTRICT_EGCS})
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.h.in ${BLITZ_CONFIG_FILE})
    SET(CHECKED_COMPILER_CXX_FEATURES TRUE CACHE INTERNAL "Gating variable to avoid checking compiler features multiple times")
ENDIF()

MACRO(GENERATE_BLITZ_HEADER header prog var)
    ADD_CUSTOM_TARGET(${header} ALL)
    ADD_DEPENDENCIES(${header} ${prog})
    ADD_DEPENDENCIES(generated-headers ${header})
    GET_TARGET_PROPERTY(PROG_EXE ${prog} LOCATION)
    ADD_CUSTOM_COMMAND(
        COMMAND ${PROG_EXE}
        TARGET  ${header}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/blitz/generate
        OUTPUTS ${header}
    )
    ADD_CUSTOM_COMMAND(
        SOURCE    ${header}
        TARGET    ${header}
   )
   SET(${var} ${${var}} ${CMAKE_CURRENT_BINARY_DIR}/${header})
ENDMACRO()

ADD_SUBDIRECTORY(generate) 
ADD_SUBDIRECTORY(meta) 
ADD_SUBDIRECTORY(array)

GENERATE_BLITZ_HEADER(vecbops.cc    genvecbops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecuops.cc    genvecuops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecwhere.cc   genvecwhere GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecbfn.cc     genvecbfn   GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(matbops.h     genmatbops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(matuops.h     genmatuops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(mathfunc.h    genmathfunc GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(promote-old.h genpromote  GENERATED_HEADERS)

SET(BLITZ_HEADERS
    applics.h array.h array-impl.h array-old.h bench.cc benchext.cc benchext.h bench.h blitz.h bzconfig.h bzdebug.h compiler.h etbase.h extremum.h
    funcs.h indexexpr.h limits-hack.h listinit.h matdiag.h matexpr.h matgen.h mathf2.h matltri.h matref.h matrix.cc matrix.h matsymm.h mattoep.h
    matutri.h memblock.cc memblock.h minmax.h mstruct.h numinquire.h numtrait.h ops.h prettyprint.h promote.h rand-dunif.h rand-mt.h rand-normal.h
    random.h randref.h rand-tt800.h rand-uniform.h range.h reduce.h shapecheck.h tau.h timer.h tiny.h tinymatexpr.h tinymat.h tinymatio.cc tinyvec.cc
    tinyvec-et.h tinyvec.h tinyvecio.cc tinyveciter.h traversal.cc traversal.h tuning.h tvcross.h tvecglobs.h update.h vecaccum.cc vecall.cc vecany.cc
    veccount.cc vecdelta.cc vecdot.cc vecexpr.h vecexprwrap.h vecglobs.cc vecglobs.h vecio.cc veciter.h vecmax.cc vecmin.cc vecnorm1.cc vecnorm.cc
    vecpick.cc vecpick.h vecpickio.cc vecpickiter.h vecproduct.cc vecsum.cc vector.cc vector-et.h vector.h vecwhere.h wrap-climits.h zero.cc zero.h
)

INSTALL(FILES ${BLITZ_HEADERS} ${GENERATED_HEADERS} DESTINATION include/blitz)
INSTALL(FILES ${BLITZ_CONFIG_FILE} DESTINATION include/blitz/${BLITZ_CONFIG_INSTALL_DIR})
