
PATH := $(PATH):$(TOOL_PATH)

SRC = $(wildcard src/*.c) $(wildcard src/*.s)

OBJ := $(SRC:.c=.o)
OBJ := $(OBJ:.s=.o)

INCLUDES = -Iinclude

ASFLAGS = -mcpu=arm1136jf-s
CFLAGS = $(WRLINUX_CFLAGS) -Os $(INCLUDES)
LDFLAGS = -static --script=link.gnu -L$(LAYER)/sysroot/uclibc/usr/lib

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

all : x-loader
	@echo "make: built targets of `pwd`"

clean :
	@echo "make: removing targets and objects of `pwd`"
	@rm src/*.o

x-loader.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ -lc

x-loader: x-loader.elf
	@echo "Converting $@"
	$(OBJCOPY) -O binary $< $@
