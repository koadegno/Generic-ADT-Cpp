#include <iostream>
#include "Vect.hpp"


int main(){
    int tab[7] = {1,2,3,4,5,6};
    Vect_fix<int,40> tab2;

    std::cout<< tab2<<std::endl;

    int val=45;
    for(int i= 0; i < 40; i++){
        tab2[i]= val;
        val++;
    }
    std::cout<< tab2<<std::endl;
    std::cout << "HELLo WORld" << std::endl;
}
