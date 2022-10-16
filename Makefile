# *********************************** Colors ***********************************
NC				:= \033[m
RED				:= \033[0;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[0;34m
PURPLE			:= \033[1;35m
CYAN			:= \033[1;36m
ILIB	=	-I$(shell brew --prefix readline)/include -Ilibft/inc
SLIB	=	-L$(shell brew --prefix readline)/lib -lreadline -lncurses

# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
LIBFT_DIR		:= $(LIB_DIR)/libft

# *********************************** Files ************************************
NAME			:= minishell
SRC				:= allocation.c  ast_add.c ast_tools.c builting.c check.c close_all.c copy_token.c ctrl_handler.c env_fonction.c env_tools.c execut_blocks.c execut_redirection.c execut_tools.c execution.c expand_heredoc.c expander.c expander_tools.c free_data.c free_env.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_free.c ft_pwd.c ft_unset.c get_cmd.c here_doc.c here_doc_fon.c init_data.c is_check.c main.c minishell.c parc_cmd.c parc_heredoc.c parc_redirection.c parc_type.c print_err.c scanner.c token.c token_set.c update.c wait.c wildcard.c wildcard_tools.c check_helper.c

OBJ				:= $(SRC:.c=.o)
INC				:= data.h mini_signal.h minishell.h parsing.h tokenization.h

LIBFT			:= libft.a
LIBFT_SRC		:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

LIBFT_INC		:= libft.h

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR)
LIBFLAGS		:= -L $(LIBFT_DIR) -lft

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

$(NAME): $(OBJ_DEP) $(INC_DEP) $(LIBFT_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(SLIB) $(LIBFLAGS) $(OBJ_DEP) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(ILIB) $(INCFLAGS) -c -o $@ $<

$(LIBFT_DEP): $(LIBFT_SRC_DEP) $(LIBFT_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(LIBFT)$(NC)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Removing$(BLUE)	$(LIBFT)Object files$(NC)"
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing	$(BLUE)$(LIBFT)$(NC)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

