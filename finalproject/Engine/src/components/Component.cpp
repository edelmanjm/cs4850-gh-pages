#include <components/Component.h>

Component::Component() = default;
Component::~Component() = default;

void Component::SetGameEntity(std::shared_ptr<GameEntity> g) { m_GameEntity = g; }

std::shared_ptr<GameEntity> Component::GetGameEntity() { return m_GameEntity; }

// Some things to think about -- component communication
//void send(int message) {}
//void receive(int message) {}