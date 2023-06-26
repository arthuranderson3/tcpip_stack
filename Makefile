CC=gcc
CFLAGS=-g
TARGET:topo_test

OBJS=gluethread/glthread.o \
		  graph.o 		   \
			net.o 				 \
		  topology.o

GL_OBJS=gluethread/glthread.o

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

topology.o:topology.c
	${CC} ${CFLAGS} -c -I . topology.c -o topology.o

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *_test