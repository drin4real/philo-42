PHILO_PATH = ./srcs/mandatory
BONUS_PATH = ./srcs/bonus

SRCS = ${addprefix ${PHILO_PATH}/, main.c \
									philo_utils.c}
# SRCS_B = ${addprefix ${BONUS_PATH}/,}

OBJS = ${SRCS:.c=.o}
# OBJS_B = ${SRCS_B:.c=.o}

NAME = philo
BONUS = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
INCLUDES = -Iincludes

all : ${NAME}

# bonus : ${BONUS}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

# ${BONUS} : ${LIBFT} ${OBJS_B}
# 	${CC} ${CFLAGS} -o ${BONUS} ${OBJS_B}

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
clean:
	@${RM} ${OBJS} ${OBJS_B}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${RM} ${NAME} ${BONUS}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re