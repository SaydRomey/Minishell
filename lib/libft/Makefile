# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 18:09:54 by cdumais           #+#    #+#              #
#    Updated: 2023/11/03 21:38:21 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
NAME 		:= libft.a

INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= obj

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror

ARCHIVE		:= ar
AR_FLAGS	:= rcs
AR_INDEX	:= ranlib

REMOVE		:= rm -rf

# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# *********** libc functions ******************* additonal functions ********* #
# **************************************************************************** #
SRC :=			ft_isalpha							ft_substr	  			   \
				ft_isdigit							ft_strjoin				   \
				ft_isalnum							ft_strtrim				   \
				ft_isascii							ft_split				   \
				ft_isprint							ft_itoa					   \
				ft_strlen							ft_strmapi				   \
				ft_memset							ft_striteri				   \
				ft_bzero							ft_putchar_fd			   \
				ft_memcpy							ft_putstr_fd			   \
				ft_memmove							ft_putendl_fd			   \
				ft_strlcpy							ft_putnbr_fd			   \
				ft_strlcat													   \
				ft_toupper													   \
				ft_tolower													   \
				ft_strchr													   \
				ft_strrchr													   \
				ft_strncmp													   \
				ft_memchr													   \
				ft_memcmp													   \
				ft_strnstr													   \
				ft_atoi													   	   \
				ft_calloc													   \
				ft_strdup	
# **************************************************************************** #
# ----------------------------------- BONUS ---------------------------------- #
# ********* linked list functions ************** additonal functions ********* #
# **************************************************************************** #
SRC +=	 		ft_lstnew													   \
				ft_lstadd_front						ft_lstcpy				   \
				ft_lstsize							ft_lstsort				   \
				ft_lstlast							ft_lstswap				   \
				ft_lstadd_back						ft_lstswitch			   \
				ft_lstdelone												   \
				ft_lstclear													   \
				ft_lstiter													   \
				ft_lstmap
# **************************************************************************** #
# ------------------------------- OTHER PROJECTS ----------------------------- #
# ************* get_next_line *********************** ft_printf ************** #
# **************************************************************************** #
SRC +=			get_next_line						ft_printf				   \
													ft_intlen				   \
													ft_putnbr_base_fd
# **************************************************************************** #
# -------------------------------- OTHER UTILS ------------------------------- #
# ************* push_swap ****************************** fdf ***************** #
# **************************************************************************** #
SRC +=			ft_swap								ft_abs					   \
				ft_min								ft_isspace				   \
				ft_max								exit_error				   \
				flow_check							ft_atoi_base
													
# **************************************************************************** #
SRC +=			ft_free														   \
				read_check													   \
				char_count
# **************************************************************************** #
# ----------------------------------- MISC  ---------------------------------- #
# **************************************************************************** #
SRC +=			ft_strainbow

# **************************************************************************** # AJOUT PO
SRC +=	ft___alloc															   \
		ft___atoi_check														   \
		ft___free_tab														   \
		ft___iswhitespace													   \
		ft___strcmp															   \
		ft___strlen_tab														   \
		ft___strstr															   \
		ft___tablen

# **************************************************************************** #
# --------------------------------- HEADERS ---------------------------------- #
# **************************************************************************** #
INC	:=			libft														   \
				libft_utils
# **************************************************************************** #				
INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# --------------------------------- ALL FILES -------------------------------- #
# **************************************************************************** #
# INCS		:=	$(wildcard $(INC_DIR)/*.h)
# SRCS		:=	$(wildcard $(SRC_DIR)/*.c)
# OBJS		:=	$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%.o, $(SRCS))
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(OBJS)
	@echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)]\\t$(GREEN)created$(RESET)"
	@$(ARCHIVE) $(AR_FLAGS) $(NAME) $(OBJS)
	@$(AR_INDEX) $(NAME)

# $(NAME): $(OBJS)
# 	@echo "$(BOLD)$(PURPLE)$(NAME)$(RESET)$(GREEN) created$(RESET)"
# 	@echo "$(GREEN)$$TITLE$(RESET)"
# 	@echo "Executed by $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
# 		$(CYAN)$(TIME)$(RESET)\n"
# 	@$(ARCHIVE) $(AR_FLAGS) $(NAME) $(OBJS)
# 	@$(AR_INDEX) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) -I$(INC_DIR) -o $@ -c $<
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

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Library removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No library to remove$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
# -------------------------------- NORMINETTE -------------------------------- #
# **************************************************************************** #
norm: $(NAME)
	@echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"
	@norminette -R CheckDefine inc/*.h
	@norminette -R CheckForbiddenSourceHeader src/*.c

nm:
	@echo "$(BOLD)$(YELLOW)Functions in $(PURPLE)$(UNDERLINE)$(NAME)$(RESET):"
	@nm $(NAME) | grep U | grep -v 'ft_'
# @nm $(NAME) | grep U | sed 's/^ *U _//'

.PHONY: norm nm

# **************************************************************************** #
# ------------------------------- DECORATIONS -------------------------------- #
# **************************************************************************** #
define TITLE

██      ██ ██████  ███████ ████████ 
██      ██ ██   ██ ██         ██    
██      ██ ██████  █████      ██    
██      ██ ██   ██ ██         ██    
███████ ██ ██████  ██         ██   

endef
export TITLE

USER		:=$(shell whoami)
TIME		:=$(shell date "+%H:%M:%S")

title:
	@echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)]\\t$(GREEN)created$(RESET)"
	@echo "$(GREEN)$$TITLE$(RESET)"
	@echo "Executed by $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
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

# $(NAME): $(OBJS)
# 	$(ARCHIVE) $(AR_FLAGS) $(NAME) $(OBJS)
# 	$(AR_INDEX) $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
# 	$(COMPILE) $(C_FLAGS) -I$(INC_DIR) -o $@ -c $<

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# clean:
# 	$(REMOVE) $(OBJ_DIR)

# fclean: clean
# 	$(REMOVE) $(NAME)

# re: fclean all
