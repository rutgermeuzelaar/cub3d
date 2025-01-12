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
CFLAGS = -Wall -Wextra -Werror -g $(HEADERS) #-fsanitize=address -v
LFLAGS := -ldl -l$(GLFW_NAME) -pthread -lm

MODULES := main parsing utils minimap shapes player raycasting
MAIN_SRCDIR := src
MAIN_OBJDIR := build
SRCDIR := $(addprefix $(MAIN_SRCDIR)/, $(MODULES))
OBJDIR := $(addprefix $(MAIN_OBJDIR)/, $(MODULES))
SRC_MAIN := $(addprefix main/, cub3d.c init.c)
SRC_PARSING := $(addprefix parsing/, get_next_line.c parsing.c)
SRC_UTILS := $(addprefix utils/, basic_utils.c basic_utils2.c)
SRC_MINIMAP := $(addprefix minimap/, minimap_draw.c)
SRC_SHAPES :=  $(addprefix shapes/, rectangle.c draw_line.c draw_circle.c)
SRC_PLAYER := $(addprefix player/, movement.c player.c)
SRC_RAYCASTING := $(addprefix raycasting/, nearest_hit.c draw_rays.c)
SRC := $(addprefix $(MAIN_SRCDIR)/, $(SRC_MAIN) $(SRC_PARSING) \
$(SRC_UTILS) $(SRC_MINIMAP) $(SRC_SHAPES) $(SRC_PLAYER) $(SRC_RAYCASTING))
OBJ := $(patsubst $(MAIN_SRCDIR)/%.c,$(MAIN_OBJDIR)/%.o, $(SRC))

.PHONY: all clean flcean re MLX_LIB

all: $(NAME)

$(MAIN_OBJDIR):
	mkdir $(MAIN_OBJDIR)

$(OBJDIR): | $(MAIN_OBJDIR)
	mkdir -p $(OBJDIR)

$(OBJ): $(MAIN_OBJDIR)/%.o: $(MAIN_SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) $(LIBS) $(LFLAGS) -o $(NAME)
	@echo "${GREEN}BUILT PROGRAM${NO_COLOUR}"

$(LIBFT):
	@make -C $(LIBFT_LIB_PATH) all

$(MLX_LIB_PATH):
	git submodule init
	git submodule update

$(MLX): $(MLX_LIB_PATH)
	@cmake $(MLX_LIB_PATH) -B $(MLX_LIB_PATH)/build && make -C \
	$(MLX_LIB_PATH)/build -j4

valgrind: $(NAME)
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

clean:
	@echo "${RED}Cleaning ${NAME} object files...${NO_COLOUR}"
	@rm -rf $(OBJ)
	
fclean: clean
	@echo "${RED}Removing ${NAME}...${NO_COLOUR}"
	@rm -rf $(NAME)
	@make -C $(LIBFT_LIB_PATH) fclean
	@rm -rf $(MLX_LIB_PATH)/build

re: fclean all
