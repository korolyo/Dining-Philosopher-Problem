
NAME	=	philo

SOURCES_LIST	= 	main.c\
					philo_util.c\
					check_argv.c\

CC		= gcc
CFLAGS	=	-Werror -Wall -Wextra

INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST = \
				philo.h

HEADERS_DIR	=	./includes/
HEADERS =	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

OBJECTS	=	$(patsubst %.c, %.o, $(SOURCES_LIST))

.PHONY:	all clean fclean re

all	: 	$(NAME)

$(NAME): $(OBJECTS)
		@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
		@rm -f $(OBJECTS)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all