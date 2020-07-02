#ifndef RNG_H
#define RNG_H
#include <random>
#include "MersenneTwister.h"
#include "pcg_random.hpp"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <memory>


typedef unsigned long uint32;

class RNG
 	{
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
	
	// Saving and loading generator state
    virtual std::stringstream save()  {
    	std::stringstream stateStrStrm;
        stateStrStrm.str("");
        
        return stateStrStrm;
    }; 
    
    virtual void load(std::istream&) {};  
	
	
  //	virtual ~RNG() { std::cout << "Goodbye" << std::endl;}
	// double rand(double a, double b){return ( ((b-a)*rand()) + a );}
	};
	

class MTFromPIMC:public RNG
	{

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
	

	
	
	    // Saving and loading generator state
    std::stringstream save();  // to array of size SAVE
    void load(std::istream&);  // from such array
    
    
	private:
	MTRand random;

	};

/*
	inline MTFromPIMC::MTFromPIMC(){ seed();};
	
	
   	inline MTFromPIMC::MTFromPIMC(const uint32 _seed){seed (_seed);};

	inline void MTFromPIMC::seed(){
	random.seed();
	};
	
    inline void MTFromPIMC::seed(const uint32 seed){
	random.seed(seed);
	};
	inline uint32 MTFromPIMC::randInt(){return random.randInt();};
	inline uint32 MTFromPIMC::randInt( const uint32 n ){return random.randInt( n );};
	inline double MTFromPIMC::rand(){return random.rand();};
	
	
	inline std::stringstream MTFromPIMC::save(){
	    std::stringstream stateStrStrm;
        stateStrStrm.str("");

        /* Save the state of the random number generator */
 
 /*
 
        uint32 randomState[random.SAVE];
        random.save(randomState);
        for (int i = 0; i < random.SAVE; i++)
            stateStrStrm << randomState[i] << " ";
        stateStrStrm << std::endl;
    
        return stateStrStrm ;
	};
*/	
	
	
	/*
	inline void MTFromPIMC::load(std::istream& stateStrStrm){
	uint32 randomState[random.SAVE];
    for (int i = 0; i < random.SAVE; i++) 
        stateStrStrm >> randomState[i];
    random.load(randomState);
	};
	
    inline double MTFromPIMC::randExc(){
    return random.randExc(); 
    };
    
    inline double MTFromPIMC::randExc( const double n )
    { return random.randExc(n); };

    inline double MTFromPIMC::randDblExc()
    { return  random.randDblExc(); };

    inline double MTFromPIMC::randDblExc( const double n )
    { return random.randDblExc(n); };
    
    inline double MTFromPIMC::randNorm( const double mean, const double stddev = 1.0 ){return random.randNorm(mean , stddev);};
/*///##############################################################################


class MTFromSTL:public RNG
	{
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
	
		    // Saving and loading generator state
    std::stringstream save();  // to array of size SAVE
    
    void load(std::istream&);  // from such array
	
	private:
	std::mt19937 generator;
	std::uniform_real_distribution<double> dis{};
	std::uniform_int_distribution<uint32> disInt{};
    std::normal_distribution<double> disNorm{};
};

class MTFromPCG:public RNG
	{
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
	
		    // Saving and loading generator state
    std::stringstream save();  // to array of size SAVE
    
    void load(std::istream&);  // from such array
	
	private:
	pcg32 generator;
	std::uniform_real_distribution<double> dis{};
	std::uniform_int_distribution<uint32> disInt{};
    std::normal_distribution<double> disNorm{};
};




/*	inline MTFromSTL::MTFromSTL(){
	    seed();
	    using parm_t = decltype(dis)::param_type;
	    dis.param(parm_t{0.0, 1.0});
	};
    inline MTFromSTL::MTFromSTL(const uint32 _seed){
        seed (_seed);
        using parm_t = decltype(dis)::param_type;
	    dis.param(parm_t{0.0, 1.0});
    };
    

	
	inline void MTFromSTL::seed(){generator.seed();};
	inline void MTFromSTL::seed( const uint32 seed ){generator.seed(seed);};

	inline uint32 MTFromSTL::randInt(){
	    return randInt((2^32)-1);
	};
	inline uint32 MTFromSTL::randInt( const uint32 n ){
	    using parm_t = decltype(disInt)::param_type;
	    return disInt( generator, parm_t{0, n});
	};
	inline double MTFromSTL::rand(){return dis(generator);};


/*///##############################################################################

class MTFromBOOST:public RNG
	{
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
	
    std::stringstream save();  // to array of size SAVE
    
    void load(std::istream&);
	
	private:
	boost::random::mt19937 generator;
	boost::random::uniform_real_distribution<double> dis{};
	boost::random::uniform_int_distribution<uint32> disInt{};
	boost::random::normal_distribution<double> disNorm{};
	
	};


/*	inline MTFromBOOST::MTFromBOOST(){
	    seed();
	    using parm_t = decltype(dis)::param_type;
	    dis.param(parm_t{0.0, 1.0});
	};
    inline MTFromBOOST::MTFromBOOST(const uint32 _seed){
        seed (_seed);
        using parm_t = decltype(dis)::param_type;
	    dis.param(parm_t{0.0, 1.0});
    };
    

	
	inline void MTFromBOOST::seed(){generator.seed();};
	inline void MTFromBOOST::seed( const uint32 seed ){generator.seed(seed);};

	inline uint32 MTFromBOOST::randInt(){
	    return randInt((2^32)-1);
	};
	inline uint32 MTFromBOOST::randInt( const uint32 n ){
	    using parm_t = decltype(disInt)::param_type;
	    return disInt( generator, parm_t{0, n});
	};
	inline double MTFromBOOST::rand(){return dis(generator);};
/*///########################################################################



/**************************************************************************/
    inline std::unique_ptr<RNG> GetRNG( int sourceID )
    {
          	
        std::unique_ptr<RNG> randomPtr;

   	    if (sourceID == 1)  {
            randomPtr = std::make_unique<MTFromPIMC>();

        	}

		else if (sourceID == 2)  {
        	randomPtr = std::make_unique<MTFromSTL>();

        	}
        		
		else if (sourceID == 3)  {
        	randomPtr = std::make_unique<MTFromBOOST>();

        	}
        	        		
		else if (sourceID == 4)  {
        	randomPtr = std::make_unique<MTFromPCG>();

        	}      
        
        return randomPtr ;
    };


    inline std::unique_ptr<RNG> GetRNG( int sourceID, const uint32 seed  )
        
    {
          	
  	    std::unique_ptr<RNG> randomPtr;

   		if (sourceID == 1)  {
        		
            randomPtr = std::make_unique<MTFromPIMC>(seed);
        		
            }

		else if (sourceID == 2)  {
        
            randomPtr = std::make_unique<MTFromSTL>(seed);

        	}
        		
		else if (sourceID == 3)  {

        	randomPtr = std::make_unique<MTFromBOOST>(seed);

        	}    
        	    		
		else if (sourceID == 4)  {
        	randomPtr = std::make_unique<MTFromPCG>(seed);

        	}        
        
       return randomPtr ;
    };

//###################################################
      inline RNG GetRNGFromPtr( RNG &random )
    {
        return random ;
    };

/************************************************************/  
 
    
    


#endif

