// Tutorial for copy, move constructor, assigment and destructor
#include <iostream>


// keyword public matters since class is private by default.
class person1{
    public: 
        person1(){
            std::cout << "Constructor for the class person is called." << "\n";
        };
};

// constructor overloading

class person2{

    public:
        person2(){
            std::cout << "Default constructor for person2 class is called" << std::endl;
        };

        person2(int age, std::string str1){
            std::cout << "overloaded constructor for class person2" << std::endl;
            std::cout << "age : " << age << std::endl;
            std::cout << "str1 : " << str1 << std::endl;
        };

        // added 

};




int main() {

    //person1 p1;
   
    person2 p2_1;
    person2 p2_2(20, "excellent");

    return 0;
}




