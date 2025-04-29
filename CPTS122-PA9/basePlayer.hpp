#pragma once
#include "_libs.hpp"

class PlayerTextures {
private:
    std::unordered_map<std::string, sf::Texture> textures;

public:
    PlayerTextures() {
        sf::Texture texture;
        if (texture.loadFromFile("missingTexture.png")) textures["NULL"] = texture;
        else std::cerr << "CRITICAL: FAILED TO LOAD missingTexture.png" << std::endl;
    }

    void addTexture(const std::string& key, const std::string& pathToTexture) {
        sf::Texture texture;
        if (texture.loadFromFile(pathToTexture)) textures[key] = texture;
        else std::cerr << "FAILED TO LOAD " << key << " : " << pathToTexture << std::endl;
    }

    sf::Texture& getTexture(const std::string& key) {
        try {
            return textures.at(key);
        }
        catch (...) {
            return textures.at("NULL");
        }
    }

    sf::Texture& get_MISSING_Texture() {
        return textures.at("NULL");
    }
};


class BasePlayer
{
protected:
    //player tracking
    bool isJumping;
    bool isChargingJump;
    bool isChargingAttack;
    bool isBlocking;
    bool isWalking;
    JumpType currentJump;
    AttackType chargingAttackType;
    float verticalVelocity;
    float horizontalVelocity;
    float currentHeight;
    bool facingRight;
    std::chrono::steady_clock::time_point chargeStart;
    float chargeTime;
    bool hasHitThisAttack;
    CharacterState currentState;
    CharacterState previousState;
    float animationTimer;
    bool walkFrame;



};


class Player : public BasePlayer {
private:
    //player tracking
    bool isJumping;
    bool isChargingJump;
    bool isChargingAttack;
    bool isBlocking;
    bool isWalking;
    JumpType currentJump;
    AttackType chargingAttackType;
    float verticalVelocity;
    float horizontalVelocity;
    float currentHeight;
    bool facingRight;
    std::chrono::steady_clock::time_point chargeStart;
    float chargeTime;
    bool hasHitThisAttack;
    CharacterState currentState;
    CharacterState previousState;
    float animationTimer;
    bool walkFrame;

    //health, attack, defense
    int health;
    bool isAttackingBool;
    AttackType currentAttack;
    std::chrono::steady_clock::time_point attackStartTime;
    float attackDuration;
    float attackMultiplier;
    sf::RectangleShape attackHitbox;
    float blockFrontDamageReduction;
    float blockBackDamageReduction;

    //visuals - hitboxs and sprite
    sf::RectangleShape body;
    sf::Color color;
    float originalHeight;
    PlayerTextures characterTextures;
    sf::Sprite* currentSprite;

    void updateAttackHitbox();
    void updateSprite(float frameTime);

public:
    Player(const sf::Vector2f& size, const sf::Color& color, bool startFacingRight, int characterChoice);
    ~Player();


    //controls
    void moveLeft();
    void moveRight();
    void startJumpCharge();
    void startAttackCharge(bool isHighAttack);
    void releaseCharge(bool leftPressed, bool rightPressed);
    void startBlock();
    void stopBlock();
    void update(float frameTime, float groundY, float maxJumpHeight);

    //attack
    bool checkAttackHit(Player& opponent);
    void takeDamage(int amount);

    //getters
    const sf::RectangleShape& getBody() const;
    const sf::RectangleShape& getAttackHitbox() const;
    int getHealth() const;
    bool isAttacking() const;
    bool isCharging() const;
    bool getIsBlocking() const;
    ChargeType getChargeType() const;
    float getChargePercentage() const;
    bool getFacingRight() const;
    float getAttackMultiplier() const;

    //setters
    void setPosition(const sf::Vector2f& position);
    void setIsWalking(bool t);

    //helpers
    void draw(sf::RenderWindow& window) const;
    void drawHealthBar(sf::RenderWindow& window) const;
    void drawChargeBar(sf::RenderWindow& window) const;
};

FightState runGameScene(sf::RenderWindow& window, int p1code, int p2code);
