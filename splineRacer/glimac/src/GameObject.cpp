#include <glimac/SDLWindowManager.hpp>
#include <glimac/GameObject.hpp>

// Constructors
GameObject::GameObject()
	:_sPosition(glm::vec3(0, 0, 0))
{}

GameObject::GameObject(float angle, float distance, float progression)
	:_sPosition(glm::vec3(angle, distance, progression))
{}

// Destructor
GameObject::~GameObject() 
{}