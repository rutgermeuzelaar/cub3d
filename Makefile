GREEN =\033[0;32m
RED = \033[0;31m
NO_COLOUR =\033[0m

CC = cc
MLX_LIB_PATH = utils/MLX42
LIBFT_LIB_PATH = utils/libft
LIBFT = $(LIBFT_LIB_PATH)/libft.a
MLX := $(MLX_LIB_PATH)/build/libmlx42.a
INC_DIRS := $(LIBFT_LIB_PATH)/include $(MLX_LIB_PATH)/include include
HEADERS = $(foreach dir, $(INC_DIRS), -I$(dir)) $(addprefix -I,$(SRCDIR))
LIBS = $(LIBFT) $(MLX)
NAME = cub3D

MAKEFLAGS += --no-print-directory
VALGRIND_FLAGS := --suppressions=MLX42.supp --track-fds=yes \
--leak-check=full --show-leak-kinds=all --track-origins=yes
CFLAGS = -Wall -Wextra -Werror -g $(HEADERS) #-fsanitize=address -v
LFLAGS := -ldl -lglfw3 -pthread -lm

MODULES := main parsing utils
MAIN_SRCDIR := src
MAIN_OBJDIR := build
SRCDIR := $(addprefix $(MAIN_SRCDIR)/, $(MODULES))
OBJDIR := $(addprefix $(MAIN_OBJDIR)/, $(MODULES))
SRC_MAIN := $(addprefix main/, cub3d.c)
SRC_PARSING := $(addprefix parsing/, get_next_line.c parsing.c)
SRC_UTILS := $(addprefix utils/, basic_utils.c)
SRC := $(addprefix $(MAIN_SRCDIR)/, $(SRC_MAIN) $(SRC_PARSING) \
$(SRC_UTILS))
OBJ := $(patsubst $(MAIN_SRCDIR)/%.c,$(MAIN_OBJDIR)/%.o, $(SRC))

.PHONY: all clean flcean re MLX_LIB

all: $(NAME)

$(MAIN_OBJDIR):
	mkdir $(MAIN_OBJDIR)

$(OBJDIR): | $(MAIN_OBJDIR)
	mkdir -p $(OBJDIR)

$(OBJ): $(MAIN_OBJDIR)/%.o: $(MAIN_SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(HEADERS)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) $(LIBS) $(LFLAGS) -o $(NAME)
	@echo "${GREEN}BUILT PROGRAM${NO_COLOUR}"

$(LIBFT):
	@make -C $(LIBFT_LIB_PATH) all

$(MLX):
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
