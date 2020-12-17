#if !defined(__PERSONNE__)
#define __PERSONNE__

#include <iostream>
#include <string>
#include <iostream>


class Personne
/* Represente un personne, cette personne possedant un age*/
{
    char _initiale;
    int _age;
    friend std::ostream& operator<< (std::ostream&,const Personne&);
    friend bool operator==(const Personne& first, const Personne& second);
    friend bool operator<(const Personne& first, const Personne& second);
    
public:
    constexpr Personne(char init ='V',int age = 4) noexcept:_initiale(init),_age(age){}
    constexpr Personne(char init) noexcept:_initiale(init),_age(1){}

    ~Personne(){}
    
    Personne& operator=(const Personne &copy) {_initiale = copy._initiale; _age = copy._age; return *this;};
    inline bool operator==(const Personne& second){return _initiale == second._initiale;}
    inline bool operator<(const Personne& second){return _initiale < second._initiale;}

};

//====================== def ================================

bool operator==(const Personne& first, const Personne& second){
    return first._age == second._age;
}

bool operator<(const Personne& first, const Personne& second){
    return first._age < second._age;
}

std::ostream& operator<<(std::ostream& out, const Personne& obj){
    out<<obj._initiale<<"- "<<obj._age<< " ans";
    return out;
}

#endif