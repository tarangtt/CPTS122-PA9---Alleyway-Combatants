#include "_libs.hpp"
#include "basePlayer.hpp"

#include "_libs.hpp"
#include "basePlayer.hpp"

FightState runGameScene(sf::RenderWindow& window, int p1code, int p2code) {
    // Load background
    sf::Texture background;
    if (!background.loadFromFile("fightSceneBg.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return FightState::Aborted;
    }
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setPosition({ 0.f, 0.f });

    // Initialize players
    Player player1(sf::Vector2f(185.0f * 0.8f, PLAYER_HEIGHT), sf::Color::Blue, true, p1code);
    Player player2(sf::Vector2f(185.0f * 0.8f, PLAYER_HEIGHT), sf::Color::Red, false, p2code);

    player1.setPosition({ 200.f, groundY - PLAYER_HEIGHT });
    player2.setPosition({ 800.f, groundY - PLAYER_HEIGHT });

    auto lastTime = std::chrono::steady_clock::now();
    bool gameRunning = true;
    FightState result = FightState::Aborted; // default return statement

    while (gameRunning && window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                gameRunning = false;
                FightState::Aborted;
            }
        }

        // win conditions
        if (player1.getHealth() <= 0) {
            gameRunning = false;
            result = FightState::P2Wins;
        }
        else if (player2.getHealth() <= 0) {
            gameRunning = false;
            result = FightState::P1Wins;
        }

        //frame time (needed for animations)
        auto currentTime = std::chrono::steady_clock::now();
        float frameTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        // P1 controls (WASD + QE)
        bool p1Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        bool p1Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        bool p1HighAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
        bool p1LowAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        bool p1Block = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

        if (p1Left || p1Right) player1.setIsWalking(true);
        else player1.setIsWalking(false);

        if (p1Block) {
            player1.startBlock();
        }
        else if (player1.getIsBlocking()) {
            player1.stopBlock();
        }

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

        // P2 controls (IJKL + UO)
        bool p2Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J);
        bool p2Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L);
        bool p2HighAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U);
        bool p2LowAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O);
        bool p2Block = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K);

        if (p2Left || p2Right) player2.setIsWalking(true);
        else player2.setIsWalking(false);

        if (p2Block) {
            player2.startBlock();
        }
        else if (player2.getIsBlocking()) {
            player2.stopBlock();
        }

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

        // update game state
        player1.update(frameTime, groundY, MAX_JUMP_HEIGHT);
        player2.update(frameTime, groundY, MAX_JUMP_HEIGHT);

        // check attacks
        if (player1.checkAttackHit(player2)) {
            player2.takeDamage(static_cast<int>(10 * player1.getAttackMultiplier()));
        }
        if (player2.checkAttackHit(player1)) {
            player1.takeDamage(static_cast<int>(10 * player2.getAttackMultiplier()));
        }

        // render
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

    return result;
}