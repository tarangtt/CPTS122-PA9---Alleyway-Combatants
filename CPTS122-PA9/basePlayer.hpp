#pragma once
#include "_libs.hpp"

class Player {
private:

    //player trackin
    bool isJumping;
    bool isChargingJump;
    bool isChargingAttack;
    bool isBlocking;
    JumpType currentJump;
    AttackType chargingAttackType;
    float verticalVelocity;
    float horizontalVelocity;
    float currentHeight;
    bool facingRight;
    std::chrono::steady_clock::time_point chargeStart;
    float chargeTime;
    bool hasHitThisAttack;
    bool isWalking;
    float walkAnimationTimer;
    bool isFirstWalkSprite;
    int characterChoice;

    //attack and health
    int health;
    bool isAttackingBool;
    AttackType currentAttack;
    std::chrono::steady_clock::time_point attackStartTime;
    float attackDuration;
    float attackMultiplier;
    sf::RectangleShape attackHitbox;
    float blockFrontDamageReduction;
    float blockBackDamageReduction;

    //visuals
    sf::RectangleShape body;
    sf::Color color;
    float originalHeight;
    sf::Sprite* currentSprite;

    //const
    const float baseGravity = 0.03f;
    const float baseJumpVelocity = -3.2f;
    const float baseHorizontalJumpSpeed = 1.1f;
    const float moveSpeed = 0.8f;
    const float minChargeTime = 0.1f;
    const float maxChargeTime = 3.0f;
    const float maxChargeMultiplier = 2.5f;
    const int baseAttackDamage = 10;
    const float attackRange = 100.f;
    const float highAttackHeightRatio = 2.2f;
    const float lowAttackHeight = 100.f;
    const float blockHeightReduction = 0.6f;

    //helper func
    void updateAttackHitbox();
    void updateSprite();

    //sprites
    spritePack characterWalk1, characterWalk2, characterBlock, characterJump;
    spritePack characterHighAttackLaunch, characterHighAttackCharge;
    spritePack characterLowAttackLaunch, characterLowAttackCharge;
    spritePack characterCharge;

public:
    Player(const sf::Vector2f& size, const sf::Color& color, bool startFacingRight);

    void loadSprites(int characterChoice, bool isPlayer1);
    void moveLeft();
    void moveRight();
    void startJumpCharge();
    void startAttackCharge(bool isHighAttack);
    void releaseCharge(bool leftPressed, bool rightPressed);
    void startBlock();
    void stopBlock();
    void update(float frameTime, float groundY, float maxJumpHeight);
    bool checkAttackHit(Player& opponent);
    void takeDamage(int amount);
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
    void setPosition(const sf::Vector2f& position);
    void setColor(const sf::Color& color);
    void draw(sf::RenderWindow& window) const;
    void drawHealthBar(sf::RenderWindow& window) const;
    void drawChargeBar(sf::RenderWindow& window) const;
    void reset();
};

void draw(sf::RenderWindow& window);
void runFightGame(sf::RenderWindow& window, int p1Choice, int p2Choice);
