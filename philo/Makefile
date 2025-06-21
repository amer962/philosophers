NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c\
	  check_args.c\
	  init.c\
	  utils.c\
	  sim.c\
	  routine.c\
	  utils_sim.c\
	  death_eat.c

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
