#include <iostream>
#include <random>
#include "pcg_random.hpp"
#include "RNG.h"
#include <chrono>
#include <string>
#include "RNG.cpp"

using namespace std;



void select_rng( int type ,  uint32 seed){
    std::unique_ptr<RNG> randomNumberGeneratorPtr;
    randomNumberGeneratorPtr = GetRNG ((type ), seed);
    
    
        //cout<<randomNumberGeneratorPtr->rand()<<endl;
        
        
        auto start_rand = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->rand();
                }
        auto end_rand = std::chrono::steady_clock::now();
        std::chrono::duration<double> rand_elapsed_seconds = end_rand-start_rand;
        cout<<"Time for rand : \t"<<rand_elapsed_seconds.count()<< "s\n";
           
            
            
        auto start_randInt = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randInt();
                }
        auto end_randInt = std::chrono::steady_clock::now();
        std::chrono::duration<double> randInt_elapsed_seconds = end_randInt-start_randInt;
        cout<<"Time for randInt : \t"<<randInt_elapsed_seconds.count()<< "s\n";
           
            
            
        auto start_seeded_randInt = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randInt(seed);
                }
        auto end_seeded_randInt = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randInt_elapsed_seconds = end_seeded_randInt-start_seeded_randInt;
        cout<<"Time for seeded_randInt : \t"<<seeded_randInt_elapsed_seconds.count()<< "s\n";
          
        
            
        auto start_randExc = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randExc();
                }
        auto end_randExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> randExc_elapsed_seconds = end_randExc-start_randExc;
        cout<<"Time for randExc() : \t"<<randExc_elapsed_seconds.count()<< "s\n";
           
            
            
        auto start_seeded_randExc = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randExc(139853.0);
                }
        auto end_seeded_randExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randExc_elapsed_seconds = end_seeded_randExc-start_seeded_randExc;
        cout<<"Time for seeded_randExc : \t"<<seeded_randExc_elapsed_seconds.count()<< "s\n";
           
            
            
        auto start_randDblExc = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randDblExc();
                }
        auto end_randDblExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> randDblExc_elapsed_seconds = end_randDblExc-start_randDblExc;
        cout<<"Time for randDblExc : \t"<<randDblExc_elapsed_seconds.count()<< "s\n";
           
            
            
        auto start_seeded_randDblExc = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randDblExc(139853.0);
                }
        auto end_seeded_randDblExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randDblExc_elapsed_seconds = end_seeded_randDblExc-start_seeded_randDblExc;
        cout<<"Time for seeded_randDblExc : \t"<<seeded_randDblExc_elapsed_seconds.count()<< "s\n";
          
            
            
        auto start_randNorm = std::chrono::steady_clock::now();
            for (int i=0; i<1000000000;i++){
                randomNumberGeneratorPtr->randNorm(1.0,2.5);
                }
            auto end_randNorm = std::chrono::steady_clock::now();
        std::chrono::duration<double> randNorm_elapsed_seconds = end_randNorm-start_randNorm;
        cout<<"Time for randNorm : \t"<<randNorm_elapsed_seconds.count()<< "s\n";
          
            }

            







int main(int argc, char *argv[]){

    uint32 seed = 139853;
    
//THIS IS TO CONVERT THE COMMAND LINE ARGUMENTS TO STRINGS
    vector<string> arg;
    for ( int i = 1 ; i< argc ; i++ ){
        arg.push_back( argv[i]);
        }


    for ( int i = 0 ; i < (argc-1); i++ ){
    //cout << "argv = \t "<< argv[j]<<endl;
        int j = i+1;
        if (arg[i] == "pimc_mt19937"){
            cout << "These random numbers are from : "<<arg[i]<<endl;
            cout<<"\n*********************************\n"; 
            auto PIMC_start = std::chrono::steady_clock::now();
                select_rng( 1 , seed );
            auto PIMC_end = std::chrono::steady_clock::now();
            std::chrono::duration<double> PIMC_seconds = PIMC_end-PIMC_start;
            std::cout << "TOTAL TIME FOR pimc_mt19937\t" << PIMC_seconds.count() << "s\n"<<std::endl;
            std::cout<<"##################################################";
            
            }
       
        else if (arg[i] == "std_mt19937"){
            cout << "\nThese random numbers are from : "<<arg[i]<<endl;
            cout<<"*********************************\n"; 
            auto STD_start = std::chrono::steady_clock::now();
                select_rng( 2 , seed );
            auto STD_end = std::chrono::steady_clock::now();
            std::chrono::duration<double> STD_seconds = STD_end-STD_start;
            std::cout << "TOTAL TIME FOR std_mt19937\t" << STD_seconds.count() << "s\n"<<std::endl;
            std::cout<<"##################################################";
            
            }
        
        else if (arg[i] == "boost_mt19937"){
            cout << "\nThese random numbers are from : "<<arg[i]<<endl;
            cout<<"*********************************\n"; 
            auto BOOST_start = std::chrono::steady_clock::now();
                select_rng( 3 , seed );
            auto BOOST_end = std::chrono::steady_clock::now();
            std::chrono::duration<double> BOOST_seconds = BOOST_end-BOOST_start;
            std::cout << "TOTAL TIME FOR boost_mt19937\t" << BOOST_seconds.count() << "s\n"<<std::endl;
            std::cout<<"##################################################";
            
            }
        
        else if (arg[i] == "PCG"){
            cout << "\nThese random numbers are from : "<<arg[i]<<endl;
            cout<<"*********************************\n"; 
            auto PCG_start = std::chrono::steady_clock::now();
                select_rng( 4 , seed );
            auto PCG_end = std::chrono::steady_clock::now();
            std::chrono::duration<double> PCG_seconds = PCG_end-PCG_start;
            std::cout << "TOTAL TIME FOR *PCG*\t" << PCG_seconds.count() << "s\n"<<std::endl;
            std::cout<<"##################################################";
            
            }

        }
        
    for ( int i =0 ; i < (argc-1); i++){
    
        if ( (arg[i] != "pimc_mt19937") && (arg[i] != "std_mt19937") && (arg[i] != "boost_mt19937") && (arg[i] != "PCG" )){
            cout<< "Incorrect RNG type :"<<arg[i]<<"\tAllowed types: pimc_mt19937, std_mt19937, boost_mt19937, PCG"<<endl;
        }
    }
    
    



     
return 0; 
}

