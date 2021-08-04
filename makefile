# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
INC_PATH := inc

# tool macros
CC := gcc
CCFLAGS := -Wall -Wextra -O3 -fPIC -I $(INC_PATH)
CCOBJFLAGS := $(CCFLAGS) -c 

# compile macros
TARGET_NAME := main
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .dll,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ)
CLEAN_LIST := $(TARGET) \
			  $(DISTCLEAN_LIST)
CLEAN := @rm -f $(CLEAN_LIST)
DISTCLEAN := @rm -f $(DISTCLEAN_LIST)
ifeq ($(OS),Windows_NT)
	SHELL := powershell.exe
	.SHELLFLAGS := -NoProfile -Command
	CLEAN := "$(CLEAN_LIST)" -split " " | ForEach-Object {Remove-Item $$_}
	DISTCLEAN := "$(DISTCLEAN_LIST)" -split " " | ForEach-Object {Remove-Item $$_}
endif

# default rule
default: all

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -shared -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAGS) -o $@ $<

# phony rules
# .PHONY: makedir
# makedir:
# 	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST);
	$(CLEAN)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST);
	$(DISTCLEAN)
