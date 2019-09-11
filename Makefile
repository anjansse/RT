# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/09/10 19:13:54 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	RTv1

GENERAL		= 	RT.c

SRCS		=	$(addprefix src/, $(GENERAL))

INCLUDES	=	-I inc/

CC			=	gcc

MINILIBX	=	-L Minilibx/minilibx_macos -lmlx -framework OpenGL -framework AppKit

SDL			=	-I SDL/include/SDL2 -L SDL/lib -l SDL2-2.0.0

DEBUG		=	-g -fsanitize=undefined -fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror $(MINILIBX)

LLIB		=	libft.a

reprog: fclean all

all: $(NAME)

$(NAME):
	@echo -n 'Compiling FDF Program...'
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) $(LLIB) -o $(NAME)
	@echo "\t\x1b[92m✓✓\x1b[0m\n"

lib:
	@echo -n 'Compiling libft...'
	@make -C libft/ re
	@cp libft/libft.a .
	@echo "\t\t\x1b[92m✓\x1b[0m\n"

totall: lib all

git:
	@git add .
	@git commit -m "$(C)"
	@git push

clean:
	@rm -rf build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LLIB)
	@echo "\t\n\x1b[96mFDF \x1b[91mlibrary has been cleaned!\x1b[0m\n"

totfclean: fclean
	@make -C libft/ fclean
	@echo "\x1b[96mLibft has been cleaned.\x1b[0m\t\x1b[91mDon't forget to\
		recompile it...\n\x1b[0m"

re: totfclean totall

tot: totfclean totall
