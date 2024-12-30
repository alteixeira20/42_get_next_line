#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 19:27:01 by paalexan          #+#    #+#              #
#    Updated: 2024/12/30 20:06:55 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                  CONFIGURATION                               #
# **************************************************************************** #

# Compiler and Flags
CC := cc
BUFFER_SIZE := 42
CFLAGS := -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)

# Paths
SRC_DIR := ..
TEST_DIR := tests
LIB := libgnl.a

# Source Files
MANDATORY_SRC := $(SRC_DIR)/get_next_line.c $(SRC_DIR)/get_next_line_utils.c
BONUS_SRC := $(SRC_DIR)/get_next_line_bonus.c $(SRC_DIR)/get_next_line_utils_bonus.c

# Object Files
MANDATORY_OBJ := $(patsubst $(SRC_DIR)/%.c, %.o, $(MANDATORY_SRC))
BONUS_OBJ := $(patsubst $(SRC_DIR)/%.c, %.o, $(BONUS_SRC))

# Test Programs
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TESTS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%, $(TEST_SRC))

# Colors
BOLD := $(shell tput bold)
RED := $(shell tput setaf 1)
GREEN := $(shell tput setaf 2)
YELLOW := $(shell tput setaf 3)
BLUE := $(shell tput setaf 4)
RESET := $(shell tput sgr0)

# **************************************************************************** #
#                                  TARGETS                                     #
# **************************************************************************** #

# Declare phony targets
.PHONY: all bonus run clean fclean re

# Default target: compile mandatory part
all: print_buffer $(LIB)

# Print the buffer size at the top
print_buffer:
	@echo "$(YELLOW)Using BUFFER_SIZE=$(BUFFER_SIZE)$(RESET)"
	@echo "------------------------------------"

# Compile the library for mandatory part
$(LIB): $(MANDATORY_OBJ)
	@ar rcs $@ $^
	@ranlib $@
	@echo "$(GREEN)Mandatory library $(LIB) created successfully!$(RESET)"

# Compile the library for bonus part
bonus: print_buffer
	@$(MAKE) fclean
	@$(MAKE) $(BONUS_OBJ)
	@ar rcs $(LIB) $(BONUS_OBJ)
	@ranlib $(LIB)
	@echo "$(GREEN)Bonus library $(LIB) created successfully!$(RESET)"

# Compile test programs
$(TESTS): $(TEST_DIR)/%: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $< -L. -lgnl
	@echo "$(BLUE)Test program $@ compiled successfully!$(RESET)"

# Run the tester
run: print_buffer $(TESTS)
	@echo "$(BLUE)Running tests...$(RESET)"
	@bash $(TEST_DIR)/run_test.sh

# Compile object files
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled test programs and object files
clean:
	@rm -f $(TESTS)
	@rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)
	@echo "$(YELLOW)Cleaned up test programs and object files.$(RESET)"

# Full clean, including the library
fclean: clean
	@rm -f $(LIB)
	@rm -rf $(TEST_DIR)/expected/*
	@echo "$(RED)Full clean completed, including $(LIB).$(RESET)"

# Recompile everything
re: fclean all
