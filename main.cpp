#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"


int main(){

    Cont<int> var(10);

    for (std::size_t i = 0; i < var.dim(); i++){ var.insert((int)i+13,(std::ptrdiff_t)i);}

    Cont<int> var2(14);
    printf("%d\n",(int)var2.dim());
    var2.insert(242,1);
    std::cout << var2 <<std::endl;

    var = var2;std::cout << var2 <<std::endl;




    std::cout <<"nb de noeud : "<< var.node_number() <<std::endl;

    std::cout << var <<std::endl;

    return 0;
}
