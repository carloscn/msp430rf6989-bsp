DEVICE:=MSP430FR6989

PATH_SRC     = src
HAL_SRC      = $(PATH_SRC)/HAL
PATH_DRIVER  = driverlib/MSP430F5xx_6xx
PATH_BUILD   = build/target
PATH_OBJS    = build/target/objects
BUILD_PATHS  = $(PATH_BUILD) $(PATH_OBJS)

CC       = msp430-elf-gcc
CFLAGS   = -I ./msp430-gcc-support-files/include
CFLAGS  += -I ./driverlib/MSP430F5xx_6xx
CFLAGS  += -I $(HAL_SRC)
CFLAGS  += -O2 -D__$(DEVICE)__ -mmcu=$(DEVICE) -g -ffunction-sections -fdata-sections -DDEPRECATED
CFLAGS  += -c

LD       = msp430-elf-gcc
LDFLAGS  = -L ./msp430-gcc-support-files/include
LDFLAGS += -L ./driverlib/MSP430FR5xx_6xx
LDFLAGS += -mmcu=$(DEVICE) -g -Wl,--gc-sections
LDFLAGS += -T msp430fr6989.ld

# Add all .c files from PATH_SRC and PATH_DRIVER directories
SRCS = $(wildcard $(PATH_SRC)/*.c) $(wildcard $(PATH_DRIVER)/*.c) $(wildcard $(HAL_SRC)/*.c)

MKDIR	   = mkdir -p

all: target convert

target: $(BUILD_PATHS) $(PATH_BUILD)/target.out

# Define OBJS with full path for object files
OBJS = $(patsubst %.c, $(PATH_OBJS)/%.o, $(notdir $(SRCS)))

$(PATH_BUILD):
	$(MKDIR) $(PATH_BUILD)

$(PATH_OBJS):
	$(MKDIR) $(PATH_OBJS)

$(PATH_BUILD)/target.out: $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

# Rule to compile source files in PATH_SRC
$(PATH_OBJS)/%.o: $(PATH_SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to compile source files in PATH_DRIVER
$(PATH_OBJS)/%.o: $(PATH_DRIVER)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to compile source files in HAL_SRC
$(PATH_OBJS)/%.o: $(HAL_SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

convert:
	msp430-elf-objcopy -O ihex $(PATH_BUILD)/target.out $(PATH_BUILD)/target.hex
	@cp -v $(PATH_BUILD)/target.hex target.hex

upload:
	LD_LIBRARY_PATH="/opt/ti/MSPFlasher_1.3.20:$LD_LIBRARY_PATH" \
    PATH="/opt/ti/MSPFlasher_1.3.20:${GCC_PATH}:$PATH" MSP430Flasher -e ERASE_ALL -w target.hex -v -z [VCC]

debug:
	mspdebug tilib

gdb:
	msp430-elf-gdb target.out

dis:
	msp430-elf-objdump -D target.out | less

clean:
	rm -rf $(PATH_OBJS)/*.o
	rm -rf $(PATH_BUILD)/*.out
	rm -rf $(PATH_BUILD)/*.hex
	rm -rf *.hex
	rm -rfd Log
