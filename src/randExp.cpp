#include "RNG.h"

inline std::unique_ptr<RNG> FAST_RANDEXP(){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("BOOST");
	return temp;
	};


inline std::unique_ptr<RNG> FAST_RANDEXP( uint32 seed){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("BOOST", seed);
	return temp;
	};
