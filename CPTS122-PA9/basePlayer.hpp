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

    //hitbox stuff
    sf::RectangleShape body;
    sf::Color color;
    float originalHeight;

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

    //sprites
    spritePack characterWalk1, characterWalk2, characterBlock, characterJump;
    spritePack characterHighAttackLaunch, characterHighAttackCharge; //punch
    spritePack characterLowAttackLaunch, characterLowAttackCharge; // kick

public:
    Player(const sf::Vector2f& size, const sf::Color& color, bool startFacingRight);
    void loadSprites(
        const std::string& walk1Path,
        const std::string& walk2Path,
        const std::string& blockPath,
        const std::string& jumpPath,
        const std::string& highAttackLaunchPath,
        const std::string& highAttackChargePath,
        const std::string& lowAttackLaunchPath,
        const std::string& lowAttackChargePath
    );

    //things player can do
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


    //getter
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

    //setter
    void setPosition(const sf::Vector2f& position);

    //helper funcs
    void draw(sf::RenderWindow& window) const;
    void drawHealthBar(sf::RenderWindow& window) const;
    void drawChargeBar(sf::RenderWindow& window) const;
};