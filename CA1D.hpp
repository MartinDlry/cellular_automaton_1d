#ifndef _CA1D_HPP_
#define _CA1D_HPP_

#include <cstdint>
#include <iostream>


class CA1D
{
    public:

        class Rule
        {
            friend std::ostream& operator <<( std::ostream &os, const CA1D::Rule& rule );
            public:
                Rule( const char* filePath );
                Rule( const uint16_t numberOfStates ) : mNumberOfStates( numberOfStates ) , mStateChangeCases( new uint8_t[numberOfStates*numberOfStates*numberOfStates ]() ) {};
                Rule( const Rule& ruleToCopy );
                Rule();

                ~Rule();

                uint8_t getNextState( int8_t left , int8_t cell , int8_t right ) const;

                void setNextState( int8_t left , int8_t cell , int8_t right , int8_t result );

                uint16_t getNumberOfStates() const ;

                void store( const char* filePath);

                static bool isRuleFileValid( const char* filePath);
                
            private:
                uint16_t mNumberOfStates; // max 2^8
                uint8_t* mStateChangeCases;

                static const uint16_t MAX_NUMBER_OF_STATES = 256;

        };

        class CellularNeighborhood
        {
            friend std::ostream& operator <<( std::ostream &os, const CellularNeighborhood& cn );
            public: 
                CellularNeighborhood( const char* filePath );
                CellularNeighborhood( const uint16_t numberOfStates , const uint64_t size ) : mNumberOfStates(numberOfStates) , mSize( size ) , mCells( new uint8_t[size] ){};
                CellularNeighborhood( const CellularNeighborhood& cnToCopy );
                CellularNeighborhood();
                ~CellularNeighborhood();

                void setRandomStates();
                void applyRuleNTimes( const Rule& rule , const uint64_t nbOfTimes );

                uint16_t getNumberOfStates() const ;

            private:
                uint16_t mNumberOfStates;
                uint64_t mSize;
                uint8_t* mCells;
        };

        CA1D( const Rule& rule , const CellularNeighborhood& cn );

        void gotoGeneration( const uint64_t generation );
        void forwardNGeneration( const uint64_t generations );
        void reset(); // go back to gen 0

        const Rule& getRule() const;
        const CellularNeighborhood& getCellularNeighborhood() const;

    private:
        CellularNeighborhood mStart;
        Rule mRule;
        CellularNeighborhood mCurrent;
        uint64_t mGeneration;

        


};

//std::ostream& operator <<( std::ostream &os, const CA1D::Rule& rule );

#endif