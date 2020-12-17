#include <iostream>

#include "Vect.hpp"
#include "BST.hpp"
#include "Cont.hpp"
#include <cstddef>
#include <cstdlib>
#include "MyChar.hpp"
#include "MyChar.hpp"
#include "personne.hpp"

char LETTRE[] = {'k','F','d','A','D','u','O','w','M'};
std::size_t LETTRE_SIZE = 9;


template <typename V>
const V max(const Vect<typename Cont<V>::Ptr2Info>* vecteur){
    /**
     * @brief Indique la maximun dans le vect
     * 
     */
    
    V biggest = V{};
    for (std::size_t i=0; i < vecteur->dim(); i++){

        const V& tmp = (*vecteur)[std::ptrdiff_t(i)];
        if (biggest < tmp){ biggest = tmp;};

    }
    return biggest;
}

template<typename V>
const V min(const Cont<V>& cont){
    /**
     * @brief Indique le minimum dans un cont
     * 
     */

    V min_ = cont[0];
    for (std::size_t i=1; i < cont.dim(); i++){
        min_ = (cont[std::ptrdiff_t(i)]< min_) ? cont[std::ptrdiff_t(i)]:min_;
    }
    //std::cout<< min_ << std::endl;
    return min_;
}

template<typename K>
void print_vect(const Vect<typename Cont<K>::Ptr2Info>* obj_vect){
    /**
     * @brief affiche le vecteur 
     * 
     */
    std::cout<< "Vecteur  : [ ";
    for(std::size_t i=0; i < obj_vect->dim(); i++){
        
        std::cout << (*obj_vect)[std::ptrdiff_t(i)]<< " " ;
    }
    std::cout << "]"<<std::endl;
}

template<typename K>
void init_pers(BST<typename Cont<K>::Info>* obj_bst, std::size_t taille){
    /**
     * @brief Initialise un bst avec des Personne 
     * 
     */
    
    srand(7858);
    for (std::size_t i = 0; i< taille; i++){
        
        obj_bst->insert({std::ptrdiff_t(i),Personne(char(MyChar(LETTRE[rand()%int(LETTRE_SIZE)])),rand()%70)});
    }
    std::cout << *obj_bst << std::endl;
}

template<typename K>
void init_char(BST<typename Cont<K>::Info>*bst,std::size_t taille){
    /**
     * @brief Initialise un bst avec des char
     * 
     */

    
    srand(78958);
    for (std::size_t i = 0; i< taille; i++){
        MyChar tmp = MyChar(LETTRE[rand()%int(LETTRE_SIZE)]);
        //std::cout << tmp << " ";
        bst->insert({std::ptrdiff_t(i),tmp});
    }
    //printf("\n");
    std::cout << *bst << std::endl;
}

template<typename K>
void test1_bst(BST<typename Cont<K>::Info>* bst){
    /**
     * @brief supprimer si un noeud existe dans l'arbre (pour Mychar)
     * 
     */
    
    std::size_t j = bst->node_number();
    
    for(std::size_t i=0; i<j; i++){
        K to_search{LETTRE[rand()%int(LETTRE_SIZE)]};
        if (bst->exists({to_search})){
            
            bst->erase({to_search});
        }
    }
    std::cout << *bst << std::endl;
    
}

template<typename T>
void test2_bst(const BST<typename Cont<T>::Info>* bst){
    /**
     * @brief indique si un noeud existe dans l'arbre (Pour MyChar)
     * 
     */
    
    
    if(!(bst->isEmpty())){
        
        for(std::ptrdiff_t i=0; std::size_t(i)<bst->node_number(); i++){
            
            T to_search{LETTRE[rand()%int(LETTRE_SIZE)]};
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
/**
 * @brief fonction de test pour Cont avec le type MyChar
 * 
 */
    
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
    /**
     * @brief Fonction de test du Cont avec le type Personne
     * 
     */
    
    std::cout << "----------------------------------\n\n";
    
    Cont<Personne> persCont{10}; 
    init_pers<Personne>(&persCont,persCont.dim());
    print_vect<Personne>(&persCont);
    std::cout<<"MIN : "<< min<Personne>(persCont) << std::endl;
    persCont.erase(min<Personne>(persCont));
    persCont.insert({0,Personne('J',45)});
    std::cout << persCont << std::endl;
    persCont.erase({Personne('K',41)});
    std::cout << persCont << std::endl;
    Personne pers1{'F',15};
    if (persCont.exists({8,pers1})){
        persCont.erase({8,pers1});
        std::cout << pers1 << " indice : 8"<<std::endl;
    }
    else{persCont.erase({9,pers1});
    std::cout << pers1 << " indice : 9"<<std::endl;}
    print_vect<Personne>(&persCont);
    


    std::cout << persCont << std::endl;


}

int main(){

    //Test1();

    //Test2();
    
    std::size_t motSize = 14;
    Cont<MyChar> mycharCont(motSize);
    Cont<MyChar> mycharCont2(motSize);
    init_char<MyChar>(&mycharCont,mycharCont.dim());

    mycharCont2 = mycharCont;

    return 0;
}
