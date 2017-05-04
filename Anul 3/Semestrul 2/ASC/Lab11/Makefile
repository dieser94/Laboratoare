CC=g++

CFLAGS=-g -Wall -std=c++11 -D FEP_OPENCL
LIB=-L/usr/local/cuda-8.0/lib64/
BUILDDIR = ./build/

all: $(BUILDDIR)/lab11_bin

$(BUILDDIR)/lab11_bin: skl_host.cpp helper.cpp
	$(CC) $(CFLAGS) $(INC) $(LIB) skl_host.cpp helper.cpp -lOpenCL -o $(BUILDDIR)/lab11_bin
	cp skl_device.cl $(BUILDDIR)/

clean:
	rm -f $(BUILDDIR)/lab11_bin
