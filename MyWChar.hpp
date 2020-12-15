#ifndef _MYWCHAR_H_
#define _MYWCHAR_H_

class MyWChar {
  unsigned data;
  friend std::ostream& operator<< (std::ostream&,const MyWChar&);
  friend bool operator==(const MyChar& first, const MyChar& second);
  friend bool operator<(const MyChar& first, const MyChar& second);
public:
  // constructeurs
  constexpr MyWChar (wchar_t c = 0) noexcept:     // conversion
      data(L'A' <= c && c <= L'Z' ? unsigned(c)-0x40 :
           L'a' <= c && c <= L'z' ? unsigned(c)-0x60 : 0) {}
  constexpr MyWChar (MyChar c): data(c.num()) {}
  // observateurs
  constexpr unsigned num () const noexcept {return data;}
  constexpr operator wchar_t () const noexcept   // conversion
    {return data ? wchar_t(data+0x40) : ' ';}
  constexpr operator MyChar () const noexcept     // conversion
    {return data ? char(data+0x40) : ' ';}
}; // MyWChar

bool operator==(const MyWChar& first, const MyWChar& second) {return first.num() == second.num();}
bool operator<(const MyWChar& first, const MyWChar& second) {return first.num() < second.num();}

std::ostream& operator<<(std::ostream& out,const MyWChar& obj)
{
    !obj.num()? out<< " ": out << static_cast<char>(obj);
    return out;

}

#endif // _MYWCHAR_H_
