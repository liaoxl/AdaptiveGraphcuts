#
# Makefile
# moondark, 2014-04-22 21:13
#

CC=g++
CFLAGS=-g -w `pkg-config opencv --libs --cflags opencv`
all:\
	AdaptiveGraphcuts

AdaptiveGraphcuts: \
	MultiLayerGraph/graph.cpp \
	MultiLayerGraph/maxflow.cpp \
	MultiLayerGraph/multilayergraph.cpp \
	adaptivegraphcuts.cpp \
	main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm AdaptiveGraphcuts


# vim:ft=make
#

