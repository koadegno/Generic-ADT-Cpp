/* GNU C++ version 10.2 - "g++ -std=c++17"
 * NOM, Pr�nom - 2020/12 - <Cont.hpp>
 * Exemple de conteneur (projet n�1)
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
  static constexpr const Info& _EMPTY{};
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}
  // Implementation
  virtual ~Cont_base()=0;

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
class Cont final: private Cont_base<T>, public BST< typename Cont_base<T>::Info >, public Vect< typename Cont_base<T>::Ptr2Info >  {
  using _Base = Cont_base<T>;
  using _Vect = Vect<typename _Base::Ptr2Info >;
  using _BST  = BST<typename _Base::Info>;
  using _Base::_index;
  using _Base::_ptr;

  std::size_t DIM;


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

  explicit Cont (std::size_t taille ): _Base(), _Vect(taille),DIM(taille){};

  Cont (const Vect<T>& obj):_Vect(obj) {std::cout << "je suis call "<< std::endl;}

  Cont(const Cont& other)noexcept:_Base(other),_BST(other),_Vect(other),DIM(other.DIM){};

  constexpr Cont(Cont&& other)noexcept:_Base(std::move(other)),_BST(std::move(other)),_Vect(std::move(other)),DIM(other.DIM){
    //other = Cont<T>(0);
    other.DIM = 0;
  }

  Cont& operator= (const Cont& other){
    if(this!= &other){
      _Vect::operator=(other);
      _BST::operator=(other);
      DIM = other.DIM;
    }
    return *this;
  }

  Cont& operator= ( Cont&& other){
    if(this!= &other){
      _Vect::operator=(other);
      _BST::operator=(other);
      DIM = other.DIM; other.DIM = 0;

    }
    return *this;
  }

  // Getter
  const T& operator[](std::ptrdiff_t idx) const {
    auto val= _Vect::operator[](idx);
    //std::cout << val << std::endl;
    return val;
  };


  int const node_number () const {
    return _BST::node_number();}


  std::size_t const dim() const {
    return DIM;}


  const T& insert (const T& v, std::ptrdiff_t idx)  {

    Info* info_wrapper = new Info(idx,v);
    Ptr2Info ptr_wrapper{};

    bool cond_to_ins = _BST::exists(*info_wrapper);
    //printf("nb d'element : %d \n",_BST::node_number());

    if (!cond_to_ins && (std::size_t)idx < DIM){

      if ( _Base::_ptr(_Vect::operator[](idx)) != nullptr ){ // at idx there is != nullptr
        _BST::erase(_Vect::operator[](idx));
        std::cout<< "pb regs ici stp";
      }

      _Base::_ptr(ptr_wrapper) = info_wrapper; // get the reference to pointer to Info inside ptr_wrapper
      _Vect::operator[](idx) = ptr_wrapper ; // add inside the vecteur
      //std::cout << "Value : " << _Vect::operator[](idx) << " Index : " << idx << std::endl;
      auto val = _BST::insert(*info_wrapper);

      //delete info_wrapper;
      return val;
    }

        // TODO can i throw an error ?
        //throw std::domain_error("Already in ... ");
    std::cout<< "Insert n2\nDeja dedans ou Plus assez de place !!\nValue : "<< v <<std::endl;
    return _BST::_NOT_FOUND;

  }


  bool erase(const Info& v,std::ptrdiff_t idx=-1) {
    //Info info_wrapper = Info(v);
    bool cond_to_del = _BST::exists(v);

    if (cond_to_del){

      auto the_info = _BST::find(v);
      idx == -1 ? idx = _Base::_index(the_info):false;

      if (_Vect::operator[](idx) == v ){ // exist in BTS and Vect

        _BST::erase(the_info); _Vect::operator[](idx) = Ptr2Info{}; // erase from everywhere (BST and Vect)
        return true;
      }
    };

    // TODO modifier le cout
    std::cout << "\nExiste pas, Value and index : "<< v <<" "<< idx<< std::endl;
    return false;

  }


  bool exists  (const T& v) const {
        auto val = _BST::exists(Info(v));
        return val;
  };


  const Info& find (const Info& v,std::ptrdiff_t idx=-1) const noexcept {

    if (idx==-1) return _BST::find(v); // simple find value

    const Ptr2Info& vect_ptr2info = _Vect::operator[](idx);
    const Info* vect_info = _Base::_ptr(vect_ptr2info);


    if (vect_info && v==*vect_info){
      return *vect_info;
    }

    return _BST::_NOT_FOUND; // idx doesn't match

  };


  virtual ~Cont() override {};
}; // Cont<T>


// Deduction guides ==========================================================

template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;

#endif // _CONT_H_
