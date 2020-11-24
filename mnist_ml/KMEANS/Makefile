CC = g++
MNIST_ML_ROOT := /Users/e1ixir/vscodeProject/MLC/mnist_ml
SRC := $(MNIST_ML_ROOT)/KMEANS/src
INLUCDE_DIR := $(MNIST_ML_ROOT)/KMEANS/include
CFLAGS := -std=c++11 

all: main

main : $(SRC)/kmeans.cc
	$(CC) $(CFLAGS) $(SRC)/kmeans.cc -o main -L$(MNIST_ML_ROOT)/lib/ \
	-I$(MNIST_ML_ROOT)/include -ldata -I$(INLUCDE_DIR)

clean:
	rm main