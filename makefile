CC = g++ -std=c++11 -pthread
CFLAGS = -g -Wall
SRCS = Node.cpp Peer.cpp main.cpp
PROG = p2pstreaming

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS) 
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)