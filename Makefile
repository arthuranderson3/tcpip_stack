CC=gcc
CFLAGS=-g
TARGET:topo_test libtcpip_stack.a

SRC=graph.c \
		net.c \
		topology.c \
		utils.c \
		gluethread/glthread.c

OBJS=graph.o \
		 net.o \
		 topology.o\
		 utils.o \
		 gluethread/glthread.o

GL_OBJS=gluethread/glthread.o

libtcpipstack.a: ${OBJS}
	ar rs libtcpipstack.a ${OBJS}

topo_test:topo_test.o ${OBJS}
	${CC} ${CFLAGS} topo_test.o ${OBJS} -o topo_test

topo_test.o:topo_test.c
	${CC} ${CFLAGS} -c topo_test.c -o topo_test.o

gluethread/glthread.o:gluethread/glthread.c
	${CC} ${CFLAGS} -c -I gluethread gluethread/glthread.c -o gluethread/glthread.o

glthread_test:gluethread/glthread_test.o gluethread/glthread.o
	${CC} ${CFLAGS} gluethread/glthread_test.o gluethread/glthread.o -o glthread_test

gluethread/glthread_test.o:gluethread/glthread_test.c
	${CC} ${CFLAGS} -c -I gluethread gluethread/glthread_test.c -o gluethread/glthread_test.o

graph.o:graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o

net.o:net.c
	${CC} ${CFLAGS} -c -I . net.c -o net.o

utils.o:utils.c
	${CC} ${CFLAGS} -c -I . utils.c -o utils.o

utils_test:utils_test.o utils.o
	${CC} ${CFLAGS} utils_test.o utils.o -o utils_test

utils_test.o:utils_test.c
	${CC} ${CFLAGS} -c -I . utils_test.c -o utils_test.o

topology.o:topology.c
	${CC} ${CFLAGS} -c -I . topology.c -o topology.o

clean:
	rm ${OBJS}
	rm libtcpipstack.a
	rm *_test
	rm *_test.o
	rm gluethread/glthread_test.o
