
/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Yves Roggeman - 2020/09 - <Vect.hpp>
 * ADT de vecteur dynamique (taille variable) et paramétrique (template)
 * Copies et transferts possibles
 */
#ifndef _Vect_H_
#define _Vect_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <initializer_list>    // liste d'initialisation
#include  <exception>
#include  <stdexcept>           // exceptions standard
#include  <ostream>             // Flux d'output

template <typename T>
class Vect {
  std::size_t _dim = 0;
  T *_val = nullptr;
  inline static T* _cp (const Vect&);

public:
  // constructeurs
  constexpr Vect () noexcept = default;   // Tableau vide
  explicit Vect (std::size_t d) noexcept: _dim(d), _val(new T[d]) {}

  // observateurs
  constexpr std::size_t dim () const noexcept {return _dim;}
  virtual inline const T& operator[] (std::ptrdiff_t) const;
  // modificateurs
  inline T& operator[] (std::ptrdiff_t);

  // copies, transferts, etc.
  Vect (const Vect& v) noexcept: _dim(v._dim), _val(_cp(v)) {}
  constexpr Vect (Vect&& v) noexcept: _dim(v._dim), _val(v._val)
    {v._dim = 0; v._val = nullptr;}
  inline Vect& operator= (const Vect&) noexcept;
  inline Vect& operator= (Vect&&) noexcept;
  // destructeur
  ~Vect () noexcept {delete[] _val;}



}; // Vect<T>

// constructeurs ============================================================


// observateurs =============================================================

template <typename T>
const T& Vect<T>::operator[] (std::ptrdiff_t idx) const {
  if (std::size_t(idx) >= _dim){
    throw std::domain_error("Vect::op[]: index out of range");};

  return _val[idx];
}

// modificateurs ============================================================

template <typename T>
T& Vect<T>::operator[] (std::ptrdiff_t idx) {
  if (std::size_t(idx) >= _dim){
    throw std::domain_error("Vect::op[]: index out of range");};

  return _val[idx];
}

// copies, transferts, etc. =================================================

template <typename T>
T* Vect<T>::_cp (const Vect<T>& v) {
  T *res = new T[v._dim];
  for (std::size_t i = 0; i < v._dim; ++i) res[i] = v._val[i];
  return res;
}

template <typename T>
Vect<T>& Vect<T>::operator= (const Vect& v) noexcept {
  if (this != &v) {delete[] _val; _dim = v._dim; _val = _cp(v);}
  return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator= (Vect&& v) noexcept {
  if (this != &v) {
    delete[] _val; _dim = v._dim; _val = v._val;
    v._dim = 0; v._val = nullptr;
  }
  return *this;
}

// fonctions externes =======================================================


#endif // _Vect_H_
