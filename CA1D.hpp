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

                uint8_t getNextState( int8_t left , int8_t cell , int8_t right ) const;
                void setNextState( int8_t left , int8_t cell , int8_t right , int8_t result );

                uint16_t getNumberOfStates();

                void store( const char* filePath);

                static bool isRuleFileValid( const char* filePath);
                
            private:
                uint16_t mNumberOfStates; // max 2^8
                uint8_t* mStateChangeCases;

                static const uint16_t MAX_NUMBER_OF_STATES = 256;

        };

        //CA1D( Rule rule , )
    private:
        uint64_t mSize;

        int8_t* mCells;

        


};

//std::ostream& operator <<( std::ostream &os, const CA1D::Rule& rule );

#endif