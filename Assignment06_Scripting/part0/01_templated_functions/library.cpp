// Include library that allows embedding of pybind
// into the engine
#include <pybind11/embed.h>
#include <string>
namespace py = pybind11; // shorten what we need to type

template <class T>
T myadd(T a, T b){
    return a+b;
}

PYBIND11_MODULE(library, m){
    m.doc() ="Templated library with some exposed types";
    m.def("myadd",&myadd<int>);
    m.def("myadd",&myadd<double>);
    m.def("myadd",&myadd<std::string>);
}
