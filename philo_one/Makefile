NAME		= philo_one
SRCS		= philo_one.c philo_one_utils.c philo_one_utils_2.c\
			philo_one_utils_3.c
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
