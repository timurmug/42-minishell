# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 08:04:23 by qtamaril          #+#    #+#              #
#    Updated: 2020/10/11 11:54:03 by fkathryn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

HEADER = get_next_line.h

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:%.c=%.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@ar rc $(NAME) $(OBJS)

%.o: %.c
	gcc -c -Wall -Wextra -Werror -D BUFFER_SIZE=32 -o $@ $<

clean:
	rm -rf *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
