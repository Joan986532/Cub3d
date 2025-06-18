SRC_DIR = sources
GNL_DIR = get_next_line
HEAD_DIR = headers
LIBFT_PATH = libft
MINILIBX_PATH = minilibx-linux
OBJ_DIR = objects

LIBFT = $(LIBFT_PATH)/libft.a
MINILIBX = $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES = $(SRC_DIR)/monitoring/cub3d.c \
		  $(SRC_DIR)/controls.c \
		  $(SRC_DIR)/utils/cub3d_utils.c \
		  $(SRC_DIR)/drawing/drawing.c \
		  $(SRC_DIR)/utils/errors.c \
		  $(SRC_DIR)/utils/image_utils.c \
		  $(SRC_DIR)/parsing/map_parsing.c \
		  $(SRC_DIR)/parsing/map_validation.c \
		  $(SRC_DIR)/minimap.c \
		  $(SRC_DIR)/parsing/parsing_color.c \
		  $(SRC_DIR)/parsing/parsing_global.c \
		  $(SRC_DIR)/parsing/parsing_texture.c \
		  $(SRC_DIR)/player.c \
		  $(SRC_DIR)/render/render_frame.c \
		  $(SRC_DIR)/drawing/draw_minimap.c \
		  $(SRC_DIR)/drawing/draw_overlay.c \
		  $(SRC_DIR)/drawing/draw_view.c \
		  $(SRC_DIR)/drawing/draw_sprite.c \
		  $(GNL_DIR)/get_next_line.c \


OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SOURCES))) \
		$(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(GNL_DIR)/%,$(SOURCES)))

INCLUDE = -lm -lXext -lX11
CFLAGS = -g -Wall -Wextra -Werror -I$(HEAD_DIR) -I$(LIBFT_PATH) -I$(GNL_DIR) -I$(MINILIBX_PATH)

NAME = cub3D

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH)
	cc $(CFLAGS) $(OBJECTS) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(MINILIBX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
