

#pragma once
#include "GameObject.h"
#include <vector>

// enumeration to represent the possible directions the snake can move in
enum Direction { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NONE };

class Snake : public GameObject {
    

	Node* m_head_node = nullptr;      // head of the snake is a pointer to a Node in the grid
	std::vector<Node*> m_tail_nodes;  // the tail of the snake is a vector of pointers to Nodes in the grid
    
    Direction m_current_dir = DIR_NONE;
	Direction m_next_dir = DIR_NONE;  // buffer for the next direction to avoid reversing direction instantly

    float m_move_timer = 0.0f; 
    float m_move_delay = 0.2f; 


public:
    Snake(); 
    void update() override;
    void draw() override;
    void init() override;
    bool containsNode(Node* node);
    void grow();
    
	// getters
    Node* getHeadNode() { return m_head_node; }
};