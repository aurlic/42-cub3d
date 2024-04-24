# **************************************************************************** #
#                                    PROGRAM                                   #
# **************************************************************************** #

NAME		:=	cub3d

# **************************************************************************** #
#                                     UTILS                                    #
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-g3 -Wall -Wextra -Werror
DEP_FLAGS	:=	-MMD -MP
RM			:=	rm -rf
MLX_FLAGS	:=	-lX11 -lXext

# **************************************************************************** #
#                                  DIRECTORIES                                 #
# **************************************************************************** #

SRCS_DIR 	:=	src
PARSER_DIR	:=	parser
RAYCAST_DIR	:=	raycasting
DISPLAY_DIR	:=	display
CORE_DIR	:=	core
EVENTS_DIR	:=	events
INCLD_DIR 	:=	includes
OBJS_DIR 	:=	objs
LIBFT_DIR	:=	libft
LIBFT_PATH	:=	src/libft
MLX_PATH	:=	minilibx-linux

# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #

NEW			:=	\r\033[K
DEFAULT		:=	\033[0m
BLACK		:=	\033[0;30m
WHITE		:=	\033[0;37m
RED			:=	\033[0;31m
NEON_RED	:=	\033[38;5;196m
GREEN		:=	\033[0;32m
U_GREEN		:=	\033[4;32m
NEON_GREEN	:=	\033[38;5;82m
YELLOW		:=	\033[0;33m
BLUE		:=	\033[0;34m
PURPLE		:=	\033[0;35m
CYAN		:=	\033[0;36m
BOLD		:=	\033[1m
ITALIC		:=	\033[3m

# **************************************************************************** #
#                                    SOURCES                                   #
# **************************************************************************** #

# INCLUDES #
define	INC	:=
				$(INCLD_DIR)/
				$(LIBFT_DIR)/$(INCLD_DIR)/
endef
INCLUDES	:=	$(strip $(INC))
INCLD_FLAG	:=	$(addprefix -I , $(INCLUDES))

# LIBFT #
LIBFT		:=	$(SRCS_DIR)/$(LIBFT_DIR)/libft.a
define	LIB	:=
				$(LIBFT)
				$(LDFLAGS)
endef
LIB			:=	$(strip $(LIB))

# MLX #
MLX			:=	$(MLX_PATH)/libmlx.a

# SOURCES #
define	SRC	:=	
				$(addprefix $(PARSER_DIR)/, \
					parser.c \
					parse_input.c \
					parse_content.c \
					parse_textures.c \
					parse_colors.c \
					remove_newlines.c \
					check_map.c \
					format_map.c \
				)
				$(addprefix $(CORE_DIR)/, \
					main.c \
					init.c \
					init_structs.c \
					error.c \
				)
				$(addprefix $(RAYCAST_DIR)/, \
					raycasting.c \
					handle_frame.c \
					position.c \
					dda.c \
					texture_view.c \
				)
				$(addprefix $(DISPLAY_DIR)/, \
					textures.c \
					display.c \
				)
				$(addprefix $(EVENTS_DIR)/, \
					handle_events.c \
					movement.c \
				)

endef
SRC			:=	$(strip $(SRC))

OBJS 		:=	$(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS		:=	$(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))


# **************************************************************************** #
#                                     RULES                                    #
# **************************************************************************** #

all:	$(NAME)

$(MLX):
		@printf "\n\r\033[K[cub3d 🧊] \033[4;32mBuilding minilibx: $<\033[0m\n"
		@make -sC $(MLX_PATH)
		@printf "\n"

$(LIBFT):
	@printf "$(NEW)[libft 📖] $(U_GREEN)Building libft: $<$(DEFAULT)\n"
	@make -C $(LIBFT_PATH)
	@printf "\n"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@printf "\r\033[K[cub3d 🧊] \033[4;32mBuilding cub3d: $<\033[0m"
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME) -lm
	@printf "\r\033[K[cub3d 🧊] \033[0;32mDone!\033[0m\n"

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@printf "$(NEW)[cub3d 🧊] $(U_GREEN)Building:$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(CORE_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSER_DIR)
	@mkdir -p $(OBJS_DIR)/$(RAYCAST_DIR)
	@mkdir -p $(OBJS_DIR)/$(DISPLAY_DIR)
	@mkdir -p $(OBJS_DIR)/$(EVENTS_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

clean:
	@printf "[cub3d 🧊] $(RED)Cleaning $(LIBFT_PATH)$(DEFAULT)\n"
	@make clean -sC $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[cub3d 🧊] $(RED)Cleaning .o$(DEFAULT)\n"
	@$(RM) $(OBJS_DIR)
	@printf "[cub3d 🧊] $(RED)Cleaned objects!$(DEFAULT)\n"

fclean: clean
	@printf "[cub3d 🧊] \033[0;31mDeleting cub3d executable\033[0m\n"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[cub3d 🧊] \033[1;32mDone\033[0m\n\n"

re: fclean all

.PHONY: all clean fclean re