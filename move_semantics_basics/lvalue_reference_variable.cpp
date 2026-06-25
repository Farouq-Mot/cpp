#include <iostream>
#include <string>



/*
If an interviewer asks:

Why is an rvalue reference variable itself an lvalue?

A good answer is:

Because value category depends on the expression, not the type. 
Any named variable is an lvalue expression, even if its type is T&&. 
This prevents accidental moves every time the variable is used. 
To explicitly treat it as an rvalue again, we use std::move().

This understanding is the entire reason std::move() exists. 
Once this clicks, move constructors and move assignment operators become much easier to understand.
*/


void test(std::string&)
{
    std::cout << "lvalue\n";
}

void test(std::string&&)
{
    std::cout << "rvalue\n";
}

int main()
{
    std::string&& s = std::string("hello");

    test(s);

    test(std::move(s));
}