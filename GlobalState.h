
#pragma once
#include "graphics.h"
#include "GameObject.h"
#include <vector>
#include <string>

enum GameStatus {
    STATUS_START,
    STATUS_PLAYING,
    STATUS_PAUSED,
    STATUS_GAMEOVER
};

class GlobalState {
    static GlobalState* m_instance;
    std::vector<GameObject*> m_objects; 
    
    // GRAPH logic 
	std::vector<Node*> m_graph_nodes; // all nodes in the grid
    float m_block_size = 20.0f;
    int m_cols = 0;
    int m_rows = 0;

    GameStatus m_status = STATUS_START; 
    int m_score = 0; 

    std::string m_player_name = "";

    float m_input_timer = 0.0f;
    
    GlobalState() {} 

public:
    ~GlobalState();
    static GlobalState* getInstance();

    void init();
    void update(float ms);
    void draw();
    
	// graph logic
    void buildGraph();

  
	// functions
    void setGameOver(bool go);
    float getCanvasWidth() { return 800.0f; }
    float getCanvasHeight() { return 600.0f; }
    
	// graph logic
    Node* getNodeAt(int col, int row);
	Node* getRandomNode(); // for food placement

    GameObject* getSnake() {
        if (!m_objects.empty()) return m_objects[0];
        return nullptr;
    }
};