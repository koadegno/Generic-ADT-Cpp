
/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Yves Roggeman - 2020/09 - <Vect_dyn.hpp>
 * ADT de vecteur dynamique (taille variable) et paramétrique (template)
 * Copies et transferts possibles
 */
#ifndef _VECT_DYN_H_
#define _VECT_DYN_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <initializer_list>    // liste d'initialisation
#include  <exception>
#include  <stdexcept>           // exceptions standard
#include  <ostream>             // Flux d'output

template <typename T>
class Vect_dyn {
  std::size_t _dim = 0;
  T *_val = nullptr;
  inline static T* _cp (const Vect_dyn&);
public:
  // constructeurs
  constexpr Vect_dyn () noexcept = default;   // Tableau vide
  explicit Vect_dyn (std::size_t d) noexcept: _dim(d), _val(new T[d]) {}
  //Vect_dyn (const std::initializer_list<T>&) noexcept;
  //Vect_dyn (std::size_t) noexcept;
  // observateurs
  constexpr std::size_t dim () const noexcept {return _dim;}
  inline const T& operator[] (std::ptrdiff_t) const;
  // modificateurs
  inline T& operator[] (std::ptrdiff_t);
  virtual T& insert(std::ptrdiff_t idx, const T& obj){
    if (std::size_t(idx) >= _dim)
    throw std::domain_error("Vect_dyn::op[]: index out of range");
    _val[idx] = obj;
  return _val[idx];}
  // copies, transferts, etc.
  Vect_dyn (const Vect_dyn& v) noexcept: _dim(v._dim), _val(_cp(v)) {}
  constexpr Vect_dyn (Vect_dyn&& v) noexcept: _dim(v._dim), _val(v._val)
    {v._dim = 0; v._val = nullptr;}
  inline Vect_dyn& operator= (const Vect_dyn&) noexcept;
  inline Vect_dyn& operator= (Vect_dyn&&) noexcept;
  // destructeur
  ~Vect_dyn () noexcept {delete[] _val;}
  // fonctions externes
  /*template <typename U>
  friend inline std::ostream& operator<< (std::ostream&, const Vect_dyn<U>&);*/
}; // Vect_dyn<T>

// constructeurs ============================================================


// observateurs =============================================================

template <typename T>
const T& Vect_dyn<T>::operator[] (std::ptrdiff_t idx) const {
  if (std::size_t(idx) >= _dim){
    throw std::domain_error("Vect_dyn::op[]: index out of range");};

  return _val[idx];
}

// modificateurs ============================================================

template <typename T>
T& Vect_dyn<T>::operator[] (std::ptrdiff_t idx) {
  if (std::size_t(idx) >= _dim){
    throw std::domain_error("Vect_dyn::op[]: index out of range");};

  return _val[idx];
}

// copies, transferts, etc. =================================================

template <typename T>
T* Vect_dyn<T>::_cp (const Vect_dyn<T>& v) {
  T *res = new T[v._dim];
  for (std::size_t i = 0; i < v._dim; ++i) res[i] = v._val[i];
  return res;
}

template <typename T>
Vect_dyn<T>& Vect_dyn<T>::operator= (const Vect_dyn& v) noexcept {
  if (this != &v) {delete[] _val; _dim = v._dim; _val = _cp(v);}
  return *this;
}

template <typename T>
Vect_dyn<T>& Vect_dyn<T>::operator= (Vect_dyn&& v) noexcept {
  if (this != &v) {
    delete[] _val; _dim = v._dim; _val = v._val;
    v._dim = 0; v._val = nullptr;
  }
  return *this;
}

// fonctions externes =======================================================


#endif // _VECT_DYN_H_
