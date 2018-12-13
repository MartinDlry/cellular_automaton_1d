#ifndef _CA1D_HPP_
#define _CA1D_HPP_

#include <cstdint>
#include <iostream>

#define RULE_FILE_BEGIN_SIGNATURE "_ca1d_rule_begin_"
#define RULE_FILE_END_SIGNATURE "_ca1d_rule_end_"

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

                void store( const char* filePath , bool compressed );
                
            private:
                uint16_t mNumberOfStates; // max 2^8
                uint8_t* mStateChangeCases;

                static constexpr char FILE_BEGIN_SIGNATURE[] = RULE_FILE_BEGIN_SIGNATURE;
                static constexpr char FILE_END_SIGNATURE[] = RULE_FILE_END_SIGNATURE;

        };

        //CA1D( Rule rule , )
    private:
        uint64_t mSize;

        int8_t* mCells;

        


};

//std::ostream& operator <<( std::ostream &os, const CA1D::Rule& rule );

#endif