CFLAGS=-Wall -g

SRCS:=${wildcard *.c}
EXECS:=${SRCS:%.c=%}
OBJS:=${SRCS:%.c=%.o}

clean:
	rm -f ${EXECS} ${OBJS}

ex19: object.o
test:
	./test.sh
