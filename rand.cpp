#include <iostream>
#include <random>
#include "pcg_random.hpp"
#include "RNG.h"

using namespace std;

int main(){

// HERE IS THE CORRECT WORKING STUFF   std::unique_ptr<RNG> randomPtr = std::unique_ptr<RNG> randomNumberGenerator(seed);
    uint32 seed = 139853;
   // std::unique_ptr<RNG>GetRNG(1) = randoom;
    //std::unique_ptr<RNG> randomPtr = GetRNG (  1  );
    //RNG random = GetRNGFromPtr ( *randomPtr );
    //RNG& random = *randomPtr;
    //std::unique_ptr<RNG> randomPtr ;
    //randomPtr = GetRNG (  1 , seed );
    //std::unique_ptr<RNG> randomPtr;
    
    //std::make_unique<MTFromPIMC>(seed);
    RNG random;
   
    std::unique_ptr<RNG> randomNumberGeneratorPtr;
    randomNumberGeneratorPtr = GetRNG (  1 , seed );
    //std::make_unique<MTFromSTL>(seed);
    //RNG random = GetRNGFromPtr ( *randomPtr );
    //RNG random = GetRNGFromPtr ( *randomPtr );
    //double x = random.rand();
    //random = GetRNGFromPtr ( *randomPtr );
    
    for (int i=1; i<10;i++){
    //cout<< random.rand();
    random = GetRNGFromPtr( *randomNumberGeneratorPtr);
    //cout << random.rand() << endl;
    cout << randomNumberGeneratorPtr->rand() << endl;
    }
return 0; }
