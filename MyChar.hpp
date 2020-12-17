#ifndef _MYCHAR_H_
#define _MYCHAR_H_

#include <iostream>

class MyChar {
  unsigned data;
  friend std::ostream& operator<< (std::ostream&,const MyChar&);
  friend bool operator==(const MyChar& first, const MyChar& second);
  friend bool operator<(const MyChar& first, const MyChar& second);
public:
  // constructeurs
    constexpr MyChar (char c = 0) noexcept:      // conversion
      data('A' <= c && c <= 'Z' ? unsigned(c)-0x40 :
           'a' <= c && c <= 'z' ? unsigned(c)-0x60 : 0) {}
    // observateurs
    constexpr unsigned num () const noexcept {return data;}
    constexpr operator char () const noexcept   // conversion
    {return data ? char(data+0x40) : ' ';}

    inline bool operator==(const MyChar& second) {return data == second.data;}

    inline bool operator< (const MyChar& second) {return data < second.data;}

}; // MyChar

bool operator==(const MyChar& first, const MyChar& second) {return first.data == second.data;}
bool operator<(const MyChar& first, const MyChar& second) {return first.data < second.data;}

std::ostream& operator<<(std::ostream& out,const MyChar& obj)
{
    obj.num()==0? out<< " ":out << char(obj);
    return out;

}

#endif // _MYCHAR_H_
