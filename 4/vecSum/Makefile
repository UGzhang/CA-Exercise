.PHONY: all clean vecSum

# HINT:
# To run 'make' successfully on a CIP machine, two changes need to be applied to this file.
#   - replace the value of the 'CC' compiler variable 'gcc' (do not forget to change it back to 'icx' on the cluster)
#   - comment the '-xHost' compiler (do not forget to change it back when using 'icx')


ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

INC_PATH  := $(SRC_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -iquote ,$(INC_DIRS))

CC      := icx
CFLAGS  := -Wall -pedantic -Werror -std=c99 -O1
UNROLLTYPE ?= 4
CFLAGS += -DUNROLLTYPE=$(UNROLLTYPE)
LDFLAGS :=

all: vecSum # program is named vecSum

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

vecSum: $(BIN_PATH)/vecSum

$(BIN_PATH)/vecSum: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

