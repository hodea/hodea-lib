# Copyright (c) 2017, Franz Hollerer. All rights reserved.
# This code is licensed under the MIT License (MIT).
# See LICENSE file for full details.

# This makefile is included from an project specific makefile and
# provides the standard targets "all, clean, release, debug" for
# a "posix_hosted" system.

# ------------------------------------------------- deduced settings ---

export SOURCE_ROOT_DIR := $(CURDIR)

CORE_FLAGS := -g -Wall -MD $(COVERAGE_FLAGS)

ifndef DEBUG
    DEBUG = 0
endif

ifneq ($(DEBUG), 0)
    CORE_FLAGS += -O0
    BUILD_DIR := $(BUILD_ROOT_DIR)/debug
else
    CORE_FLAGS += -O3
    BUILD_DIR := $(BUILD_ROOT_DIR)/release
endif

INCLUDE_FLAGS := $(patsubst %,-I $(SOURCE_ROOT_DIR)/%,$(INCLUDE_DIRS))

export CFLAGS := $(CORE_FLAGS) -std=c11 $(INCLUDE_FLAGS)

export CXXFLAGS := $(CORE_FLAGS) -std=c++11 $(INCLUDE_FLAGS)

export LDFLAGS := $(COVERAGE_FLAGS)

BUILD_SUPPORT_DIR := $(SOURCE_ROOT_DIR)/$(HODEA_ROOT_DIR)/build_support

# ---------------------------------------------------------- targets ---

.PHONY: all clean release debug

all release: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) \
	-f $(BUILD_SUPPORT_DIR)/posix_hosted_build.make \
        $(TARGET)

clean:
	rm -rf $(BUILD_ROOT_DIR)

debug:
	$(MAKE) DEBUG=1 all

$(BUILD_DIR):
	for d in $(dir $(C_SOURCE_FILES) $(CXX_SOURCE_FILES)) ; do \
		mkdir -p $(BUILD_DIR)/$$d;  \
	done

