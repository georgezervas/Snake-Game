
#pragma once
#include "graphics.h"

// we define a Node structure to represent each cell in the grid. Each node has a position (x, y), a size, and pointers to its neighboring nodes (up, down, left, right).
// Additionally, we can mark a node as a wall if needed.
struct Node {
	float x, y;      // position of the cell
    float size;      // cell size
    
	// each node has pointers to its neighboring nodes in the grid
    Node* up = nullptr;
    Node* down = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    
    bool isWall = false; 
};

class GameObject {
public:
    virtual void update() = 0; 
    virtual void draw() = 0;   
    virtual void init() = 0;   
    virtual ~GameObject() {}   
};