GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS =	src/main.c

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $@
	@echo "$(PINK)꒰ᐢ. .ᐢ꒱$(DEF_COLOR) philosophers compiled successfully!"

clean:
	@$(MAKE) clean -sC $(LIBFT_DIR)

fclean: clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "$(YELLOW)✧･ﾟ:* ꒰ᐢ. .ᐢ꒱ :ﾟ･✧$(DEF_COLOR) philosophers cleaned!"

re: fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push
	
.PHONY: all clean fclean re