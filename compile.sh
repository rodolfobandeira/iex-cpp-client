#!/bin/bash

echo "Starting compilation"

g++ -o main main.cpp -lcurl -ljsoncpp -std=c++11 ${CFLAGS} ${LDFLAGS}

echo "Done"

