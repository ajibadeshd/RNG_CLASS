#include "RNG.h"

inline std::unique_ptr<RNG> FAST_RANDINT(){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("PCG");
	return temp;
	};


inline std::unique_ptr<RNG> FAST_RANDINT( uint32 seed){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("PCG", seed);
	return temp;
	};
