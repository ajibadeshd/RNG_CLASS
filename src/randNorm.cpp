#include "RNG.h"

inline std::unique_ptr<RNG> FAST_RANDNORM(){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("BOOST");
	return temp;
	};


inline std::unique_ptr<RNG> FAST_RANDNORM( uint32 seed){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("BOOST", seed);
	return temp;
	};
