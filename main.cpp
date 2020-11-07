#include <iostream>
#include "Cont.hpp"
#include  "Vect.hpp"
#include  "BST.hpp"
#include <cstddef>
#include "MyChar.hpp"
#include "MyWChar.hpp"


template< typename T > void add(Cont<const BST<T>>& obj) {obj.insert(23);}

using tmp = BST<int>;

int main(){

    MyWChar test('a');
    Cont<MyWChar> var(20);

    std::cout << test <<std::endl;
    var.insert(test);
    std::cout << var[0] <<std::endl;







    return 0;
}
