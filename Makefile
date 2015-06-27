#DIRECTORY LAYOUT
SRCDIR=emu
BINDIR=bin
LIBDIR=lib
OBJDIR=obj
TESTDIR=test

TESTS=testboard testproc

#OUTPUTS AND THEIR PREREQUISITES
BINS=main
LIBS=libemu.a
HDRS=board processor
OUTPUTS=$(BINS:%=$(BINDIR)/%) $(TESTS:%=$(TESTDIR)/%) $(BINS) $(LIBS:%=$(LIBDIR)/%)

OMAIN=main board processor
MAIN_OBJECTS=$(OMAIN:%=$(OBJDIR)/%.o)

OBTEST=board boardtest
BTEST_OBJECTS=$(OBTEST:%=$(OBJDIR)/%.o)

OPTEST=board processor proctest
PTEST_OBJECTS=$(OPTEST:%=$(OBJDIR)/%.o)

OLIB=board processor
LIB_OBJECTS=$(OLIB:%=$(OBJDIR)/%.o)

#LINKING AND INCLUDES
LOCAL_INCLUDES=-I. -I$(SRCDIR)
EXTERN_INCLUDES=
LIB_SEARCH=
LINK_LIBS=
INCLUDES=$(LOCAL_INCLUDES) $(EXTERN_INCLUDES)

#CONFIGURATION VARIABLES
CC=gcc
STANDARDS=-Wall
BUILD_TYPE=-g

BUILD_PARAM=$(STANDARDS) $(BUILD_TYPE)
CFLAGS=$(BUILD_PARAM) $(INCLUDES)
LDFLAGS=$(LIB_SEARCH) $(LINK_LIBS)
BFLAGS=$(BUILD_PARAM) $(INCLUDES) $(LIB_SEARCH) $(LINK_LIBS)

#MAIN TARGET
all: $(OUTPUTS) $(HDRS:%=$(LIBDIR)/%.h)

#DIRECTORY STRUCTURE
$(BINDIR):
	@printf '\e[33mCREATING DIRECTORY \e[96m$@\e[m\n'
	mkdir $(BINDIR)
$(OBJDIR):
	@printf '\e[33mCREATING DIRECTORY \e[96m$@\e[m\n'
	mkdir $(OBJDIR)
$(SRCDIR):
	@printf '\e[33mCREATING DIRECTORY \e[96m$@\e[m\n'
	mkdir $(SRCDIR)
$(LIBDIR):
	@printf '\e[33mCREATING DIRECTORY \e[96m$@\e[m\n'
	mkdir $(LIBDIR)
$(TESTDIR):
	@printf '\e[33mCREATING DIRECTORY \e[96m$@\e[m\n'
	mkdir $(TESTDIR)

#HEADER COPYING
$(LIBDIR)/%.h: $(SRCDIR)/%.h
	@printf '\e[33mCOPYING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m\n'
	cp $^ $@

#SYMLINKS FOR OUTPUTS
%: $(BINDIR)/%
	@printf '\e[33mCREATING SYMLINK \e[96m$@\e[m \e[33mTO \e[94m$^\e[m\n'
	ln -s $^ $@

#BINARY TARGETS
$(BINDIR)/main: $(MAIN_OBJECTS) | $(BINDIR)
	@printf '\033[33mLINKING \033[96m$@\033[m \033[33mFROM \033[94m$^\033[m\n'
	$(CC) $(BUILD_PARAM) $^ $(LDFLAGS) -o $@
	@printf "\033[m"

$(TESTDIR)/testboard: $(BTEST_OBJECTS) | $(TESTDIR)
	@printf '\033[33mLINKING \033[96m$@\033[m \033[33mFROM \033[94m$^\033[m\n'
	$(CC) $(BUILD_PARAM) $^ $(LDFLAGS) -o $@
	@printf "\033[m"

$(TESTDIR)/testproc: $(PTEST_OBJECTS) | $(TESTDIR)
	@printf '\033[33mLINKING \033[96m$@\033[m \033[33mFROM \033[94m$^\033[m\n'
	$(CC) $(BUILD_PARAM) $^ $(LDFLAGS) -o $@
	@printf "\033[m"

$(LIBDIR)/libemu.a: $(LIB_OBJECTS) | $(LIBDIR)
	@printf '\033[33mARCHIVING \033[96m$@\033[m \033[33mFROM \033[94m$^\033[m\n'
	ar rcs $@ $^
	@printf "\033[m"

#GENERIC OBJECT TARGET
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(SRCDIR)
	@printf '\033[33mCOMPILING \033[96m$@\033[m \033[33mFROM \033[94m$^\033[m\n'
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[m"

#CLEANING
clean:
	@printf '\033[33mCLEANING...\033[m\n'
	rm -r -f -v *~ $(OBJDIR)

clobber: clean
	@printf '\033[33mCLOBBERING...\033[m\n'
	rm -r -f -v $(OUTPUTS) $(BINDIR) $(TESTDIR) $(LIBDIR)

