SRC_DIR = ./sources_files
OBJ_DIR = ./objects_files
INC_DIR = ./includes
BT_DIR = ./builtins

INCLUDES = $(wildcard $(INC_DIR)/*)
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

BT_SRCS = $(wildcard $(BT_DIR)/*.c)
BT_OBJ = $(BT_SRCS:.c=)

RM = rm -f
NAME = minishell
LIB = $(INC_DIR)/libft/libft.a
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
AUTHOR = babreton - babreton@student.42perpignan.fr

.PHONY: all clean fclean re table

all: $(NAME) ${LIB} builtins

$(BT_DIR)/%: $(BT_DIR)/%.c ${LIB}
	@$(CC) $(CFLAGS) $< -L$(INC_DIR)/libft -lft -o $@
	@echo "\033[32m[✓] $@ succesfully compiled\033[0m"

builtins: $(BT_OBJ)

${LIB}:
	@echo "$(GREEN)Compiling libft : $(NC)"
	@make -s -C $(INC_DIR)/libft/ all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) ${LIB}
	@$(CC) $(CFLAGS) $(OBJ) -L$(INC_DIR)/libft -lft -lreadline -o $(NAME)
	@echo "\033[32m[✓] minishell succesfully compiled\033[0m"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -s -C $(INC_DIR)/libft/ clean

fclean: clean
	@$(RM) $(NAME) $(BT_OBJ)
	@make -s -C $(INC_DIR)/libft/ fclean

re: fclean all
