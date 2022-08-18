CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g

# ******************************* Other commands *******************************
RM		:= rm -rf
AR		:= ar rcs
MKDIR	:= mkdir -p

# ******************************** Directories *********************************
INCLUDES_DIR	:= include
SRCS_DIR		:= src
LIBS_DIR		:= lib
OBJS_DIR		:= obj

# *********************************** Colors ***********************************
NC		:= '\033[0m'
GREEN	:= '\033[32m'
RED		:= '\033[0;31m'
BLUE	:= '\033[0;34m'

# *********************************** Files ************************************
NAME	:=	libft.a
SRCS	:=	$(shell ls $(SRCS_DIR))
OBJS	:=	$(SRCS:.c=.o)
HEADER	:=	libft.h

# ********************************** Targets ***********************************
all:	$(NAME)

$(NAME):	$(addprefix $(OBJS_DIR)/, $(OBJS))
	@echo "Archiving" $(BLUE) $(NAME) $(NC)
	@$(AR) $(NAME) $?

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(INCLUDES_DIR)/$(HEADER)
	@$(MKDIR) -p $(OBJS_DIR)
	@echo "Compiling" $(GREEN) $(basename $(shell basename $<)) $(NC)
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c -o $@ $<

clean:
	@echo "Removing" $(RED) "object files" $(NC)
	@$(RM) $(OBJS_DIR)

fclean:	clean
	@echo "Removing" $(RED) $(NAME) $(NC)
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re