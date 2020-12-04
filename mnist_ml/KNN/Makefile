CC = g++
PROJECT_ROOT := $(shell pwd)
MNIST_ML_ROOT := $(PROJECT_ROOT)/..
SRC := $(PROJECT_ROOT)/src
INLUCDE_DIR := $(PROJECT_ROOT)/include
CFLAGS := -std=c++11 -D EUCLID

all : main

main : $(SRC)/knn.cc
	$(CC) $(CFLAGS) $(SRC)/knn.cc -o main -L$(MNIST_ML_ROOT)/lib/ \
	-I$(MNIST_ML_ROOT)/include -ldata -I$(INLUCDE_DIR)

clean :
	rm main