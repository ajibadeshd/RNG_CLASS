//######################  UsageExample.cpp  #########################
//
//  This cpp file explains the useage of all the method of the RNG
//  class. We illustrate this using the the classic example of the
//  Monte-carlo technique for the estimation of PI
//
//####################################################################



#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include <cmath>
#include <fstream>
#include <thread>         

using namespace std;


// Including our source codes

#include "RNG.cpp" // Always needed
#include "rand.cpp" //Needed for our estimation of PI
#include "randInt.cpp"
#include "randExp.cpp"
#include "randNorm.cpp"
#include "randBernouli.cpp"
//   NOTE: Only rand.cpp in needed for our estimation of PI. Others, i.e
//   randInt, randExp e.t.c are only included to illustrate their usage.
//   RNG.cpp is always needed. 




//**************  Describes the operation of this code  ****************
void display_usage(){
    cout<< "\n\t\t\t\t\tMONTE-CARLO ESTIMATION OF PI\n";
    cout<<"\tThis code illustrates the usage of this library with interactive estimation of PI\n\n";
    }


//************** Pause function for clarity of operation **************
void pause( int sec){
    this_thread::sleep_for (std::chrono::seconds( sec));
    }



//*********** CHECKS IF SAVED STATE FILES EXISTS ******************
inline bool file_exist(const std::string& name){
    ifstream file(name);
    if(!file){ 
    	return false;}  
    else{  
	file.close();
    return true;}
    }


int main(){

	display_usage();
	pause(4);
	
	
	//user-defined seed
	uint32 _seed = 139853;
	
	
	//  Pointers for each class members (unseeded)
	std::unique_ptr<RNG> RAND; 
	std::unique_ptr<RNG> RANDINT;
	std::unique_ptr<RNG> RANDEXP;
	std::unique_ptr<RNG> RANDNORM;
	std::unique_ptr<RNG> RANDBERNOULI;
	
	
	//  Pointers for each class members (seeded)
	std::unique_ptr<RNG> RAND_unseeded;
	std::unique_ptr<RNG> RANDINT_unseeded;
	std::unique_ptr<RNG> RANDEXP_unseeded;
	std::unique_ptr<RNG> RANDNORM_unseeded;
	std::unique_ptr<RNG> RANDBERNOULI_unseeded;
	
	
	//  Object Instantiations
	RAND = FAST_RAND( _seed);// samples from uniform distribution in the range [0, 1]
	RANDINT = FAST_RANDINT( _seed);
	RANDEXP = FAST_RANDEXP( _seed);
	RANDNORM = FAST_RANDNORM( _seed );
	RANDBERNOULI = FAST_RANDBERNOULI( _seed );
	
	RAND_unseeded = FAST_RAND( ); 
	RANDINT_unseeded = FAST_RANDINT( );
	RANDEXP_unseeded = FAST_RANDEXP( );
	RANDNORM_unseeded = FAST_RANDNORM( );
	RANDBERNOULI_unseeded = FAST_RANDBERNOULI( );

	//NOTE:
	//Previously unseeded objects can be seeded at any stage as follows:
	//RAND_unseeded.seed( _seed);
	//RANDNORM_unseeded.seed( _seed);

	
	//#####################################################################
	//            THIS PART DOES THE ACTUAL ESTIMATION OF pi 
	//*********************************************************************


	//###################### ATTEMPT TO LOAD SAVED RNG STATE ##################
	cout<<"Do you want to load a previously saved rng_state ?\n"<<"Y or N to proceed\n";
	string response;
	cin >> response;
	string correct = "y";
	string correct2 = "Y";
	string file_name = "RAND_state.dat";


	if ((response == correct) or ( response == correct2)){
		pause(1);
		cout<<"\nAttempting to load previously saved RNG state data file: '";
		cout<< file_name<< "'...\n\n";
		pause(2);
		if (file_exist(file_name) ){
			ifstream myfile;
			myfile.open (file_name);
			
			
			// This is how we load the RNG state:
			RAND->load(myfile);
			
			myfile.close();
			cout<< "SUCCESS: \tRNG State data successfully loaded !!!\n";}
		else{
			cout<<"\nFAILED!!!\tUnable to find RNG state file '";
			cout<< "RAND_state.dat";
			pause(2);}
		}
		
	else{
		cout<< "\nWARNING:\t RNG state not loaded !!!\n";
		pause(2);}
    
	//###################### ATTEMPT TO LOAD SAVED PI STATE ##################	
	cout<<"\nAttempting to load previously saved PI simulation stage data file: '";
	cout<< "PI_stage_data.dat'...\n";
	pause(2);
	
	//This allows for loading of simulation specific data
	double in  , out  ,total , initial_count;
	if (file_exist("PI_stage_data.dat")){       
		ifstream myfile ("PI_stage_data.dat",std::ios::in);
		double line = 0.0;
		int i = 0;
		vector<double> content;
		while (myfile >> line){
			content.push_back(line);
			i +=1;
			if (i==4)
			    break;}
			    
		myfile.close();
		
		for (int i = 0; i <= content.size(); ++i){
			if (i == 0){
				in = content[i];}
			if (i == 1){
				out = content[i];}
			if (i == 2){
				total = content[i];}
			if (i == 3){
				initial_count = content[i];
				break;}		
			}
		cout<< "\nSUCCESS: \tPi simulation stage data successfully loaded\n";
		pause(2);
		}

	else{
		cout<<"\nFAILED!!! \tUnable to find PI simulation stage data file: '";
		cout<< "PI_stage_data.dat'...\n";
		in = 0.0 , out = 0.0  ,total = 0.0 , initial_count = 0.0;
		pause(2);
		}     
    
    
    double  x = 0, y = 0, det =0, PI = 0, pi = 0 , new_count = 0;
    
	cout<<" \nEnter MC sample count (some integer)\n";
	cin>>new_count;
	double sample_count;
	sample_count = new_count + initial_count;
	
	for (int i = 0; i < new_count ; i++){ 
	   
	   	//This is where we actually do the random number generation.
		x = RAND->rand();
		y = RAND->rand();
		
		det = sqrt( x*x + y*y);
		if (det <= 1 ){in = in+1;}       
		if (det > 1 ){out = out+1;}	   
		pi = (4 * in) / (out + in );
		total = total + pi ;	    
		}


	PI = total / sample_count;
	cout<< "\t\t\t\tPI ESTIMATION RESULT:"<<endl;
	cout<< "\t\t=============================================\n";
	cout << "\tEstimated value for PI with a total sample count of";
	cout<< sample_count<<" is : " << PI;
	cout<< "\n--------------------------------------------------------------------------------------------\n";
	
	
	//########### Now we Let's save useful information ################
	
	// First RNG state file
	ofstream myfile;
	myfile.open (file_name);
	
	// This is how we save the RNG state:
	myfile<<RAND->save().str();
	
	cout<< "RNG state file saved as: '" << file_name<<"'\n";
	myfile.close();
    
    
    // Second PI simulation stage data
    //This are information recognized to be important for MC Pi estimation.
    //It is only for illustration purpose and there is no conventionality involved.
    //Users are encouraged to make decisions as it pertains to their projects.
	ofstream myfile2;
	myfile2.open ("PI_stage_data.dat");
	myfile2<<in<<endl;
	myfile2<<out<<endl;
	myfile2<<total<<endl;
	myfile2<<sample_count<<endl;
	cout<< "PI estimation stage data saved as: 'PI_stage_data.dat'\n"<<endl;
	myfile2.close();     
	//###################### END OF estimate_pi ###########################
		    
    return 0;
    }
