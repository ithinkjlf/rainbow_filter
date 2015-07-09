CC=g++
FLAGS=`pkg-config --libs --cflags opencv`
CXX11=-std=c++0x

app: main.cc
	${CC} -o app ${FLAGS} ${CXX11} main.cc

clean: 
	rm app
