OBJS_DIR	= bin
SRCS_DIR 	= srcs
INCL_DIR	= includes
LIBFT_DIR	= libft
MLX_DIR		= mlx

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra
INCLUDES	= -I$(INCL_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

HEAD_NAME	= miniRT.h
HEADERS		:= $(patsubst %.h, $(INCL_DIR)/%.h, $(HEAD_NAME))

SRCS_NAME	= miniRT.c conf.c camera.c vector.c
SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(SRCS_NAME))
OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

NAME		= miniRT

#-------------------------------------------------------------------------------------------------#


all:				update $(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

update:				
					@make -sC $(LIBFT_DIR)
					@make -sC $(MLX_DIR)

#-------------------------------------------------------------------------------------------------#

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(LIBFT) $(HEADERS) | bin
					$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -c

bin:				
					mkdir -p $@

#-------------------------------------------------------------------------------------------------#

norm:
					@norminette $(LIBFT_DIR)
					@norminette $(INCL_DIR)
					@norminette $(SRCS_DIR)

leaks:				
					leaks --atExit -- ./$(NAME)

re:					fclean all

clean:
					@make -sC $(LIBFT_DIR) clean
					@echo "cleaned libft"
					$(RM) $(OBJS)

fclean:				clean
					@make -sC $(LIBFT_DIR) fclean
					@echo "fcleaned libft"
					$(RM) $(NAME)

.PHONY:				all clean fclean re update leaks
