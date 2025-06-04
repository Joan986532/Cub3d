# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 17:50:29 by jnauroy           #+#    #+#              #
#    Updated: 2024/10/25 15:07:39 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_SOURCES = ft_bzero.c \
			 ft_isalnum.c \
			 ft_isalpha.c \
			 ft_isascii.c \
			 ft_isdigit.c \
			 ft_isprint.c \
			 ft_memcpy.c \
			 ft_memset.c \
			 ft_strlen.c \
			 ft_memmove.c \
			 ft_strlcat.c \
			 ft_strlcpy.c \
			 ft_toupper.c \
			 ft_tolower.c \
			 ft_strchr.c \
			 ft_strrchr.c \
			 ft_strncmp.c \
			 ft_memchr.c \
			 ft_memcmp.c \
			 ft_strnstr.c \
			 ft_atoi.c \
			 ft_calloc.c \
			 ft_strdup.c \
			 ft_split.c \
			 ft_substr.c \
			 ft_strjoin.c \
			 ft_strtrim.c \
			 ft_itoa.c \
			 ft_strmapi.c \
			 ft_striteri.c \
			 ft_putchar_fd.c \
			 ft_putstr_fd.c \
			 ft_putendl_fd.c \
			 ft_putnbr_fd.c \
			 ft_freetab.c

HEADER = libft.h

BONUS_SOURCES = ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

MY_OBJECTS = $(MY_SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

CFLAGS += -Wall -Wextra -Werror
AR = ar -rcs

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	$(AR) $(NAME) $(MY_OBJECTS) -o $(NAME)

bonus: $(BONUS_OBJECTS)
	$(AR) $(NAME) $(BONUS_OBJECTS) -o $(NAME)

clean:
	rm -f $(MY_OBJECTS)
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
re: fclean all

.PHONY: all clean fclean re bonus
