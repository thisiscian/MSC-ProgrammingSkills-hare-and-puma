ACLOCAL_AMFLAGS = -I m4

CFLAGS = -Wall
CXXFLAGS = -Wall

SUBDIRS = src


#
# Proxy definition to make targets in src directory
#
.PHONY : guitest
.PHONY : performancetest
guitest performancetest:
	cd src && $(MAKE) $(AM_MAKEFLAGS) $@

