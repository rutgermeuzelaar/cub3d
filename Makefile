GREEN =\033[0;32m
RED = \033[0;31m
NO_COLOUR =\033[0m

MAKEFLAGS += --no-print-directory

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -v

SRC = src/main/cub3d.c \
	src/parsing/get_next_line.c \
	src/parsing/parsing.c \
	src/utils/basic_utils.c \

CC = cc
OBJ = $(SRC:.c=.o)
MLX_LIB = ./utils/MLX42
LIBFT_LIB = utils/libft
LIBFT = $(LIBFT_LIB)/libft.a
HEADERS = -I ./include -I $(MLX_LIB)/include
LIBS = $(MLX_LIB)/build/libmlx42.a -ldl -lglfw -pthread -lm
NAME = cub3D


.PHONY: all clean flcean re MLX_LIB

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	@make -C $(LIBFT_LIB) all
	@cmake $(MLX_LIB) -B $(MLX_LIB)/build && make -C $(MLX_LIB)/build -j4
	@$(CC) $(OBJ) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "${GREEN}BUILT PROGRAM${NO_COLOUR}"

all: $(NAME)

clean:
	@echo "${RED}Cleaning ${NAME} object files...${NO_COLOUR}"
	@rm -rf $(OBJ)
	@rm -rf $(MLX_LIB)/build
	@make -C $(LIBFT_LIB) silent_clean
	

fclean: clean
	@echo "${RED}Removing ${NAME}...${NO_COLOUR}"
	@rm -rf $(NAME)
	@make -C $(LIBFT_LIB) fclean

re: fclean all