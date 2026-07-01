
#include "graphics.h"
#include "GlobalState.h"

void update(float ms) {
    GlobalState::getInstance()->update(ms);
}

void draw() {
    GlobalState::getInstance()->draw();
}

int main() {
    graphics::createWindow(800, 600, "SGG Snake");

    GlobalState::getInstance()->init(); // game init

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GlobalState::getInstance()->getCanvasWidth(), GlobalState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}