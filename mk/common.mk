SHELL := /bin/bash

# Detect repo root as parent of this mk directory
REPO_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

# Problem directory (relative to repo root or absolute)
PROB ?= TEMPLATE

# Normalize PROB to absolute path
ifeq ($(patsubst /%,/,$(PROB)),/)
PROB_ABS := $(PROB)
else
PROB_ABS := $(abspath $(REPO_ROOT)/$(PROB))
endif

BIN := $(PROB_ABS)/build/main
SRC := $(PROB_ABS)/main.cpp

CXX ?= g++
CXXFLAGS ?= -O2 -pipe -std=c++20 -Wall -Wextra -Wshadow -Wformat=2 -Wconversion -Wno-sign-conversion -fno-exceptions -fno-rtti
DEBUG ?= 0
SAN ?= 0
# Allow std IO headers (cstdio/iostream), still avoid STL containers in code style
ifeq ($(DEBUG),1)
  CXXFLAGS += -O0 -g -DDEBUG=1
else
  CXXFLAGS += -DNDEBUG
endif
ifeq ($(SAN),1)
  CXXFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
  LDFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
endif
LDFLAGS ?=
INCLUDES := -I$(REPO_ROOT)/lib

.PHONY: build run judge clean help

build: $(BIN)

$(BIN): $(SRC) $(REPO_ROOT)/mk/common.mk $(wildcard $(REPO_ROOT)/lib/*.hpp)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(SRC) $(LDFLAGS)

# Run single case: make run PROB=... [CASE=path/to/input]
CASE ?= $(PROB_ABS)/cases/1.in
run: $(BIN)
	@echo [RUN] $(PROB_ABS) <= $(CASE)
	@"$(BIN)" < "$(CASE)" | cat

# Run all cases in cases/ and compare with expected outputs
judge: $(BIN)
	@bash "$(REPO_ROOT)/scripts/run_cases.sh" "$(PROB_ABS)"

clean:
	@rm -rf "$(PROB_ABS)/build"

help:
	@echo "Targets:"
	@echo "  build: compile problem (PROB=path)"
	@echo "  run:   run one case (CASE=...)"
	@echo "  judge: run all cases via scripts/run_cases.sh"
	@echo "Usage:"
	@echo "  make build PROB=TEMPLATE"
	@echo "  make run PROB=TEMPLATE CASE=TEMPLATE/cases/1.in"
	@echo "  make judge PROB=TEMPLATE"


