SET(BLITZ_ARRAY_HEADERS
    asexpr.h cartesian.h cgsolve.h complex.cc convolve.cc convolve.h cycle.cc domain.h et.h eval.cc expr.h fastiter.h
    funcs.h functorExpr.h geometry.h indirect.h interlace.cc io.cc iter.h map.h methods.cc misc.cc multi.h newet.h
    newet-macros.h ops.cc ops.h reduce.cc reduce.h resize.cc shape.h slice.h slicing.cc stencil-et.h stencilops.h stencils.cc
    stencils.h storage.h where.h zip.h
)

GENERATE_BLITZ_HEADER(bops.cc genarrbops BLITZ_ARRAY_GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(uops.cc genarruops BLITZ_ARRAY_GENERATED_HEADERS)

INSTALL(FILES ${BLITZ_ARRAY_HEADERS} ${BLITZ_ARRAY_GENERATED_HEADERS} DESTINATION include/blitz/array)
