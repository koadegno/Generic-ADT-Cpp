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
  virtual ~Cont_base()=0;
protected:
  static constexpr const Info _EMPTY{};
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}
  // Implementation



  // ...
public:
  // ...
}; // Cont_base<T>

template <typename T>
Cont_base<T>::~Cont_base() {}

// Embedded class Info =====================================================

template <typename T>
class Cont_base<T>::Info {
  friend class Cont_base<T>;   // for _index static methods
  std::ptrdiff_t _index = -1;  // valeur sentinelle
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
class Cont final: private Cont_base<T>, public BST< typename Cont_base<T>::Info >, public Vect_fix< typename Cont_base<T>::Ptr2Info >  {
  using _Base = Cont_base<T>;
  using _Vect = Vect_fix<typename _Base::Ptr2Info >;
  using _BST =  BST<typename _Base::Info>;
  using _Base::_index;
  using _Base::_ptr;

  const std::size_t DIM;
  std::ptrdiff_t current_vect_idx{};
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
  explicit Cont (std::size_t taille ):DIM(taille), _Base(), _Vect(taille){};

  // methode
  const T& insert (const T& v) {

      bool cond_to_ins = _BST::exists(Info(v));
      if (!cond_to_ins){
          auto tmp = _BST::insert(Info(current_vect_idx,v));
          current_vect_idx++;
          return tmp;
      }
      else{

        //throw std::domain_error("Already in ... ");
        std::cout<< "\nDeja dedans : "<< v <<std::endl;
      };

      };

  const std::size_t current_space() {return current_vect_idx;}



  virtual ~Cont() override {};
}; // Cont<T>



// Deduction guides ==========================================================
/*
template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;
*/
#endif // _CONT_H_
