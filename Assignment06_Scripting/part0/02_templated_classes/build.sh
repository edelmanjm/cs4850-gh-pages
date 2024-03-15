# build the library that will be used in pybind 
clang++ -shared -fPIC -std=c++17 -I./pybind11/include/ `python3.6 -m pybind11 --includes` *.cpp -o library.so `python3.6-config --ldflags`

