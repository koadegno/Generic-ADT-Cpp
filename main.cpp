#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"
#include <cstddef>
#include "MyChar.hpp"
#include "MyWChar.hpp"



int main(){

    MyWChar test('a');
    MyWChar test2{'s'};
    Cont<MyWChar> var(20);


    std::cout << test <<std::endl;
    var.insert(test); var.insert(test2);
    //add(var);
    std::cout << var.find(test2,1)<<std::endl;
    std::cout << char(var[1]) <<std::endl;







    return 0;
}
