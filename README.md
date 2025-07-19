# kdata
* I made it to practice my algorithms and data structures knowledge.
* This library focuses on simplicity (C++ isn't taken into account, the amount of constructors already exceeds amount of functions in python). So please `git --force gud` and use kd::darray instead of a stack.

## Usage
* Have you never used a library with an include directory before??
* The only thing I can add to the above line is that if specific files are needed, look at their includes, they may have dependencies.

## Compile tests
```sh
git clone https://github.com/ivkei/kdata
cd kdata
mkdir build
clang++ tests/<datastruct>.cpp -o build/<datastruct>
```

## API
* To enable assertions define `_KDATA_ENABLE_ASSERTS` before a header.
* The rest is like in STL, except length, and a few more functions.

## Contributors
* Me
* Myself
* I
* ivkei
* kei
