GREEN =\033[0;32m
RED = \033[0;31m
NO_COLOUR =\033[0m

CC = cc
MLX_LIB_PATH = utils/MLX42
LIBFT_LIB_PATH = utils/libft
LIBFT = $(LIBFT_LIB_PATH)/libft.a
MLX := $(MLX_LIB_PATH)/build/libmlx42.a
INC_DIRS := $(LIBFT_LIB_PATH) $(MLX_LIB_PATH)/include include
HEADERS = $(foreach dir, $(INC_DIRS), -I$(dir)) $(addprefix -I,$(SRCDIR))
LIBS = $(LIBFT) $(MLX)
NAME = cub3D

MAKEFLAGS += --no-print-directory
VALGRIND_FLAGS := --suppressions=MLX42.supp --track-fds=yes \
--leak-check=full --show-leak-kinds=all --track-origins=yes
GLFW_NAME := $(shell if [ ! -f /usr/local/lib/libglfw3.a ]; then echo "glfw"; \
else echo "glfw3"; fi)
CFLAGS = -Wall -Wextra -Werror -g -O3 $(HEADERS) #-fsanitize=address -v
LFLAGS := -ldl -l$(GLFW_NAME) -pthread -lm

MODULES := main parsing utils minimap shapes player raycasting pre_parsing \
textures
MAIN_SRCDIR := src
MAIN_OBJDIR := build
SRCDIR := $(addprefix $(MAIN_SRCDIR)/, $(MODULES))
OBJDIR := $(addprefix $(MAIN_OBJDIR)/, $(MODULES))
SRC_MAIN := $(addprefix main/, cub3d.c init.c struct_free.c drawing.c \
terminate.c)
SRC_PARSING := $(addprefix parsing/, get_next_line.c parsing.c \
find_file_contents.c rgba_parsing.c find_textures.c get_map.c )
SRC_PRE_PARSING := $(addprefix pre_parsing/,  pre_parse_prefix.c \
pre_parse_colors.c pre_parse_map.c pre_parse_utils.c pre_parse_crlf.c)
SRC_UTILS := $(addprefix utils/, basic_utils.c basic_utils2.c)
SRC_MINIMAP := $(addprefix minimap/, minimap_draw.c minimap_circle.c \
minimap_pad.c)
SRC_SHAPES :=  $(addprefix shapes/, rectangle.c draw_line.c draw_circle.c \
draw_line_utilities.c)
SRC_PLAYER := $(addprefix player/, movement.c player.c collision_detection.c \
move_angle.c)
SRC_RAYCASTING := $(addprefix raycasting/, cast_ray_all.c cast_ray.c \
cast_utilities.c cast_ray_helper.c)
SRC_TEXTURES := $(addprefix textures/, render_texture.c)
SRC := $(addprefix $(MAIN_SRCDIR)/, $(SRC_MAIN) $(SRC_PARSING) $(SRC_PRE_PARSING) \
$(SRC_UTILS) $(SRC_MINIMAP) $(SRC_SHAPES) $(SRC_PLAYER) \
$(SRC_TEXTURES) $(SRC_RAYCASTING))
OBJ := $(patsubst $(MAIN_SRCDIR)/%.c,$(MAIN_OBJDIR)/%.o, $(SRC))

.PHONY: all clean flcean re

all: $(NAME)

$(MAIN_OBJDIR):
	@mkdir $(MAIN_OBJDIR)

$(OBJDIR): | $(MAIN_OBJDIR)
	@mkdir -p $(OBJDIR)

$(OBJ): $(MAIN_OBJDIR)/%.o: $(MAIN_SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $(OBJ) $(LIBS) $(LFLAGS) -o $(NAME)
	@echo "${GREEN}BUILT PROGRAM${NO_COLOUR}"

$(LIBFT):
	@make -C $(LIBFT_LIB_PATH) all

$(MLX_LIB_PATH)/.git:
	git submodule init
	git submodule update

$(MLX): $(MLX_LIB_PATH)/.git
	@cmake $(MLX_LIB_PATH) -B $(MLX_LIB_PATH)/build && make -C \
	$(MLX_LIB_PATH)/build -j4

valgrind: $(NAME)
	valgrind $(VALGRIND_FLAGS) ./$(NAME) maps/valid/small.cub

clean:
	@echo "${RED}Cleaning ${NAME} object files...${NO_COLOUR}"
	@rm -rf $(OBJ)
	
fclean: clean
	@echo "${RED}Removing ${NAME}...${NO_COLOUR}"
	@rm -rf $(NAME)
	@make -C $(LIBFT_LIB_PATH) fclean
	@rm -rf $(MLX_LIB_PATH)/build

re: fclean all
