# =========================
# Project configuration
# =========================
PROJECT       := stm32_drivers
BUILD_DIR     := build
LINKER_SCRIPT := STM32F407VGTX_FLASH.ld   # change to *_RAM.ld if needed

# Source roots
SRC_DIRS := \
  Src \
  drivers/Src \
  Startup

INC_DIRS := \
  Inc \
  drivers/Inc

# =========================
# Toolchain configuration
# =========================
CC      := arm-none-eabi-gcc
AS      := arm-none-eabi-gcc
LD      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size

# =========================
# MCU / CPU flags
# =========================
MCU := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Common preprocessor defines
DEFS := \
  -DSTM32F407xx
  # -DUSE_HAL_DRIVER   # uncomment ONLY if using STM32 HAL

# Warnings & language level
WARN := -Wall -Wextra -Werror=implicit-function-declaration -Wno-unused-parameter
CSTD := -std=c11

# Optimization & debug
OPT := -O2
DBG := -g3

# =========================
# Compilation & Link Flags
# =========================
CFLAGS := $(MCU) $(OPT) $(DBG) $(WARN) $(CSTD) $(DEFS) \
          $(addprefix -I,$(INC_DIRS)) -ffunction-sections -fdata-sections

ASFLAGS := $(MCU) $(DBG) -x assembler-with-cpp $(addprefix -I,$(INC_DIRS))

LDFLAGS := $(MCU) -T$(LINKER_SCRIPT) -Wl,--gc-sections -Wl,-Map,$(BUILD_DIR)/$(PROJECT).map


# =========================
# Select the main to build*
# =========================

 C_SOURCES := \
   Src/3_IT_BTN_LED.c \
   Src/syscalls.c \
   Src/sysmem.c \
   drivers/Src/stm32f407_GPIO_Driver.c \
   drivers/Src/stm32f407_SPI_Driver.c

S_SOURCES := Startup/startup_stm32f407vgtx.s


# =========================
# Object generation
# =========================
OBJECTS := \
  $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES)) \
  $(patsubst %.s,$(BUILD_DIR)/%.o,$(S_SOURCES))

DEPS := $(OBJECTS:.o=.d)


# =========================
# Top-level targets
# =========================
.PHONY: all clean size dir

all: dir $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin $(BUILD_DIR)/$(PROJECT).hex size
	@echo " Build complete -> $(BUILD_DIR)/$(PROJECT).{elf,bin,hex}"

dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))

# =========================
# Linking
# =========================
$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

# =========================
# Binary / Hex generation
# =========================
$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

# =========================
# Size report
# =========================
size: $(BUILD_DIR)/$(PROJECT).elf
	$(SIZE) --format=berkeley $<

# =========================
# Compilation rules
# =========================
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -MMD -MP -c $< -o $@

# =========================
# Cleanup
# =========================
clean:
	@echo " Cleaning $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

# =========================
# Dependency include
# =========================
-include $(DEPS)
