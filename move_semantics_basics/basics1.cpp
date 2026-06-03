#include <iostream>
#include <vector>


// Instead of copying expensive data from one object to another, C++ can move ownership of the data

int main() {
std::string a = "This is a long string";
std::string b = a;   // copy

std::cout << a << "\n";
std::cout << b << "\n";

std::string c = std::move(a);  // move ownership to c

std::cout << "a: " << a << "\n";
std::cout << "c: " << c << "\n";



std::vector<int>  v1={1,2,3,4,5};
std::vector<int>  v2=v1;

std::cout << "v1: " << v1.size() << "\n";
std::cout << "v2: " << v2.size() << "\n";

std::vector<int>  v3=std::move(v1);

std::cout << "v1: " << v1.size() << "\n";
std::cout << "v3: " << v3.size() << "\n";




return 0;

};


