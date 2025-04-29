#pragma once

#include "_libs.hpp"

using namespace sf;
using namespace std;

class testCases
{
public:
    testCases() { initVariables(); initWindows(); }

    void update();
    void render();
    const bool testRunning() const;

    void testScale();
    void testMoveLeft();
    void testMoveRight();
    void testMoveDown();
    void testJump();

private:
    RenderWindow window;
    RectangleShape rect;

    void initVariables();
    void initWindows();
};

