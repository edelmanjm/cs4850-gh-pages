# build the library that will be used in pybind 
# DO NOT FORGET to link in sdl here -- otherwise you will get a segmentation fault
clang++ -D LINUX -shared -fPIC -std=c++17 -I./pybind11/include/ `python3.6 -m pybind11 --includes` *.cpp -o library.so `python3.6-config --ldflags` -lSDL2 -ldl

