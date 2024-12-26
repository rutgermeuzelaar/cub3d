GREEN =\033[0;32m
RED = \033[0;31m
NO_COLOUR =\033[0m

MAKEFLAGS += --no-print-directory
VALGRIND_FLAGS := --suppressions=readline.supp --track-fds=yes \
--leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -v
LFLAGS :=
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
CC = cc
MLX_LIB = ./utils/MLX42
LIBFT_LIB = utils/libft
LIBFT = $(LIBFT_LIB)/libft.a
INC_DIRS := $(LIBFT_LIB)/include $(MLX_LIB)/include include
HEADERS = $(foreach dir, $(INC_DIRS), -I$(dir)) $(addprefix -I,$(SRCDIR))
LIBS = $(MLX_LIB)/build/libmlx42.a -ldl -lglfw3 -pthread -lm
NAME = cub3D

.PHONY: all clean flcean re MLX_LIB

all: $(NAME)

$(MAIN_OBJDIR):
	mkdir $(MAIN_OBJDIR)

$(OBJDIR): | $(MAIN_OBJDIR)
	mkdir -p $(OBJDIR)

$(OBJ): $(MAIN_OBJDIR)/%.o: $(MAIN_SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(HEADERS)

$(NAME): $(OBJ)
	@make -C $(LIBFT_LIB) all
	@cmake $(MLX_LIB) -B $(MLX_LIB)/build && make -C $(MLX_LIB)/build -j4
	$(CC) $(OBJ) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "${GREEN}BUILT PROGRAM${NO_COLOUR}"

clean:
	@echo "${RED}Cleaning ${NAME} object files...${NO_COLOUR}"
	@rm -rf $(OBJ)
	
fclean: clean
	@echo "${RED}Removing ${NAME}...${NO_COLOUR}"
	@rm -rf $(NAME)
	@make -C $(LIBFT_LIB) fclean
	@rm -rf $(MLX_LIB)/build

re: fclean all
