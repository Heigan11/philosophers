NAME		= philo_three
SRCS		= philo_three.c philo_three_utils.c philo_three_utils_2.c\
			philo_three_utils_3.c
OBJS		= $(SRCS:.c=.o)
CFLAGS		= -Wall -Werror -Wextra -MMD
CC			= gcc

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc  -o $(NAME) $(OBJS)
			@echo ""
			@echo "▂▃▅▇█▓▒░ DONE ░▒▓█▇▅▃▂"
			@echo ""

-include	$(SRCS:.c=.d)

run:		$(NAME)
			./$(NAME)

clean:
			@ rm -f $(OBJS) $(SRCS:.c=.d)

fclean:		clean
			@ rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
