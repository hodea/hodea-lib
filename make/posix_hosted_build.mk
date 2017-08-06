# Copyright (c) 2017, Franz Hollerer. All rights reserved.
# This code is licensed under the MIT License (MIT).
# See LICENSE file for full details.

# This makefile is executed within the build directory to build the
# given target for a "posix_hosted" system.

C_OBJ_FILES := $(addsuffix .o, $(C_SOURCE_FILES))
CXX_OBJ_FILES := $(addsuffix .o, $(CXX_SOURCE_FILES))

-include $(C_OBJ_FILES:.o=.d)
-include $(CXX_OBJ_FILES:.o=.d)

$(TARGET): $(C_OBJ_FILES) $(CXX_OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

$(C_OBJ_FILES):
	$(CC) $(CFLAGS) -c $(SOURCE_ROOT_DIR)/$(basename $@) -o $@

$(CXX_OBJ_FILES):
	$(CXX) $(CXXFLAGS) -c $(SOURCE_ROOT_DIR)/$(basename $@) -o $@

