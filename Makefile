# *********************************** Colors ***********************************
NC				:= \033[m
RED				:= \033[0;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[0;34m
PURPLE			:= \033[1;35m
CYAN			:= \033[1;36m

ILIB	=	-I /usr/include
SLIB	=	-lreadline


# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
LIBFT_DIR		:= $(LIB_DIR)/libft

# *********************************** Files ************************************
NAME			:= minishell
SRC				:= $(shell ls $(SRC_DIR))
OBJ				:= $(SRC:.c=.o)
INC				:= minishell.h
LIBFT			:= libft.a
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))
LIBFT_INC		:= libft.h

# ********** Compiler Options **********
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g #-fsanitize=address
#-fsanitize=address
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) $(ILIB)
LIBFLAGS		:= $(LIBFT_DIR)/$(LIBFT)

# *********** Other commands ***********
RM				:= rm -rf
MKDIR			:= mkdir -vp

# *********** Dependencies ***********
OBJ_DEP			:= $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)

# ************ Targets *************
all: $(NAME)

$(NAME): $(OBJ_DEP) $(INC_DEP) $(LIBFT_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_DEP) $(LIBFLAGS) $(SLIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(LIBFT_DEP): $(LIBFT_SRC_DEP) $(LIBFT_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(LIBFT)$(NC)"
	@> /dev/null make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Removing$(BLUE)	$(LIBFT)Object files$(NC)"
	@> /dev/null make clean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@> /dev/null $(RM) $(OBJ_DIR) $(OBJ)

fclean: clean
	@echo "$(RED)Removing	$(BLUE)$(LIBFT)$(NC)"
	@> /dev/null make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@> /dev/null $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re