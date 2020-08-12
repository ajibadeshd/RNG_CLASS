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
After clonning this directory, the code can be compiled using g++ with the command:
    g++ -o rng_sample rng_sample.cpp

## CODE USAGE

The sample code, rng_sample.cpp, after compilation take command line argument(s) and can be used in two modes: Test mode and run mode

do [./rng_sample -h] to see the help string:       

USAGE:	-h [help]	Displays this help message
	-t [test mode] 	<test sample size> (An integer value)
	-r [run mode] 	<pimc_mt19937||std_mt19937||boost_mt19937||PCG>


    
## Test mode   
When used in test mode the code does speed test on all member functions from each RNGs

## Run mode
In run mode, with specified RNG, the code does an estimation of pi using the Monte Carlo Technique. When used in this mode, users have the leverage of loading the state of previously used RNG and saved data specific to their simulation. For illustration, we have chossed to save our data of interest as "PI_data.dat"


# NOTE
Users should be aware of the need to save neccesary data partinent to their own simulations if they intend to do a restart of the same simulation by modifying the test code to suit their need. An example of this is done for the estimation of pi. (see source code) 


# SOME RESULTS
## TEST MODE
    ./rng_sample -t 1000000

    These random numbers are from pimc_mt19937 

    *********************************
    TESTING WITH SAMPLE SIZE OF : 1000000 Random Numbers


    Time for rand : 		0.0062123s
    Time for randInt : 		0.00543594s
    Time for seeded_randInt : 	0.0269939s
    Time for randExc() : 		0.00529508s
    Time for seeded_randExc : 	0.00731224s
    Time for randDblExc : 		0.00612604s
    Time for seeded_randDblExc : 	0.00595221s
    Time for randNorm : 		0.0484477s
    TOTAL TIME FOR pimc_mt19937	0.112193s

    ##################################################

    These random numbers are from : std_mt19937
    *********************************
    TESTING WITH SAMPLE SIZE OF : 1000000 Random Numbers


    Time for rand : 		0.0147648s
    Time for randInt : 		0.0323796s
    Time for seeded_randInt : 	0.0308177s
    Time for randExc() : 		0.013847s
    Time for seeded_randExc : 	0.0144567s
    Time for randDblExc : 		0.0143309s
    Time for seeded_randDblExc : 	0.0169595s
    Time for randNorm : 		0.0442447s
    TOTAL TIME FOR std_mt19937	0.182003s

    ##################################################

    These random numbers are from : boost_mt19937
    *********************************
    TESTING WITH SAMPLE SIZE OF : 1000000 Random Numbers


    Time for rand : 		0.0121233s
    Time for randInt : 		0.0172277s
    Time for seeded_randInt : 	0.018304s
    Time for randExc() : 		0.010847s
    Time for seeded_randExc : 	0.00925956s
    Time for randDblExc : 		0.0132604s
    Time for seeded_randDblExc : 	0.0111977s
    Time for randNorm : 		0.0197577s
    TOTAL TIME FOR boost_mt19937	0.112185s


    These random numbers are from PCG: 
    *********************************
    TESTING WITH SAMPLE SIZE OF : 1000000 Random Numbers


    Time for rand : 		0.00756159s
    Time for randInt : 		0.0304582s
    Time for seeded_randInt : 	0.0296845s
    Time for randExc() : 		0.006636s
    Time for seeded_randExc : 	0.00640673s
    Time for randDblExc : 		0.0083306s
    Time for seeded_randDblExc : 	0.010872s
    Time for randNorm : 		0.0282037s
    TOTAL TIME FOR PCG		0.128343s

    ##################################################

## RUN MODE

    ./rng_sample -r boost_mt19937

    THIS CODE ESTIMATES PI USING THE MONTE CARLO TECHNIQUE

    Load a previously saved rng_state ?
    Y or N to proceed
    y

    LOADING RNG STATE OF A PREVIOUSLY SAVED SIMULATION ... 

    rng state data successfully loaded

    ATTEMPTING TO LOAD PREVIOUS PI_SIMULATION STAGE DATA ...

    simulation data file successfully loaded
     
    Enter sample count (MC sample points)
    1000000000

    ESTIMATED VALUE FOR PI IS : 3.14167

    RNG state file saved as (boost_mt19937_rng_state.dat )
    PI estimation data saved as (PI_data.dat)

