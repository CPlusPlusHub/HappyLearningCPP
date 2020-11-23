CC = g++
MNIST_ML_ROOT := /Users/e1ixir/vscodeProject/MLC/mnist_ml
SRC := $(MNIST_ML_ROOT)/KNN/src
INLUCDE_DIR := $(MNIST_ML_ROOT)/KNN/include
CFLAGS := -std=c++11 -D EUCLID

all : main

main : $(SRC)/knn.cc
	$(CC) $(CFLAGS) $(SRC)/knn.cc -o main -L$(MNIST_ML_ROOT)/lib/ \
	-I$(MNIST_ML_ROOT)/include -ldata -I$(INLUCDE_DIR)

clean :
	rm main