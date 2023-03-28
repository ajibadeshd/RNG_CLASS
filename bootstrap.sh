#!/bin/bash

#Remove old redundant files
rm -rf speed_test pcg* RNG.* MersenneTwister.h rng_sample.cpp 
sleep 1
echo ""
echo "Downloading and setting up PCG"
echo ""
sleep 1
wget https://www.pcg-random.org/downloads/pcg-cpp-0.98.zip
unzip pcg-cpp-0.98.zip
mkdir include/pcg
cp pcg-cpp-0.98/include/* include/pcg
rm -rf pcg-cpp-0.98*
echo ""
echo ""

# Get Boost
echo "Downloading and setting up BOOST"
echo ""
sleep 1
wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
tar -xf boost_1_81_0.tar.gz
cp -r boost_1_81_0/boost include/
rm -rf boost_1_81_0*
echo ""

echo "COMPLETED"
echo ""
echo "Now generating additional source codes......"
echo ''
sleep 3
g++ -o  SETUP/test_speed.e  SETUP/speed_test.cpp -I include
SETUP/test_speed.e -t 10000000 >  SETUP/no_optimization.dat
sleep 1

g++ -o  SETUP/test_speed.e  SETUP/speed_test.cpp -I include -O1 
SETUP/test_speed.e -t 10000000 >  SETUP/O1_optimization.dat
sleep 1

g++ -o  SETUP/test_speed.e  SETUP/speed_test.cpp -I include -O2
SETUP/test_speed.e -t 10000000 >  SETUP/O2_optimization.dat
sleep 1

g++ -o  SETUP/test_speed.e  SETUP/speed_test.cpp -I include -O3 
SETUP/test_speed.e -t 10000000 >  SETUP/O3_optimization.dat
sleep 1

lscpu | grep "Model name" >  SETUP/system.info
hostnamectl | grep "Operating\|Kernel" >>  SETUP/system.info

python SETUP/generate_source.py
echo ''
echo ''
g++ -o example/Monter-Carlo-pi/estimate_pi.e  example/Monter-Carlo-pi/Monte-Carlo-pi.cpp -I include -O3

echo '******************************************************'
echo '      RNG LIBRARY SETUP SUCCESSFULLY COMPLETED'
echo '******************************************************'

