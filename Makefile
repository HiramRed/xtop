SHELL = /bin/sh

CC=cc
srcdir=.
CFLAGS=-O

# Extra libraries
LIBS=

OBJS=processes.o str.o main.o

.c.o:
	${CC} ${CFLAGS} -I${srcdir} -c $<

main: ${OBJS}
	${CC} ${CFLAGS} -o main ${OBJS} ${LIBS}

clean:
	rm -f main ${OBJS}

# Some header file dependencies that really ought to be automatically deduced.
processes.o: processes.h
str.o: str.h
