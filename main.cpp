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
const V max(const BST<typename Cont<V>::Info>* tree){
    const Vect<typename Cont<V>::Ptr2Info>* vect = dynamic_cast<const Vect<typename Cont<V>::Ptr2Info>* >(tree);
    V biggest;
    for (std::size_t i=0; i < vect->dim(); i++){

        const V& tmp = (*vect)[i];
        std::cout << "indice : " << i <<" Value : "<< tmp <<std::endl;
        //biggest < tmp ? biggest = tmp: false;
        if (biggest < tmp){ biggest = tmp;};

    }
    return biggest;
};

template <typename V>
const V min(const BST<typename Cont<V>::Info>* tree){
    const Vect<typename Cont<V>::Ptr2Info>* vect = dynamic_cast<const Vect<typename Cont<V>::Ptr2Info>* >(tree);
    V min_ = (*vect)[0];
    for (std::size_t i=0; i < vect->dim(); i++){

        const V& tmp = (*vect)[i];
        std::cout << "indice : " << i <<" Value : "<< tmp <<std::endl;
        //biggest < tmp ? biggest = tmp: false;
        if (tmp < min_){ min_ = tmp;};

    }
    return min_;
};



template<typename K>
const std::ptrdiff_t index(const BST<typename Cont<K>::Info>* tree,const K& to_search){
    std::ptrdiff_t ret_val = -1;
    if (tree->exists(to_search)){
        K val = 0;
        const Vect<typename Cont<K>::Ptr2Info>* vect = dynamic_cast<const Vect<typename Cont<K>::Ptr2Info>* >(tree);
        for(std::size_t i =0; i< vect->dim(); i++){
            val = (*vect)[i];
            if( val == to_search){ret_val = i;break;}

        };
    }
    return ret_val;
}

template<typename K>
void clear(Vect< typename Cont<K>::Ptr2Info >* vecteur){
    delete *vecteur;
}

void print_vect(const Vect<Cont<int>::Ptr2Info>* obj_vect){
    std::cout<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[ ";

    for(std::size_t i=0; i < obj_vect->dim(); i++)
        std::cout << (*obj_vect)[i]<< " " ;

    std::cout << "]"<<std::endl;
}
#endif // TEST


int main(){


    Cont<int>var{5};

    Vect<int> test(10);
    test[0] = 2; test[2] = 4;

    //Cont var(test);

    var.insert(30,2);var.insert(3,3);var.insert(90,0);var.insert(101,var.dim()-1);var.insert(6,1);

    BST<Cont<int>::Info>* b;
    Vect<Cont<int>::Ptr2Info>* c;
    b = &var;
    c = &var;
    //auto z =  Cont<int>::Info(84);
    //b->insert(z,4);
    auto f = static_cast< Vect<Cont<int>::Ptr2Info>* >(&var);

    std::cout <<"Find value 30\n";
    std::cout << (*b) << std::endl;
    std::cout << var << std::endl;
    std::cout << var.find(30) << std::endl;
    std::cout << "\n***************"<<std::endl;
    std::cout <<"Find value 32 with index 1\n";
    std::cout << (*b) << std::endl;
    std::cout << var << std::endl;
    std::cout << var.find(32,1) << std::endl;
    std::cout << "\n***************"<<std::endl;
    std::cout << (*dynamic_cast< Vect<Cont<int>::Ptr2Info>* >(b))[0] << std::endl; std::cout << "___________------__________"<<std::endl;
    std::cout << var << std::endl;

    printf("\n\nFunction to print Cont\n\n");
    print_vect(f);

    std::cout<<"\n----------------------------------\nFind the max and the index of a value " <<std::endl;
    std::cout << min<int>(b) << std::endl;

    std::cout << index<int>(b,3) << std::endl;

    std::cout<<"\n----------------------------------\Clear the Cont " <<std::endl;
    clear<int>(c);
    std::cout << var << std::endl;

    return 0;
}
