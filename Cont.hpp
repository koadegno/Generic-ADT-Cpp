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
  std::size_t current_vect_idx{};

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
  const T& insert (const T& v)  {

      Info info_wrapper = Info(current_vect_idx,v);
      Ptr2Info ptr_wrapper{};

      bool cond_to_ins = _BST::exists(info_wrapper);

      if (!cond_to_ins && current_vect_idx < DIM){
            auto tmp = _Base::_ptr(ptr_wrapper); // get the Info* inside ptr_wrapper
            //std::cout << "indice : " << current_vect_idx << std::endl;
            tmp = &info_wrapper; _Vect::operator[](current_vect_idx) = ptr_wrapper ; // add inside the vecteur
            current_vect_idx++;

            auto val =  _BST::insert(info_wrapper);

            return val;
      }
      else{
            // TODO can i throw an error ?
            //throw std::domain_error("Already in ... ");
            std::cout<< "\nDeja dedans ou Plus assez de place !!\nValue : "<< v <<std::endl;

            return _BST::_NOT_FOUND;
      };

      };

  const bool erase(const T& v) {

        Info info_wrapper = Info(v);bool cond_to_del = _BST::exists(info_wrapper);

        if ( !cond_to_del ){
            auto the_info = _BST::find(info_wrapper);
            auto the_ptr2info = _Base::_index(the_info);
            _BST::erase(the_info); _Vect::operator[](the_ptr2info) = _Vect::_NULL;
            return true;
        }
        else{
            std::cout << "\nExiste pas tu joues a quoi ?  Value : "<< info_wrapper <<std::endl;
            return false;
        };


  }

  bool exists (const T& v) const noexcept override{
        return _BST::exists( Info(v) );


  }

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
