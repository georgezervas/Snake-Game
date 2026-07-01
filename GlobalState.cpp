
#include "GlobalState.h"
#include "Snake.h"
#include "Food.h" 
#include <cmath> 
#include <string> 
#include <iostream>

GlobalState* GlobalState::m_instance = nullptr;

GlobalState* GlobalState::getInstance() {
    if (!m_instance) m_instance = new GlobalState();
    return m_instance;
}

GlobalState::~GlobalState() {
    for (auto* obj : m_objects) delete obj;
    m_objects.clear();
    for (auto* node : m_graph_nodes) delete node;
    m_graph_nodes.clear(); 
}


void GlobalState::buildGraph() {
    
    for (auto* node : m_graph_nodes) delete node;
    m_graph_nodes.clear();

    float w = getCanvasWidth();
    float h = getCanvasHeight();
    m_cols = (int)(w / m_block_size);
    m_rows = (int)(h / m_block_size);

    std::vector<std::vector<Node*>> grid(m_cols, std::vector<Node*>(m_rows));

    for (int i = 0; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            Node* newNode = new Node();
            newNode->x = i * m_block_size;
            newNode->y = j * m_block_size;
            newNode->size = m_block_size;
            grid[i][j] = newNode;
            m_graph_nodes.push_back(newNode);
        }
    }
    for (int i = 0; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            Node* curr = grid[i][j];
            if (j > 0) curr->up = grid[i][j - 1];
            if (j < m_rows - 1) curr->down = grid[i][j + 1];
            if (i > 0) curr->left = grid[i - 1][j];
            if (i < m_cols - 1) curr->right = grid[i + 1][j];
        }
    }
}

Node* GlobalState::getNodeAt(int col, int row) {
    if (col >= 0 && col < m_cols && row >= 0 && row < m_rows) {
        for (auto* n : m_graph_nodes) {
            if ( (int)(n->x / m_block_size) == col && (int)(n->y / m_block_size) == row)
                return n;
        }
    }
    return nullptr;
}

Node* GlobalState::getRandomNode() {
    if (m_graph_nodes.empty()) return nullptr;
    int idx = rand() % m_graph_nodes.size();
    return m_graph_nodes[idx];
}

void GlobalState::init() {
    m_status = STATUS_START; 
    m_score = 0;
    m_player_name = "";
     

    buildGraph(); 

    graphics::setFont("assets/orange juice 2.0.ttf");
    
    
    graphics::playMusic("assets/SnakeGameMusic.mp3", 0.5f, true, 1000); 

    for (auto* obj : m_objects) delete obj;
    m_objects.clear();

    m_objects.push_back(new Snake());
    m_objects.push_back(new Food());
    
    for (auto* obj : m_objects) obj->init();
}

void GlobalState::setGameOver(bool go) {
    if (go && m_status != STATUS_GAMEOVER) {
        m_status = STATUS_GAMEOVER;
        graphics::playMusic("assets/GameOverMusic.mp3", 0.5f, false, 1000); 
    }
}


float key_timer = 0.0f; 

void GlobalState::update(float ms) {
    float dt = graphics::getDeltaTime();
    
    // increment the timer each time the update runs
    m_input_timer += dt; 

    //name insert
    if (m_status == STATUS_START) {
        if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
            if (!m_player_name.empty()) {
                m_status = STATUS_PLAYING; 
                 
                m_input_timer = 0.0f; 
            }
        }
        
        
        if (m_input_timer > 200.0f) { 
            for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; ++i) {
                if (graphics::getKeyState((graphics::scancode_t)i)) {
                    m_player_name += (char)('A' + (i - graphics::SCANCODE_A));
                    m_input_timer = 0.0f; 
                }
            }
            if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE) && !m_player_name.empty()) {
                m_player_name.pop_back();
                m_input_timer = 0.0f;
            }
        }
        return; 
    }

    //  PAUSE SCREEN
    if (m_status == STATUS_PAUSED) {
        
        if (graphics::getKeyState(graphics::SCANCODE_SPACE) && m_input_timer > 200.0f) {
            m_status = STATUS_PLAYING;
            m_input_timer = 0.0f; 
        }
        if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
            graphics::stopMessageLoop();
        }
        return; 
    }

    //  GAME OVER SCREEN
    if (m_status == STATUS_GAMEOVER) {
        if (graphics::getKeyState(graphics::SCANCODE_RETURN) && m_input_timer > 500.0f) {
            init(); 
        }
        return; 
    }

   
    //  PAUSE
    if (graphics::getKeyState(graphics::SCANCODE_SPACE) && m_input_timer > 0.2f) {
        m_status = STATUS_PAUSED;
        m_input_timer = 0.0f;
        return;
    }

    for (auto* obj : m_objects) obj->update();
    
    Snake* snake = (Snake*)m_objects[0];
    Food* food = (Food*)m_objects[1];
    
    if (snake->getHeadNode() == food->getNode()) {
        snake->grow();
        food->init(); 
        m_score++; 
        graphics::playSound("assets/eatmusic.wav", 0.5f, false);
    }
}
    

  
    

void GlobalState::draw() {
    float w = getCanvasWidth();
    float h = getCanvasHeight();
    
    graphics::Brush bg;
    graphics::Brush text_brush;
    text_brush.fill_color[0]=1; text_brush.fill_color[1]=1; text_brush.fill_color[2]=1;

    // A. START SCREEN
    if (m_status == STATUS_START) {
        
        bg.texture = "assets/SnakeGameWH.png"; 
        bg.outline_opacity = 0.0f;
        graphics::drawRect(w/2, h/2, w, h, bg);

        
        graphics::Brush shadow;
        shadow.fill_color[0]=0; shadow.fill_color[1]=0; shadow.fill_color[2]=0; shadow.fill_opacity=0.5f;
        graphics::drawRect(w/2, h/2 + 50, 400, 200, shadow);

        graphics::drawText(w/2 - 120, h/2, 50, "SNAKE GAME", text_brush);
        
        graphics::drawText(w/2 - 150, h/2 + 60, 30, "Enter Name: " + m_player_name, text_brush);
        
        
        if ((int)(graphics::getGlobalTime() / 500) % 2 == 0)
            graphics::drawText(w/2 - 130, h/2 + 120, 25, "Press ENTER to Start", text_brush);
            
        return;
    }

    // PLAYING SCREEN 
    graphics::Brush cell_brush;
    cell_brush.outline_opacity = 0.2f; 

    for (auto* node : m_graph_nodes) {
        int ci = (int)(node->x / m_block_size);
        int ri = (int)(node->y / m_block_size);
        if ((ci + ri) % 2 == 0) {
            cell_brush.fill_color[0] = 0.2f; cell_brush.fill_color[1] = 0.2f; cell_brush.fill_color[2] = 0.2f;
        } else {
            cell_brush.fill_color[0] = 0.15f; cell_brush.fill_color[1] = 0.15f; cell_brush.fill_color[2] = 0.15f;
        }
        graphics::drawRect(node->x + node->size/2, node->y + node->size/2, node->size, node->size, cell_brush);
    }

    for (auto* obj : m_objects) obj->draw();
    graphics::drawText(10, 30, 20, "Score: " + std::to_string(m_score), text_brush);

    // PAUSE SCREEN 
    if (m_status == STATUS_PAUSED) {
        bg.texture = ""; //  texture cleaning
        bg.fill_color[0]=0; bg.fill_color[1]=0; bg.fill_color[2]=0;
		bg.fill_opacity = 0.6f; //semi-transparent black background
        graphics::drawRect(w/2, h/2, w, h, bg);

        graphics::drawText(w/2 - 50, h/2 - 50, 50, "PAUSE", text_brush);
        graphics::drawText(w/2 - 180, h/2 + 20, 25, "Press SPACE Button to continue your SNAKE GAME", text_brush);
        graphics::drawText(w/2 - 100, h/2 + 60, 25, "Press ESC Button to Exit", text_brush);
    }

    //GAME OVER SCREEN
    if (m_status == STATUS_GAMEOVER) {
        bg.texture = "";
        bg.fill_color[0]=0; bg.fill_color[1]=0; bg.fill_color[2]=0;
        bg.fill_opacity = 0.8f; 
        graphics::drawRect(w/2, h/2, w, h, bg);

        graphics::Brush red_brush; 
        red_brush.fill_color[0]=1; red_brush.fill_color[1]=0.2f; red_brush.fill_color[2]=0.2f;
        
        graphics::drawText(w/2 - 120, h/2 - 50, 50, "GAME OVER", red_brush);
        
        graphics::drawText(w/2 - 100, h/2 + 20, 30, "Your score is: " + std::to_string(m_score), text_brush);
        
        // to close message !
        graphics::drawText(w/2 - 100, h/2 + 60, 30, "Bye " + m_player_name, text_brush);
        
        graphics::drawText(w/2 - 130, h/2 + 120, 20, "Press ENTER to Restart", text_brush);
    }
}