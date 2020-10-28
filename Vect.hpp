/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Yves Roggeman - 2020/09 - <Vect_fix.hpp>
 * ADT de vecteur statique, mais paramétrique (template)
 * Taille fixée dans le type; transferts impossibles
 */
#ifndef _VECT_FIX_H_
#define _VECT_FIX_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <initializer_list>    // liste d'initialisation
#include  <exception>
#include  <stdexcept>           // exceptions standard
#include  <ostream>             // Flux d'output

template <typename T, std::size_t DIM>
class Vect_fix {
  T _val[DIM]{};
  T _NULL{};
  void _to_null(T vec[]){ for(std::size_t i=0; i<=DIM; i++){}   }
public:
  // constructeurs
  constexpr Vect_fix () noexcept = default;   // Tableau vide
  constexpr Vect_fix (const std::initializer_list<T>&) noexcept;
  // observateurs
  static constexpr std::size_t dim () noexcept {return DIM;}
  inline const T& operator[] (std::ptrdiff_t) const;
  // modificateurs
  inline T& operator[] (std::ptrdiff_t);

  // copie && transfer
  Vect_fix (const Vect_fix &v): _val(v._val){};
  Vect_fix (const Vect_fix&& v): _val(v._val){};

  virtual Vect_fix& operator= (const Vect_fix& v) = delete;
  virtual Vect_fix& operator= (const Vect_fix&& v) = delete;


  // fonctions externes
  template <typename U, std::size_t D>
  friend inline std::ostream& operator<< (std::ostream&, const Vect_fix<U,D>&);


}; // Vect_fix<T>

// constructeurs ============================================================

template <typename T, std::size_t DIM>
constexpr Vect_fix<T, DIM>::Vect_fix (const std::initializer_list<T>& init) noexcept {
  const std::size_t d = init.size() < DIM ? init.size() : DIM;
  auto p = init.begin();
  for (std::size_t i = 0; i < d; ++i) _val[i] = *p++;
}

// observateurs =============================================================

template <typename T, std::size_t DIM>
const T& Vect_fix<T, DIM>::operator[] (std::ptrdiff_t idx) const {
  if (std::size_t(idx) >= DIM)
    throw std::domain_error("Vect_fix::op[]: index out of range");
  return _val[idx];
}

// modificateurs ============================================================

template <typename T, std::size_t DIM>
T& Vect_fix<T, DIM>::operator[] (std::ptrdiff_t idx) {
  if (std::size_t(idx) >= DIM)
    throw std::domain_error("Vect_fix::op[]: index out of range");
  return _val[idx];
}

// fonctions externes =======================================================

template <typename T, std::size_t DIM>
inline std::ostream& operator<< (std::ostream& out, const Vect_fix<T, DIM>& v){
  out << "[ "; for (auto x: v._val) out << x << ' '; out << ']';
  return out;
}



#endif // _VECT_FIX_H_
