#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"
#include <cstddef>


template<typename T>void add(T& value,const BST<T>& obj) {obj.insert(value,0);}



int main(){

    Cont<int> var(20);

    for (std::size_t i = 0; i < var.dim(); i++){ var.insert((int)i+13,(std::ptrdiff_t)i);}
    std::cout << var[8] << std::endl;
    std::cout << var <<std::endl;


    Cont<int> var2(20);
    add(2,var2); 
    std::cout << var2 <<std::endl;


    return 0;
}
