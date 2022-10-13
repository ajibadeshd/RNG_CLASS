#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include "RNG.cpp"
#include <cmath>
#include <fstream>
#include <thread>         

using namespace std;



//*********** CHECKS IF SAVED STATE FILES EXISTS ******************
inline bool file_exist(const std::string& name){
        ifstream file(name);
        if(!file){ 
            return false;}  
        else{  
            file.close();
        return true;}
        }
//******************************************************************


//**************DESCRIBES THE USAGE OF THE PROGRAM********************
void display_usage(){
            cout<< "\nUSAGE:\t-h [help]\tDisplays this help message\n";
            cout<<"\t-t [test mode] \t<test sample size> (An integer value)\n";
            cout<<"\t-r [run mode] \t<pimc_mt19937||std_mt19937||boost_mt19937||PCG>\n";
            }

//######### Pause function for better visualization ###############
void pause( int sec){
        this_thread::sleep_for (std::chrono::seconds( sec));
        }


//#####################################################################
//########## THIS FUNCTION DOES THE ACTUAL ESTIMATION OF pi ###########
//#####################################################################
void estimate_pi( int w){
        cout<<"\nTHIS CODE ESTIMATES PI USING THE MONTE CARLO TECHNIQUE\n"<<endl;
        std::unique_ptr<RNG> rngPtr;
        rngPtr = GetRNG ( w );

        cout<<"Load a previously saved rng_state ?\n"<<"Y or N to proceed"<<endl;
        string res;
        cin>>res;
        string correct = "y";
        string correct2 = "Y";
        string file_name = "_rng_state.dat";

        file_name = optarg + file_name;

        //###################### ATTEMPT TO LOAD SAVED RNG STATE ##################
        if ( (res == correct) or (res == correct2)){
                if (file_exist(file_name) ){
                        cout<<"\nLOADING RNG STATE OF A PREVIOUSLY SAVED SIMULATION ... \n";
                        pause(2);
                        ifstream myfile;
                        myfile.open (file_name);
                        rngPtr->load(myfile);
                        myfile.close();
                        cout<< "\nrng state data successfully loaded\n";}
                else{
                        cout<<"\nFailed!\nUnable to find saved rng state file.\n";
                        pause(2);}
                }
        else{
                cout<< "\nWARNING: Unable to load rng state!!!\n";
                pause(3);}
    
        //###################### ATTEMPT TO LOAD SAVED PI STATE ##################        
        cout<<"\nATTEMPTING TO LOAD PREVIOUS PI_SIMULATION STAGE DATA ...\n";
        pause(2);
        
        //This allows for loading of simulation specific data
        double in  , out  ,total , initial_count;
        double  x = 0, y = 0, det =0, PI = 0, pi = 0 , new_count = 0;

        if (file_exist("PI_data.dat")){       
                ifstream myfile ("PI_data.dat",std::ios::in);
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
                cout<< "\nPi simulation file successfully loaded\n";
                pause(1);
                }

        else{
                cout<<" CAN'T FIND SIMULATION DATA FILE (PI_data.dat)"<<endl;
                in = 0.0 , out = 0.0  ,total = 0.0 , initial_count = 0.0;
                pause(2);
                }     
    
        cout<<" \nEnter sample count (MC sample points)\n";
        cin>>new_count;
        double sample_count;
        sample_count = new_count + initial_count;
        for (int i = 0; i < new_count ; i++){    
                x = rngPtr->rand();
                y = rngPtr->rand();
                det = sqrt( x*x + y*y);
                if (det <= 1 ){in = in+1;}       
                if (det > 1 ){out = out+1;}           
                pi = (4 * in) / (out + in );
                total = total + pi ;            
                }


        PI = total / sample_count;
        cout << "\nESTIMATED VALUE FOR PI IS : " << PI<<endl<<endl;
        
        //#################### Let's make some saving ################
        ofstream myfile;
        myfile.open (file_name);
        myfile<<rngPtr->save().str();
        cout<< "RNG state file saved as (" << file_name<<" )"<<endl;
        myfile.close();
    
        ofstream myfile2;
        myfile2.open ("PI_data.dat");
        myfile2<<in<<endl;
        myfile2<<out<<endl;
        myfile2<<total<<endl;
        myfile2<<sample_count<<endl;
        cout<< "PI estimation data saved as (PI_data.dat)"<<endl;
        myfile2.close();     
        }
//###################### END OF estimate_pi() ###########################



//***********THIS FUNCTION TESTS THE SPEED OF EACH MEMBER FUNCTIONS FROM ALL THE RANDOM NUMBER GENERATOR TYPES***************************
void time_rngs( int type ,  uint32 seed){
        int test_sample_size = atoi(optarg);
        cout<< "TESTING WITH SAMPLE SIZE OF : "<<test_sample_size<<" Random Numbers"<<endl<<endl<<endl;
        std::unique_ptr<RNG> randomNumberGeneratorPtr;
        randomNumberGeneratorPtr = GetRNG ((type ), seed);
        
        //######## Estimate time for rand() ##############
        auto start_rand = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->rand();}
        auto end_rand = std::chrono::steady_clock::now();
        std::chrono::duration<double> rand_elapsed_seconds = end_rand-start_rand;
        cout<<"Time for rand : \t\t"<<rand_elapsed_seconds.count()<< "s\n";
       

        //######## Estimate time for randInt() ##############
        auto start_randInt = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randInt();}
        auto end_randInt = std::chrono::steady_clock::now();
        std::chrono::duration<double> randInt_elapsed_seconds = end_randInt-start_randInt;
        cout<<"Time for randInt : \t\t"<<randInt_elapsed_seconds.count()<< "s\n";
       
        
        //######## Estimate time for randInt(seed) ##############
        auto start_seeded_randInt = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randInt(seed);}
        auto end_seeded_randInt = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randInt_elapsed_seconds = end_seeded_randInt-start_seeded_randInt;
        cout<<"Time for seeded_randInt : \t"<<seeded_randInt_elapsed_seconds.count()<< "s\n";
      
    
        //######## Estimate time for randInt(seed) ##############
        auto start_randExc = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randExc();}
        auto end_randExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> randExc_elapsed_seconds = end_randExc-start_randExc;
        cout<<"Time for randExc() : \t\t"<<randExc_elapsed_seconds.count()<< "s\n";
       
        
        //######## Estimate time for randExc(139853.0) ##############
        auto start_seeded_randExc = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randExc(139853.0);}
        auto end_seeded_randExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randExc_elapsed_seconds = end_seeded_randExc-start_seeded_randExc;
        cout<<"Time for seeded_randExc : \t"<<seeded_randExc_elapsed_seconds.count()<< "s\n";
       
        
        //######## Estimate time for randDblExc() ############
        auto start_randDblExc = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randDblExc();}
        auto end_randDblExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> randDblExc_elapsed_seconds = end_randDblExc-start_randDblExc;
        cout<<"Time for randDblExc : \t\t"<<randDblExc_elapsed_seconds.count()<< "s\n";
       
        
        //######## Estimate time for randDblExc(139853.0) ############
        auto start_seeded_randDblExc = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randDblExc(139853.0);}
        auto end_seeded_randDblExc = std::chrono::steady_clock::now();
        std::chrono::duration<double> seeded_randDblExc_elapsed_seconds = end_seeded_randDblExc-start_seeded_randDblExc;
        cout<<"Time for seeded_randDblExc : \t"<<seeded_randDblExc_elapsed_seconds.count()<< "s\n";
      
        

        auto start_randNorm = std::chrono::steady_clock::now();
        for (int i=0; i<test_sample_size;i++){
                randomNumberGeneratorPtr->randNorm(1.0,2.5);}
        auto end_randNorm = std::chrono::steady_clock::now();
        std::chrono::duration<double> randNorm_elapsed_seconds = end_randNorm-start_randNorm;
        cout<<"Time for randNorm : \t\t"<<randNorm_elapsed_seconds.count()<< "s\n";
        }

////////////////  END OF FUNCTIONS    /////////////////////////


int main(int argc, char *argv[]){
        if (argc < 2){
                display_usage();
        return 1;
        }

        uint32 seed = 139853;
        int option;
        while(  (option = getopt (argc, argv, "ht:r:") ) != -1 ){
                switch (option){
                        case 't': {                                           
                                cout << "\nThese random numbers are from pimc_mt19937 "<<endl;
                                cout<<"\n*********************************\n"; 
                                auto PIMC_start = std::chrono::steady_clock::now();
                                        time_rngs( 1 , seed );
                                auto PIMC_end = std::chrono::steady_clock::now();
                                std::chrono::duration<double> PIMC_seconds = PIMC_end-PIMC_start;
                                std::cout << "TOTAL TIME FOR pimc_mt19937\t" << PIMC_seconds.count() << "s\n"<<std::endl;
                                std::cout<<"##################################################"<<endl;

                                cout << "\nThese random numbers are from : "<<"std_mt19937"<<endl;
                                cout<<"*********************************\n"; 
                                auto STD_start = std::chrono::steady_clock::now();
                                        time_rngs( 2 , seed );
                                auto STD_end = std::chrono::steady_clock::now();
                                std::chrono::duration<double> STD_seconds = STD_end-STD_start;
                                std::cout << "TOTAL TIME FOR std_mt19937\t" << STD_seconds.count() << "s\n"<<std::endl;
                                std::cout<<"##################################################"<<endl;

                                cout << "\nThese random numbers are from : "<<"boost_mt19937"<<endl;
                                cout<<"*********************************\n"; 
                                auto BOOST_start = std::chrono::steady_clock::now();
                                        time_rngs( 3 , seed );
                                auto BOOST_end = std::chrono::steady_clock::now();
                                std::chrono::duration<double> BOOST_seconds = BOOST_end-BOOST_start;
                                std::cout << "TOTAL TIME FOR boost_mt19937\t" << BOOST_seconds.count() << "s\n"<<std::endl;

                                cout << "\nThese random numbers are from PCG: "<<endl;
                                cout<<"*********************************\n"; 
                                auto PCG_start = std::chrono::steady_clock::now();
                                        time_rngs( 4 , seed );
                                auto PCG_end = std::chrono::steady_clock::now();
                                std::chrono::duration<double> PCG_seconds = PCG_end-PCG_start;
                                std::cout << "TOTAL TIME FOR PCG\t\t" << PCG_seconds.count() << "s\n"<<std::endl;
                                std::cout<<"##################################################"<<endl;
                                break;

                                return 0;
                                }
                                
                        case 'r':{
                                if(strcmp("pimc_mt19937", optarg)== 0) {
                                        estimate_pi(1);}
                                else if(strcmp("std_mt19937", optarg)== 0){
                                        estimate_pi(2);}
                                else if(strcmp("boost_mt19937", optarg)== 0) {
                                        estimate_pi(3);}
                                else if(strcmp("PCG", optarg)== 0) {
                                        estimate_pi(4);}
                                else{
                                        cout<<"Invalid rng type : "<< optarg<<endl;
                                        display_usage();
                                        return 1;
                                        } 
                                } 

                        case 'h':{              
                                display_usage();
                                return 0;
                                }                                       

                        default :{
                                display_usage();     
                                return 0;
                                }
                        }
                }                                    
        return 0;
        }

