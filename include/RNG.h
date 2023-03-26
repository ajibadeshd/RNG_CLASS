#ifndef RNG_H
#define RNG_H
#include <random>
#include "MersenneTwister.h"
#include "pcg/pcg_random.hpp"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <memory>


typedef unsigned long uint32;

//###################### BASE CLASS ######################
class RNG{
 	public:
		virtual void seed(){};
		virtual void seed( const uint32 oneSeed ){};
		virtual uint32 randInt( const uint32 n ){return 0;}
		virtual uint32 randInt(){return 0;}
		virtual double rand(){return 0.0;}
		virtual double randExc(){return 0.0;}
		virtual double randExc(const double n){return 0.0;}
		virtual double randNorm( const double mean , const double stddev ){return 0.0;}
		virtual double randDblExc(){ return  0.0; };
		virtual double randDblExc( const double n ) { return 0.0; };
		
		//TEST DISTRIBUTIONS
		virtual double randBernoulli(const double n){return 0.0;};
		virtual double randExp(const double n){return 0.0;};
		
		
		
		
		// Saving the generator state
		virtual std::stringstream save(){
			std::stringstream stateStrStrm;
			stateStrStrm.str("");
			return stateStrStrm;
			}; 
		//Loading the generator state
			virtual void load(std::istream&) {};  
	};
	
//###################### SUBCLASS MTFromPIMC AND MEMBER FUNCTIONS DECLARATION ######################
class MTFromPIMC:public RNG{
	public:
		MTFromPIMC();
		MTFromPIMC(const uint32 );
		void seed();
		void seed( const uint32 );
		uint32 randInt();
		uint32 randInt( const uint32 );
		double rand();
		double randExc();
		double randExc(const double );
		double randNorm( const double , const double );
		double randDblExc();
		double randDblExc( const double );
		
		//TEST EXPONENTIAL DISTRIBUTIONS
		double randExp(const double );	
		double randBernoulli( const double);	
	
	    	// Saving and loading generator state
		std::stringstream save();  // to array of size SAVE
		void load(std::istream&);  // from such array
	private:
		MTRand random;
	};


class MTFromSTL:public RNG{
	public:
		MTFromSTL();
		MTFromSTL(const uint32 );
		void seed();
		void seed( const uint32 );
		uint32 randInt();
		uint32 randInt( const uint32 );
		double rand();
		double randExc();
		double randExc(const double );
		double randNorm( const double , const double );
		double randDblExc();
		double randDblExc( const double );

		//TEST DISTRIBUTIONS
		double randExp(const double );
		double randBernoulli( const double);		
	    // Saving and loading generator state
		std::stringstream save();  // to array of size SAVE
		void load(std::istream&);  // from such array
	
	private:
		std::mt19937 generator;
		std::uniform_real_distribution<double> dis{};
		std::uniform_int_distribution<uint32> disInt{};
		std::normal_distribution<double> disNorm{};
		std::exponential_distribution<double> disExp{};
		std::bernoulli_distribution disBernoulli{};
	};


class MTFromPCG:public RNG{
	public:
		MTFromPCG();
		MTFromPCG(const uint32 );
		void seed();
		void seed( const uint32 );
		uint32 randInt();
		uint32 randInt( const uint32 );
		double rand();
		double randExc();
		double randExc(const double );
		double randNorm( const double , const double );
		double randDblExc();
		double randDblExc( const double );

		//TEST DISTRIBUTIONS
		double randExp(const double );
		double randBernoulli(const double );
	
		// Saving and loading generator state
		std::stringstream save();  // to array of size SAVE
		void load(std::istream&);  // from such array

	private:
		pcg32 generator;
		std::uniform_real_distribution<double> dis{};
		std::uniform_int_distribution<uint32> disInt{};
		std::normal_distribution<double> disNorm{};
		
		//TEST DISTRIBUTIONS
		std::exponential_distribution<double> disExp{};
		std::bernoulli_distribution disBernoulli{};
	};


class MTFromBOOST:public RNG{
	public:
		MTFromBOOST();
		MTFromBOOST(const uint32 );
		void seed();
		void seed( const uint32 );
		uint32 randInt();
		uint32 randInt( const uint32 );
		double rand();
		double randExc();
		double randExc(const double );
		double randNorm( const double , const double );
		double randDblExc();
		double randDblExc( const double );

		
		//TEST DISTRIBUTION
		double randExp(const double );
		double randBernoulli( const double );
		
		std::stringstream save();  // to array of size SAVE
		void load(std::istream&);
	
	private:
		boost::random::mt19937 generator;
		boost::random::uniform_real_distribution<double> dis{};
		boost::random::uniform_int_distribution<uint32> disInt{};
		boost::random::normal_distribution<double> disNorm{};
		
		//TEST DISTRIBUTION
		boost::random::exponential_distribution<double> disExp{};
		boost::random::bernoulli_distribution<double> disBernoulli{};
	};


//############ Pointers for selecting the RNG engine of choice #############
/**************************************************************************/
inline std::unique_ptr<RNG> GetRNG( std::string sourceID){
	std::unique_ptr<RNG> randomPtr;
	if (sourceID == "PIMC"){
		randomPtr = std::make_unique<MTFromPIMC>();}
	else if (sourceID == "STL"){
        	randomPtr = std::make_unique<MTFromSTL>();}
	else if (sourceID == "BOOST"){
        	randomPtr = std::make_unique<MTFromBOOST>();}
	else if (sourceID == "PCG"){
        	randomPtr = std::make_unique<MTFromPCG>();}         
        
	return randomPtr ;
	};

inline std::unique_ptr<RNG> GetRNG( std::string sourceID, const uint32 seed ){
	std::unique_ptr<RNG> randomPtr;
	if (sourceID == "PIMC"){
		randomPtr = std::make_unique<MTFromPIMC>(seed);}
	else if (sourceID == "STL"){
		randomPtr = std::make_unique<MTFromSTL>(seed);}
	else if (sourceID == "BOOST"){
		randomPtr = std::make_unique<MTFromBOOST>(seed);}    
	else if (sourceID == "PCG"){
        	randomPtr = std::make_unique<MTFromPCG>(seed);}          
       
	return randomPtr ;
	};
/*
//################# This returns the chossen RNG object ####################
inline RNG GetRNGFromPtr( RNG &random ){
	return random ;};
*/

#endif
