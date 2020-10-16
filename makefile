## Name of Project

NAME = scop

## Color for compiling (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs
LIBFT_DIR = lib/libft
FRMWK_DIR = frameworks

## Compilating Utilities
LIB_PATH = ./lib/
LIB_NAME = libft glfw/src

LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

FAST = -Ofast
# DEBUG = -fsanitize=address -g3
FLAGS =$(FAST) $(DEBUG) -g
INC = $(INC_DIR:%=-I./$(LIBFT_DIR)/%) $(INC_DIR:%=-I./%)
CC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo
# LIB = -L$(LIB_DIR) -L glfw/src -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo



INC_FRMWK = -D_THREAD_SAFE -F ./$(FRMWK_DIR)
HOME =  $(shell pwd)/Frameworks
# FRMWK = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -F ./$(FRMWK_DIR) -rpath $(HOME)



CC = clang $(FLAGS)

## List of Functions


SRC_FT = main \

## List of Utilities

SRC = $(SRC_FT:%=$(SRC_DIR)/%.c) \


OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS = 

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;30m[All OK]\0033[1;37m"




$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(INC_FRMWK) -c $< -o $@
	# @echo "$(COLOR)Compiled :\t\0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[1;37m"

$(OBJ_DIRS):
	# @mkdir -p $@
	# @echo "$(COLOR)Creating :\t\0033[0;32m$@\0033[1;37m"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(INC_FRMWK) -c $< -o $@
	@echo "$(COLOR)Compiled :\033[100D\033[40C\0033[1;32m$(@:$(OBJ_DIR)/%=%)\0033[1;37m"

$(NAME): $(OBJ_DIRS) $(SRC) $(INCLUDES)

	@mkdir -p ./$(OBJ_DIR)
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@make -j -C $(LIBFT_DIR)
	@$(CC) $(LIB) $(FRMWK) $(OBJ) $(GCC_LIBS) -o $@
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/
	@make norme -C $(LIBFT_DIR)

frameworks_clean:
	@rm -rf ./$(FRMWK_DIR)
	@echo "$(COLOR)$(FRMWK_DIR) \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"


frameworks: frameworks_clean
	@mkdir ./$(FRMWK_DIR)

	@#https://www.libsdl.org/release/
	@echo "$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;36m[Downloading]\0033[1;37m"
	@curl -o SDL2 https://www.libsdl.org/release/SDL2-2.0.8.dmg --silent
	@echo "\033[A\033[K$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;32m[Downloaded]\0033[1;37m"

	@#https://www.libsdl.org/projects/SDL_image/release/
	@echo "$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;36m[Downloading]\0033[1;37m"
	@curl -o SDL2_image https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.dmg --silent
	@echo "\033[A\033[K$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;32m[Downloaded]\0033[1;37m"

	@#https://www.libsdl.org/projects/SDL_ttf/release/
	@echo "$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;36m[Downloading]\0033[1;37m"
	@curl -o SDL2_ttf https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg --silent
	@echo "\033[A\033[K$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;32m[Downloaded]\0033[1;37m"
	

	@echo "$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;36m[Attaching]\0033[1;37m"
	@hdiutil attach SDL2 -quiet
	@echo "\033[A\033[K$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;32m[Attached]\0033[1;37m"

	@echo "$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;36m[Attaching]\0033[1;37m"
	@hdiutil attach SDL2_image -quiet
	@echo "\033[A\033[K$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;32m[Attached]\0033[1;37m"


	@echo "$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;36m[Attaching]\0033[1;37m"
	@hdiutil attach SDL2_ttf -quiet
	@echo "\033[A\033[K$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;32m[Attached]\0033[1;37m"


	@cp -rf /Volumes/SDL2/SDL2.framework ./$(FRMWK_DIR)
	@echo "$(COLOR)SDL2.framework \033[100D\033[40C\0033[1;32m[Imported]\0033[1;37m"

	@cp -rf /Volumes/SDL2_image/SDL2_image.framework ./$(FRMWK_DIR)
	@echo "$(COLOR)SDL2_image.framework \033[100D\033[40C\0033[1;32m[Imported]\0033[1;37m"
	
	@cp -rf /Volumes/SDL2_ttf/SDL2_ttf.framework ./$(FRMWK_DIR)
	@echo "$(COLOR)SDL2_ttf.framework \033[100D\033[40C\0033[1;32m[Imported]\0033[1;37m"

	@hdiutil detach /Volumes/SDL2 -quiet
	@echo "$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;32m[Detached]\0033[1;37m"
	@hdiutil detach /Volumes/SDL2_image -quiet
	@echo "$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;32m[Detached]\0033[1;37m"
	@hdiutil detach /Volumes/SDL2_ttf -quiet
	@echo "$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;32m[Detached]\0033[1;37m"
	@rm -rf SDL2
	@echo "$(COLOR)SDL2.dmg \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"
	@rm -rf SDL2_image
	@echo "$(COLOR)SDL2_image.dmg \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"
	@rm -rf SDL2_ttf
	@echo "$(COLOR)SDL2_ttf.dmg \033[100D\033[40C\0033[1;31m[Deleted]\0033[1;37m"




coffee: frameworks all
	@echo ""
	@echo "         {"
	@echo "      {   }"
	@echo "       }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "    \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "   \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "   \0033[1;34m| -.._____..- |"
	@echo "   |             ;--."
	@echo "   |            (__  \ "
	@echo "   |             | )  )"
	@echo "   |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "   |             /  / "
	@echo "   |            (  / "
	@echo "   \             | "
	@echo "     -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3CTake Your Coffee"
	@echo "\0033[1;37m"


cleanAll: fclean frameworks_clean

.PHONY: all clean fclean re norme frameworks frameworks_clean coffee cleanAll