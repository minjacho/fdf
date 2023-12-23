.DEFAULT_GOAL := all
SRCS = err_handle.c fdf_main.c fdf_printer.c parse.c rotate.c input_read.c
SRCS_BONUS =
LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
MLX = -lmlx -framework OpenGL -framework AppKit
NAME = fdf
BONUS =
-include $(DEPS)

all :
	@echo "PUSH_SWAP : make $(NAME)"
	@make $(NAME)

bonus :
	@echo "PUSH_SWAP : make $(BONUS)"
	@make $(BONUS)

$(LIBFT) :
	@ echo "PUSH_SWAP : make $(LIBFT)"
	@ make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR) $(MLX) -L./mlx -Imlx

$(BONUS) : $(LIBFT) $(OBJS_BONUS)
	@$(CC) -o $(BONUS) $(OBJS_BONUS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR)

%.o : %.c
	@$(CC) -c $<  -I$(LIBFT_DIR) -Imlx

clean :
	@echo "PUSH_SWAP : make clean"
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean :
	@echo "PUSH_SWAP : make fclean"
	@rm -f $(OBJS) $(NAME) $(DEPS) $(OBJS_BONUS) $(BONUS) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) fclean

re : fclean
	@ echo "PUSH_SWAP : make re"
	@make all

.PHONY: all clean fclean re
