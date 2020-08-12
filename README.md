# RNG_CLASS

A collection of codes for generating random numbers from disparring Random Number Generators (RNGs) sources, all integrated into one RNG CLASS.
This class also allows for the saving and loading of states of any of the RNGs which creates room for continuation of simulations, at some later time, without having to start all over again.

The different RNGs implemented in this class are:

    Boost.Random ( https://www.boost.org/doc/libs/1_66_0/doc/html/boost_random.html )
    
    C++ standard library Mersenne Twister ( https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine )
    
    PCG ( https://www.pcg-random.org/index.html ) Header only.
    
    A header only Mersenne Twister by  Makoto Matsumoto ( http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html )
    
While these are the four RNGs used in this project for our RNG class, its implementation allows for easy addition of other RNGs if so desired ( check source codes ).


#INTSTALLATION, COMPILATION AND USAGE

The 



# EXAMPLE CODE USAGE

The sample code, rng_sample.cpp, can be used in two modes:
    Test mode
    Run mode
## Test mode   
When used in test mode the code does speed test on all the member functions from each RNGs

## Run mode
In run mode with any RNG specified by the user, the code does an estimation of pi using the Monte Carlo Technique. When used in this mode, users have the leverage of saving and loading of the state of any of the RNGs.

# NOTE
Users should be aware of the need to save neccesary data partinent to their own simulations if they intend to do a restart of the same simulation by modifying the test code to suit their need. An example of this is done for the estimation of pi. (see source code) 


