#if !defined(__PERSONNE__)
#define __PERSONNE__

#include <iostream>
#include <string>
#include <iostream>


class Personne
/* Represente un personne, cette personne peut etre infecter par une maladie.*/
{
    std::string _prenom;
    std::string _nom;
    friend std::ostream& operator<< (std::ostream&,const Personne&);
    friend bool operator==(const Personne& first, const Personne& second);
    friend bool operator<(const Personne& first, const Personne& second);
    int _age;
public:
        Personne() noexcept; 
        Personne(std::string prenom,std::string nom = "",int age = 1);
        Personne(std::string nom,int age):_prenom("Erik") ,_nom(nom),_age(age){}
        ~Personne(){}
        
        Personne& operator=(const Personne &copy)= delete;
        inline bool operator==(const Personne& second){return _age == second._age;}
        inline bool operator<(const Personne& second){return _age < second._age;}

        const std::string info_pers() const;
};

//============ code ================================

bool operator==(const Personne& first, const Personne& second){
    return first._age == second._age;
}

bool operator<(const Personne& first, const Personne& second){
    return first._age < second._age;
}

std::ostream& operator<<(std::ostream& out, const Personne& obj){
    out<< obj.info_pers();
    return out;
}

Personne::Personne()noexcept:_prenom("Jean"),_nom("Dupont"),_age(35){}
/* Constructeur avec parametre par defaut*/


Personne::Personne(std::string prenom ,std::string nom , int age ):
_prenom(prenom),_nom(nom),_age(age){}


const std::string Personne::info_pers() const
/* return les infos sur la personne*/
{
    std::string info;info = _nom + " " +_prenom+ " "+ std::to_string(_age)+" ans";
    return info;
}


#endif