#include <iostream>
#include <cstdint>

#include "CA1D.hpp"

int main()
{   
    CA1D::CellularNeighborhood cn( 5 , 20 );
    cn.setRandomStates();
    std::cout << cn << std::endl;

    CA1D ca1d( CA1D::Rule("rule_exemple.txt") , cn );


}