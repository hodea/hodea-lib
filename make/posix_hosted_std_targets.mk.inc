# Copyright (c) 2017, Franz Hollerer. All rights reserved.
# This code is licensed under the MIT License (MIT).
# See LICENSE file for full details.

# This makefile is included from an project specific makefile and
# provides the standard targets "all, clean, release, debug" for
# a "posix_hosted" system.

# ------------------------------------------------- deduced settings ---

export SOURCE_ROOT_DIR := $(CURDIR)

ifndef DEBUG
    DEBUG = 0
endif

ifneq ($(DEBUG), 0)
    CFLAGS_OPT := -O0
    BUILD_DIR := $(BUILD_ROOT_DIR)/debug
else
    CFLAGS_OPT := -O3
    BUILD_DIR := $(BUILD_ROOT_DIR)/release
endif

export CFLAGS := -g -MD $(CFLAGS_OPT) \
    $(patsubst %,-I $(SOURCE_ROOT_DIR)/%,$(INCLUDE_DIRS))

export CXXFLAGS := $(CFLAGS)

# ---------------------------------------------------------- targets ---

.PHONY: all clean release debug

all release: $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) \
        -f $(SOURCE_ROOT_DIR)/$(HODEA_ROOT_DIR)/make/posix_hosted_build.mk \
        $(TARGET)

clean:
	rm -rf $(BUILD_ROOT_DIR)

debug:
	$(MAKE) DEBUG=1 all

$(BUILD_DIR):
	for d in $(dir $(C_SOURCE_FILES) $(CXX_SOURCE_FILES)) ; do \
		mkdir -p $(BUILD_DIR)/$$d;  \
	done

