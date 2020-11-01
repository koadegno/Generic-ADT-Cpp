#include <iostream>
#include "Cont.hpp"
#include  "Vect2.hpp"
#include  "BST.hpp"


int main(){

    Cont<int> var(10);
    Vect_dyn<int> test(10);
    test.insert(0,2);
    std::cout << test[0] <<std::endl;


    var.insert(10,1);
    var.insert(11);
    var.insert(13);
    //var.erase(10);


    std::cout << var <<std::endl;
    std::cout << var[2] <<std::endl;
    return 0;
}
