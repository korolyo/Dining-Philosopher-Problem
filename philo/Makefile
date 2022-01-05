
NAME	=	philo

SOURCES_LIST	= 	main.c\
					philo_util.c\
					check_argv.c\
					messaging.c\
					monitor.c\
					actions.c\

CC		= gcc
CFLAGS	=	-Werror -Wall -Wextra -g
LIBS	= 	-pthread

INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST = \
				philo.h

HEADERS_DIR	=	./includes/
HEADERS =	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

OBJECTS	=	$(patsubst %.c, %.o, $(SOURCES_LIST))

.PHONY:	all clean fclean re

all	: 	$(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJECTS) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
		@rm -f $(OBJECTS)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all
