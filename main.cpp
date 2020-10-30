#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"


int main(){
    Cont<int> test1(2);
    //#ifndef _BST_DBG_
    #define _BST_DBG_
    BST<int> test;
    test.insert(10);
    test.insert(30);
    test.insert(3);
    test.insert(40);

    test1.insert(20);//
    std::cout << test1 <<std::endl;
    std::cout << "la taille : " << test1.current_space() << std::endl;
    test1.insert(10);test1.insert(30);test1.insert(20);
    std::cout << test1 <<std::endl;
    std::cout << "la taille : " << test1.current_space() << std::endl;


    //#endif // _BST_DBG_


}
