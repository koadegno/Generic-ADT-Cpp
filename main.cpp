#include <iostream>
#include "Cont.hpp"
#include  "Vect2.hpp"
#include  "BST.hpp"


int main(){

    Cont<int> var(10);
    Vect_dyn<int> test(10);


    for (std::size_t i = 0; i < var.dim(); i++){ var.insert((int)i+13,(std::ptrdiff_t)i);}



 std::cout << var.node_number() <<std::endl;

    std::cout << var <<std::endl;

    return 0;
}
