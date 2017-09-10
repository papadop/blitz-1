TESTS(example
      array cartesian cast cfd complex-test convolve curldiv deriv diff erf fixed
      indirect io iter matmult nested numinquire outer pauli pick polymorph prettyprint
      qcd rand2 random rangexpr reduce simple slicing stencil2 stencil3 stencil
      stencilet storage tiny transform useret where whitt)

#EXTRA_DIST = stencil4.f profile.cpp tiny2.cpp tiny3.cpp
#
#AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir) -I$(top_builddir)
#LDADD = -L$(top_builddir)/lib -lblitz
#
##profile_SOURCES = profile.cpp
##tiny2_SOURCES = tiny2.cpp
##tiny3_SOURCES = tiny3.cpp
#
#check-examples: $(EXTRA_PROGRAMS)
#	@echo Running examples...
#	@for prog in $(EXTRA_PROGRAMS) ; do \
#		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
#	done
#	@echo All tests passed.
