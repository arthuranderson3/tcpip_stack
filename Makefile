CC=gcc
CFLAGS=-g
TARGET:topo_test

OBJS=gluethread/glthread.o \
		  graph.o 		   \
		  topology.o

topo_test:topo_test.o ${OBJS}
	${CC} ${CFLAGS} topo_test.o ${OBJS} -o topo_test

topo_test.o:topo_test.c
	${CC} ${CFLAGS} -c topo_test.c -o topo_test.o

gluethread/glthread.o:gluethread/glthread.c
	${CC} ${CFLAGS} -c -I gluethread gluethread/glthread.c -o gluethread/glthread.o
graph.o:graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o
topology.o:topology.c
	${CC} ${CFLAGS} -c -I . topology.c -o topology.o

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *_test
