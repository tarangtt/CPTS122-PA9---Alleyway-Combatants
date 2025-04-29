#include "basePlayer.hpp"
#include "_libs.hpp"

Player::Player(const sf::Vector2f& size, const sf::Color& color, bool startFacingRight) :
    body(size),
    color(color),
    health(100),
    isJumping(false),
    isChargingJump(false),
    isChargingAttack(false),
    isBlocking(false),
    currentJump(JumpType::None),
    chargingAttackType(AttackType::None),
    verticalVelocity(0.f),
    horizontalVelocity(0.f),
    currentHeight(0.f),
    facingRight(startFacingRight),
    chargeTime(0.f),
    hasHitThisAttack(false),
    isAttackingBool(false),
    currentAttack(AttackType::None),
    attackDuration(0.2f),
    attackMultiplier(1.0f),
    blockFrontDamageReduction(0.7f),
    blockBackDamageReduction(0.3f),
    originalHeight(size.y),
    isWalking(false),
    walkAnimationTimer(0.f),
    isFirstWalkSprite(true),
    characterChoice(1),
    currentSprite(nullptr)
{
    body.setFillColor(color);
    attackHitbox.setFillColor(sf::Color(255, 255, 0, 150));
}

//void Player::loadSprites(int characterChoice, bool isPlayer1) {
//    this->characterChoice = characterChoice;
//    std::string characterPrefix;
//
//    switch (characterChoice) {
//    case 1: characterPrefix = "Yuta"; break;
//    case 2: characterPrefix = "Tarang"; break;
//    case 3: characterPrefix = "John"; break;
//    default: characterPrefix = "Yuta"; break;
//    }
//
//    characterWalk1 = spritePack(characterPrefix + "Walk1.png");
//    characterWalk2 = spritePack(characterPrefix + "Walk2.png");
//    characterBlock = spritePack(characterPrefix + "Block.png");
//    characterJump = spritePack(characterPrefix + "Jump.png");
//    characterHighAttackLaunch = spritePack(characterPrefix + "Punch2.png");
//    characterHighAttackCharge = spritePack(characterPrefix + "Punch1.png");
//    characterLowAttackLaunch = spritePack(characterPrefix + "Kick2.png");
//    characterLowAttackCharge = spritePack(characterPrefix + "Kick1.png");
//
//    currentSprite = &characterWalk1.sprite;
//}

void Player::loadSprites(int characterChoice, bool isPlayer1) {
    this->characterChoice = characterChoice;
    std::string characterPrefix;

    switch (characterChoice) {
    case 1: characterPrefix = "Yuta"; break;
    case 2: characterPrefix = "Tarang"; break;
    case 3: characterPrefix = "John"; break;
    default: characterPrefix = "Yuta"; break;
    }

    sf::RenderWindow window1(sf::VideoMode({ 800, 800 }), "Walk1");
    characterWalk1 = spritePack(window1, characterPrefix + "Walk1.png");

    sf::RenderWindow window2(sf::VideoMode({ 800, 800 }), "Walk2");
    characterWalk2 = spritePack(window2, characterPrefix + "Walk2.png");

    sf::RenderWindow window3(sf::VideoMode({ 800, 800 }), "Block");
    characterBlock = spritePack(window3, characterPrefix + "Block.png");

    sf::RenderWindow window4(sf::VideoMode({ 800, 800 }), "Jump");
    characterJump = spritePack(window4, characterPrefix + "Jump.png");

    sf::RenderWindow window5(sf::VideoMode({ 800, 800 }), "High Attack Launch");
    characterHighAttackLaunch = spritePack(window5, characterPrefix + "Punch2.png");

    sf::RenderWindow window6(sf::VideoMode({ 800, 800 }), "High Attack Charge");
    characterHighAttackCharge = spritePack(window6, characterPrefix + "Punch1.png");

    sf::RenderWindow window7(sf::VideoMode({ 800, 800 }), "Low Attack Launch");
    characterLowAttackLaunch = spritePack(window7, characterPrefix + "Kick2.png");

    sf::RenderWindow window8(sf::VideoMode({ 800, 800 }), "Low Attack Charge");
    characterLowAttackCharge = spritePack(window8, characterPrefix + "Kick1.png");

    currentSprite = &characterWalk1.sprite;
}



void Player::updateSprite() {
    if (isJumping) {
        currentSprite = &characterJump.sprite;
    }
    else if (isBlocking) {
        currentSprite = &characterBlock.sprite;
    }
    else if (isAttackingBool) {
        currentSprite = (currentAttack == AttackType::High)
            ? &characterHighAttackLaunch.sprite
            : &characterLowAttackLaunch.sprite;
    }
    else if (isChargingAttack) {
        if (characterChoice == 2 && characterCharge.texture.getSize().x > 0) {
            currentSprite = &characterCharge.sprite;
        }
        else {
            currentSprite = (chargingAttackType == AttackType::High)
                ? &characterHighAttackCharge.sprite
                : &characterLowAttackCharge.sprite;
        }
    }
    else if (isWalking) {
        currentSprite = isFirstWalkSprite
            ? &characterWalk1.sprite
            : &characterWalk2.sprite;
    }
    else {
        currentSprite = &characterWalk1.sprite;
    }

    currentSprite->setPosition(body.getPosition());
    if (facingRight)
    {
        currentSprite->setScale({ 1.0f, 1.0f });
    }
    else
    {
        currentSprite->setScale({- 1.0f, 1.0f});
    }
}

void Player::moveLeft() {
    if (!isJumping && !isBlocking) {
        body.move({ -moveSpeed, 0.f });
        facingRight = false;
        isWalking = true;
    }
}

void Player::moveRight() {
    if (!isJumping && !isBlocking) {
        body.move({ moveSpeed, 0.f });
        facingRight = true;
        isWalking = true;
    }
}

void Player::startJumpCharge() {
    if (!isChargingJump && !isChargingAttack && !isAttackingBool && !isBlocking) {
        isChargingJump = true;
        chargeStart = std::chrono::steady_clock::now();
    }
}

void Player::startAttackCharge(bool isHighAttack) {
    if (!isChargingJump && !isChargingAttack && !isAttackingBool && !isBlocking) {
        isChargingAttack = true;
        chargingAttackType = isHighAttack ? AttackType::High : AttackType::Low;
        chargeStart = std::chrono::steady_clock::now();
    }
}

void Player::releaseCharge(bool leftPressed, bool rightPressed) {
    if (isChargingJump && !isBlocking) {
        isChargingJump = false;
        isJumping = true;

        float chargeMultiplier = 1.0f +
            std::clamp(chargeTime, minChargeTime, maxChargeTime) / maxChargeTime *
            (maxChargeMultiplier - 1.0f);

        verticalVelocity = baseJumpVelocity * chargeMultiplier;

        if (leftPressed && !rightPressed) {
            currentJump = facingRight ? JumpType::Backward : JumpType::Forward;
            horizontalVelocity = -baseHorizontalJumpSpeed * chargeMultiplier;
        }
        else if (rightPressed && !leftPressed) {
            currentJump = facingRight ? JumpType::Forward : JumpType::Backward;
            horizontalVelocity = baseHorizontalJumpSpeed * chargeMultiplier;
        }
        else {
            currentJump = JumpType::Straight;
            horizontalVelocity = 0.f;
        }
    }
    else if (isChargingAttack && !isBlocking) {
        isChargingAttack = false;
        isAttackingBool = true;
        currentAttack = chargingAttackType;
        attackStartTime = std::chrono::steady_clock::now();
        attackMultiplier = 1.0f +
            std::clamp(chargeTime, minChargeTime, maxChargeTime) / maxChargeTime *
            (maxChargeMultiplier - 1.0f);
        hasHitThisAttack = false;
    }
}

void Player::startBlock() {
    if (!isJumping && !isAttackingBool && !isCharging() && !isBlocking) {
        isBlocking = true;
        sf::Vector2f size = body.getSize();
        body.setSize({ size.x, originalHeight * (1.0f - blockHeightReduction) });
        body.move({ 0, originalHeight * blockHeightReduction });
    }
}

void Player::stopBlock() {
    if (isBlocking) {
        isBlocking = false;
        sf::Vector2f size = body.getSize();
        float currentBottom = body.getPosition().y + size.y;
        body.setSize({ size.x, originalHeight });
        body.setPosition({ body.getPosition().x, currentBottom - originalHeight });
    }
}

void Player::update(float frameTime, float groundY, float maxJumpHeight) {
    if (isJumping) {
        verticalVelocity += baseGravity;

        sf::Vector2f newPos = body.getPosition();
        newPos.y += verticalVelocity;
        newPos.x += horizontalVelocity;

        float maxHeightY = (groundY - body.getSize().y) - maxJumpHeight;
        if (newPos.y < maxHeightY) {
            newPos.y = maxHeightY;
            verticalVelocity = 0.f;
        }

        newPos.x = std::clamp(newPos.x, 0.f, SCREEN_WIDTH - body.getSize().x);
        body.setPosition(newPos);

        if (newPos.y >= groundY - body.getSize().y) {
            body.setPosition({ newPos.x, groundY - body.getSize().y });
            isJumping = false;
            currentJump = JumpType::None;
            verticalVelocity = 0.f;
            horizontalVelocity = 0.f;
        }
    }

    if (isAttackingBool) {
        float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - attackStartTime).count();
        if (elapsed >= attackDuration) {
            isAttackingBool = false;
            currentAttack = AttackType::None;
            hasHitThisAttack = false;
        }
        else {
            updateAttackHitbox();
        }
    }
}

void Player::updateAttackHitbox() {
    float attackY = body.getPosition().y;
    float attackHeight = 0.f;

    if (currentAttack == AttackType::High) {
        attackHeight = body.getSize().y / highAttackHeightRatio;
    }
    else {
        attackY += body.getSize().y - lowAttackHeight;
        attackHeight = lowAttackHeight;
    }

    float attackX = body.getPosition().x;
    if (facingRight) {
        attackX += body.getSize().x;
    }
    else {
        attackX -= attackRange;
    }

    attackHitbox.setPosition({ attackX, attackY });
    attackHitbox.setSize(sf::Vector2f(attackRange, attackHeight));
}

bool Player::checkAttackHit(Player& opponent) {
    if (!isAttackingBool || hasHitThisAttack) {
        return false;
    }

    bool hit = attackHitbox.getGlobalBounds().findIntersection(
        opponent.getBody().getGlobalBounds()).has_value();

    if (hit) {
        hasHitThisAttack = true;
    }
    return hit;
}

void Player::takeDamage(int amount) {
    if (isBlocking) {
        bool attackFromFront = (facingRight == (attackHitbox.getPosition().x > body.getPosition().x));
        float reduction = attackFromFront ? blockFrontDamageReduction : blockBackDamageReduction;
        amount = static_cast<int>(amount * (1.0f - reduction));
    }
    health = max(0, health - amount);
}

const sf::RectangleShape& Player::getBody() const {
    return body;
}

const sf::RectangleShape& Player::getAttackHitbox() const {
    return attackHitbox;
}

int Player::getHealth() const {
    return health;
}

bool Player::isAttacking() const {
    return isAttackingBool;
}

bool Player::isCharging() const {
    return isChargingJump || isChargingAttack;
}

bool Player::getIsBlocking() const {
    return isBlocking;
}

ChargeType Player::getChargeType() const {
    if (isChargingJump) return ChargeType::Jump;
    if (isChargingAttack) return ChargeType::Attack;
    return ChargeType::None;
}

float Player::getChargePercentage() const {
    return std::clamp(chargeTime / maxChargeTime, 0.f, 1.f);
}

float Player::getAttackMultiplier() const {
    return attackMultiplier;
}

bool Player::getFacingRight() const {
    return facingRight;
}

void Player::setPosition(const sf::Vector2f& position) {
    body.setPosition(position);
}


void Player::drawHealthBar(sf::RenderWindow& window) const {
    float width = body.getSize().x * (health / 100.f);
    sf::RectangleShape bar({ width, 10.f });
    bar.setFillColor(health > 50 ? sf::Color::Green :
        health > 25 ? sf::Color::Yellow : sf::Color::Red);
    bar.setPosition({ body.getPosition().x, body.getPosition().y - 20.f });
    window.draw(bar);
}

void Player::drawChargeBar(sf::RenderWindow& window) const {
    float width = 100.f * getChargePercentage();
    sf::RectangleShape bar({ width, 8.f });
    bar.setFillColor(getChargeType() == ChargeType::Attack ?
        sf::Color(255, 165, 0, 180) : sf::Color(0, 255, 0, 180));
    bar.setPosition({ body.getPosition().x + (body.getSize().x / 2.f - 50.f),
                    body.getPosition().y - (getChargeType() == ChargeType::Attack ? 40.f : 30.f) });
    window.draw(bar);
}

void Player::reset() {
    health = 100;
    isJumping = false;
    isChargingJump = false;
    isChargingAttack = false;
    isBlocking = false;
    currentJump = JumpType::None;
    chargingAttackType = AttackType::None;
    verticalVelocity = 0.f;
    horizontalVelocity = 0.f;
    isAttackingBool = false;
    currentAttack = AttackType::None;
    hasHitThisAttack = false;
    isWalking = false;
    walkAnimationTimer = 0.f;
    isFirstWalkSprite = true;
    currentSprite = &characterWalk1.sprite;
}