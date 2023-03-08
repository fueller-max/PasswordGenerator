// PasswordGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<memory>
#include "password_generator.h"


int main()
{
    composite_password_generator generator;

    generator.add(std::make_unique<digit_generator>(2));
    generator.add(std::make_unique<symbol_generator>(2));
    generator.add(std::make_unique<upper_letter_generator>(2));
    generator.add(std::make_unique<lower_letter_generator>(2));

    auto password = generator.generate();

    std::cout << password;
}

