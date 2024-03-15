// Include library that allows embedding of pybind
// into the engine
#include <pybind11/embed.h>
#include <string>
namespace py = pybind11; // shorten what we need to type

template <class T>
class Component{
    public:
        // Constructor
        Component() {}
        // Setter function
        void SetData(T _data){
            data = _data;
        }
        // Return the type
        T GetData(){
            return data;
        }
     private:
        // Templated field
        T data;
};

PYBIND11_MODULE(library, m){
    m.doc() ="Templated class library with some exposed types";

    // Notice the templated type here
    py::class_<Component<int>>(m,"ComponentInt")
        .def(py::init())
        .def("SetData", &Component<int>::SetData)
        .def("GetData", &Component<int>::GetData);
        // Each function above uses the template argument
    // Notice the templated type here
    py::class_<Component<std::string>>(m,"ComponentString")
        .def(py::init())
        .def("SetData", &Component<std::string>::SetData)
        .def("GetData", &Component<std::string>::GetData);
        // Each function above uses the template argument
}
