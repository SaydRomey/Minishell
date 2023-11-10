# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 21:05:52 by cdumais           #+#    #+#              #
#    Updated: 2023/11/09 13:29:56 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
NAME		:= minishell

INC_DIR		:= inc
LIB_DIR		:= lib
OBJ_DIR		:= obj
SRC_DIR		:= src
SRC_DIR_C	:= src_c
SRC_DIR_P	:= src_p

LIBFT_DIR	:= $(LIB_DIR)/libft
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
# -------------------------------- READLINE (variables) ---------------------- #
# **************************************************************************** #
READLINE_DIR			:= $(LIB_DIR)/readline
READLINE_SRC_URL		:= https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC			:= $(READLINE_DIR)/readline-8.2.tar.gz
READLINE_BUILD_DIR		:= $(READLINE_DIR)/src
READLINE_INSTALL_DIR	:= $(READLINE_DIR)/install
READLINE_SENTINEL		:= $(READLINE_DIR)/.installed

HEADERS += -I$(READLINE_INSTALL_DIR)/include
LDFLAGS += -L$(READLINE_INSTALL_DIR)/lib -lreadline -lncurses

READLINE_DEP := $(if $(wildcard $(READLINE_SENTINEL)),,install_readline)
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
SRC		:=	main															   \
			minishell
# **************************************************************************** #
# **************************************************************************** #
SRC_C	:=	assign_var			error_status			pwd					   \
			builtin_utils		exit_status				reset				   \
			builtin				exit					shellv				   \
			cd_utils			export					shlvl				   \
			cd					info					signals_child		   \
			child_env			path					signals				   \
			commands			print_env				unset				   \
			echo				print_export			var_utils			   \
			env_list			prompt					var_values
# **************************************************************************** #
# **************************************************************************** #
SRC_P	:=	commands_free		token_checks			lexer_clean			   \
			commands_utils		token_clean-1			lexer_expansion_process\
			commands			token_clean-2			lexer_list_free		   \
			count_utils			token_create			lexer_list_utils	   \
			env_utils			token_types_utils		lexer				   \
			errors				token_types				expand_utils		   \
														expand				   \
			redirection_checks							skip_utils			   \
			redirection_heredoc_utils										   \
			redirection_heredoc												   \
			execution_redirection_io_fd										   \
			execution_redirection_io_single									   \
			execution_redirection_io_utils									   \
			execution_redirection_io										   \
			execution_redirection_pipeline									   \
			execution_utils													   \
			execution
# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
INC		:=	minishell			minishell_c				minishell_p			   \
			macros															   \
			ms_errors
# **************************************************************************** #
# -------------------------------- TEAM FILES -------------------------------- #
# **************************************************************************** #
INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))

SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
SRCS_C		:=	$(addprefix $(SRC_DIR_C)/, $(addsuffix .c, $(SRC_C)))
SRCS_P		:=	$(addprefix $(SRC_DIR_P)/ms_, $(addsuffix .c, $(SRC_P)))

OBJ_S		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_C		:=	$(patsubst $(SRC_DIR_C)/%.c,$(OBJ_DIR)/%.o,$(SRCS_C))
OBJS_P		:=	$(patsubst $(SRC_DIR_P)/%.c,$(OBJ_DIR)/%.o,$(SRCS_P))
OBJS		:=	$(OBJ_S) $(OBJS_C) $(OBJS_P)
# **************************************************************************** #
# ------------------------------- TEAM * FILES ------------------------------- #
# **************************************************************************** #
# INCS		:=	$(wildcard $(INC_DIR)/*.h)
# SRCS		:=	$(wildcard $(SRC_DIR)/*.c)
# SRCS_C	:=	$(wildcard $(SRC_DIR_C)/*.c)
# SRCS_P	:=	$(wildcard $(SRC_DIR_P)/*.c)
# OBJ_S		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# OBJS_C	:=	$(patsubst $(SRC_DIR_C)/%.c,$(OBJ_DIR)/%.o,$(SRCS_C))
# OBJS_P	:=	$(patsubst $(SRC_DIR_P)/%.c,$(OBJ_DIR)/%.o,$(SRCS_P))
# OBJS		:=	$(OBJS) $(OBJS_C) $(OBJS_P)
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(READLINE_DEP) $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCS) $(READLINE_DEP)
	@echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)]\\t$(GREEN)created$(RESET)"
	@echo "$(GRAY)$$TITLE$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
	@make -C $(LIBFT_DIR) $(NPD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR)/%.o: $(SRC_DIR_C)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR)/%.o: $(SRC_DIR_P)/%.c $(INCS) | $(OBJ_DIR)
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
		curl -# -o $(READLINE_SRC) $(READLINE_SRC_URL); \
	fi
	@mkdir -p $(READLINE_BUILD_DIR)
	@tar -xf $(READLINE_SRC) -C $(READLINE_BUILD_DIR) --strip-components=1
	@cd $(READLINE_BUILD_DIR) && \
	./configure --prefix=$(PWD)/$(READLINE_INSTALL_DIR) && \
	clear && echo "$(BOLD)$(CYAN)readline$(RESET) is now being built" && \
	make --quiet && \
	clear && echo "$(BOLD)$(CYAN)readline$(RESET) is now being installed" && \
	make install --quiet
	@printf "$(TOP_LEFT)$(ERASE_ALL)"
	@echo "[$(BOLD)$(PURPLE)readline$(RESET)] \
	installed locally in $(CYAN)$(UNDERLINE)$(READLINE_DIR)$(RESET)"
	@touch $@

rclean:
	@if [ -n "$(wildcard $(READLINE_SENTINEL))" ]; then \
		$(REMOVE) $(READLINE_DIR); \
		echo "[$(BOLD)$(PURPLE)readline$(RESET)] \
		$(GREEN)all files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)readline$(RESET)] \
		$(YELLOW)No readline to clean$(RESET)"; \
	fi

.PHONY: install_readline rclean
# **************************************************************************** #
# ---------------------------------- NORME ----------------------------------- #
# **************************************************************************** #
norm:
	@if which norminette > $(VOID); then \
		echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"; \
		norminette -R CheckDefine inc/*.h; \
		norminette -R CheckForbiddenSourceHeader src*/*.c; \
		make norm -C $(LIBFT_DIR); \
	else \
		echo "$(BOLD)$(YELLOW)Norminette not installed$(RESET)"; \
	fi

nm:
	@echo "$(BOLD)$(YELLOW)Functions in $(PURPLE)$(UNDERLINE)$(NAME)$(RESET):"
	@nm $(NAME) | grep U
	@make nm -C $(LIBFT_DIR) $(NPD)

.PHONY: norm nm
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
run: all
	@./$(NAME)

debug: C_FLAGS += -g
debug: re
# @./$(NAME)
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= minishell_en.pdf
GIT_URL := https://github.com/SaydRomey/Minishell
PDF_URL := $(GIT_URL)/blob/main/instructions/minishell_en.pdf?raw=true
OS		:= $(shell uname -s)

pdf:
	@curl -# -L $(PDF_URL) -o $(PDF)
ifeq ($(OS),Darwin)
	@open $(PDF)
else
	@xdg-open $(PDF) || echo "Please install a compatible PDF viewer"
endif
	@sleep 2
	@rm -f $(PDF)

.PHONY: pdf
# **************************************************************************** #
# ---------------------------------- BACKUP ---------------------------------- #
# **************************************************************************** #
USER		:=$(shell whoami)
ROOT_DIR	:=$(notdir $(shell pwd))
TIMESTAMP	:=$(shell date "+%Y%m%d_%H%M%S")
BACKUP_NAME	:=$(ROOT_DIR)_$(USER)_$(TIMESTAMP).zip
BACKUP_NAME	:=$(ROOT_DIR)_$(USER)_$(TIMESTAMP).zip
MOVE_TO		:= ~/Desktop/$(BACKUP_NAME)

backup: ffclean
	@if which zip > $(VOID); then \
		zip -r --quiet $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) $(MOVE_TO); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		compressed as: $(CYAN)$(UNDERLINE)$(MOVE_TO)$(RESET)"; \
	else \
		echo "Please install zip to use the backup feature"; \
	fi

.PHONY: backup
# **************************************************************************** #
# -------------------------------- LEAKS ------------------------------------- #
# **************************************************************************** #
VAL_CHECK	:= $(shell which valgrind > $(VOID); echo $$?)

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

# default valgrind tool
BASE_TOOL = valgrind $(ORIGIN) $(LEAK_CHECK) $(LEAK_KIND)

# specific valgrind tool (change options as needed)
BASE_TOOL += $(CHILDREN) $(FD_TRACK) $(NO_REACH)

LEAK_TOOL = $(BASE_TOOL) $(LOG_FILE)
SUPP_TOOL = $(BASE_TOOL) $(SUPP_GEN) $(LOG_FILE)

# run valgrind
leaks: C_FLAGS += -g
leaks: all
	@if [ $(VAL_CHECK) -eq 0 ]; then \
		$(LEAK_TOOL) ./$(NAME); \
	else \
		echo "Please install valgrind to use the leaks feature"; \
	fi

# generate suppression file
supp: C_FLAGS += -g
supp: all
	$(SUPP_TOOL) ./$(NAME)
	awk '/^{/,/^}/' valgrind-out.txt > suppression.supp

# use suppression file
suppleaks: C_FLAGS += -g
suppleaks: all
	$(LEAK_TOOL) $(SUPPRESS) ./$(NAME) && cat valgrind-out.txt

# remove suppression and log files
vclean:
	@if [ -n "$(wildcard suppression.supp)" ]; then \
		$(REMOVE) $(SUPP_FILE); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)suppression file removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)no suppression file to remove$(RESET)"; \
	fi
	@if [ -n "$(wildcard valgrind-out.txt)" ]; then \
		$(REMOVE) valgrind-out.txt; \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)log file removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)no log file to remove$(RESET)"; \
	fi

.PHONY: leaks supp suppleaks vclean
# **************************************************************************** #
ffclean: fclean vclean rclean

.PHONY: ffclean
# **************************************************************************** #
# ------------------------------- DECORATIONS -------------------------------- #
# **************************************************************************** #
define TITLE

⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⠀⣀⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡴⠦⣤⣴⡟⠉⠉⡗⠚⡇⠀⠈⡷⢤⠖⠒⠲⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡇⠀⠀⢸⠀⡇⠀⠀⠇⠀⡇⠀⠀⡇⢸⠀⠀⢠⠋⡝⠉⠓⢦⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠁⢣⢰⠀⠀⠈⡆⢳⠀⠀⠀⠀⡇⠀⢸⠀⡇⠀⠀⡜⢰⠃⠀⠀⡜⢦⢤⣀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⡠⢴⠻⡀⠀⠈⡎⡇⠀⠀⢃⢸⠀⠀⢸⠀⡇⠀⢸⢀⡇⠀⢠⠃⡎⠀⠀⡼⢡⠃⠀⠙⡆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⠁⠀⢣⢱⡀⠀⢸⣸⡀⠀⢸⠈⡄⠀⢸⠀⡇⠀⠘⢸⠀⠀⡸⢰⠁⠀⢰⢡⠏⠀⠀⡜⡿⢤⡀⠀⠀
⠀⠀⠀⠀⠀⣠⠞⣷⡄⠀⢣⢣⠀⠀⢧⢇⠀⠈⡆⡇⠀⢸⠀⡇⠀⡇⡼⠀⢀⠇⡏⠀⢠⢇⠎⠀⢀⡜⡜⠁⠀⢳⠀⠀
⠀⠀⠀⠀⢸⡁⠀⠈⢻⣦⠀⢫⢧⠀⠘⡾⡄⠀⣇⢡⠀⢸⠀⡇⠀⡇⡇⠀⣸⢸⠀⢀⠏⡜⠀⢀⢎⠞⠀⢀⡴⡻⡄⠀
⠀⠀⠀⠀⣰⠻⣆⠀⠀⠻⣷⡀⢻⢰⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢠⢾⠎⠀⡰⢫⠞⠀⡟⠀⠀
⠀⠀⠀⠀⢹⣅⠙⢷⣄⠀⠙⣷⢧⣼⠀⠀⠀⠉⠉⠙⠛⠛⠛⠛⠛⠛⠋⠉⠉⠀⢸⣿⡇⣯⠋⣠⣾⡖⢁⡠⠚⣿⡄⠀
⠀⠀⠀⠀⢹⡕⢄⠑⢌⠛⢦⠈⣿⡇⠐⣶⣿⣿⣷⣦⡄⠀⠀⢠⣶⣾⣿⣿⣶⠀⢸⡇⡻⢃⡴⡷⢋⡴⢋⡤⣺⠇⠀
⠀⠀⠀⠀⠙⢦⣝⢦⡑⢄⠳⣌⢻⡇⠀⠈⠙⠛⠛⠁⠀⠀⠀⠀⠉⠛⠛⠋⠁⠀⢸⡇⢡⣾⢞⣴⣯⡔⣫⢴⠟⠀⠀
⠀⠀⠀⠀⠘⣏⠳⣄⠙⣦⡀⠘⠸⣷⣶⣤⣤⣤⣤⣤⣀⣀⣀⣀⣤⣤⣤⣤⣤⣶⣾⠇⠋⡡⣫⣞⣽⣋⣴⠟
⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢿⣮⡳⣌⢦⡱⡌⣆⢸⠀⡟⡆⡇⡇⡇⢸⠁⡜⠀⡼⠁⡜⠁⣪⠞⣿⡵⠟⠉⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⡾⣾⣷⣵⡜⡜⡄⠇⢣⡇⡇⢳⠁⡎⠀⠀⡼⢁⠞⠠⢾⡵⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠈⠛⢿⣾⣾⣾⠘⠈⠁⠇⠀⠀⠁⠀⠾⠁⢀⣤⠞⢫⡗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⣄⠀⠙⠿⣟⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠛⣡⡴⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠒⠦⠬⠷⢄⡀⠀⠀⠀⣠⠴⠟⠚⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠒⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

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
help:
	@echo "\nUsage:"
	@echo "  make [TARGET]\n"
	@echo "Targets:"
	@echo "  all        Compile and create the program"
	@echo "  clean      Remove object files"
	@echo "  fclean     Remove object files and executable"
	@echo "  re         Re-compile (equivalent to running 'make fclean all')"
	@echo "  run        Compile and run the program"
	@echo "  debug      Re-compile with debug flags [and run the program]"
	@echo "  norm       Check for norminette errors"
	@echo "  nm         Show functions in the binary"
	@echo "  pdf        Open the project PDF (from github)"
	@echo "  backup     Create a backup 'fcleaned' zip of the current directory"
	@echo "  leaks      Run the program with valgrind to check for leaks"
	@echo "  supp       Generate a suppression file for valgrind"
	@echo "  suppleaks  Run the program with valgrind using the suppression file"
	@echo "  vclean     Remove suppression and valgrind log files"
	@echo "  rclean     Remove readline source files"
	@echo "  ffclean    fclean, vclean and rclean"
	@echo "  title      Print the project title"
	@echo "  help       Print this help message"
	@echo "\n"

.PHONY: help 
