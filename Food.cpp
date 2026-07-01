
#include "Food.h"
#include "GlobalState.h"
#include "Snake.h"

Food::Food() {}

void Food::init() {
	// take the snake pointer from the global state to check if the random node is part of the snake
    Snake* snake = (Snake*)GlobalState::getInstance()->getSnake();
    Node* random_node = nullptr;

	// find a random node that is not part of the snake
    do {
        random_node = GlobalState::getInstance()->getRandomNode();
    } while (snake != nullptr && snake->containsNode(random_node));

    m_current_node = random_node;
}

void Food::update() {}

void Food::draw() {
    if (m_current_node) {
        graphics::Brush br;
        br.fill_color[0] = 1.0f; br.fill_color[1] = 0.2f; br.fill_color[2] = 0.2f;
        br.outline_opacity = 0.0f;
        
		//draw a disk in the center of the node
        float cx = m_current_node->x + m_current_node->size/2;
        float cy = m_current_node->y + m_current_node->size/2;
        graphics::drawDisk(cx, cy, m_current_node->size/2, br);
    }
}