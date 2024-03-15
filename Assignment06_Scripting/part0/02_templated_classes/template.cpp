// Simple template example to demonstrate how to create
// 'reusable' functions
#include <iostream>
#include <string>

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

int main(){
    // Instantiation of our integer component
    Component<int> integerComponent;
    integerComponent.SetData(5);
    std::cout   << "integerComponet.GetData() = " 
                << integerComponent.GetData() << "\n";
    // Instantation of our string component
    Component<std::string> stringComponent;
    stringComponent.SetData("mike");
    std::cout   << "stringComponet.GetData() = " 
                << stringComponent.GetData() << "\n";

    return 0;
}
