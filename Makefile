
SRC_DIR = sources
GNL_DIR = get_next_line
HEAD_DIR = headers
LIBFT_PATH = libft
MINILIBX_PATH = minilibx-linux

LIBFT = $(LIBFT_PATH)/libft.a
MINILIBX = $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES = $(SRC_DIR)/cub3d.c \
		  $(SRC_DIR)/controls.c \
		  $(SRC_DIR)/cub3d_utils.c \
		  $(SRC_DIR)/drawing.c \
		  $(SRC_DIR)/errors.c \
		  $(SRC_DIR)/image_utils.c \
		  $(SRC_DIR)/map_parsing.c \
		  $(SRC_DIR)/map_validation.c \
		  $(SRC_DIR)/minimap.c \
		  $(SRC_DIR)/parsing_color.c \
		  $(SRC_DIR)/parsing_global.c \
		  $(SRC_DIR)/parsing_texture.c \
		  $(SRC_DIR)/player.c \
		  $(GNL_DIR)/get_next_line.c \

OBJECTS = $(SOURCES:.c=.o)

INCLUDE = -lm -lXext -lX11
CFLAGS = -g -Wall -Wextra -Werror -I$(HEAD_DIR) -I$(LIBFT_PATH) -I$(GNL_DIR) -I$(MINILIBX_PATH)

NAME = cub3D

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH)
	cc $(CFLAGS) $(OBJECTS) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)


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
