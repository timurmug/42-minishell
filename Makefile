# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 15:03:36 by qtamaril          #+#    #+#              #
#    Updated: 2020/09/29 17:09:51 by qtamaril         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_A =	libft/libft.a

INCLUDE = includes/minishell.h

FLAGS_W = -Wall -Wextra -Werror
FLAGS_LIB = -Iincludes

DIR_SRCS = srcs
DIR_LIB = libft

SRCS = srcs/main.c
OBJS = $(SRCS:%.c=%.o)

.PHONY: all clean fclean re norme run

all: $(NAME)

$(NAME): $(INCLUDE) $(OBJS)
	@make -C $(DIR_LIB)
	@make bonus -C $(DIR_LIB)
	gcc $(FLAGS_W) $(LIB_A) $(OBJS) -o $(NAME)
	./$(NAME)

norme:
	@make fclean
	@echo
	norminette includes/
	@echo
	norminette ./$(DIR_LIB)/
	@echo
	norminette ./$(DIR_SRCS)

%.o: %.c
	gcc -c $(FLAGS_LIB) $(FLAGS_W) -o $@ $<

clean:
	rm -rf $(OBJS)
	@make -C $(DIR_LIB) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(DIR_LIB) fclean

re: fclean all
