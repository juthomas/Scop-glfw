NAME = scop
CC = gcc

COLOR = \0033[1;35m

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)libft/includes/ $(LIB_PATH)glfw/include/ \

GCC_FLGS = -g #-Werror -Wextra -Wall
GCC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo 

SRC_NAME = main.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft glfw/src

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;30m[All OK]\0033[1;37m"


$(NAME): $(OBJ)
	@make -C $(LIB_PATH)libft -j
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@# make -C $(LIB_PATH)libmat -j
	@$(CC) $(GCC_FLGS) $(LIB) -lft $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<
	@echo "$(COLOR)Compiled :\033[100D\033[40C\0033[1;32m$(@:$(OBJ_PATH)/%=%)\0033[1;37m"
	

clean:
	@rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"


fclean: clean
	@make -C $(LIB_PATH)libft fclean
	@echo "$(COLOR)$(LIB_PATH)libft \033[100D\033[40C\0033[1;31m[Cleaned]\0033[1;37m"
	@# make -C $(LIB_PATH)libmat fclean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"


re: fclean all
