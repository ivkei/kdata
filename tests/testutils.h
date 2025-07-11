#pragma once

#ifndef _KDATA_TESTUTILS_H
#define _KDATA_TESTUTILS_H

#include<functional>
#include<chrono>
#include<iostream>

namespace kd{

//Tests a func and outputs its benchmark, func returns anything (just so compiler doesnt optimize)
void Test(const char* title, std::function<bool(void)> func){
  std::cout << "===" << title << "===" << std::endl;

  auto begin = std::chrono::high_resolution_clock::now();
  begin = std::chrono::high_resolution_clock::now(); //Init the library, in case its not

  volatile bool failed = func(); //volatile just in case

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - begin;
  std::cout << "Overall time taken: " << dur.count() << "ns" << std::endl;
}

};

#endif
