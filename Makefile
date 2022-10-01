# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: severi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 00:48:33 by severi            #+#    #+#              #
#    Updated: 2022/06/23 22:56:58 by severi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = lem_in.c \
init.c \
check_lem_in.c \
do_lem_in.c \
print.c \
queue.c \
util.c \
free.c \
neigbors.c \
path.c \
path_reversed.c \
calc_paths.c \
move_ants.c \
bread_first_traversal.c \

SRCS = $(addprefix srcs/, $(SRC))

OBJ = $(SRC:.c=.o)

OBJS = $(addprefix obj/, $(SRC:.c=.o))

INC = includes/

LIBDIR = libft/

LIB_INC = libft/includes/

OBJ_DIR = obj/

CC = gcc

CFLAGS = -Wall -Werror -Wextra $(DEBUG_FLAGS)

DEBUG_FLAGS = -Wconversion -g -fsanitize=address

DEBUG_NAME = lem-in.debug

all: dir $(NAME)

$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) -I $(INC) -I $(LIB_INC) $(OBJS) -L $(LIBDIR) -lft -o $(NAME)
	@echo "project \"$(NAME)\" compiled"

$(OBJS): obj/%.o : srcs/%.c
	$(CC) $(CFLAGS) -I $(INC) -I $(LIB_INC) -c $< -o $@ 

debug: dir $(DEBUG_NAME)

$(DEBUG_NAME): $(OBJS_DEBUG)
	@make -C libft/
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(INC) -I $(LIB_INC) $(OBJS) -L $(LIBDIR) -lft -o $(DEBUG_NAME)
	@echo Project \"$(DEBUG_NAME)\" compiled with debugging flags

$(OBJS_DEBUG): obj/%.o : srcs/%.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(INC) -I $(LIB_INC) -c $< -o $@ 

dir:
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C libft/
	@rm -f $(OBJ)
	@rm -f -r $(OBJ_DIR)
	@echo "project cleaned, removed *.o files"

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@echo "removed $(NAME)"

re: fclean all
