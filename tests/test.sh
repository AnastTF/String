#!/bin/bash
g++ test.cpp -o test -lgtest -lgmock -pthread
./test

