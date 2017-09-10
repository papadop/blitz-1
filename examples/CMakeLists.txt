#TESTS(example
#      array cartesian cast cfd complex-test convolve curldiv deriv diff erf fixed
#      indirect io iter matmult nested numinquire outer pauli pick polymorph prettyprint
#      qcd rand2 random rangexpr reduce simple slicing stencil2 stencil3 stencil
#      stencilet storage tiny transform useret where whitt)

add_custom_target(examples)

TESTS(examples
      array cartesian cast complex-test convolve deriv fixed
      io iter matmult nested numinquire outer polymorph prettyprint
      rand2 random reduce simple slicing stencil2 
      storage tiny useret where whitt)

add_custom_target(check-examples
                  DEPENDS blitz examples
                  COMMAND ${CMAKE_BUILD_TOOL} test)
