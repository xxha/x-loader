# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

JOBS?=1
TARGET_JOBS?=$(JOBS)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = ARMV6LNcrossdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := /home/xxha/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/x-loader



#Global Build Macros
PROJECT_TYPE = APP
DEFINES = 
GENERATE_MAP_FILE = 0
EXPAND_DBG = 0


#BuildSpec specific Build Macros
CPU = ARMV6
LIBPATH = 
LIBS = -Ws
LINKER_FILE = $(PRJ_ROOT_DIR)/default.dld
TGT_FLAG = -tARMV6LN:cross
TOOL_PATH = 

IDE_INCLUDES = -I$(PRJ_ROOT_DIR)/include 

IDE_LIBRARIES = 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_C-Linker = 
DEBUGFLAGS_C++-Linker = 
DEBUGFLAGS_Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -Xasm-debug-on
else
DEBUGFLAGS_C-Compiler = -Xsize-opt
DEBUGFLAGS_C++-Compiler = -Xsize-opt
DEBUGFLAGS_C-Linker = 
DEBUGFLAGS_C++-Linker = 
DEBUGFLAGS_Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = 
endif


#Project Targets
PROJECT_TARGETS = x-loader/$(MODE_DIR)/x-loader.elf


#Rules

# x-loader
ifeq ($(DEBUG_MODE),1)
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C-Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C++-Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -Xasm-debug-on
else
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -Xsize-opt
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -Xsize-opt
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C-Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_C++-Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Linker = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
x-loader/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = 
endif
x-loader/$(MODE_DIR)/% : IDE_INCLUDES = -I$(PRJ_ROOT_DIR)/include 
x-loader/$(MODE_DIR)/% : IDE_LIBRARIES = 
x-loader/$(MODE_DIR)/% : IDE_DEFINES = 
x-loader/$(MODE_DIR)/% : PROJECT_TYPE = APP
x-loader/$(MODE_DIR)/% : DEFINES = 
x-loader/$(MODE_DIR)/% : GENERATE_MAP_FILE = 0
x-loader/$(MODE_DIR)/% : EXPAND_DBG = 0
x-loader/$(MODE_DIR)/% : CPU = ARMV6
x-loader/$(MODE_DIR)/% : LIBPATH = 
x-loader/$(MODE_DIR)/% : LIBS = -Ws
x-loader/$(MODE_DIR)/% : LINKER_FILE = $(PRJ_ROOT_DIR)/default.dld
x-loader/$(MODE_DIR)/% : TGT_FLAG = -tARMV6LN:cross
x-loader/$(MODE_DIR)/% : TOOL_PATH = 
x-loader/$(MODE_DIR)/% : OBJ_DIR := x-loader/$(MODE_DIR)

x-loader/$(MODE_DIR)/Objects/x-loader/src/__crc32.o : $(PRJ_ROOT_DIR)/src/__crc32.s $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)das $(DEBUGFLAGS_Assembler)  $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/crc32.o : $(PRJ_ROOT_DIR)/src/crc32.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/crt0.o : $(PRJ_ROOT_DIR)/src/crt0.s $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)das $(DEBUGFLAGS_Assembler)  $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/dma.o : $(PRJ_ROOT_DIR)/src/dma.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/env.o : $(PRJ_ROOT_DIR)/src/env.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/gpio.o : $(PRJ_ROOT_DIR)/src/gpio.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/harman.o : $(PRJ_ROOT_DIR)/src/harman.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/main.o : $(PRJ_ROOT_DIR)/src/main.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/nand.o : $(PRJ_ROOT_DIR)/src/nand.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/support.o : $(PRJ_ROOT_DIR)/src/support.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/uart.o : $(PRJ_ROOT_DIR)/src/uart.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


x-loader/$(MODE_DIR)/Objects/x-loader/src/wd.o : $(PRJ_ROOT_DIR)/src/wd.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) -Xmake-dependency=0xd $(TGT_FLAG) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DTOOL_FAMILY=diab -DTOOL=diab -DCPU=$(CPU) $(DEFINES) -o "$@" -c "$<"


OBJECTS_x-loader = x-loader/$(MODE_DIR)/Objects/x-loader/src/__crc32.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/crc32.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/crt0.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/dma.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/env.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/gpio.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/harman.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/main.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/nand.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/support.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/uart.o \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/wd.o

ifeq ($(TARGET_JOBS),1)
x-loader/$(MODE_DIR)/x-loader.elf : $(OBJECTS_x-loader)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";if [ "$(GENERATE_MAP_FILE)" = "1" ]; then MAP_OPTION=-Wl,-m6;MAP_NAME="-Wl,-@O=$@.map";fi;if [ ".$(LINKER_FILE)" != "." ]; then LINK_FILE_OPTION="-Wm$(LINKER_FILE)";fi;echo "$(OBJECTS_x-loader)" > objects.lst; cat objects.lst; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Linker)  $(TGT_FLAG) -o "$@" @objects.lst $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) $$LINK_FILE_OPTION $$MAP_OPTION $$MAP_NAME && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi;rm objects.lst

else
x-loader/$(MODE_DIR)/x-loader.elf : x-loader/$(MODE_DIR)/x-loader.elf_jobs

endif
x-loader/$(MODE_DIR)/x-loader_compile_file : $(FILE) ;

_clean :: x-loader/$(MODE_DIR)/x-loader_clean

x-loader/$(MODE_DIR)/x-loader_clean : 
	$(TRACE_FLAG)if [ -d "x-loader" ]; then cd "x-loader"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo update makefile template
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := x-loader/$(MODE_DIR)/Objects/x-loader/src/__crc32.d x-loader/$(MODE_DIR)/Objects/x-loader/src/crc32.d x-loader/$(MODE_DIR)/Objects/x-loader/src/crt0.d \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/dma.d x-loader/$(MODE_DIR)/Objects/x-loader/src/env.d x-loader/$(MODE_DIR)/Objects/x-loader/src/gpio.d \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/harman.d x-loader/$(MODE_DIR)/Objects/x-loader/src/main.d x-loader/$(MODE_DIR)/Objects/x-loader/src/nand.d \
	 x-loader/$(MODE_DIR)/Objects/x-loader/src/support.d x-loader/$(MODE_DIR)/Objects/x-loader/src/uart.d x-loader/$(MODE_DIR)/Objects/x-loader/src/wd.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

TARGET_JOBS_RULE=$(MAKE) -f $(MAKEFILE) --jobs $(TARGET_JOBS) $(MFLAGS) $* TARGET_JOBS=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS) TARGET_JOBS=1 &&\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
