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
const std::ptrdiff_t index(const BST<typename Cont<K>::Info>* tree, const K& to_search){
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
void print_vect(const Vect<typename Cont<K>::Ptr2Info>* obj_vect){
    std::cout<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[ ";

    for(std::size_t i=0; i < obj_vect->dim(); i++)
        std::cout << (*obj_vect)[i]<< " " ;

    std::cout << "]"<<std::endl;
}
#endif // TEST


void Test1(){

    char mot[] = "Adegno";
    std::size_t motSize = 6;
    Cont<MyChar> mycharCont(motSize);
    
    for (std::size_t i= 0; i< motSize; i++){
        mycharCont.insert(MyWChar(mot[i]),i);
        
    };

    std::cout << mycharCont<< std::endl;
    //print_vect(mycharCont);
    

}

int main(){

    Test1();
    return 0;
}
