#include "RNG.h"

inline std::unique_ptr<RNG> FAST_RAND(){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("PCG");
	return temp;
	};


inline std::unique_ptr<RNG> FAST_RAND( uint32 seed){
	std::unique_ptr<RNG> temp;
	temp = GetRNG("PCG", seed);
	return temp;
	};
