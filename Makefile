
SRC_DIR = sources
GNL_DIR = get_next_line
HEAD_DIR = headers
LIBFT_PATH = libft
MINILIBX_PATH = minilibx-linux

LIBFT = $(LIBFT_PATH)/libft.a
MINILIBX = $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES = $(SRC_DIR)/cub3d.c \
		  $(SRC_DIR)/parsing.c \
		  $(SRC_DIR)/errors.c \
		  $(GNL_DIR)/get_next_line.c \

OBJECTS = $(SOURCES:.c=.o)

INCLUDE = -lm -lXext -lX11
CFLAGS = -g -Wall -Wextra -Werror

NAME = cub3D

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH) -j
	cc $(CFLAGS) $(INCLUDE) $(OBJECTS) $(MINILIBX) $(LIBFT) -o $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) $(INCS) -c $< -o $@;

clean:
	$(MAKE) -C $(MINILIBX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	rm -f $(OBJECTS)
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
re: fclean all

.PHONY: clean fclean re all
