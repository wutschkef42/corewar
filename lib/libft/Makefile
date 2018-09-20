# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/19 16:01:19 by wutschkef         #+#    #+#              #
#    Updated: 2018/07/10 08:02:24 by wutschkef        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99

SRCDIR = ./src
OBJDIR = ./obj
PFDIR = ./obj/printf
INCDIR = ./includes

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
	ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
	ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_iswhitespace.c ft_lstadd.c ft_lstpushback.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstrev.c ft_lstiter.c ft_lstmap.c get_next_line.c ft_tolower_str.c \
	printf/ft_printf.c \
	printf/process_format.c \
	printf/seek_index.c \
	printf/check_token.c \
	printf/check_token2.c \
	printf/parse_token.c \
	printf/proceed.c \
	printf/init_cspec.c \
	printf/parse_cspec.c \
	printf/dispatch.c \
	printf/print_cspec.c \
	printf/string_handler.c \
	printf/num_handler.c \
	printf/unum_handler.c \
	printf/escape_percent.c \
	printf/char_handler.c \
	printf/pf_atoi.c \
	printf/pf_itoa.c \
	printf/pf_num.c \
	circular_doubly_linked_list.c


OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: obj $(NAME)
	

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(PFDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS) $(OBJDIR)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
