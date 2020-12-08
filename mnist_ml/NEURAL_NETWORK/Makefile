CC = g++
PROJECT_ROOT := $(shell pwd)
MNIST_ML_ROOT := $(PROJECT_ROOT)/..
SRC := $(PROJECT_ROOT)/SRC
INCLUDE_DIR := $(PROJECT_ROOT)/include
CFLAGS := -std=c++11


all:main

main : $(SRC)/layer.cc $(SRC)/network.cc $(SRC)/neuron.cc
	$(CC) $(CFLAGS) $(SRC)/layer.cc $(SRC)/network.cc $(SRC)/neuron.cc \
	-o main -L$(MNIST_ML_ROOT)/lib -ldata -I$(MNIST_ML_ROOT)/include -I$(INCLUDE_DIR)

clean:
	rm main