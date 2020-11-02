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

  virtual const T& insert (const T& v) = 0;
  virtual const T& insert (const T& v, std::ptrdiff_t idx) = 0;
  virtual const bool erase(const T& v) = 0;
  virtual const bool erase(const T& v, std::ptrdiff_t idx) = 0;
  virtual const T& operator[] (std::ptrdiff_t idx) const = 0;
  virtual bool exists (const T& v) const = 0;
  virtual const T& find (const T&) const = 0;
  virtual const T& find (const T&, std::ptrdiff_t idx) const = 0;

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
  using _BST =  BST<typename _Base::Info>;
  using _Base::_index;
  using _Base::_ptr;

  std::size_t DIM;
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
  Cont() = delete;
  explicit Cont (std::size_t taille ): _Base(), _Vect(taille),DIM(taille){};

  Cont(const Cont& other)noexcept:_Base(other),_BST(other),_Vect(other),DIM(other.DIM),current_vect_idx(other.current_vect_idx){};

  constexpr Cont(Cont&& other)noexcept:_Base(other),_BST(other),_Vect(other),DIM(other.DIM),current_vect_idx(other.current_vect_idx){
    other = Cont<T>(); other.DIM = 0; other.current_vect_idx = 0;
  }

  Cont& operator= (const Cont& other){
    if(this!= &other){
      _Vect::operator=(other);
      _BST::operator=(other);
      DIM = other.DIM;
      current_vect_idx = other.current_vect_idx;
    }
    return *this;
  }

  Cont& operator= ( Cont&& other){
    if(this!= &other){
      _Vect::operator=(other);
      _BST::operator=(other);
      DIM = other.DIM; other.DIM = 0;
      current_vect_idx = other.current_vect_idx; other.current_vect_idx =0;

    }
    return *this;
  }

  // Getter
  const T& operator[](std::ptrdiff_t idx) const {
    auto val= _Vect::operator[](idx);
    return val;
  };


  inline const std::size_t current_space() {
    return current_vect_idx;}

  int const node_number () const {
    return _BST::node_number();}

  std::size_t const dim() const {
    return DIM;}

  // methode
  const T& insert (const T& v) override {

    Info* info_wrapper = new Info(current_vect_idx,v);
    Ptr2Info ptr_wrapper{};

    bool cond_to_ins = _BST::exists(*info_wrapper);

    if (!cond_to_ins && (std::size_t)current_vect_idx < DIM){
      if ( _Base::_ptr(_Vect::operator[](current_vect_idx)) != nullptr ){
        _BST::erase(_Vect::operator[](current_vect_idx));
      }
      _Base::_ptr(ptr_wrapper) = info_wrapper; // get the pointer to Info inside ptr_wrapper
        //std::cout << "indice : " << current_vect_idx << std::endl;

        _Vect::operator[](current_vect_idx) = ptr_wrapper ; // add inside the vecteur
        current_vect_idx++;
        auto val = _BST::insert(*info_wrapper);
      return val;
    }
    else{
      // TODO can i throw an error ?
      //throw std::domain_error("Already in ... ");
      std::cout<< "Insert n1\nDeja dedans ou Plus assez de place !!\nValue : "<< v <<std::endl;
      return _BST::_NOT_FOUND;
    };

  };


  const T& insert (const T& v, std::ptrdiff_t idx) override {

    Info* info_wrapper = new Info(idx,v);
    Ptr2Info ptr_wrapper{};

    bool cond_to_ins = _BST::exists(*info_wrapper);
    //printf("nb d'element : %d \n",_BST::node_number());

    if (!cond_to_ins && (std::size_t)idx < DIM){

      if ( _Base::_ptr(_Vect::operator[](idx)) != nullptr ){ // at idx there is != nullptr
        _BST::erase(_Vect::operator[](idx));
        printf("I get here idx : %d \n",(int)idx);
      }

      _Base::_ptr(ptr_wrapper) = info_wrapper; // get the reference to pointer to Info inside ptr_wrapper
      _Vect::operator[](idx) = ptr_wrapper ; // add inside the vecteur
      auto val = _BST::insert(*info_wrapper);

      return val;
    }

        // TODO can i throw an error ?
        //throw std::domain_error("Already in ... ");
    std::cout<< "Insert n2\nDeja dedans ou Plus assez de place !!\nValue : "<< v <<std::endl;
    return _BST::_NOT_FOUND;

  }


  const bool erase(const T& v) override {

    Info info_wrapper = Info(v);bool cond_to_del = _BST::exists(info_wrapper);

    if ( cond_to_del ){
      auto the_info = _BST::find(info_wrapper);
      auto the_index_2info = _Base::_index(the_info); // get the index in Vect
      _BST::erase(the_info); _Vect::operator[](the_index_2info) = Ptr2Info{};
      return true;
    }
    // TODO modifier le cout
    std::cout << "\nExiste pas tu joues a quoi ?  Value : "<< info_wrapper <<std::endl;
    return false;



  }


  const bool erase(const T& v,std::ptrdiff_t idx) override {
    Info info_wrapper = Info(v);bool cond_to_del = _BST::exists(info_wrapper);

    if ( cond_to_del && _Vect::operator[](idx) == info_wrapper ){ // existe in BTS and Vect
      auto the_info = _BST::find(info_wrapper);
      _BST::erase(the_info); _Vect::operator[](idx) = Ptr2Info{}; // erase from everywhere
      return true;
    }

    // TODO modifier le cout
    std::cout << "\nExiste pas, Value and index : "<< info_wrapper << idx<< std::endl;
    return false;

  }


  bool exists  (const T& v) const override{
        auto val = _BST::exists(Info(v));
        return val;
  };


  const T& find (const T& v) const noexcept override{
    return _BST::find(Info(v));
  }


  const T& find (const T& v,std::ptrdiff_t idx) const noexcept override{

    Info val_info = Info(v);
    if (idx == _Base::_index(_BST::find(val_info)) ){ // get the info in the BTS and then get idx of that info
      return _BST::find(Info(v));
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
