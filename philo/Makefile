NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c\
	  check_args.c\
	  init.c\
	  utils.c\
	  sim.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lpthread

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
