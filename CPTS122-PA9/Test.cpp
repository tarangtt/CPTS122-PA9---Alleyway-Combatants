#include "Test.hpp"

void testCases::initVariables()
{
    rect.setSize(Vector2f({ 50.f, 50.f }));
    rect.setFillColor(Color::Cyan);
    rect.setPosition({ 100.f, 100.f });  // default position
}

void testCases::initWindows()
{
    window.create(VideoMode({ 800, 600 }), "Rectangle Test Cases");
    window.setFramerateLimit(60);
}

const bool testCases::testRunning() const
{
    return window.isOpen();
}

void testCases::update()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void testCases::render()
{
    window.clear(Color::Black);
    window.draw(rect);
    window.display();
}

void testCases::testScale()
{
    cout << "Running testScale...\n";
    rect.setScale({ 2.f, 2.f });
    Vector2f scale = rect.getScale();

    if (scale.x == 2.f && scale.y == 2.f)
        cout << "Rectangle scaled correctly to (2,2).\n";
    else
        cout << "Rectangle scale test failed.\n";
}

void testCases::testMoveLeft()
{
    cout << "Running testMoveLeft...\n";
    rect.setPosition({ 100.f, 100.f });
    rect.move({ -10.f, 0.f });

    if (rect.getPosition().x == 90.f)
        cout << "Rectangle moved left to x = 90.\n";
    else
        cout << "Rectangle did not move left correctly.\n";
}

void testCases::testMoveRight()
{
    cout << "Running testMoveRight...\n";
    rect.setPosition({ 100.f, 100.f });
    rect.move({ 10.f, 0.f });

    if (rect.getPosition().x == 110.f)
        cout << "Rectangle moved right to x = 110.\n";
    else
        cout << "Rectangle did not move right correctly.\n";
}

void testCases::testMoveDown()
{
    cout << "Running testMoveDown...\n";
    rect.setPosition({ 100.f, 100.f });
    rect.move({ 0.f, 20.f });

    if (rect.getPosition().y == 120.f)
        cout << "Rectangle moved down to y = 120.\n";
    else
        cout << "Rectangle did not move down correctly.\n";
}

void testCases::testJump()
{
    cout << "Running testJump...\n";
    rect.setPosition({ 100.f, 300.f });
    float jumpHeight = 50.f;
    rect.move({ 0.f, -jumpHeight });

    if (rect.getPosition().y == 250.f)
        cout << "Rectangle jumped up to y = 250.\n";
    else
        cout << "Rectangle jump test failed.\n";
}
