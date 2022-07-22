# *********************************** Colors ***********************************
NC				:= \033[m
RED				:= \033[0;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[0;34m
PURPLE			:= \033[1;35m
CYAN			:= \033[1;36m

# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib

# *********************************** Files ************************************
NAME			:= minishell
SRC				:= $(shell ls $(SRC_DIR))
OBJ				:= $(SRC:.c=.o)
INC				:= $(shell ls $(INC_DIR))
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR)

# ******************************* Other commands *******************************
RM				:= rm -rf
MKDIR			:= mkdir -p

# ******************************** Dependencies ********************************
OBJ_DEP			:= $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)/libft.h

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ_DEP) $(INC_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_DEP) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

clean:
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
