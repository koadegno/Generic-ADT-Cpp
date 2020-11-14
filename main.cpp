#include <iostream>

#include  "Vect.hpp"
#include  "BST.hpp"
#include "Cont.hpp"
#include <cstddef>
#include "MyChar.hpp"
#include "MyWChar.hpp"


#define TEST


#ifdef TEST

template <typename V>
max(BST<typename Cont<V>::Info>* tree){
    Vect<typename Cont<V>::Ptr2Info>* vect = dynamic_cast< Vect<typename Cont<V>::Ptr2Info>* >(tree);
    V biggest{};
    for (std::size_t i=0; i < vect->dim(); i++){

        V tmp = (*vect)[i];
        std::cout << "indice : " << i <<" Value : "<< tmp <<std::endl;
        biggest < tmp ? biggest = tmp: false;

    }
    return biggest;
};

void print_vect(const Vect<Cont<int>::Ptr2Info>* obj_vect){
    std::cout<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[ ";

    for(std::size_t i=0; i < obj_vect->dim(); i++)
        std::cout << (*obj_vect)[i]<< " " ;

    std::cout << "]"<<std::endl;
}
#endif // TEST


int main(){


    Cont<int>var{20};

    Vect<int> test(10);
    test[0] = 2; test[2] = 4;

    //Cont var(test);

    var.insert(30,2);var.insert(3,3);var.insert(90,0);var.insert(101,var.dim()-1);

    BST<Cont<int>::Info>* b;
    b = &var;
    //auto z =  Cont<int>::Info(84);
    //b->insert(z,4);
    auto f = static_cast< Vect<Cont<int>::Ptr2Info>* >(&var);

    std::cout << (*b) << std::endl;
    std::cout << var << std::endl;
    std::cout << var.find(30) << std::endl;
    std::cout << "\n***************"<<std::endl;
    std::cout << (*b) << std::endl;
    std::cout << var << std::endl;
    std::cout << var.find(32,1) << std::endl;
    std::cout << "\n***************"<<std::endl;
    std::cout << (*dynamic_cast< Vect<Cont<int>::Ptr2Info>* >(b))[0] << std::endl; std::cout << "___________------__________"<<std::endl;
    std::cout << var << std::endl;

    print_vect(f);

    std::cout << max<int>(b) << std::endl;

    return 0;
}
