/*######################  UsageExample.cpp  #########################
#																	#
#  This cpp file explains the useage of all the method of the RNG	#
#  class. We illustrate this using the the classic example of the	#
#  Monte-carlo technique for the estimation of PI					#
#																	#
####################################################################*/


// Including our source codes
#include "RNG.cpp" // Always needed
#include "rand.cpp"
#include "randInt.cpp"
#include "randExp.cpp"
#include "randNorm.cpp"
#include "randBernoulli.cpp"
//   NOTE: Only RNG.cpp in always needed. Others, i.e randInt, randExp e.t.c
//	 are depends on the only included to illustrate their usage.
//   RNG.cpp is always needed. 


int main(){
	
	//user-defined seed
	uint32 _seed = 139853;

	//  Pointers for each class members (seeded)
	std::unique_ptr<RNG> RAND; 
	std::unique_ptr<RNG> RANDINT;
	std::unique_ptr<RNG> RANDEXP;
	std::unique_ptr<RNG> RANDNORM;
	std::unique_ptr<RNG> RANDBERNOULLI;
	
	//  Object Instantiations
	RAND = FAST_RAND( _seed);// Uniform distribution in the range [0, 1]
	RANDINT = FAST_RANDINT( _seed);// Uniform distribution in the range [0, 2^(32) -1]
	RANDEXP = FAST_RANDEXP( _seed); //Exponential distribution 
	RANDNORM = FAST_RANDNORM( _seed); //Gaussian distribution
	RANDBERNOULLI = FAST_RANDBERNOULLI( _seed); //Bernoulli (Coin flip) distribution
	
	//#############################################################################
	
	
	//  Pointers for each class members (unseeded)
	std::unique_ptr<RNG> RANDINT_unseeded;
	std::unique_ptr<RNG> RANDEXP_unseeded;
	std::unique_ptr<RNG> RANDNORM_unseeded;
	std::unique_ptr<RNG> RANDBERNOULLI_unseeded;

	// Same as above, but unseeded.
	RAND_unseeded = FAST_RAND(); 
	RANDINT_unseeded = FAST_RANDINT();
	RANDEXP_unseeded = FAST_RANDEXP();
	RANDNORM_unseeded = FAST_RANDNORM();
	RANDBERNOULLI_unseeded = FAST_RANDBERNOULLI();
	
	//Alternatively previously unseeded objects can be seeded at any stage as follows:
	RANDNORM_unseeded->seed( _seed);
	// Now RANDNORM_unseeded is actually seeded !
	
	
	
	
	//#############################################################################
	//########### To save the state of an RNG object ################
	// Open a state file
	ofstream myfile;
	myfile.open (state_file_name);
	// This is how we save the RNG state:
	myfile<<RAND->save().str();
	// CLose the state file
	myfile.close();
	//**********************************************************
	
	
	//########### To load the state of an RNG object ################
	ifstream myfile;
	myfile.open (file_name);
	// This is how we load the RNG state:
	RAND->load(myfile);
	// CLose the state file
	myfile.close();
	//#############################################################################
	
	
    for (int i = 0; i < 10; i++){
        RAND->rand();
        RANDINT->randInt(10);
        RANDEXP->randExp(3.5);
        RANDNORM->randNorm(0.5, 4.2);
        RANDBERNOULLI->randBernoulli(0.2);
    	std::cout<<RAND->rand()<<std::endl;
    	std::cout<<RANDINT->randInt(10)<<std::endl;
    	std::cout<<RANDEXP->randExp(3.5)<<std::endl;
        std::cout<<RANDNORM->randNorm(0.5, 4.2)<<std::endl;
    	std::cout<<RANDBERNOULLI->randBernoulli(0.2)<<std::endl;
    	//std::cout<<"#############\n";
    	//std::cout<<RAND_unseeded->rand()<<std::endl;
    	//std::cout<<RANDINT_unseeded->randInt(10)<<std::endl;
    	//std::cout<<RANDEXP_unseeded->randExp(3.5)<<std::endl;
    	//std::cout<<RANDNORM_unseeded->randNorm(0.5, 4.2)<<std::endl;
    	//std::cout<<RANDBERNOULLI_unseeded->randBernoulli(0.2)<<std::endl;
    	//std::cout<<"********************************\n";
    	
    	}
    	
    return 0;}
