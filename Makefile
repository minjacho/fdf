.DEFAULT_GOAL := all
SRCS = \
		fdf_err_handle.c fdf_main.c fdf_printer.c\
		fdf_parse.c fdf_rotate.c fdf_input_read.c \
		fdf_key_hook.c fdf_mlx.c
SRCS_BONUS = \
		fdf_err_handle_bonus.c fdf_main_bonus.c fdf_printer_bonus.c\
		fdf_parse_bonus.c fdf_rotate_bonus.c fdf_input_read_bonus.c \
		fdf_key_hook_bonus.c fdf_mlx_bonus.c
LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP
MLX = -lmlx -framework OpenGL -framework AppKit
NAME = fdf
MANDA = .manda
BONUS = .bonus
-include $(DEPS)

all :
	@echo "FDF : make $(NAME)"
	@make $(MANDA)

bonus :
	@echo "FDF : make BONUS"
	@make $(BONUS)

$(LIBFT) :
	@ echo "FDF : make $(LIBFT)"
	@ make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	@make $(MANDA)

$(MANDA) : $(LIBFT) $(OBJS)
	@rm -rf $(BONUS)
	@touch $(MANDA)
	@$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR) $(MLX)

$(BONUS) : $(LIBFT) $(OBJS_BONUS)
	@rm -rf $(MANDA)
	@touch $(BONUS)
	@$(CC) -o $(NAME) $(OBJS_BONUS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR) $(MLX)

%.o : %.c
	@$(CC) -c $<  -I$(LIBFT_DIR)

clean :
	@echo "FDF : make clean"
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean :
	@echo "FDF : make fclean"
	@rm -f $(OBJS) $(NAME) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) fclean

re : fclean
	@ echo "FDF : make re"
	@make all

.PHONY: all clean fclean re
