#include "RNG.cpp"
#include "rand.cpp"
#include "randInt.cpp"
#include "randExp.cpp"
#include "randNorm.cpp"
#include "randBernouli.cpp"

int main(){

	uint32 seed = 139853;
	std::unique_ptr<RNG> RAND;
	std::unique_ptr<RNG> RANDINT;
	std::unique_ptr<RNG> RANDEXP;
	std::unique_ptr<RNG> RANDNORM;
	std::unique_ptr<RNG> RANDBERNOULI;
	
	std::unique_ptr<RNG> RAND_unseeded;
	std::unique_ptr<RNG> RANDINT_unseeded;
	std::unique_ptr<RNG> RANDEXP_unseeded;
	std::unique_ptr<RNG> RANDNORM_unseeded;
	std::unique_ptr<RNG> RANDBERNOULI_unseeded;
	
	RAND = FAST_RAND( seed);
	RANDINT = FAST_RANDINT( seed);
	RANDEXP = FAST_RANDEXP( seed);
	RANDNORM = FAST_RANDNORM(seed );
	RANDBERNOULI = FAST_RANDBERNOULI(seed );
	
	RAND_unseeded = FAST_RAND( );
	RANDINT_unseeded = FAST_RANDINT( );
	RANDEXP_unseeded = FAST_RANDEXP( );
	RANDNORM_unseeded = FAST_RANDNORM( );
	RANDBERNOULI_unseeded = FAST_RANDBERNOULI( );
	
	//pipe->seed( seed);
	/*std::unique_ptr<RNG> standard;
	std::unique_ptr<RNG> boost;
	std::unique_ptr<RNG> pcg;
	
	std::unique_ptr<RNG> pimc_seed;
	std::unique_ptr<RNG> standard_seed;
	std::unique_ptr<RNG> boost_seed;
	std::unique_ptr<RNG> pcg_seed;
	
    pimc = GetRNG("PIMC");
    standard = GetRNG("STL");
    boost = GetRNG("BOOST");
    pcg = GetRNG("PCG");
    
    //pimc_seed = GetRNG ( "PIMC", seed);
    standard_seed = GetRNG ("STL", seed);
    boost_seed = GetRNG ( "BOOST", seed);
    pcg_seed = GetRNG ( "PCG", seed);
    
    
    pimc->seed(seed);
    */

    for (int i = 0; i < 100000000 ; i++){
        RAND->rand();
        RANDINT->randInt(10);
        RANDEXP->randExp(3.5);
        RANDNORM->randNorm(0.5, 4.2);
        RANDBERNOULI->randBernouli(0.2);
    	//std::cout<<RAND->rand()<<std::endl;
    	//std::cout<<RANDINT->randInt(10)<<std::endl;
    	//std::cout<<RANDEXP->randExp(3.5)<<std::endl;
        //std::cout<<RANDNORM->randNorm(0.5, 4.2)<<std::endl;
    	//std::cout<<RANDBERNOULI->randBernouli(0.2)<<std::endl;
    	//std::cout<<"#############\n";
    	//std::cout<<RAND_unseeded->rand()<<std::endl;
    	//std::cout<<RANDINT_unseeded->randInt(10)<<std::endl;
    	//std::cout<<RANDEXP_unseeded->randExp(3.5)<<std::endl;
    	//std::cout<<RANDNORM_unseeded->randNorm(0.5, 4.2)<<std::endl;
    	//std::cout<<RANDBERNOULI_unseeded->randBernouli(0.2)<<std::endl;
    	//std::cout<<"********************************\n";
    	
    	}
    	
    return 0;}
