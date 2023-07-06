LIBS=-lpthread -L ./CommandParser/ -lcli
CC=gcc
CFLAGS=-g

TARGET:maincli

OBJS=comm.o \
		 graph.o \
		 net.o \
		 nwcli.o \
		 topology.o\
		 utils.o \
		 glthread.o

GL_OBJS=glthread.o

maincli: maincli.o ${OBJS} CommandParser/libcli.a
	${CC} ${CFLAGS} maincli.o ${OBJS} ${LIBS} -o maincli

maincli.o:maincli.c
	${CC} ${CFLAGS} -c -I . maincli.c -o maincli.o

topo_test:topo_test.o ${OBJS}
	${CC} ${CFLAGS} topo_test.o ${OBJS} -o topo_test

topo_test.o:topo_test.c
	${CC} ${CFLAGS} -c topo_test.c -o topo_test.o

glthread.o:glthread.c
	${CC} ${CFLAGS} -c -I . glthread.c -o glthread.o

glthread_test:glthread_test.o glthread.o
	${CC} ${CFLAGS} glthread_test.o glthread.o -o glthread_test

glthread_test.o:glthread_test.c
	${CC} ${CFLAGS} -c -I . glthread_test.c -o glthread_test.o

comm.o: comm.c
	${CC} ${CFLAGS} -c -I . comm.c -o comm.o

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

nwcli.o:nwcli.c
	${CC} ${CFLAGS} -c -I . nwcli.c -o nwcli.o

CommandParser/libcli.a:
	${MAKE} -C CommandParser libcli.a

clean:
	${MAKE} -C CommandParser clean
	rm maincli
	rm *.o
	rm *_test
	rm CMD_HIST_RECORD_FILE.txt
