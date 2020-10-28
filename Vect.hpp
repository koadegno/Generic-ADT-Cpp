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

template <typename T>
class Vect_fix {
  std::size_t const DIM;
  T* _val;
  T _NULL{};
  void _to_null(T vec[]){ for(std::size_t i=0; i<=DIM; i++){}   };
public:
  // constructeurs
  //constexpr Vect_fix(): DIM(10) {T tab[DIM]{}; _val= tab;};   // Tableau vide
  constexpr Vect_fix (const std::size_t taille=10) noexcept;
  // observateurs
  const std::size_t dim () const noexcept {return DIM;};
  inline const T& operator[] (std::ptrdiff_t) const;
  // modificateurs
  inline T& operator[] (std::ptrdiff_t);

  // copie && transfer
  Vect_fix (const Vect_fix &v): _val(v._val){};
  Vect_fix (const Vect_fix&& v): _val(v._val){};

  virtual Vect_fix& operator= (const Vect_fix& v) = delete;
  virtual Vect_fix& operator= (const Vect_fix&& v) = delete;


  // fonctions externes
  template <typename U>
  friend inline std::ostream& operator<< (std::ostream&, const Vect_fix<U>&);


}; // Vect_fix<T>

// constructeurs ============================================================

template <typename T>
constexpr Vect_fix<T>::Vect_fix (std::size_t taille) noexcept : DIM(taille) {T tab[DIM]{}; _val= tab;}

// observateurs =============================================================

template <typename T>
const T& Vect_fix<T>::operator[] (std::ptrdiff_t idx) const {
  if (std::size_t(idx) >= DIM)
    throw std::domain_error("Vect_fix::op[]: index out of range");
  return _val[idx];
}

// modificateurs ============================================================

template <typename T>
T& Vect_fix<T>::operator[] (std::ptrdiff_t idx) {
  if (std::size_t(idx) >= DIM)
    throw std::domain_error("Vect_fix::op[]: index out of range");
  return _val[idx];
}

// fonctions externes =======================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Vect_fix<T>& v){
    const std::size_t tmp = v.dim();
  out << "[ "; for (std::size_t i=0; i< tmp;i++){ out << v._val[i] << ' ';}; out << ']';
  return out;
}



#endif // _VECT_FIX_H_
