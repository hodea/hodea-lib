# Copyright (c) 2017, Franz Hollerer. All rights reserved.
# This code is licensed under the MIT License (MIT).
# See LICENSE file for full details.

# This makefile is included from an project specific makefile and
# provides the standard targets "all, clean, release, debug" for
# a "posix_hosted" system.

# ------------------------------------------------- deduced settings ---

export SOURCE_ROOT_DIR := $(CURDIR)

CORE_FLAGS += -g -Wall -MD -ffreestanding $(USER_FLAGS)

DEBUG ?= 0

ifneq ($(DEBUG), 0)
    CORE_FLAGS += -O0
    BUILD_DIR := $(BUILD_ROOT_DIR)/debug
else
    CORE_FLAGS += -O3
    BUILD_DIR := $(BUILD_ROOT_DIR)/release
endif

INCLUDE_FLAGS := $(patsubst %,-I $(SOURCE_ROOT_DIR)/%,$(INCLUDE_DIRS))

export ASFLAGS := $(CORE_FLAGS)

export CFLAGS := $(CORE_FLAGS) -std=c11 $(INCLUDE_FLAGS)

export CXXFLAGS := $(CORE_FLAGS) -std=c++11 $(INCLUDE_FLAGS)

export LDFLAGS := \
    $(CORE_FLAGS) \
    --specs=nano.specs --specs=nosys.specs \
    -T$(SOURCE_ROOT_DIR)/$(LINKER_SCRIPT) \
    -Xlinker -Map=$(TARGET).map


BUILD_SUPPORT_DIR := $(SOURCE_ROOT_DIR)/$(HODEA_ROOT_DIR)/build_support

# ---------------------------------------------------------- targets ---

.PHONY: all clean release debug

all release: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) \
	-f $(BUILD_SUPPORT_DIR)/cross_compile_build.make \
        $(TARGET).bin $(TARGET).hex

clean:
	rm -rf $(BUILD_ROOT_DIR)

debug:
	$(MAKE) DEBUG=1 all

$(BUILD_DIR):
	for d in $(dir $(AS_SOURCE_FILES) $(C_SOURCE_FILES) \
            $(CXX_SOURCE_FILES)) ; do \
		mkdir -p $(BUILD_DIR)/$$d;  \
	done

