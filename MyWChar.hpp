/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Yves Roggeman - 2020/09 - <MyWChar.hpp>
 * Exercice de conversions
 * Classe de caractères étranges (version wchar_t)
 */
#ifndef _MYWCHAR_H_
#define _MYWCHAR_H_

class MyWChar {
  unsigned _val;
  friend std::ostream& operator<< (std::ostream&,const MyWChar&);
  friend bool operator==(const MyChar& first, const MyChar& second);
  friend bool operator<(const MyChar& first, const MyChar& second);
public:
  // constructeurs
  constexpr MyWChar (wchar_t c = 0) noexcept:     // conversion
      _val(L'A' <= c && c <= L'Z' ? unsigned(c)-0x40 :
           L'a' <= c && c <= L'z' ? unsigned(c)-0x60 : 0) {}
  constexpr MyWChar (MyChar c): _val(c.num()) {}
  // observateurs
  constexpr unsigned num () const noexcept {return _val;}
  constexpr operator wchar_t () const noexcept   // conversion
    {return _val ? wchar_t(_val+0x40) : ' ';}
  constexpr operator MyChar () const noexcept     // conversion
    {return _val ? char(_val+0x40) : ' ';}
}; // MyWChar

bool operator==(const MyWChar& first, const MyWChar& second) {return first.num() == second.num();};
bool operator<(const MyWChar& first, const MyWChar& second) {return first.num() < second.num();}

std::ostream& operator<<(std::ostream& out,const MyWChar& obj)
{
    obj.num()==0? out<< " ":out << wchar_t(obj.num());

    return out;

};

#endif // _MYWCHAR_H_
