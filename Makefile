
# Makefile for project.


OBJS=./main.cpp ./data_generator.cpp ./get_info.cpp ./log.cpp
CFLAGS=-std=c++11 -Wall -Wwrite-strings -Wunused-variable
TARGET=usb2uart_mapping_tool
INCLUDES=-I./




all: clean build


build:
	g++  $(INCLUDES) $(OBJS) $(CFLAGS) -o $(TARGET) -pthread


.PHONY:clean
clean:
	rm -rf *.o *.log $(TARGET) || TRUE





