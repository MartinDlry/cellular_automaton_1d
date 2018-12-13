#include "CA1D.hpp"

#include <fstream>
#include <iomanip>
#include <cassert>
#include <sstream>

constexpr char CA1D::Rule::FILE_BEGIN_SIGNATURE[];
constexpr char CA1D::Rule::FILE_END_SIGNATURE[];

CA1D::Rule::Rule( const char* filePath )
{
    std::ifstream is;
    is.open( filePath );
    std::string str;
    
    is >> str;
    assert( str == FILE_BEGIN_SIGNATURE );
    is >> str;
    assert( str == "format");
    
    int format;
    is >> format;
    assert( format == 0 || format == 1 );

    is >> str;
    assert( str == "number_of_states");

    is >> mNumberOfStates;

    assert( mNumberOfStates <= 256 );

    uint32_t numberofCases = mNumberOfStates * mNumberOfStates * mNumberOfStates;
    mStateChangeCases = new uint8_t[numberofCases];

    uint16_t temp;
    if( format == 0 )
    {
        for( uint32_t i = 0 ; i < numberofCases ; i ++ )
        {    
            is >> temp;
            mStateChangeCases[i] = temp;
            assert( mStateChangeCases[i] < mNumberOfStates );
        }
    }
    else
    {

    }
    is >> str;
    assert( str == RULE_FILE_END_SIGNATURE);
}
uint16_t CA1D::Rule::getNumberOfStates()
{
    return mNumberOfStates;
}

uint8_t CA1D::Rule::getNextState( int8_t left , int8_t cell , int8_t right ) const
{
    return mStateChangeCases[ (left * mNumberOfStates + cell) * mNumberOfStates + right ];
}

std::ostream& operator <<( std::ostream &os, const CA1D::Rule& rule )
{
    std::ios baseIos(NULL);
    baseIos.copyfmt(os);

    os << "number_of_states = " << rule.mNumberOfStates << std::endl;

    // change formatting
    int maxDigits = std::to_string(rule.mNumberOfStates-1).length();

    uint16_t i1, i2, i3;
    for( i1 = 0 ; i1 < rule.mNumberOfStates ; i1 ++ )
        for( i2 = 0 ; i2 < rule.mNumberOfStates ; i2 ++ )
            for( i3 = 0 ; i3 < rule.mNumberOfStates ; i3 ++ )
                os << std::setw( maxDigits ) << i1 << "|" << std::setw( maxDigits ) << i2 << "|" << std::setw( maxDigits ) << i3 << " -> " << std::setw( maxDigits ) << (int)rule.getNextState( i1 , i2 , i3 ) << std::endl;
    
    os.copyfmt(baseIos);//reset formatting
    return os ;
}