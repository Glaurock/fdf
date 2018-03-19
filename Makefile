# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2018/03/19 15:12:19 by gmonnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = fdf

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCDIR = srcs
OBJDIR = obj
INCDIR = includes \
		 ./libft/includes

SRC = \
	main.c \
	errors.c \
	input.c \
	set_map.c \
	utils.c \
	utils2.c \
	draw.c \
	events.c \
	colors.c

LIB = ./libft/libft.a \

#MLXFLAGS_LINUX = $(shell pkg-config --libs --static mlx)
MLXFLAGS_MAC = -lmlx -L minilibx_macos -lmlx -framework OpenGL -framework AppKit
LIBMATH = -lm

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

#Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(FLAGS) $(LIB) $(MLXFLAGS_MAC) $(LIBMATH) -o $@
	@echo "Compiling project $(NAME)...$(_GREEN)DONE$(_END)"

clean:
	@echo "Removed objects (.o) files."
	@make clean -C ./libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "Removed project ($(NAME))."
	@make fclean -C ./libft
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@clear
	@printf "$(_CYAN)Compiling $@ $(_END)"
	@mkdir -p 2>/dev/null $(OBJDIR) || true
	@$(CC) -o $@ -c $(FLAGS) $< $(INCS)

$(LIB):
	make -C $(@D)
