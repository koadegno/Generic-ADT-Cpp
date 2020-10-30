#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"


int main(){
    Cont<int> test1(10);

    #define _BST_DBG_
    BST<int> test;
    test.insert(10);
    test.insert(30);
    test.insert(3);
    test.insert(40);

    auto val = test1.insert(20);

    std::cout << test1<<val <<std::endl;
    std::cout << "la taille : " << test1.current_space() << std::endl;

    test1.insert(10);test1.insert(30);

    if (test1.exists(20)){
        std::cout<<"rends pas fou";
    };

    return 0
}
