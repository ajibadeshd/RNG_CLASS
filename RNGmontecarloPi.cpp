#include <iostream>
#include <random>
#include "pcg_random.hpp"
#include "RNG.h"

using namespace std;

int main(){


    uint32 seed = 1234;
    std::unique_ptr<RNG> randomPtr = std::make_unique<PIMC>(seed);


    cout<< random.rand();

return 0; }
//std::unique_ptr<RNG> GetRNG( 1 )

//pcg32 ronaldo (time(0));
//mt19937 ronaldo(time(0));
//uniform_real_distribution<double> dis(0.0,1.0);

    //std::unique_ptr<RNG> randomPtr = GetRNG (  1 , seed );
    uint32 seed = 1234;
    std::unique_ptr<RNG> randomPtr = std::make_unique<PCG>(seed);

    // RNG random = GetRNGFromPtr ( *randomPtr );
   //RNG& random = *randomPtr;
    //RNG random = GetRNGFromPtr ( *randomPtr );
    //RNG& random = *randomPtr;
    
double x = 0.0, y = 0.0, det = 0.0, PI = 0.0, pi = 0.0,  ac = 0.0 , as = 0.0  ,total = 0.0 ;

/*
for (int i = 1; i < 500000 ; i++){    
    x = random.rand();
    y = random.rand();
    //x = random;
    //y = dis (ronaldo);
    //y = random;
    det = sqrt( x*x + y*y);
    
    
    if (det <= 1 ){ac = ac+1;}
    
    if (det > 1 ){as = as+1;}
    
    pi = (4 * ac) / (ac + as );
    total = total + pi ;
    
    //cout << pi <<endl;
    
    }

cout << "the mean of the estamated PI is : " << (total / 500000.0) << endl;
*/

cout<< random.rand();

return 0; }
