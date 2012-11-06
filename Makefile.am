ACLOCAL_AMFLAGS = -I m4

CFLAGS = -Wall
CXXFLAGS = -Wall

SUBDIRS = src


#
# Proxy definition to make guitest target in src directory
#
.PHONY : guitest
guitest :
	cd src && $(MAKE) $(AM_MAKEFLAGS) $@

