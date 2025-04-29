#include "_libs.hpp"
#include "basePlayer.hpp"

void runFightGame(sf::RenderWindow& window, int p1Choice, int p2Choice) {
    // Load background
    sf::Texture background;
    if (!background.loadFromFile("fightSceneBg.png")) {
        std::cerr << "Failed to load background!" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(background);

    // Create players
    Player player1(sf::Vector2f(185.0f * 0.6f, PLAYER_HEIGHT), sf::Color::Blue, true);
    Player player2(sf::Vector2f(185.0f * 0.6f, PLAYER_HEIGHT), sf::Color::Red, false);

    // Load character sprites
    player1.loadSprites(p1Choice, true);
    player2.loadSprites(p2Choice, false);

    // Position players
    player1.setPosition({ 200.f, groundY - PLAYER_HEIGHT });
    player2.setPosition({ 800.f, groundY - PLAYER_HEIGHT });

    // Game loop
    window.setFramerateLimit(240);
    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Add other event handling here if needed
            // (though fighting game typically uses real-time input)
        }

        // Game over check
        if (player1.getHealth() <= 0 || player2.getHealth() <= 0) {
            window.close();
            continue;
        }

        float deltaTime = clock.restart().asSeconds();

        // Player 1 controls (WASD+QE)
        bool p1Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        bool p1Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        bool p1HighAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
        bool p1LowAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        bool p1Block = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

        if (p1Block) player1.startBlock();
        else if (player1.getIsBlocking()) player1.stopBlock();

        if (p1Left) player1.moveLeft();
        if (p1Right) player1.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player1.startJumpCharge();
        }
        else if (p1HighAttack) {
            player1.startAttackCharge(true);
        }
        else if (p1LowAttack) {
            player1.startAttackCharge(false);
        }
        else {
            player1.releaseCharge(p1Left, p1Right);
        }

        // Player 2 controls (IJKL+UO)
        bool p2Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J);
        bool p2Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L);
        bool p2HighAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U);
        bool p2LowAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O);
        bool p2Block = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K);

        if (p2Block) player2.startBlock();
        else if (player2.getIsBlocking()) player2.stopBlock();

        if (p2Left) player2.moveLeft();
        if (p2Right) player2.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
            player2.startJumpCharge();
        }
        else if (p2HighAttack) {
            player2.startAttackCharge(true);
        }
        else if (p2LowAttack) {
            player2.startAttackCharge(false);
        }
        else {
            player2.releaseCharge(p2Left, p2Right);
        }

        // Update game state
        player1.update(deltaTime, groundY, MAX_JUMP_HEIGHT);
        player2.update(deltaTime, groundY, MAX_JUMP_HEIGHT);

        // Handle attacks
        if (player1.checkAttackHit(player2)) {
            player2.takeDamage(static_cast<int>(10 * player1.getAttackMultiplier()));
        }
        if (player2.checkAttackHit(player1)) {
            player1.takeDamage(static_cast<int>(10 * player2.getAttackMultiplier()));
        }

        // Rendering
        window.clear();
        window.draw(backgroundSprite);

        player1.drawHealthBar(window);
        player2.drawHealthBar(window);

        player1.draw(window);
        player2.draw(window);

        if (player1.isCharging()) player1.drawChargeBar(window);
        if (player2.isCharging()) player2.drawChargeBar(window);

        window.display();
    }
}

void Player::draw(sf::RenderWindow& window) const {
    // Debug rectangle (always visible)
    sf::RectangleShape debugBox(body.getSize());
    debugBox.setPosition(body.getPosition());
    debugBox.setFillColor(sf::Color::Green);
    window.draw(debugBox);

    if (currentSprite) {
        window.draw(*currentSprite);
    }
}
