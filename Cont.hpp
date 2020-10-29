/* GNU C++ version 10.2 - "g++ -std=c++17"
 * NOM, Prénom - 2020/12 - <Cont.hpp>
 * Exemple de conteneur (projet n°1)
 */
#ifndef _CONT_H_
#define _CONT_H_

#include  "Vect.hpp"
#include  "BST.hpp"
#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

// Abstract base class =======================================================

template <typename T>
class Cont_base { // abstract
public:
  class Info;
  class Ptr2Info;
protected:
  static constexpr const Info _EMPTY{};
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}
  // Implementation

  virtual ~Cont_base()= 0;

  // ...
public:
  // ...
}; // Cont_base<T>

// Embedded class Info =====================================================

template <typename T>
class Cont_base<T>::Info {
  friend class Cont_base<T>;   // for _index static methods
  std::ptrdiff_t _index = -1;
  const T _data{};
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  // Constructors & casts
  constexpr Info () noexcept = default;
  constexpr Info (std::ptrdiff_t i, const T& v) noexcept: _index(i), _data(v) {}
  constexpr Info (const T& v) noexcept: _data(v) {}             // implicit cast
  constexpr operator const T& () const noexcept {return _data;} // implicit cast
}; // Info

// Embedded class Ptr2Info ===================================================

template <typename T>
class Cont_base<T>::Ptr2Info {
  friend class Cont_base<T>;   // for _ptr static methods
  const Info *_ptr = nullptr;
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  // Constructors & casts
  constexpr Ptr2Info () noexcept = default;
  constexpr operator const Info& () const noexcept     // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
  constexpr operator const T& () const noexcept        // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
  // Getter
  constexpr bool isEmpty () const noexcept {return !_ptr;}



}; // Ptr2Info

// Main class ================================================================

template <typename T>
class Cont final: private Cont_base<T>, public BST<T>, public Vect_fix<T>  {
  using _Base = Cont_base<T>;
  using _Vect = Vect_fix<T>;
  using _BST =  BST<T>;
  using _Base::_index;
  using _Base::_ptr;
  // ...
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  using Info = typename _Base::Info;
  using Ptr2Info = typename _Base::Ptr2Info;
  // ...

  // constructeur
  explicit Cont (std::size_t taille ) :_Base(), _BST(), _Vect(taille){};

  //explicit Cont (const T obj) :_Base(obj), _BST(obj), _Vect(obj,DIM){};

  virtual ~Cont() override = default;
}; // Cont<T>



// Deduction guides ==========================================================
/*
template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;
*/
#endif // _CONT_H_
