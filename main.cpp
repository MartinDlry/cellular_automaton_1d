#include <iostream>
#include <cstdint>

#include "CA1D.hpp"

int main()
{   
    std::cout << CA1D::Rule::isRuleFileValid("rule_exemple.txt") << std::endl;
}