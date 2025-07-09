#pragma once

#ifndef _KDATA_DARRAY_H
#define _KDATA_DARRAY_H

#include<initializer_list>
#include<malloc.h>
#include<cstdlib>
#include<stdexcept>
#include<cstring>

#include"utils.h"

#ifndef NDEBUG
#define assert(x)\
  if (!(x)){\
    printf("Assertion failed, line: %d, file: \"%s\"!\n", __LINE__, __FILE__);\
    exit(1);\
  }
#else
#define assert(x)\
  if (!(x)) throw std::runtime_error("Assertion failed");
#endif

namespace kd{

//Dynamic array, alternative of std::vector
template<class T>
class darray final{
private:
  T* _pData;
  long long _n;
  long long _allocN;

  void _Extend();
  void _Slide(void* b, void* m, void* e);
public:
  darray();
  darray(long long n);
  darray(long long n, const T& val);
  //TODO(kei): Add assign copy and move, remake them to call objects' move and copy ctors (maybe not, havent decided yet)
  darray(const darray& other);
  darray(darray&& other);
  darray(std::initializer_list<T>&& other);

  ~darray();

  //Wrapping - [-1] becomes [n - 1], python style
  //But [n] will not wrap
  T& operator[](long long i);

  void push_back(const T& v);

  template<class...Ts>
  void emplace_back(Ts&&... vs);

  void push_front(const T& v);

  template<class...Ts>
  void emplace_front(Ts&&... vs);

  void pop_back();

  void pop_front();

  void push(long long index, const T& v);

  template<class...Ts>
  void emplace(long long index, Ts&&... vs);

  void pop(long long index);

  bool contains(const T& v) const;
  //Return -1 if not found
  long long index_of(const T& v) const;

  long long length() const;

  void clear();

  T* operator&();
  T* data();
};

template<class T>
darray<T>::darray()
: _pData(nullptr), _n(0), _allocN(4){
  _pData = malloc(sizeof(T) * _allocN);
  assert(_pData != nullptr);
}

template<class T>
darray<T>::darray(const darray& other)
: _pData(nullptr), _n(other._n), _allocN(other._allocN){
  _pData = malloc(sizeof(T) * _n);
  std::memcpy(_pData, other._pData, sizeof(T) * _n);
  assert(_pData != nullptr);
}

template<class T>
darray<T>::darray(darray&& other)
: _pData(other._pData), _n(other._n), _allocN(other._allocN){
  other._pData = nullptr;
  other._n = 0;
  other._allocN = 0;
  assert(_pData != nullptr);
}

template<class T>
darray<T>::darray(std::initializer_list<T>&& other)
: _pData(nullptr), _n(0), _allocN(4){
  _pData = malloc(sizeof(T) * 4);
  assert(_pData != nullptr);

  for (auto&& i : other){
    this->push_back(i);
  }
}

template<class T>
darray<T>::darray(long long n)
: _pData(nullptr), _n(n), _allocN(n){
  _pData = malloc(sizeof(T) * _allocN);
  assert(_pData != nullptr);
}

template<class T>
darray<T>::darray(long long n, const T& val)
: _pData(nullptr), _n(0), _allocN(n){
  _pData = malloc(sizeof(T) * _allocN);
  assert(_pData != nullptr);

  for (int i = 0; i < n; ++i){
    this->push_back(val);
  }
}

template<class T>
darray<T>::~darray(){
  clear();
  free(_pData);
}

template<class T>
T& darray<T>::operator[](long long i){
  assert(((i + _n) % _n) >= 0);

  if (i >= 0) return _pData[i];
              return _pData[((i + _n) % _n)]; //Wrapping - [-1] becomes [n - 1], python style
}

template<class T>
void darray<T>::push_back(const T& v){
  if (_n == _allocN){
    _Extend();
  }

  _pData[_n] = v;
  ++_n;
}

template<class T>
template<class...Ts>
void darray<T>::emplace_back(Ts&&... vs){
  if (_n == _allocN){
    _Extend();
  }

  _pData[_n] = T(vs...);
  ++_n;
}

template<class T>
void darray<T>::push_front(const T& v){
  if (_n == _allocN){
    _Extend();
  }

  _Slide(_pData + 1, _pData + _n, _pData + _n + 1);
  _pData[0] = v;

  ++_n;
}

template<class T>
template<class...Ts>
void darray<T>::emplace_front(Ts&&... vs){
  if (_n == _allocN){
    _Extend();
  }

  _Slide(_pData + 1, _pData + _n, _pData + _n + 1);
  _pData[0] = T(vs...);

  ++_n;
}

template<class T>
void darray<T>::pop_back(){
  assert(_n != 0);
  --_n;
  _pData[_n].~T();
}

template<class T>
void darray<T>::pop_front(){
  assert(_n != 0);

  if (_n != 1){
    _Slide(_pData, _pData + 1, _pData + _n);
  }

  --_n;
  _pData[_n].~T();
}

template<class T>
void darray<T>::push(long long index, const T& v){
  if (_n == _allocN){
    _Extend();
  }

  _Slide(_pData + index, _pData + _n, _pData + _n + 1);
  _pData[index] = v;

  ++_n;
}

template<class T>
template<class...Ts>
void darray<T>::emplace(long long index, Ts&&... vs){
  if (_n == _allocN){
    _Extend();
  }

  _Slide(_pData + index, _pData + _n, _pData + _n + 1);
  _pData[index] = T(vs...);

  ++_n;
}

template<class T>
void darray<T>::pop(long long index){
  _Slide(_pData + index, _pData + _n - 1, _pData + _n);
  --_n;
  _pData[_n].~T();
}

template<class T>
bool darray<T>::contains(const T& v) const{
  return index_of(v) != -1;
}

template<class T>
long long darray<T>::index_of(const T& v) const{
  return kd::lsearch(v, *this);
}

template<class T>
T* darray<T>::operator&(){
  return _pData;
}

template<class T>
T* darray<T>::data(){
  return _pData;
}

template<class T>
long long darray<T>::length() const{
  return _n;
}

template<class T>
void darray<T>::clear(){
  for (int i = 0; i < _n; ++i){
    pop_back();
  }
}

template<class T>
void darray<T>::_Extend(){
  _allocN *= 2;

  _pData = realloc(_pData, sizeof(T) * _allocN);

  assert(_pData != nullptr);
}

template<class T>
void darray<T>::_Slide(void* b, void* m, void* e){
  unsigned long long bmSize = (unsigned long long)m - (unsigned long long)b;
  unsigned long long meSize = (unsigned long long)e - (unsigned long long)m;
  char buf[bmSize]; //TODO(kei): fix this, variable sized arrays arent a thing

  std::memcpy(buf, b, bmSize);
  std::memmove(b, m, meSize);
  std::memcpy((char*)b + meSize, buf, bmSize);
}

};

#endif //_KDATA_DARRAY_H
