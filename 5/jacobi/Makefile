.PHONY: all clean jacobi

# HINT:
# To run 'make' successfully on a CIP machine, two changes need to be applied to this file.
#   - replace the value of the 'CC' compiler variable 'gcc' (do not forget to change it back to 'icx' on the cluster)
#   - comment the '-xHost' compiler (do not forget to change it back when using 'icx')


ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

LIKWID_INC ?= -I/usr/local/include
LIKWID_DEFINES ?= -DLIKWID_PERFMON
LIKWID_LIB ?= -L/usr/local/lib

INC_PATH  := $(ROOT_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -iquote ,$(INC_DIRS)) ${LIKWID_INC} -DLIKWID_PERFMON
CC      := icx

CFLAGS  := -Wall -pedantic -std=c99 -O1
ifeq ($(strip $(WISE)), COLUMN)
    CFLAGS += -DCOLUMN_WISE
else
	CFLAGS += -DROW_WISE
endif

LDFLAGS := ${LIKWID_LIB} -llikwid
all: jacobi # program is named jacobi

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

jacobi: $(BIN_PATH)/jacobi

$(BIN_PATH)/jacobi: $(BUILD_PATH)/main.o $(BUILD_PATH)/jacobi.o $(BUILD_PATH)/get_time.o $(BUILD_PATH)/draw.o
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@ 

