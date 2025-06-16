# ************************************************************************ #
#                			        MAIN                                   #
# ************************************************************************ #

NAME 		= Cub3D

# ************************************************************************ #
#                			     DIRECTORIES                               #
# ************************************************************************ #

INCLUDES_CUB	= includes
INCLUDES_LIB	= libft/includes
MLX_DIR			= minilibx-linux
GNL_DIR			= get_next_line
LIBFT_DIR		= libft
SRCS_DIR		= src
OBJS_DIR		= obj

# ************************************************************************ #
#                			 SRCS && OBJECTS FILES                         #
# ************************************************************************ #

CUB3D			= 	$(addprefix $(SRCS_DIR)/, main.c\
					parsing/enclosure_check.c\
					parsing/map_colors.c\
					parsing/map_textures.c\
					parsing/map_validation.c\
					parsing/open_map.c\
					parsing/parser_utils1.c\
					parsing/parser_utils2.c\
					bonus/minimap_draw1.c\
					bonus/minimap_draw2.c\
					bonus/minimap_rays.c\
					bonus/mouse_event.c\
					raycasting/init_rays.c\
					raycasting/raycasting.c\
					rendering/draw_wall.c\
					rendering/render_walls1.c\
					rendering/render_walls2.c\
					rendering/put_texture.c\
					rendering/load_texture.c\
					game_base/init_game.c\
					game_base/free_everything.c\
					game_base/keys_hook.c\
					game_base/movements.c)

SRCS			= ${CUB3D}
CUB3D_OBJS		= ${CUB3D:${SRCS_DIR}/%.c=$(OBJS_DIR)/%.o}
OBJS			= $(CUB3D_OBJS) $(GNL_OBJS) 
LIBFT 			= -L$(LIBFT_DIR) -lft

GNL 			= $(addprefix $(GNL_DIR)/, get_next_line_utils.c\
					get_next_line.c)

GNL_OBJS 		= ${GNL:$(GNL_DIR)/%.c=$(OBJS_DIR)/%.o}

# ************************************************************************ #
#                    			 COMPILATION                               #
# ************************************************************************ #

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3 -I$(INCLUDES_CUB) -I$(INCLUDES_LIB)
MLX_PATH    = minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_PATH) -lXext -lX11 -lm -lz
RM          = rm -rf

# ************************************************************************ #
#                  		       	 PROCESS                                   #
# ************************************************************************ #

all: $(NAME)

$(MLX_LIB):
	@echo "\033[1;33m\n🔨 COMPILING MINILIBX... 🔨\n"
	@$(MAKE) -C $(MLX_PATH) -s
	@echo "\033[1;32m💾 MINILIBX COMPILED 💾\n"

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_LIB)
	@echo "\033[1;33m🧊  COMPILING CUB3D... 🧊\n"
	$(CC) $(OBJS) $(CFLAGS) $(MLX_FLAGS) $(MLX_LIB) $(LIBFT) -o $(NAME)
	@echo "\033[1;32m💾 ./$(NAME) created 💾\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# ************************************************************************ #
#                          LIBFT COMPILATION                               #
# ************************************************************************ #

$(LIBFT_DIR)/libft.a:
	@echo "\033[1;33m\n🔨 COMPILING LIBFT... 🔨\n"
	@$(MAKE) -C $(LIBFT_DIR) -s
	@echo "\033[1;32m💾 LIBFT COMPILED 💾\n"

# ************************************************************************ #
#                  		     CLEANUP SESSION                               #
# ************************************************************************ #

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) -s
	@echo "\033[1;32m🫧  DONE 🫧"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) -s
	@echo "\033[1;32m🫧  DONE 🫧"

re: fclean all
	@echo "\033[1;32m🫧  RE DONE 🫧"

.PHONY: all clean fclean re

# ************************************************************************ #
#                  	        	     COLORS                                #
# ************************************************************************ #

COLOR_RESET = \033[0m

# Regular Colors
COLOR_BLACK = \033[0;30m
COLOR_RED = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_MAGENTA = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_WHITE = \033[0;37m

# Bright Colors
COLOR_BLACKB = \033[1;30m
COLOR_REDB = \033[1;31m
COLOR_GREENB = \033[1;32m
COLOR_YELLOWB = \033[1;33m
COLOR_BLUEB = \033[1;34m
COLOR_MAGENTAB = \033[1;35m
COLOR_CYANB = \033[1;36m
COLOR_WHITEB = \033[1;37m

# Additional Styles
COLOR_BOLD = \033[1m
COLOR_DIM = \033[2m
COLOR_ITALIC = \033[3m
COLOR_UNDERLINE = \033[4m
COLOR_BLINK = \033[5m
COLOR_REVERSE = \033[7m
COLOR_HIDDEN = \033[8m