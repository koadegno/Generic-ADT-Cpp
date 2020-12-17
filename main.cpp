#include <iostream>

#include "Vect.hpp"
#include "BST.hpp"
#include "Cont.hpp"
#include <cstddef>
#include <cstdlib>
#include "MyChar.hpp"
#include "MyChar.hpp"
#include "personne.hpp"

template <typename V>
const V max(const Vect<typename Cont<V>::Ptr2Info>* vecteur){
    
    V biggest = V{};
    for (std::size_t i=0; i < vecteur->dim(); i++){

        const V& tmp = (*vecteur)[std::ptrdiff_t(i)];
        if (biggest < tmp){ biggest = tmp;};

    }
    return biggest;
}


template<typename K>
void print_vect(const Vect<typename Cont<K>::Ptr2Info>* obj_vect){
    std::cout<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[ ";
    const typename Cont<K>::Ptr2Info& EMPTY{};
    for(std::ptrdiff_t i=0; std::size_t(i) < obj_vect->dim(); i++){
        if ((*obj_vect)[i] = EMPTY){
            std::cout << (*obj_vect)[i]<< " " ;
        }
    }
    std::cout << "]"<<std::endl;
}

template<typename K>
void init_pers(BST<typename Cont<K>::Info>* obj_bst, std::size_t taille){
    char lettre[] = {'k','f','d','a','c','u','o','w','m'};
    srand(7892458);
    for (std::ptrdiff_t i = 0; std::size_t(i)< taille; i++){
        
        obj_bst->insert({i,Personne(lettre[rand()%9],rand()%70)});
    }
    std::cout << *obj_bst << std::endl;
}

template<typename K>
void init_char(BST<typename Cont<K>::Info>*bst,std::size_t taille){

    char lettre[] = {'k','f','d','a','c','u','o','w','m'};
    srand(7892458);
    for (std::ptrdiff_t i = 0; std::size_t(i)< taille; i++){
        MyChar tmp = MyChar(lettre[rand()%9]);
        //std::cout << tmp << " ";
        bst->insert({i,tmp});
    }
    //printf("\n");
    std::cout << *bst << std::endl;
}

template<typename K>
void test1_bst(BST<typename Cont<K>::Info>* bst){

    char lettre[] = {'k','f','d','a','c','u','o','w','m'};
    std::size_t j = bst->node_number()-7;
    
    for(std::ptrdiff_t i=0; std::size_t(i)<j; i++){
        K to_search{lettre[rand()%9]};
        std::cout << "to erase : " << to_search <<std::endl;
        if (bst->exists({to_search})){
            
            bst->erase({to_search});
        }
    }
    std::cout << *bst << std::endl;
    
}

template<typename T>
void test2_bst(const BST<typename Cont<T>::Info>* bst){

    char lettre[] = {'k','f','d','a','c','u','o','w','m'};
    
    if(!(bst->isEmpty())){
        
        for(std::ptrdiff_t i=0; std::size_t(i)<bst->node_number(); i++){
            
            T to_search{lettre[rand()%9]};
            if (bst->exists({to_search})){
                std::cout <<"Dans le bst : "<< bst->find(to_search) << std::endl;
            }
            else{
                std::cout <<"Pas dans le bst : " << to_search << std::endl;
            }
            
        }
    }
}


void Test1(){

    
    std::size_t motSize = 14;
    Cont<MyChar> mycharCont(motSize);
    init_char<MyChar>(&mycharCont,mycharCont.dim());

    test1_bst<MyChar>(&mycharCont);
    std::cout << mycharCont << std::endl;
    test2_bst<MyChar>(&mycharCont);

    print_vect<MyChar>(&mycharCont);
    std::cout << std::endl;

}


void Test2(){
    
    Cont<int> ageCont{10};
    
    
    Cont<Personne> persCont{10};
    const Vect<typename Cont<Personne>::Ptr2Info> * objvect = &persCont;

    std::cout << persCont[0] << std::endl;
    
    
    init_pers<Personne>(&persCont,persCont.dim());
    
    std::cout << persCont << std::endl;
    print_vect<Personne>(&persCont);
    
    

    std::cout << persCont << std::endl;


    

}

int main(){

    Test1();

    //Test2();
    

    return 0;
}
