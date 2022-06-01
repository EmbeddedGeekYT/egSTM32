
#########
# DEBUG #
#########
DEBUG = 1


##########
# OUTPUT #
##########
BUILD_DIR = build
TARGET = sgSTM32


#########
# INPUT #
#########

# Sources
SOURCES = \
Src/startup_stm32f091xc.cpp \
Src/main.cpp

# Inlcudes
INCLUDES = \
Src \
CMSIS/Include \
CMSIS/Device/ST/STM32F0xx/Include

# Defines
DEFINES = \
STM32F091xC

ifeq ($(DEBUG), 1)
DEFINES += DEBUG=1
endif

# Includes (Should append SOURCES, INCLUDES, DEFINES)
include src/hal/hal.mk

# Linker input
LDSCRIPT = STM32F091RCTx_FLASH.ld
LIBS = -lc -lm -lnosys 


#########
# FLAGS #
#########

MCU_FLAGS = -mcpu=cortex-m0 -mthumb

# compile flags
FLAGS = ${MCU_FLAGS}
FLAGS += $(addprefix -D, $(sort $(DEFINES)))
FLAGS += $(addprefix -I, $(sort $(INCLUDES)))
FLAGS += -Wall -Wno-reorder -Wno-unknown-pragmas
FLAGS += -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fno-threadsafe-statics
FLAGS += -std=c++17
FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), 1)
FLAGS += -g -gdwarf-2
# Optimization -Og for debug
FLAGS += -Og
else
# Optimization -O2 for non debug
FLAGS += -O2
endif

# linker flags
LDFLAGS = $(MCU_FLAGS) -specs=nano.specs -specs=nosys.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

#########
# BUILD #
#########

# List objects and add to virtual path
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES)))

# Compiler
CC = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy
SZ = arm-none-eabi-size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

.PHONY: all clean flash

# Default action
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Compile action
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CC) -c $(FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

# Link action
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

# Crete hex-file action
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

# Create bin-file action
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

# Create build dir action
$(BUILD_DIR):
	mkdir $@		

# Clean action
clean:
	-rm -fR $(BUILD_DIR)



flash: all
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"
  

################
# DEPENDENCIES #
################
-include $(wildcard $(BUILD_DIR)/*.d)