#include"../include/kdata/darray.h"

#include"testutils.h"

#include<iostream>
#include<vector>
#include<algorithm>

bool DarrayTest(){
  kd::darray<int> da;

  // Test push_back and length
  for (int i = 0; i < 1000; ++i) {
    da.push_back(i);
    if (da.length() != i + 1) {
      std::cerr << "DarrayTest: push_back failed, expected length " << i + 1 << ", got " << da.length() << std::endl;
      // Continue to avoid cascading errors
    }
  }

  // Test operator[] and contains
  for (int i = 0; i < 1000; ++i) {
    if (da[i] != i) {
      std::cerr << "DarrayTest: operator[] failed, expected " << i << ", got " << da[i] << " at index " << i << std::endl;
    }
    if (!da.contains(i)) {
      std::cerr << "DarrayTest: contains failed for value " << i << std::endl;
    }
  }

  // Test pop_back
  for (int i = 0; i < 500; ++i) {
    long long old_length = da.length();
    da.pop_back();
    if (da.length() != old_length - 1) {
      std::cerr << "DarrayTest: pop_back failed, expected length " << old_length - 1 << ", got " << da.length() << std::endl;
    }
  }
  if (da.length() != 500) {
    std::cerr << "DarrayTest: final length after pop_back failed, expected 500, got " << da.length() << std::endl;
  }

  // Test clear
  da.clear();
  if (da.length() != 0) {
    std::cerr << "DarrayTest: clear failed, expected length 0, got " << da.length() << std::endl;
  }

  return true;
}

bool VectorTest(){
  std::vector<int> vec;

  // Test push_back and size
  for (int i = 0; i < 1000; ++i) {
    vec.push_back(i);
    if (vec.size() != i + 1) {
      std::cerr << "VectorTest: push_back failed, expected size " << i + 1 << ", got " << vec.size() << std::endl;
    }
  }

  // Test operator[] and find
  for (int i = 0; i < 1000; ++i) {
    if (vec[i] != i) {
      std::cerr << "VectorTest: operator[] failed, expected " << i << ", got " << vec[i] << " at index " << i << std::endl;
    }
    if (std::find(vec.begin(), vec.end(), i) == vec.end()) {
      std::cerr << "VectorTest: find failed for value " << i << std::endl;
    }
  }

  // Test pop_back
  for (int i = 0; i < 500; ++i) {
    size_t old_size = vec.size();
    vec.pop_back();
    if (vec.size() != old_size - 1) {
      std::cerr << "VectorTest: pop_back failed, expected size " << old_size - 1 << ", got " << vec.size() << std::endl;
    }
  }
  if (vec.size() != 500) {
    std::cerr << "VectorTest: final size after pop_back failed, expected 500, got " << vec.size() << std::endl;
  }

  // Test clear
  vec.clear();
  if (vec.size() != 0) {
    std::cerr << "VectorTest: clear failed, expected size 0, got " << vec.size() << std::endl;
  }

  return true;
}

int main(){

  std::cout << "------(Cold) Trial 1------" << std::endl;
  kd::Test("std::vector", VectorTest);
  kd::Test("kd::darray", DarrayTest);
  std::cout << "--------------------------" << std::endl << std::endl;

  std::cout << "------Trial 2 (Reverse order)------" << std::endl;
  kd::Test("kd::darray", DarrayTest);
  kd::Test("std::vector", VectorTest);
  std::cout << "-----------------------------------" << std::endl << std::endl;

  std::cout << "------Trial 3 (Initial order)------" << std::endl;
  kd::Test("std::vector", VectorTest);
  kd::Test("kd::darray", DarrayTest);
  std::cout << "-----------------------------------" << std::endl << std::endl;

  return 0;
}
