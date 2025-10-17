# =========================
# Project configuration
# =========================
PROJECT       := stm32_drivers
BUILD_DIR     := build
LINKER_SCRIPT := STM32F407VGTX_FLASH.ld   # change to *_RAM.ld if you link to RAM

# Source roots
SRC_DIRS := \
  Src \
  drivers/Src \
  Startup

INC_DIRS := \
  Inc \
  drivers/Inc

# Toolchain
CC      := arm-none-eabi-gcc
AS      := arm-none-eabi-gcc
LD      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size

# MCU/CPU flags (STM32F407VG: Cortex-M4F with single-precision FPU)
MCU     := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Common preprocessor defines
DEFS := \
  -DSTM32F407xx
  # -DUSE_HAL_DRIVER   # uncomment ONLY if using STM32 HAL

# Warnings & language level
WARN := -Wall -Wextra -Werror=implicit-function-declaration -Wno-unused-parameter
CSTD := -std=c11

# Optimization & debug
OPT  := -O2
DBG  := -g3

# C/ASM/Link flags
CFLAGS   := $(MCU) $(OPT) $(DBG) $(WARN) $(CSTD) $(DEFS) \
            $(addprefix -I,$(INC_DIRS)) -ffunction-sections -fdata-sections

ASFLAGS  := $(MCU) $(DBG) -x assembler-with-cpp $(addprefix -I,$(INC_DIRS))

LDFLAGS  := $(MCU) -T$(LINKER_SCRIPT) -Wl,--gc-sections -Wl,-Map,$(BUILD_DIR)/$(PROJECT).map

# =========================
# Source/objects discovery
# =========================
# Find all .c and .s sources under SRC_DIRS
C_SOURCES := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
S_SOURCES := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.s) $(wildcard $(d)/*.S))

# Turn sources into objects under build/
OBJECTS := \
  $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES)) \
  $(patsubst %.s,$(BUILD_DIR)/%.o,$(S_SOURCES)) \
  $(patsubst %.S,$(BUILD_DIR)/%.o,$(S_SOURCES))

# Dependency files
DEPS := $(OBJECTS:.o=.d)

# =========================
# Top-level targets
# =========================
.PHONY: all clean size dir

all: dir $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin $(BUILD_DIR)/$(PROJECT).hex size
	@echo "Build complete -> $(BUILD_DIR)/$(PROJECT).{elf,bin,hex}"

dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))

# Link
$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

# Binary/Hex from ELF
$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

# Size report
size: $(BUILD_DIR)/$(PROJECT).elf
	$(SIZE) --format=berkeley $<

# Compile C -> obj (with depfile)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Assemble -> obj (with depfile)
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -MMD -MP -c $< -o $@

# Clean
clean:
	@echo "Cleaning $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

# Include generated dependency files if they exist
-include $(DEPS)
