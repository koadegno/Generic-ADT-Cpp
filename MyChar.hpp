/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Yves Roggeman - 2020/09 - <MyChar.hpp>
 * Exercice de conversions
 * Classe de caractères étranges
 */
#ifndef _MYCHAR_H_
#define _MYCHAR_H_

#include <iostream>

class MyChar {
  unsigned _val;
  friend std::ostream& operator<< (std::ostream&,const MyChar&);
  friend bool operator==(const MyChar& first, const MyChar& second);
  friend bool operator<(const MyChar& first, const MyChar& second);
public:
  // constructeurs
    constexpr MyChar (char c = 0) noexcept:      // conversion
      _val('A' <= c && c <= 'Z' ? unsigned(c)-0x40 :
           'a' <= c && c <= 'z' ? unsigned(c)-0x60 : 0) {}
    // observateurs
    constexpr unsigned num () const noexcept {return _val;}
    constexpr operator char () const noexcept   // conversion
    {return _val ? char(_val+0x40) : ' ';}

    inline bool operator==(const MyChar& second) {return _val == second._val;}

    inline bool operator< (const MyChar& second) {return _val < second._val;}

}; // MyChar

bool operator==(const MyChar& first, const MyChar& second) {return first._val == second._val;};
bool operator<(const MyChar& first, const MyChar& second) {return first._val < second._val;}

std::ostream& operator<<(std::ostream& out,const MyChar& obj)
{
    obj.num()==0? out<< " ":out << static_cast<char>(obj);
    return out;

};

#endif // _MYCHAR_H_
