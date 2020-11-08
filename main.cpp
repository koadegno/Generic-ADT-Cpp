#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"
#include <cstddef>
#include "MyChar.hpp"
#include "MyWChar.hpp"


#ifdef TEST
void bst_add_int(std::ptrdiff_t idx, int value, BST<int> obj_bst) {
    //obj_bst.insert(idx,value);
    return;
}

void print_vect(std::ostream& out, Vect<int>* obj_vect){
    out<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[";

    for(std::size_t i=0; i < obj_vect->dim(); i++)
        out << obj_vect[i];

    out << "]"<<std::endl;
}
#endif // TEST


int main(){


    Cont<int>var{20};

    Vect<int> test(10);
    test[0] = 2; test[2] = 4;

    //Cont var(test);

    auto t = var.insert(30);var.insert(3);var.insert(32);


    #ifdef TEST
    BST<int>* b;

    BST<MyWChar> c{};
    Cont v(c);
    #endif // TEST


    //print_vect(std::cout,&var);

    std::cout << var <<t<< std::endl;

    return 0;
}
