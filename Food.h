

#pragma once
#include "GameObject.h"

class Food : public GameObject {
	Node* m_current_node = nullptr; // pointer to the current node where the food is located
public:
    Food();
    void update() override;
    void draw() override;
    void init() override;
    
    Node* getNode() { return m_current_node; }
};