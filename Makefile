# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/11/26 11:16:30 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	RT

MAIN			=	RT.c main_loop.c

STORE			=	store_objects.c store_cam.c store_light.c store_sphere.c\
					store_plane.c store_cone.c store_cyclinder.c

PARSER			=	parser.c

RAY_INTERSEC	=	intersection_plane.c intersection_sphere.c intersection_dispatch.c

RAY_INFO		=	ray_info_light.c ray_info_primary.c ray_info_refraction.c\
					ray_info_reflection.c

RAY_CAST		=	cast_rays.c dispatch_rays.c

EXTRA_FUNC		=	extra.c matrix.c color.c threads.c

GENERAL			=	$(addprefix store/, $(STORE)) $(addprefix ray_intersections/, $(RAY_INTERSEC))\
					$(addprefix ray_info/, $(RAY_INFO)) $(MAIN) $(PARSER) $(RAY_CAST) $(EXTRA_FUNC)

SRCS			=	$(addprefix src/, $(GENERAL))

INCLUDES		=	-I inc/

CC				=	gcc

MINILIBX		=	-L Minilibx/minilibx_macos -lmlx -framework OpenGL -framework AppKit

SDL				=	-I SDL2/include/ -L SDL2/lib -l SDL2-2.0.0


DEBUG			=	-g -fsanitize=undefined -fsanitize=address

OPTI			=	-O2

PROFILER		=	-g -pg

NUKLEAR			=	-I nuklear/

CFLAGS			=	-Wall -Wextra -Werror $(SDL) $(DEBUG)

LLIB			=	libft.a

reprog: fclean all

all: $(NAME)

$(NAME):
	@echo -n 'Compiling RT...'
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) $(LLIB) -o $(NAME)
	@echo "\t\t\x1b[92m✓✓\x1b[0m\n"

lib:
	@echo -n 'Compiling libft...'
	@make -C libft/ re
	@cp libft/libft.a .
	@echo "\t\x1b[92m✓\x1b[0m\n"

totall: lib all

sdl_install:
	@brew install sdl2
	@brew switch sdl2 2.0.10
	@clear
	@echo -n 'Adapting SDL to your computer...'
	@rm -rf SDL2/include/*
	@rm -rf SDL2/lib/*
	@cp -R ~/.brew/Cellar/sdl2/2.0.10/include/SDL2/* SDL2/include/
	@cp -R ~/.brew/Cellar/sdl2/2.0.10/lib/* SDL2/lib/
	@echo "\t\x1b[92mDone\x1b[0m\n"
	@sleep 0.3
	@clear

sdl:
	@echo -n 'Adapting SDL to your computer...'
	@rm -rf SDL2/include/*
	@rm -rf SDL2/lib/*
	@cp -R ~/.brew/Cellar/sdl2/2.0.10/include/SDL2/* SDL2/include/
	@cp -R ~/.brew/Cellar/sdl2/2.0.10/lib/* SDL2/lib/
	@echo "\t\x1b[92mDone\x1b[0m\n"
	@sleep 0.3
	@clear

git:
	@git add .
	@git commit -m "$(C)"
	@git push

clean:
	@rm -rf build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LLIB)
	@rm -rf RT.dSYM
	@echo "\t\n\x1b[96mRT \x1b[91mlibrary has been cleaned!\x1b[0m\n"

totfclean: fclean
	@make -C libft/ fclean
	@echo "\x1b[96mLibft has been cleaned.\x1b[0m\t\x1b[91mDon't forget to\
	 recompile it...\n\x1b[0m"

re: totfclean totall
	@sleep 0.1
	@clear

tot: totfclean totall
