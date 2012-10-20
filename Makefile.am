ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src


#
# Proxy definition to make guitest target in src directory
#
.PHONY : guitest
guitest :
	cd src && $(MAKE) $(AM_MAKEFLAGS) $@
