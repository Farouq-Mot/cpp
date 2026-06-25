
#include <iostream>

// std::move converts an lvalue into an rvalue reference.

// Before C++11, there was a major problem:
// C++ could identify temporary objects, but it had no way to say "I want to steal resources from this temporary."

void print(std::string& s){
    std::cout << s << "\n";
}

void print_str_const(const std::string& s){
    std::cout << "const test: " << s << "\n";
}

void print_str_rvalue_only( std::string&& s){
    std::cout << "r value test: " << s << "\n";
}



int main (){

std::string s1="test 1";
print(s1);
//print("test_rvalue"); does not print rvalue, needs const
print_str_const(s1);
print_str_const("test_rvalue");

//print_str_rvalue_only(s1);
print_str_rvalue_only(std::move(s1));
print_str_rvalue_only("test_rvalue");


return 0;
}


