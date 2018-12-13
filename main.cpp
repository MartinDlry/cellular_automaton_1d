#include <iostream>
#include <iomanip>
#include <cstdint>

#include "CA1D.hpp"

int main()
{   
    CA1D::Rule rule("rule_exemple_compressed.txt");
    std::cout << rule << std::endl;
}