#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: semartin <semartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/12 12:35:21 by semartin          #+#    #+#              #
#    Updated: 2016/04/11 15:58:47 by semartin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
SRC_DIR = ./srcs/
SRC = ft_pixel_put_to_image.c ft_build_wolf.c ft_wolf3d.c ft_map.c \
		ft_key_event.c ft_error.c ft_math_wolf.c ft_wall.c ft_menu.c \
		ft_raycasting.c
VPATH = $(SRC_DIR)
OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))
O_DIR = ./objs
LIB = libft 

all : $(NAME)

$(NAME): $(OBJ)
	@echo "Making library."
	@make -C libft/
	@echo "Library made."
	@echo "Making exe."
	@gcc -o $(NAME) -Werror -Wextra -Wall -lmlx \
		-framework OpenGL -framework AppKit -I includes/ $(OBJ) -L libft/ -lft
	@echo "Exe made."

$(O_DIR)/%.o: %.c
	@cp libft/include/libft.h includes
	@mkdir -p $(O_DIR)
	@gcc -Wall -Werror -Wextra -ferror-limit=2 -I includes -o $@ -c $<

clean:
	@echo "Removing objets."
	@rm -f $(OBJ)
	@echo "Clean done."

fclean: clean
	@echo "Removing exe."
	@rm -f $(NAME)
	@echo "Fclean done."

re: fclean all

.PHONY: all clean fclean re