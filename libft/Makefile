# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 09:51:04 by anjansse          #+#    #+#              #
#    Updated: 2019/12/14 17:11:07 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
RM			= rm -rf
NAMELIB		= libft.a
CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I includes/

IS			= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
			  ft_verifstr.c

STRUCT		= ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
			  ft_lstnew.c

MEMORY		= ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memcpy.c ft_memcmp.c\
			  ft_memchr.c ft_memdel.c ft_memmove.c ft_memset.c \
			  ft_memtransform.c ft_free_db_tab.c

NUMBER		= ft_atoi.c ft_itoa.c ft_stoi.c ft_stof.c

PRINT		= ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putendl.c\
			  ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c\
			  send_error.c ft_rgb.c

STRING		= ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c\
			  ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c\
			  ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c\
			  ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c\
			  ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c\
			  ft_strtrim.c ft_swap.c ft_capitalize.c ft_iswhitespace.c\
			  ft_range.c ft_strclen.c ft_strappend.c ft_strjoinfree.c\
			  ft_strjoinfree1.c ft_strjoinfree2.c ft_array_len.c

CHAR		= ft_tolower.c ft_toupper.c skip_ws.c

READ_FILE	= read_file.c

GNL			= get_next_line.c

PRINTF		= ft_printf.c check.c handle.c keys.c main_check.c manage.c\
			  parse.c manage_dsc.c manage_pf.c manage_uox.c ftoa.c ft_iitoa.c\
			  ft_itoa_base.c pf_functions.c pf_functions2.c pf_functions3.c

VECTOR		= vec_add.c vec_new.c vec_rotx.c vec_roty.c vec_rotz.c vec_sub.c\
			  vec_scale.c vec_rotxyz.c vec_set.c vec_normalize.c\
			  vec_cross_product.c vec_dot_product.c vec_magnitude.c\
			  vec_abs.c

FUNCTIONS	= $(IS) $(STRUCT) $(MEMORY) $(NUMBER) $(PRINT) $(STRING) $(CHAR)\
			  $(READ_FILE)

FILES		= $(addprefix srcs/, $(FUNCTIONS))\
			  $(addprefix srcs/, $(addprefix gnl/, $(GNL)))\
			  $(addprefix srcs/, $(addprefix printf/, $(PRINTF)))\
			  $(addprefix srcs/, $(addprefix vector/, $(VECTOR)))\

OBJECTS		= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAMELIB)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAMELIB): $(OBJECTS)
	@ar rc $(NAMELIB) $(OBJECTS)
	@ranlib $(NAMELIB)

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAMELIB)

re: fclean all
