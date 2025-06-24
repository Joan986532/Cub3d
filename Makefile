SRC_DIR = sources
SRC_DIR_BONUS = sources_bonus
HEAD_DIR = headers
LIBFT_PATH = libft
MINILIBX_PATH = minilibx-linux
OBJ_DIR = objects

LIBFT = $(LIBFT_PATH)/libft.a
MINILIBX = $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES = $(SRC_DIR)/monitoring/cub3d.c \
		  $(SRC_DIR)/controls/controls.c \
		  $(SRC_DIR)/utils/cub3d_utils.c \
		  $(SRC_DIR)/drawing/drawing.c \
		  $(SRC_DIR)/utils/errors.c \
		  $(SRC_DIR)/utils/get_next_line.c \
		  $(SRC_DIR)/utils/image_utils.c \
		  $(SRC_DIR)/utils/raycast_utils.c \
		  $(SRC_DIR)/utils/texture_utils.c \
		  $(SRC_DIR)/utils/stripe_utils.c \
		  $(SRC_DIR)/utils/wall_utils.c \
		  $(SRC_DIR)/utils/parsing_utils.c \
		  $(SRC_DIR)/parsing/map_parsing.c \
		  $(SRC_DIR)/parsing/map_validation.c \
		  $(SRC_DIR)/parsing/parsing_color.c \
		  $(SRC_DIR)/parsing/parsing_global.c \
		  $(SRC_DIR)/parsing/parsing_texture.c \
		  $(SRC_DIR)/render/render_frame.c \
		  $(SRC_DIR)/drawing/draw_view.c \
		  $(SRC_DIR)/drawing/draw_player.c \

SOURCES_BONUS = $(SRC_DIR_BONUS)/monitoring/cub3d_bonus.c \
				$(SRC_DIR_BONUS)/controls/controls_bonus.c \
				$(SRC_DIR_BONUS)/utils/cub3d_utils_bonus.c \
				$(SRC_DIR_BONUS)/drawing/drawing_bonus.c \
				$(SRC_DIR_BONUS)/utils/errors_bonus.c \
				$(SRC_DIR_BONUS)/utils/get_next_line_bonus.c \
				$(SRC_DIR_BONUS)/utils/image_utils_bonus.c \
				$(SRC_DIR_BONUS)/utils/raycast_utils_bonus.c \
				$(SRC_DIR_BONUS)/utils/texture_utils_bonus.c \
				$(SRC_DIR_BONUS)/utils/stripe_utils_bonus.c \
				$(SRC_DIR_BONUS)/utils/wall_utils_bonus.c \
				$(SRC_DIR_BONUS)/utils/parsing_utils_bonus.c \
				$(SRC_DIR_BONUS)/parsing/map_parsing_bonus.c \
				$(SRC_DIR_BONUS)/parsing/map_validation_bonus.c \
				$(SRC_DIR_BONUS)/parsing/parsing_color_bonus.c \
				$(SRC_DIR_BONUS)/parsing/parsing_global_bonus.c \
				$(SRC_DIR_BONUS)/parsing/parsing_texture_bonus.c \
				$(SRC_DIR_BONUS)/render/render_frame_bonus.c \
				$(SRC_DIR_BONUS)/drawing/draw_minimap_bonus.c \
				$(SRC_DIR_BONUS)/drawing/draw_overlay_bonus.c \
				$(SRC_DIR_BONUS)/drawing/draw_view_bonus.c \
				$(SRC_DIR_BONUS)/drawing/draw_sprite_bonus.c \
				$(SRC_DIR_BONUS)/drawing/draw_player_bonus.c \

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES)) \

OBJECTS_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c,$(OBJ_DIR)/%.o,$(SOURCES_BONUS)) \

INCLUDE = -lm -lXext -lX11
CFLAGS = -O0 -g -Wall -Wextra -Werror -I$(HEAD_DIR) -I$(LIBFT_PATH) -I$(MINILIBX_PATH)

NAME = cub3D

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH)
	cc $(CFLAGS) $(OBJECTS) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)

bonus: $(OBJECTS_BONUS)
	@make -C $(LIBFT_PATH)
	@make -C $(MINILIBX_PATH)
	cc $(CFLAGS) $(OBJECTS_BONUS) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)_bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(MINILIBX_PATH) clean
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME) $(NAME)_bonus

re: fclean all
rebonus: fclean bonus

.PHONY: clean fclean re all bonus rebonus
