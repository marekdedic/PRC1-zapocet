LD = $(CXX)

CFLAGS_ALL = -Wnon-virtual-dtor -Winit-self -Wredundant-decls -Wcast-align -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -std=c++11 -Wfatal-errors -Wextra -Wall
LIB_ALL =

CFLAGS_WIN = $(CFLAGS_ALL)
CFLAGS_LINUX = $(CFLAGS_ALL)
LIB_WIN = $(LIB_ALL) -lmingw32 -mwindows
LIB_LINUX = $(LIB_ALL)
EXEC_NAME_WIN = BigInt.exe
EXEC_NAME_LINUX = BigInt
RM_WIN = del /Q
RM_LINUX = rm -fr
MKDIR_WIN = for /F "tokens=* delims= " %%p in ("$(1)") do ( for %%b in (%%p) do ( if not exist %%b mkdir %%b ))
MKDIR_LINUX = mkdir -p $(1) || true

ifeq ($(OS),Windows_NT)
	CFLAGS = $(CFLAGS_WIN)
	LIB = $(LIB_WIN)
	EXEC_NAME = $(EXEC_NAME_WIN)
	RM = $(RM_WIN)
	MKDIR = $(MKDIR_WIN)
else
	CFLAGS = $(CFLAGS_LINUX)
	LIB = $(LIB_LINUX)
	EXEC_NAME = $(EXEC_NAME_LINUX)
	RM = $(RM_LINUX)
	MKDIR = $(MKDIR_LINUX)
endif

SRCDIR = src
OBJDIR = obj
BINDIR = bin
ERRFILE = /ErrorLog.txt
CORE = /core
VALG_OUT = /valgrind-output.txt

CFLAGS_DEBUG = $(CFLAGS) -g
LIB_DEBUG = $(LIB)
SRCDIR_DEBUG = $(SRCDIR)
OBJDIR_DEBUG = $(OBJDIR)/debug
OBJDIRS_DEBUG = 
BINDIR_DEBUG = $(BINDIR)/debug
OUT_DEBUG = $(BINDIR_DEBUG)/$(EXEC_NAME)

CFLAGS_RELEASE = $(CFLAGS) -s -O3
LIB_RELEASE = $(LIB)
SRCDIR_RELEASE = $(SRCDIR)
OBJDIR_RELEASE = $(OBJDIR)/release
OBJDIRS_RELEASE =
BINDIR_RELEASE = $(BINDIR)/release
OUT_RELEASE = $(BINDIR_RELEASE)/$(EXEC_NAME)

OBJ_DEBUG = $(OBJDIR_DEBUG)/Main.o $(OBJDIR_DEBUG)/BigInt.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/Main.o $(OBJDIR_RELEASE)/BigInt.o

ifeq ($(OS),Windows_NT)
	ERRFILE ::= $(strip $(subst /,\, $(ERRFILE)))
	CORE ::= $(strip $(subst /,\, $(CORE)))
	VALG_OUT ::= $(strip $(subst /,\, $(VALG_OUT)))
	OBJDIR_DEBUG ::= $(subst /,\, $(OBJDIR_DEBUG))
	OBJDIRS_DEBUG ::= $(subst /,\, $(OBJDIRS_DEBUG))
	BINDIR_DEBUG ::= $(subst /,\, $(BINDIR_DEBUG))
	OUT_DEBUG ::= $(subst /,\, $(OUT_DEBUG))
	OBJDIR_RELEASE ::= $(subst /,\, $(OBJDIR_RELEASE))
	OBJDIRS_RELEASE ::= $(subst /,\, $(OBJDIRS_RELEASE))
	BINDIR_RELEASE ::= $(subst /,\, $(BINDIR_RELEASE))
	OUT_RELEASE ::= $(subst /,\, $(OUT_RELEASE))
endif

all: debug release

clean: clean_debug clean_release

before_debug:
	$(call MKDIR, $(OBJDIR_DEBUG))
	$(call MKDIR, $(OBJDIRS_DEBUG))
	$(call MKDIR, $(BINDIR_DEBUG))

debug: before_debug out_debug

out_debug: $(OBJ_DEBUG)
	$(LD) -o $(OUT_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/%.o: $(SRCDIR_DEBUG)/%.cpp
	$(CXX) $(CFLAGS_DEBUG) -c $< -o $@

clean_debug:
	$(RM) $(OBJDIR_DEBUG)
	$(RM) $(OBJDIRS_DEBUG)
	$(RM) $(BINDIR_DEBUG)$(ERRFILE)
	$(RM) $(BINDIR_DEBUG)$(CORE)
	$(RM) $(BINDIR_DEBUG)$(VALG_OUT)
	$(RM) $(OUT_DEBUG)

before_release:
	$(call MKDIR, $(OBJDIR_RELEASE))
	$(call MKDIR, $(OBJDIRS_RELEASE))
	$(call MKDIR, $(BINDIR_RELEASE))

release: before_release out_release

out_release: before_release $(OBJ_RELEASE)
	$(LD) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/%.o: $(SRCDIR_RELEASE)/%.cpp
	$(CXX) $(CFLAGS_RELEASE) -c $< -o $@

clean_release:
	$(RM) $(OBJDIR_RELEASE)
	$(RM) $(OBJDIRS_RELEASE)
	$(RM) $(BINDIR_RELEASE)$(ERRFILE)
	$(RM) $(BINDIR_RELEASE)$(CORE)
	$(RM) $(OUT_RELEASE)

.PHONY: all clean before_debug debug out_debug clean_debug before_release release out_release clean_release
