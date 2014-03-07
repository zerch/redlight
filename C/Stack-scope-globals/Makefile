CFLAGS=-Wall -g

SRCS:=${wildcard *.c}
EXECS:=${SRCS:%.c=%}
OBJS:=${SRCS:%.c=%.o}

clean:
	rm -f ${EXECS} ${OBJS}

ex22_main: ex22.o
