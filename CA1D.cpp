#include "CA1D.hpp"

#include <fstream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <regex>

#include "rule_file_format.hpp"

CA1D::Rule::Rule( const char* filePath )
{
    /*std::ifstream is;
    is.open( filePath );
    std::string str;
    
    is >> str;
    assert( str == FILE_BEGIN_SIGNATURE );
    is >> str;
    assert( str == "format");
    
    is >> str;
    assert( str == "number_of_states");

    is >> mNumberOfStates;

    assert( mNumberOfStates <= 256 );

    uint32_t numberofCases = mNumberOfStates * mNumberOfStates * mNumberOfStates;
    mStateChangeCases = new uint8_t[numberofCases];

    uint16_t temp;
    for( uint32_t i = 0 ; i < numberofCases ; i ++ )
    {    
        is >> temp;
        mStateChangeCases[i] = temp;
        assert( mStateChangeCases[i] < mNumberOfStates );
    }
    is >> str;
    assert( str == RULE_FILE_END_SIGNATURE);
    */
}

bool nextNonEmptyLine( std::ifstream& ifs , std::string& str ) //return false is reached end of file before finding non empty line and str isn't changed
{
    std::regex emptyLine( RULE_FILE_EMPTY_LINE_REGEX );
    std::string str2;
    do
    {
        if( ifs.eof() ) return false;
        getline( ifs , str2 );
    }while( std::regex_match( str2 , emptyLine ) );
    str = str2;
    return true;
}

bool CA1D::Rule::isRuleFileValid( const char* filePath )
{
    
    std::ifstream is;
    is.open( filePath );
    std::string str;
    std::stringstream strs;
    
    nextNonEmptyLine( is , str );

    // signature test
    if( !std::regex_match( str , std::regex( RULE_FILE_FIRST_LINE_REGEX ) ) ) return false;
    nextNonEmptyLine( is , str );

    // number of states test
    if( !std::regex_match( str , std::regex( RULE_FILE_NUMBER_OF_STATE_LINE_REGEX ) ) ) return false;
    uint numberOfStates;
    (std::stringstream)str >> str >> numberOfStates;
    if( numberOfStates > MAX_NUMBER_OF_STATES ) return false;

    nextNonEmptyLine( is , str );

    //default line test
    if( !std::regex_match( str , std::regex( RULE_FILE_DEFAULT_LINE_REGEX ) ) ) return false;
    uint defaultResultState;
    (std::stringstream)str >> str >> defaultResultState;
    if( defaultResultState >= numberOfStates ) return false;

    //testing cases
    std::regex lastLineRegex(RULE_FILE_LAST_LINE_REGEX);
    std::regex casesRegex( RULE_FILE_CASE_LINE_REGEX );
    std::regex separatorSymbol( RULE_FILE_CASE_SEPARATOR_1 "|" RULE_FILE_CASE_SEPARATOR_2 );
    std::regex generalStateSymbol( RULE_FILE_GENERAL_CASE_STATE_SYMBOL );
    std::stringstream ss;
    std::string state;
    
    while( nextNonEmptyLine( is , str ) )
    {    
        if( std::regex_match(str, lastLineRegex ) ) break;
        if( !std::regex_match(str, casesRegex ) ) return false;

        //treating line
        str = std::regex_replace( str , separatorSymbol , " " ); // replacing separator with spaces
        ss = std::stringstream(str);
        for( uint i = 0 ; i < 4 ; i++ )
        {
            ss >> str;
            if( !std::regex_match( str , generalStateSymbol ) && (uint)std::stoi(str) >= numberOfStates )
                return false;
        }
    }

    //end signature test
    if( !std::regex_match(str, lastLineRegex ) ) return false;


    is.close();
    return true;
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
                os << std::setw( maxDigits ) << i1 << " | " << std::setw( maxDigits ) << i2 << " | " << std::setw( maxDigits ) << i3 << " -> " << std::setw( maxDigits ) << (int)rule.getNextState( i1 , i2 , i3 ) << std::endl;
    
    os.copyfmt(baseIos);//reset formatting
    return os ;
}