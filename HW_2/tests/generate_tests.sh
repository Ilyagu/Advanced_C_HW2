#!/usr/bin/env bash

g++ -std=c++11 generate_matrix.cpp -o generator
./generator size_10 10
./generator size_100 100
./generator size_200 200
./generator size_500 500
./generator size_600 600
./generator size_1000 1000
./generator size_2000 2000
./generator size_5000 5000
./generator size_10000 10000

./generator size_20 20
./generator size_30 30
./generator size_40 40
./generator size_50 50
./generator size_60 60