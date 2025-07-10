#pragma once

#ifndef _KDATA_UTILS_H
#define _KDATA_UTILS_H

namespace kd{

//TODO(kei): implement
template<class T>
void sort(T& container);

//TODO(kei): implement
template<class T>
void sort(T&& container);

//TODO(kei): implement
template<class T, class U>
long long bsearch(const T& key, const U& container);

//Return -1 if not found
template<class T, class U>
long long lsearch(const T& key, const U& container){
  long long n = container.length();
  for (long long i = 0; i < n; ++i){
    if (container[i] == key) {
      return i;
    }
  }

  return -1;
}

};

#endif
