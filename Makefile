# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 21:05:52 by cdumais           #+#    #+#              #
#    Updated: 2023/09/28 16:28:51 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
NAME		:= minishell

INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= obj

LIBFT_DIR	:= libft
LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
LIBFT_HDR	:= $(LIBFT_INC)/libft.h
LIBFT_SRCS	:= $(wildcard $(LIBFT_DIR)/$(SRC_DIR)/*.c)
LIBFT		:= $(LIBFT_DIR)/libft.a

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null

HEADERS 	:= -I$(INC_DIR) -I$(LIBFT_INC)

# **************************************************************************** #
# --------------------------------- READLINE (variables) --------------------- #
# **************************************************************************** #
READLINE_DIR			:= readline
READLINE_SRC_URL		:= https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
READLINE_SRC			:= $(READLINE_DIR)/readline-8.1.tar.gz
READLINE_BUILD_DIR		:= $(READLINE_DIR)/src
READLINE_INSTALL_DIR	:= $(READLINE_DIR)/install
READLINE_SENTINEL		:= $(READLINE_DIR)/.installed

HEADERS += -I$(READLINE_INSTALL_DIR)/include
LDFLAGS += -L$(READLINE_INSTALL_DIR)/lib -lreadline -lncurses

READLINE_DEP := $(if $(wildcard $(READLINE_SENTINEL)),,install_readline)

# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
# SRC :=			main														   \
# 				

# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
# INC	:=			minishell

# **************************************************************************** #
# --------------------------------- ALL FILES -------------------------------- #
# **************************************************************************** #
# INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
# SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
INCS		:=	$(wildcard $(INC_DIR)/*.h)
SRCS		:=	$(wildcard $(SRC_DIR)/*.c)
OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(READLINE_DEP) $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCS) $(READLINE_DEP)
	@echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) created$(RESET)"
	@echo "$(GREEN)$$TITLE$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
	@make -C $(LIBFT_DIR) $(NPD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -n "$(wildcard $(OBJS)*.o)" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
	fi
	@make clean -C $(LIBFT_DIR) $(NPD)

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Executable removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No executable to remove$(RESET)"; \
	fi
	@make fclean -C $(LIBFT_DIR) $(NPD)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
# --------------------------------- READLINE (rules) ------------------------- #
# **************************************************************************** #
install_readline: $(READLINE_SENTINEL)

$(READLINE_SENTINEL):
	@mkdir -p $(READLINE_DIR)
	@echo "$(CYAN)Downloading and installing readline...$(RESET)"
	@if [ ! -f $(READLINE_SRC) ]; then \
		curl -o $(READLINE_SRC) $(READLINE_SRC_URL); \
	fi
	@mkdir -p $(READLINE_BUILD_DIR)
	@tar -xf $(READLINE_SRC) -C $(READLINE_BUILD_DIR) --strip-components=1
	@cd $(READLINE_BUILD_DIR) && \
	./configure --prefix=$(PWD)/$(READLINE_INSTALL_DIR) && \
	make && make install
	@echo "$(GREEN)readline installed locally in $(READLINE_DIR)$(RESET)"
	@touch $@

rclean:
	@if [ -n "$(wildcard $(READLINE_SENTINEL))" ]; then \
		echo "$(CYAN)Cleaning readline...$(RESET)"; \
		$(REMOVE) $(READLINE_DIR); \
		echo "$(GREEN)readline cleaned$(RESET)"; \
	else \
		echo "$(YELLOW)No readline to clean$(RESET)"; \
	fi

.PHONY: install_readline rclean

# **************************************************************************** #
# ---------------------------------- BONUS ----------------------------------- #
# **************************************************************************** #
# BNS_DIR		:= src_bonus

# B_SRCS		:=	$(addprefix $(BNS_DIR)/, $(addsuffix _bonus.c, $(SRC)))
# B_OBJS		:=	$(patsubst $(BNS_DIR)/%.c,$(OBJ_DIR)/%.o,$(B_SRCS))

# $(OBJ_DIR)/%_bonus.o: $(BNS_DIR)/%_bonus.c $(INCS) | $(OBJ_DIR)
# 	@echo "$(CYAN)Compiling bonus...$(ORANGE)\t$(notdir $<)$(RESET)"
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
# 	@printf "$(UP)$(ERASE_LINE)"

# bonus: $(LIBFT) $(B_OBJS) $(INCS)
# 	@echo "$(BOLD)$(PURPLE)$(NAME)$(ORANGE) Bonus$(RESET)$(GREEN) created$(RESET)"
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(B_OBJS) $(LIBFT) -o $(NAME)

# rebonus: fclean bonus

# .PHONY: bonus rebonus

# **************************************************************************** #
# ---------------------------------- TESTS ----------------------------------- #
# **************************************************************************** #
run: all
	@./$(NAME)

# **************************************************************************** #
# ---------------------------------- NORME ----------------------------------- #
# **************************************************************************** #
# norm:
# 	@echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"
# 	@norminette -R CheckDefine inc/*.h
# 	@norminette -R CheckForbiddenSourceHeader src/*.c
# 	@make norm -C $(LIBFT_DIR)

# norm but checks if norminette is installed first
norm:
	@if which norminette > $(VOID); then \
		echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"; \
		norminette -R CheckDefine inc/*.h; \
		norminette -R CheckForbiddenSourceHeader src/*.c; \
		make norm -C $(LIBFT_DIR); \
	else \
		echo "$(BOLD)$(YELLOW)Norminette not installed$(RESET)"; \
	fi

nm:
	@echo "$(BOLD)$(YELLOW)Functions in $(PURPLE)$(UNDERLINE)$(NAME)$(RESET):"
	@nm $(NAME) | grep U
	@make nm -C $(LIBFT_DIR) $(NPD)

# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
pdf:
# @open https://

# **************************************************************************** #
# ---------------------------------- BACKUP ---------------------------------- #
# **************************************************************************** #
ROOT_DIR	:=$(notdir $(shell pwd))
TIMESTAMP	:=$(shell date "+%Y%m%d_%H%M%S")
BACKUP_NAME	:=backup_$(ROOT_DIR)_$(TIMESTAMP).zip

backup: fclean lclean rclean
	@if which zip > $(VOID); then \
		zip -r $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) ~/Desktop/; \
	else \
		echo "Please install zip to use the backup feature"; \
	fi

.PHONY: norm nm pdf backup

# **************************************************************************** #
# -------------------------------- LEAKS ------------------------------------- #
# **************************************************************************** #

# TODO: adjust this for current project..

# valgrind options
ORIGIN		:= --track-origins=yes
LEAK_CHECK	:= --leak-check=full
LEAK_KIND	:= --show-leak-kinds=all
CHILDREN	:= --trace-children=yes
FD_TRACK	:= --track-fds=yes
NO_REACH	:= --show-reachable=no
VERBOSE		:= --verbose
LOG_FILE	:= --log-file=valgrind-out.txt

# suppression-related options
SUPP_FILE	:= suppression.supp
SUPP_GEN	:= --gen-suppressions=all
SUPPRESS	:= --suppressions=$(SUPP_FILE)

ifeq ($(shell uname), Linux)
BASE_TOOL = valgrind $(ORIGIN) $(LEAK_CHECK) $(LEAK_KIND) $(CHILDREN) $(FD_TRACK)
else ifeq ($(shell uname), Darwin)
BASE_TOOL = valgrind $(ORIGIN) $(LEAK_CHECK) $(LEAK_KIND) $(CHILDREN) $(FD_TRACK)
endif

# BASE_TOOL = leaks --atExit --

LEAK_TOOL = $(BASE_TOOL) $(LOG_FILE)
SUPP_TOOL = $(BASE_TOOL) $(SUPP_GEN) $(LOG_FILE)

# run valgrind
leaks: C_FLAGS += -g
leaks: all
	$(LEAK_TOOL) ./$(NAME) && cat valgrind-out.txt

# generate suppression file
supp: C_FLAGS += -g
supp: all
	$(SUPP_TOOL) ./$(NAME)
	awk '/^{/,/^}/' valgrind-out.txt > suppression.supp

# use suppression file
suppleaks: C_FLAGS += -g
suppleaks: all
	$(LEAK_TOOL) $(SUPPRESS) ./$(NAME) && cat valgrind-out.txt

# remove log file and suppression file
# lclean:
# 	@$(REMOVE) $(SUPP_FILE) valgrind-out.txt
# 	@echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) log files removed$(RESET)"

# lclean only if files to suppress exist
lclean:
	@if [ -n "$(wildcard suppression.supp)" ]; then \
		$(REMOVE) $(SUPP_FILE); \
		echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) suppression file removed$(RESET)"; \
	else \
		echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(YELLOW) no suppression file to remove$(RESET)"; \
	fi
	@if [ -n "$(wildcard valgrind-out.txt)" ]; then \
		$(REMOVE) valgrind-out.txt; \
		echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) log file removed$(RESET)"; \
	else \
		echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(YELLOW) no log file to remove$(RESET)"; \
	fi

.PHONY: leaks supp suppleaks lclean

# **************************************************************************** #
# ------------------------------- DECORATIONS -------------------------------- #
# **************************************************************************** #
define TITLE

███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      
████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      
██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      
██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      
██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ 

endef
export TITLE

USER		:=$(shell whoami)
TIME		:=$(shell date "+%H:%M:%S")

title:
	@echo "$(BOLD)$(PURPLE)$(NAME)$(GREEN) created$(RESET)"
	@echo "$(GREEN)$$TITLE$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"

.PHONY: title

# **************************************************************************** #
# ----------------------------------- ANSI ----------------------------------- #
# **************************************************************************** #
# ****** https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 ******* #

ESC			:= \033

RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
DIM			:= $(ESC)[2m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m
BLINK		:= $(ESC)[5m #no effect on iterm?
INVERT		:= $(ESC)[7m
HIDDEN		:= $(ESC)[8m
STRIKE		:= $(ESC)[9m

# Cursor movement
UP			:= $(ESC)[A
DOWN		:= $(ESC)[B
FORWARD		:= $(ESC)[C
BACK		:= $(ESC)[D
NEXT_LINE	:= $(ESC)[E
PREV_LINE	:= $(ESC)[F
COLUMN		:= $(ESC)[G
TOP_LEFT	:= $(ESC)[1;1H

# Erasing
ERASE_REST	:= $(ESC)[K
ERASE_LINE	:= $(ESC)[2K
ERASE_ALL	:= $(ESC)[2J

# **************************************************************************** #
# ---------------------------------- COLORS ---------------------------------- #
# **************************************************************************** #
# Text
BLACK		:= $(ESC)[30m
RED			:= $(ESC)[91m
GREEN		:= $(ESC)[32m
YELLOW		:= $(ESC)[93m
ORANGE		:= $(ESC)[38;5;208m
BLUE		:= $(ESC)[94m
PURPLE		:= $(ESC)[95m
CYAN		:= $(ESC)[96m
WHITE		:= $(ESC)[37m
GRAY		:= $(ESC)[90m

# Background
BG_BLACK	:= $(ESC)[40m
BG_RED		:= $(ESC)[101m
BG_GREEN	:= $(ESC)[102m
BG_YELLOW	:= $(ESC)[103m
BG_ORANGE	:= $(ESC)[48;5;208m
BG_BLUE		:= $(ESC)[104m
BG_PURPLE	:= $(ESC)[105m
BG_CYAN		:= $(ESC)[106m
BG_WHITE	:= $(ESC)[47m
BG_GRAY		:= $(ESC)[100m

# **************************************************************************** #
# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJS) $(INCS)
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@

# $(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
# 	@make -C $(LIBFT_DIR) $(NPD)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# clean:
# 	@$(REMOVE) $(OBJS)
# 	@$(REMOVE) $(OBJ_DIR)
# 	@make clean -C $(LIBFT_DIR) $(NPD)

# fclean: clean
# 	@$(REMOVE) $(NAME)
# 	@make fclean -C $(LIBFT_DIR) $(NPD)

# re: fclean all

# .PHONY: all clean fclean re

help:
	@echo "\nUsage:"
	@echo "  make [TARGET]\n"
	@echo "Targets:"
	@echo "  all        Compile and create the program"
	@echo "  clean      Remove object files"
	@echo "  fclean     Remove object files and executable"
	@echo "  re         Re-compile (equivalent to running 'make fclean all')"
	@echo "  run        Compile and run the program"
	@echo "  norm       Check for norminette errors"
	@echo "  nm         Show functions in the binary"
	@echo "  pdf        Open the project PDF in a web browser"
	@echo "  backup     Create a backup zip of the current directory"
	@echo "  leaks      Run the program with valgrind to check for leaks"
	@echo "  supp       Generate a suppression file for valgrind"
	@echo "  suppleaks  Run the program with valgrind using the suppression file"
	@echo "  lclean     Remove suppression and valgrind log files"
	@echo "  rclean     Remove readline source files\n"
