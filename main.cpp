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

template <typename V>
const V min(const Vect<typename Cont<V>::Ptr2Info>* vect){
    
    V min_ = (*vect)[0];
    for (std::size_t i=1; i < vect->dim(); i++){

        const V& tmp = (*vect)[std::ptrdiff_t(i)];
        if (tmp < min_){ min_ = tmp;};

    }
    return min_;
}


template<typename K>
std::ptrdiff_t index(const Vect<typename Cont<K>::Ptr2Info>* vect, K& to_search){
    std::ptrdiff_t ret_val = -1;
    
    K val{};
    for(std::size_t i =0; i< vect->dim(); i++){
        val = (*vect)[std::ptrdiff_t(i)];
        if( val == to_search){ret_val = std::ptrdiff_t(i);break;}

        };
    
    return ret_val;
}


template<typename K>
void print_vect(const Vect<typename Cont<K>::Ptr2Info>* obj_vect){
    std::cout<< "Vecteur de taille : "<<obj_vect->dim()<<std::endl << "[ ";

    for(std::size_t i=0; i < obj_vect->dim(); i++)
        std::cout << (*obj_vect)[i]<< " " ;

    std::cout << "]"<<std::endl;
}


void Test1(){

    char mot[] = "dvpgnAoeZybwux";
    std::size_t motSize = 14;
    Cont<MyChar> mycharCont(motSize);
    BST<typename Cont<MyChar>::Info>* wordTree =nullptr;
    wordTree = &mycharCont;

    for (std::size_t i= 0; i< motSize; i++){
        wordTree->insert(MyChar(mot[i]));
        
    };

    std::cout <<"Le conteneur : "<< mycharCont<< std::endl;
    
    auto tmp = min<MyChar>(&mycharCont);
    std::cout << "min value : "<<tmp<<std::endl;
    std::ptrdiff_t idx = index<MyChar>(&mycharCont,tmp);
    mycharCont.erase(tmp,idx);
    std::cout <<"Le conteneur : "<< *wordTree<< std::endl;
    mycharCont.insert(tmp,5);
    std::cout <<"Le conteneur : "<< *wordTree<< std::endl;

    tmp = max<MyChar>(&mycharCont);
    std::cout << "max value delete : " << tmp << std::endl;
    mycharCont.erase(max<MyChar>(&mycharCont),index<MyChar>(&mycharCont,tmp));
    std::cout <<"Le conteneur : "<< *wordTree<< std::endl;
    tmp = max<MyChar>(&mycharCont);
    std::cout << "max value delete : " << tmp << std::endl;
    wordTree->erase(tmp);

    std::cout <<"Le conteneur : "<< *wordTree<< std::endl;
    for (MyChar elem: mot){
        if (mycharCont.exists(elem)){
            wordTree->erase(elem);
        }
    }
    std::cout <<"Le conteneur : "<< mycharCont<< std::endl;

    for (std::ptrdiff_t i= 0; std::size_t(i)< motSize; i++){
        mycharCont.insert(MyChar(mot[i]),i);
        
    };

    std::cout <<"Le conteneur : "<< mycharCont<< std::endl;


}


void Test2(){
    Cont<int> ageCont{10};
    
    
    Cont<Personne> persCont{10};
    for (std::ptrdiff_t i = 0; std::size_t(i)< persCont.dim(); i++){
        
        try
        {
            persCont.insert(Personne{"Satie",rand()%70},i);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        };
        
        
    }

    

    std::cout << persCont << std::endl;

}

int main(){

    //Test1();

    Test2();


    return 0;
}
