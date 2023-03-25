#!/bin/bash

g++ -o speed_test/test_speed.e speed_test/speed_test.cpp -I include
sleep 1
./speed_test/test_speed.e -t 10000000 > speed_test/no_optimization.dat
sleep 1

g++ -o speed_test/test_speed.e speed_test/speed_test.cpp -I include -O1 
sleep 1
./speed_test/test_speed.e -t 10000000 > speed_test/O1_optimization.dat
sleep 1

g++ -o speed_test/test_speed.e speed_test/speed_test.cpp -I include -O2
sleep 1
./speed_test/test_speed.e -t 10000000 > speed_test/O2_optimization.dat
sleep 1

g++ -o speed_test/test_speed.e speed_test/speed_test.cpp -I include -O3 
sleep 1
./speed_test/test_speed.e -t 10000000 > speed_test/O3_optimization.dat
sleep 1

lscpu | grep "Model name" > speed_test/system.info
hostnamectl | grep "Operating\|Kernel" >> speed_test/system.info
