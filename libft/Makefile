# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: severi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 18:43:06 by severi            #+#    #+#              #
#    Updated: 2022/02/11 15:44:42 by severi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_CORE = \
ft_atoi.c \
ft_bzero.c \
ft_strlen.c \
ft_strdup.c \
ft_strcmp.c \
ft_strncmp.c\
ft_strcpy.c \
ft_strncpy.c \
ft_strcat.c \
ft_strncat.c \
ft_strlcat.c \
ft_strchr.c \
ft_strrchr.c \
ft_strstr.c \
ft_strnstr.c \
ft_isalpha.c \
ft_isdigit.c \
ft_issign.c \
ft_isalnum.c \
ft_isprint.c \
ft_isascii.c \
ft_toupper.c \
ft_tolower.c \
ft_memset.c \
ft_memcpy.c \
ft_memccpy.c \
ft_memchr.c \
ft_memmove.c \
ft_memcmp.c \
ft_memalloc.c \
ft_memdel.c \
ft_strnew.c \
ft_strdel.c \
ft_strclr.c \
ft_striter.c \
ft_striteri.c \
ft_strmap.c \
ft_strmapi.c \
ft_strequ.c \
ft_strnequ.c \
ft_strsub.c \
ft_strtrim.c \
ft_strjoin.c \
ft_strsplit.c \
ft_itoa.c \
ft_litoa.c \
ft_llitoa.c \
ft_utoa.c \
ft_lutoa.c \
ft_count_digits.c \
ft_count_ldigits.c \
ft_count_u_digits.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putchar.c \
ft_putstr.c \
ft_putendl.c \
ft_putnbr.c \
ft_putnbr_fd.c \
get_next_line.c

SRC_PRINTF = ft_printf.c \
ft_frexp.c \
ft_frexpl.c \
ft_calc_str.c \
ft_float_conv.c \
ft_int_conv.c \
ft_floatl.c \
ft_get_res.c \
ft_vlq.c \
ft_vlq_sum.c \
ft_vlq_mult.c \
ft_vlq_conv.c \
ft_vlq_pow.c \
ft_print_flags.c \
ft_print_before.c \
ft_print_signed.c \
ft_print_str.c \
ft_print_unsigned.c \
ft_return_flags.c \
ft_print_f.c \
ft_print_i.c \
ft_print_x.c \
ft_basetoa.c \
ft_utils.c \
ft_utils_2.c \
ft_round.c \
ft_read_match.c

SRCS_CORE = $(addprefix srcs/, $(SRC_CORE))

SRCS_PRINTF = $(addprefix ft_printf/, $(SRC_PRINTF))

SRCS = $(SRC_CORE) $(SRCS_PRINTF)

OBJS_CORE = $(addprefix obj/, $(SRC_CORE:.c=.o))

OBJS_PRINTF = $(addprefix obj/, $(SRC_PRINTF:.c=.o))

OBJS = $(OBJS_CORE) $(OBJS_PRINTF)

INC = includes/

OBJ_DIR = obj/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS_DEBUG = -g -fsanitize=address -Wconversion

all: dir $(NAME)

$(NAME): $(OBJS_CORE) $(OBJS_PRINTF)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "library compiled"

dir:
	@mkdir -p $(OBJ_DIR)

$(OBJS_CORE): obj/%.o : srcs/%.c
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ 

$(OBJS_PRINTF): obj/%.o : ft_printf/%.c
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ 

clean:
	@rm -f $(OBJ)
	@rm -f -r $(OBJ_DIR)
	@echo "library cleaned, removed *.o files"

fclean: clean
	@rm -f $(NAME)
	@echo "removed $(NAME)"

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)

.PHONY: clean fclean all
