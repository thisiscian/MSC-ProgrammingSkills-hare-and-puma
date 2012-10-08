ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src


#
# Qt build stuff
#
# See autotroll.m4 :)


SUFFIXES = .moc.cpp .moc.cc .moc.cxx .moc.C .h .hh .hpp \
           .ui .ui.h .ui.hh .ui.hpp \
           .qrc .qrc.cpp .qrc.cc .qrc.cxx .qrc.C

# --- #
# MOC #
# --- #

.hpp.moc.cpp:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.hh.moc.cpp:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.h.moc.cpp:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@

.hpp.moc.cc:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.hh.moc.cc:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.h.moc.cc:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@

.hpp.moc.cxx:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.hh.moc.cxx:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.h.moc.cxx:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@

.hpp.moc.C:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.hh.moc.C:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@
.h.moc.C:
	$(MOC) $(QT_CPPFLAGS) $(EXTRA_CPPFLAGS) $< -o $@

# --- #
# UIC #
# --- #

.ui.ui.hpp:
	$(UIC) $< -o $@

.ui.ui.hh:
	$(UIC) $< -o $@

.ui.ui.h:
	$(UIC) $< -o $@

# --- #
# RCC #
# --- #

.qrc.qrc.cpp:
	$(RCC) -name `echo "$<" | sed 's|^.*/\(.*\)\.qrc$$|\1|'` $< -o $@

.qrc.qrc.cc:
	$(RCC) -name `echo "$<" | sed 's|^.*/\(.*\)\.qrc$$|\1|'` $< -o $@

.qrc.qrc.cxx:
	$(RCC) -name `echo "$<" | sed 's|^.*/\(.*\)\.qrc$$|\1|'` $< -o $@

.qrc.qrc.C:
	$(RCC) -name `echo "$<" | sed 's|^.*/\(.*\)\.qrc$$|\1|'` $< -o $@

DISTCLEANFILES = $(BUILT_SOURCES)
