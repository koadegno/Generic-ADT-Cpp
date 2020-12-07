/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Adegnon, Kokou - 2020/12 - <Cont.hpp>
 * Exemple de conteneur (projet n1)
 */
#ifndef _CONT_H_
#define _CONT_H_

#include  "Vect.hpp"
#include  "BST.hpp"
//#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
//#include  <exception>
//#include  <stdexcept>           // standard exceptions
//#include  <ostream>             // output streams
#include  <iostream>


// Common output operator ====================================================

namespace _Cont_base {
  namespace {
    template <typename U>
    struct _Base {
      constexpr void _dsp (std::ostream& out) const
        {static_cast<const U*>(this)->_dsp(out);}
    };
  }
}

template <typename U>
std::ostream& operator<< (std::ostream& out, const _Cont_base::_Base<U>& b)
  {b._dsp(out); return out;}


// Abstract base class =======================================================

template <typename T>
class Cont_base { // abstract
public:

  class Info;
  class Ptr2Info;

protected:
  template <typename U> using _Base = _Cont_base::_Base<U>;
  static const Info _EMPTY;
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}

  // Implementation
  std::size_t _used = 0;
  virtual void _dsp (std::ostream&) const = 0;

  // Non virtual assignations => protected
  Cont_base& operator= (const Cont_base&) = default;
  Cont_base& operator= (Cont_base&& c)
    {if (this != &c) {_used = c._used; c._used = 0;} return *this;}

  // ...
public:
  // Getter
  constexpr std::size_t used () const noexcept {return _used;};
  // Constructors & destructor
  constexpr Cont_base () noexcept = default;
  constexpr Cont_base (const Cont_base&) noexcept = default;
  constexpr Cont_base (Cont_base&& c) noexcept: _used(c._used) {c._used = 0;}
  virtual ~Cont_base () noexcept = default;

}; // Cont_base<T>

template <typename T>
const typename Cont_base<T>::Info Cont_base<T>::_EMPTY{};


// Embedded class Info =====================================================

template <typename T>
class Cont_base<T>::Info:
    public _Cont_base::_Base<typename Cont_base<T>::Info> {
  friend class Cont_base<T>;   // for _index static methods
  std::ptrdiff_t _index = -1;
  const T _data{};
  friend struct _Cont_base::_Base<Info>;
  constexpr void _dsp (std::ostream& out) const {out << _data;}
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
  template <typename>
  friend constexpr bool operator< (const Info&, const Info&) noexcept;
  template <typename>
  friend constexpr bool operator== (const Info&, const Info&) noexcept;
  constexpr bool operator< (const Info& i) const noexcept
    {return _data < i._data;}
  constexpr bool operator== (const Info& i) const noexcept
    {return _data == i._data;}
}; // Info

// Embedded class Ptr2Info ===================================================

template <typename T>
class Cont_base<T>::Ptr2Info:
    public _Cont_base::_Base<typename Cont_base<T>::Ptr2Info> {
  friend class Cont_base<T>;   // for _ptr static methods
  const Info *_ptr = nullptr;
  friend struct _Cont_base::_Base<Ptr2Info>;
  constexpr void _dsp (std::ostream& out) const
    {out << (_ptr ? *_ptr : _EMPTY);}
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
  constexpr bool operator< (const Ptr2Info& i) const noexcept
    {return _ptr->_data < i._ptr->_data;}
  constexpr bool operator== (const Ptr2Info& i) const noexcept
    {return _ptr->_data == i._ptr->_data;}
}; // Ptr2Info

namespace _Cont_base {
  template <typename> using _Base = void;   // "destroy" access to real _Base
}

// Main class ================================================================

template <typename T>
class Cont final: private Cont_base<T>, public BST< typename Cont_base<T>::Info >, public Vect< typename Cont_base<T>::Ptr2Info >  {

private:
  using _Base = Cont_base<T>;
  using _Vect = Vect<typename _Base::Ptr2Info >;
  using _BST  = BST<typename _Base::Info>;
  using _Base::_index;
  using _Base::_ptr;

  std::size_t DIM;

  virtual void _dsp (std::ostream& out) const override {_BST::_dsp(out);}

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
  const T& operator[](std::ptrdiff_t idx) {

    //std::cout << val << std::endl;
    return _Vect::operator[](idx);
  };


  std::size_t const node_number () const {
    return _BST::node_number();}


  std::size_t const dim() const {
    return DIM;}

  // methode
  const Info& insert (const T& v, std::ptrdiff_t idx)  {

    Info* info_wrapper = new Info(idx,v);
    Ptr2Info ptr_wrapper{};

    bool cond_to_ins = _BST::exists(*info_wrapper) && node_number()< DIM;

    if (!cond_to_ins && idx < DIM){

      if ( _Base::_ptr(_Vect::operator[](idx)) != nullptr ){ // write on a existing value
        _BST::erase(_Vect::operator[](idx));
      }

      _Base::_ptr(ptr_wrapper) = info_wrapper; // get the reference to pointer to Info inside ptr_wrapper
      _Vect::operator[](idx) = ptr_wrapper ; // add inside the vecteur
      //std::cout << "Value : " << _Vect::operator[](idx) << " Index : " << idx << std::endl;
      //delete info_wrapper;
      return _BST::insert(*info_wrapper);

    }

        // TODO can i throw an error ?
        //throw std::domain_error("Already in ... ");
    std::cout<< "Insert \nDeja dedans ou Plus assez de place !!\nValue : "<< v <<std::endl;
    return _BST::_NOT_FOUND;

  }

  const Info& insert (const Info& val) override{

    std::ptrdiff_t idx = _Vect::getIndex();
    const Info& ret_val = insert(val,idx);
    return ret_val;

  }

  bool erase(const Info& v) override {
    bool cond_to_del = _BST::exists(v);

    if (cond_to_del){

      auto the_info = _BST::find(v);
      std::ptrdiff_t idx = _Base::_index(the_info);

      _BST::erase(v); _Vect::operator[](idx) = Ptr2Info{}; // erase from everywhere (BST and Vect)
      return true;
      }
    std::cout << "\nExiste pas, Value : "<< v << std::endl;
    return false;

  }


  bool erase(const Info& v,std::ptrdiff_t idx) {
    //Info info_wrapper = Info(v);


    if (_Vect::operator[](idx) == v ){ // exist in BTS and Vect

      _BST::erase(v); _Vect::operator[](idx) = Ptr2Info{}; // erase from everywhere (BST and Vect)
      return true;
      }


    // TODO modifier le cout
    std::cout << "\nExiste pas, Value and index : "<< v <<" "<< idx<< std::endl;
    return false;

  }


  bool exists  (const Info& v) const noexcept override{
        auto val = _BST::exists(Info(v));
        return val;
  };


  const Info& find(const Info& v) const noexcept override {

    return _BST::find(v);
  }


  const Info& find (const Info& v,std::ptrdiff_t idx) const noexcept  {

    const Ptr2Info& vect_ptr2info = _Vect::operator[](idx); // get the Ptr2info in the vect
    const Info* vect_info = _Base::_ptr(vect_ptr2info); // get Info in Ptr2Info


    if (vect_info && v==*vect_info){ // not empty and v equal info in the vect
      return *vect_info;
    }

    return _BST::_NOT_FOUND; // idx doesn't match

  };


  ~Cont() override {};

  template <typename I>
  friend inline std::ostream& operator<< (std::ostream& , const Cont<I>&);



}; // Cont<T>


// Deduction guides ==========================================================
/*
template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;

*/
// Associated functions ======================================================


template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Cont<T>& c)
  {out << "CONT : [ "; c._dsp(out); out << ']'; return out;}

#endif // _CONT_H_
