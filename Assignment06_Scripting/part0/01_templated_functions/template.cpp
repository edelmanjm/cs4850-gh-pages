// Simple template example to demonstrate how to create
// 'reusable' functions
#include <iostream>
#include <string>

template <class T>
T myadd(T a, T b){
    return a+b;
}

int main(){

    std::cout << myadd(5,2) << std::endl;
    std::cout << myadd(5.2,2.5) << std::endl;
    std::string s1 = "mike";
    std::string s2 = " says hi";
    std::cout << myadd(s1,s2) << std::endl;

    return 0;
}
