#
# Copyright (c) 2016      Intel, Inc.  All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#

headers = \
         collectives_brucks.h

sources = \
          collectives_brucks_component.c \
          collectives_brucks.c

# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_scon_collectives_brucks_DSO
lib =
lib_sources =
component = mca_collectives_brucks.la
component_sources = $(headers) $(sources)
else
lib = libmca_collectives_brucks.la
lib_sources = $(headers) $(sources)
component =
component_sources =
endif

mcacomponentdir = $(sconlibdir)
mcacomponent_LTLIBRARIES = $(component)
mca_collectives_brucks_la_SOURCES = $(component_sources)
mca_collectives_brucks_la_LDFLAGS = -module -avoid-version

noinst_LTLIBRARIES = $(lib)
libmca_collectives_brucks_la_SOURCES = $(lib_sources)
libmca_collectives_brucks_la_LDFLAGS = -module -avoid-version

