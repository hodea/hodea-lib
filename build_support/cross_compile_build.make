# Copyright (c) 2017, Franz Hollerer. All rights reserved.
# This code is licensed under the MIT License (MIT).
# See LICENSE file for full details.

# This makefile is executed within the build directory to build the
# given target for a "posix_hosted" system.

AS_OBJ_FILES := $(addsuffix .o, $(AS_SOURCE_FILES))
C_OBJ_FILES := $(addsuffix .o, $(C_SOURCE_FILES))
CXX_OBJ_FILES := $(addsuffix .o, $(CXX_SOURCE_FILES))

-include $(AS_OBJ_FILES:.o=.d)
-include $(C_OBJ_FILES:.o=.d)
-include $(CXX_OBJ_FILES:.o=.d)

$(TARGET).elf: $(AS_OBJ_FILES) $(C_OBJ_FILES) $(CXX_OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -Obinary $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -Oihex $< $@

$(AS_OBJ_FILES):
	$(CC) $(CFLAGS) -c $(SOURCE_ROOT_DIR)/$(basename $@) -o $@

$(C_OBJ_FILES):
	$(CC) $(CFLAGS) -c $(SOURCE_ROOT_DIR)/$(basename $@) -o $@

$(CXX_OBJ_FILES):
	$(CXX) $(CXXFLAGS) -c $(SOURCE_ROOT_DIR)/$(basename $@) -o $@

