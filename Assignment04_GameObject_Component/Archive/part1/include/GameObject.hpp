#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include "Component.hpp"

class GameObject{
    public:
        GameObject();
        ~GameObject();

    // Note: You may want to add member functions like 'Update' or 'Render'
    // Note: You may want to add member functions like "AddComponent" or "RemoveComponent"
    
    private:
        std::vector<Component> m_components;
};


#endif
