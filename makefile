# MIT License
#
# Copyright (c) 2024 Uriel García Rivas
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# https://github.com/zoningorg/zondata/blob/main/LICENSE

# Compilation. Activate as many warnings as possible for maximum safety.
# TODO: Include -Wredundant-decls -Wpadded -Wc90-c99-compat
#               -Wtraditional-conversion -fanalyzer -Wlong-long
# NOTE: Exclude -Wc++-compat -Wabi-tag
CC = gcc

# General Warnings.
CWARN_GENERAL = -Wall -Wextra -Werror -Wpedantic -Wsystem-headers # -fanalyzer

# Conversion and Format Warnings.
CWARN_CONVERSION_FORMAT = -Wconversion -Wformat=2 -Wformat-security \
	-Wformat-signedness -Wformat-zero-length -Woverlength-strings \
	-Wformat-overflow -Wformat-truncation -Wformat-nonliteral -Wformat-y2k

# Variable and Assignment Warnings.
CWARN_VARIABLES = -Wshadow -Wwrite-strings -Wlogical-op -Wfloat-equal \
	-Wpointer-arith -Wchar-subscripts -Wzero-length-bounds -Warray-bounds \
	-Wduplicated-cond -Winit-self -Wduplicated-branches \
	-Wlogical-not-parentheses

# Deprecated and Legacy Warnings.
CWARN_DEPRECATED = -Wdeprecated-declarations -Wold-style-definition \
	-Wmissing-format-attribute

# Preprocessor Warnings.
CWARN_PREPROCESSOR = -Wundef -Wl,-z,now -Wl,-z,defs

# Unused Warnings.
CWARN_UNUSED = -Wunused -Wunused-parameter -Wunused-function -Wunused-label \
	-Wunused-value -Wuninitialized -Wunused-variable -Wunused-macros \
	-Wunused-local-typedefs -Wunused-const-variable -Wunused-result \
	-Wunused-but-set-variable -Wunused-but-set-parameter

# Declaration Warnings.
CWARN_DECLARATIONS = -Wstrict-prototypes -Wmissing-prototypes \
	-Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs \
	-Wnested-externs # -Wredundant-decls # -Wtraditional-conversion

# Switch Warnings.
CWARN_SWITCH = -Wswitch-default -Wswitch-enum

# Pointer and Cast Warnings.
CWARN_POINTERS = -Wincompatible-pointer-types -Wcast-qual -Wpointer-sign \
	-Wrestrict -Wnull-dereference -Wuseless-cast -Wnonnull -Walloca \
	-Wcast-align=strict -Wbad-function-cast -Wcast-function-type \
	-Wstack-protector -Waddress -Wstringop-overread -Wnonnull-compare \
	-Wpointer-compare

# Optimization Warnings.
CWARN_OPTIMIZATION = -Wdisabled-optimization -Wdouble-promotion \
	-Wunsafe-loop-optimizations -Wunsuffixed-float-constants \
	-Wfloat-conversion -Winline -Waddress-of-packed-member -Wclobbered \
	-Wdiscarded-qualifiers

# Implicit Warnings.
CWARN_IMPLICIT = -Wimplicit-int -Wimplicit-function-declaration \
	-Wimplicit-fallthrough

# Overflow and Size Warnings.
CWARN_OVERFLOW_SIZE = -Wstrict-overflow=5 -Wlarger-than=65536 -Wpacked \
	-Wpacked-not-aligned -Wshift-overflow # -Wpadded

# Compatibility Warnings.
CWARN_COMPATIBILITY = -Wsign-compare # -Wc90-c99-compat # -Wlong-long

# Code Quality Warnings.
CWARN_CODE_QUALITY = -Waggregate-return -Winvalid-pch -Wmultistatement-macros \
	-Wstrict-aliasing=3 -Wunreachable-code -Wstringop-overflow \
	-Wstringop-truncation -Wnormalized=nfkc -Walloc-zero -Wparentheses \
	-Wshift-count-negative -Wshift-count-overflow -Wmissing-noreturn \
	-Wvariadic-macros -Wjump-misses-init -Wmain -Wvector-operation-performance \
	-Wsequence-point -Wreturn-local-addr

# All flags.
CFLAGS = $(CWARN_GENERAL) \
	$(CWARN_CONVERSION_FORMAT) \
	$(CWARN_VARIABLES) \
	$(CWARN_DEPRECATED) \
	$(CWARN_PREPROCESSOR) \
	$(CWARN_UNUSED) \
	$(CWARN_DECLARATIONS) \
	$(CWARN_SWITCH) \
	$(CWARN_POINTERS) \
	$(CWARN_OPTIMIZATION) \
	$(CWARN_IMPLICIT) \
	$(CWARN_OVERFLOW_SIZE) \
	$(CWARN_COMPATIBILITY) \
	$(CWARN_CODE_QUALITY) \
	-I./inc/ \
	-I./test/deps/

# All targets. This assumes there exists a .h, .c, and _test.c per target.
TARGETS = zng_array \
	zng_hash_map \
	zng_hash_set \
	zng_linked_list \
	zng_sort_map \
	zng_sort_set \
	zng_string

# Object files.
OBJ_DIR = ./obj/
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(TARGETS))

# Test files.
SRC_DIR = ./test/src/
BIN_DIR = ./test/bin/
BIN = $(patsubst %, $(BIN_DIR)/%_test, $(TARGETS))

# General rule for every object file.
$(OBJ_DIR)/%.o: ./src/%.c
	@$(CC) $(CFLAGS) -x c -c $< -o $@

# General rule for every test binary.
$(BIN_DIR)/%_test: $(SRC_DIR)/%_test.c $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $^ -o $@

# Top-level rule. Creates objects only.
all: $(OBJ)

# Testing rule to create and run all tests in BIN.
test: $(BIN)
	@$(foreach test_binary, $(BIN), ./$(test_binary);)
	@make clean

# Initialize the repository for compiling and testing.
init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Remove created files.
clean:
	@rm -f $(OBJ) $(BIN)

# This is required, otherwise if there exist files named like
# the following, the rules will not be executed.
.PHONY: clean test
