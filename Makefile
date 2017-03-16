all: lzwTools

lzwTools: main.cpp lzwTools.cpp lzwTools.h
	g++ main.cpp lzwTools.cpp lzwTools.h -W -Wall -O3