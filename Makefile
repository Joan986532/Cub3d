
NAME = cub3D

SRC_DIR = sources
HEAD_DIR = headers
LIBFT_PATH = libft
MINILIBX_PATH = minilibx-linux

LIBFT = $(LIBFT_PATH)/libft.a
MINILIBX = $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES = $(SRC_DIR)/cub3d.c

OBJECTS = $(SOURCES:.c=.o)

INCLUDE = -lm -lXext -lX11
CFLAGS = -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH) -j
	cc $(OBJECTS) $(INCLUDE) $(MINILIBX) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(MINILIBX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean fclean re all
