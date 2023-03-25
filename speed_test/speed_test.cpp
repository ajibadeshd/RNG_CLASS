#include <iostream>
#include <unistd.h>
#include <string>
#include <chrono>
#include "RNG.cpp" 

using namespace std;



//**************DESCRIBES THE USAGE OF THE PROGRAM********************
void display_usage(){
    cout<< "\nUSAGE:\t-h [help]\tDisplays this help message\n";
    cout<<"\t-t [test mode] \t<test sample size> (An integer value)\n";
    }


//THIS FUNCTION TESTS THE SPEED OF EACH MEMBER FUNCTIONS OF THE GENERATORS
void time_rngs(string rng_choice ,  uint32 seed, int sample_size){
	int test_sample_size = sample_size;
	cout<< "TESTING WITH SAMPLE SIZE OF: "<<test_sample_size<<" Random Numbers\n\n\n";
	unique_ptr<RNG> randomNumberGeneratorPtr;
	randomNumberGeneratorPtr = GetRNG (rng_choice , seed);

	//######## Estimate time for rand() ##############
	auto start_rand = chrono::steady_clock::now();
	for (int i=0; i<test_sample_size;i++){
	    randomNumberGeneratorPtr->rand();}
	auto end_rand = chrono::steady_clock::now();
	chrono::duration<double> rand_elapsed_seconds = end_rand-start_rand;
	cout<<"Time for rand : \t\t"<<rand_elapsed_seconds.count()<< "s\n";

	//######## Estimate time for randInt() ##############
	auto start_randInt = chrono::steady_clock::now();
	for (int i=0; i<test_sample_size;i++){
	    randomNumberGeneratorPtr->randInt();}
	auto end_randInt = chrono::steady_clock::now();
	chrono::duration<double> randInt_elapsed_seconds = end_randInt-start_randInt;
	cout<<"Time for randInt : \t\t"<<randInt_elapsed_seconds.count()<< "s\n";
		      
	//######## Estimate time for randExp() ##############
	auto start_randExp = chrono::steady_clock::now();
	for (int i=0; i<test_sample_size;i++){
		    randomNumberGeneratorPtr->randExp(3.5);}
	auto end_randExp = chrono::steady_clock::now();
	chrono::duration<double> randExp_elapsed_seconds = end_randExp-start_randExp;
	cout<<"Time for randExp : \t\t"<<randExp_elapsed_seconds.count()<< "s\n";

	//######## Estimate time for randBernoulli() ##############
	auto start_randBernoulli = chrono::steady_clock::now();
	for (int i=0; i<test_sample_size;i++){
	    randomNumberGeneratorPtr->randBernouli(0.5);}
	auto end_randBernoulli = chrono::steady_clock::now();
	chrono::duration<double> randBernoulli_elapsed_seconds = end_randBernoulli-start_randBernoulli;
	cout<<"Time for randBernoulli : \t"<<randBernoulli_elapsed_seconds.count()<< "s\n";
		       
	//######## Estimate time for randNorm ############
	auto start_randNorm = chrono::steady_clock::now();
	for (int i=0; i<test_sample_size;i++){
	    randomNumberGeneratorPtr->randNorm(1.0,2.5);}
	auto end_randNorm = chrono::steady_clock::now();
	chrono::duration<double> randNorm_elapsed_seconds = end_randNorm-start_randNorm;
	cout<<"Time for randNorm : \t\t"<<randNorm_elapsed_seconds.count()<< "s\n";
	}


int main(int argc, char *argv[]){
	
	if (argc < 2){
		display_usage();
		return 1;}
		
	int option;
	while((option = getopt (argc, argv, "ht:")) != -1 ){
		switch (option){
			case 'h': {
				display_usage();
				return 0;
				}
				
			case 't': {
				int sample_size = atoi(optarg);		
				string rng_choice ;
				uint32 seed = 139853;
				//PIMC timing
				cout << "\nThese random numbers are from PIMC: "<<endl;
				cout<<"*********************************\n";	
				rng_choice = "PIMC";
				auto PIMC_start = chrono::steady_clock::now();
					time_rngs(rng_choice, seed ,sample_size);
				auto PIMC_end = chrono::steady_clock::now();
				chrono::duration<double> PIMC_seconds = PIMC_end-PIMC_start;
				cout << "TOTAL TIME FOR pimc_mt19937\t" <<PIMC_seconds.count() << "s\n"<<endl;
				cout<<"##################################################"<<endl;
				cout << "\nThese random numbers are from STL:"<<endl;
				cout<<"*********************************\n";

				// STL timing
				rng_choice = "STL" ;
				auto STD_start = chrono::steady_clock::now();
					time_rngs(rng_choice, seed ,sample_size);
				auto STD_end = chrono::steady_clock::now();
				chrono::duration<double> STD_seconds = STD_end-STD_start;
				cout << "TOTAL TIME FOR std_mt19937\t" << STD_seconds.count() << "s\n"<<endl;
				cout<<"##################################################"<<endl;
				cout << "\nThese random numbers are from BOOST:"<<endl;
				cout<<"*********************************\n";

				//BOOST timing
				rng_choice = "BOOST"; 
				auto BOOST_start = chrono::steady_clock::now();
					time_rngs(rng_choice, seed ,sample_size);
				auto BOOST_end = chrono::steady_clock::now();
				chrono::duration<double> BOOST_seconds = BOOST_end-BOOST_start;
				cout << "TOTAL TIME FOR boost_mt19937\t" << BOOST_seconds.count() << "s\n"<<endl;
				cout << "\nThese random numbers are from PCG: "<<endl;
				cout<<"*********************************\n";

				//PCG timing
				rng_choice = "PCG"; 
				auto PCG_start = chrono::steady_clock::now();
					time_rngs(rng_choice, seed ,sample_size);
				auto PCG_end = chrono::steady_clock::now();
				chrono::duration<double> PCG_seconds = PCG_end-PCG_start;
				cout << "TOTAL TIME FOR PCG\t\t" << PCG_seconds.count() << "s\n"<<endl;
				cout<<"##################################################"<<endl;
				}
			}
			
		}	

	


	return 0;}
