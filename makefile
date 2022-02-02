# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 08:25:01 by abellakr          #+#    #+#              #
#    Updated: 2022/01/13 18:18:16 by abellakr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFlAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	make -C ./libft 
	gcc pipex.c ./libft/libft.a -o $(NAME)
bonus :
	make -C ./libft 
	gcc pipex_bonus.c ./libft/libft.a -o $(NAME)
clean :
	rm -rf $(NAME) 
	make clean -C ./libft
fclean : clean
	make fclean -C ./libft
re : fclean all bonus
	
.PHONY : clean fclean all re
