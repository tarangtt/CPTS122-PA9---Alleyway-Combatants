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
    originalHeight(size.y)
{
    body.setFillColor(color);
    attackHitbox.setFillColor(sf::Color(255, 255, 0, 150));
}

void Player::loadSprites(
    const std::string& walk1Path,
    const std::string& walk2Path,
    const std::string& blockPath,
    const std::string& jumpPath,
    const std::string& highAttackLaunchPath,
    const std::string& highAttackChargePath,
    const std::string& lowAttackLaunchPath,
    const std::string& lowAttackChargePath
) {
    characterWalk1 = spritePack(walk1Path);
    characterWalk2 = spritePack(walk2Path);
    characterBlock = spritePack(blockPath);
    characterJump = spritePack(jumpPath);
    characterHighAttackLaunch = spritePack(highAttackLaunchPath);
    characterHighAttackCharge = spritePack(highAttackChargePath);
    characterLowAttackLaunch = spritePack(lowAttackLaunchPath);
    characterLowAttackCharge = spritePack(lowAttackChargePath);
}

void Player::moveLeft() {
    if (!isJumping && !isBlocking) {
        body.move({ -moveSpeed, 0.f });
        facingRight = false;
    }
}

void Player::moveRight() {
    if (!isJumping && !isBlocking) {
        body.move({ moveSpeed, 0.f });
        facingRight = true;
    }
}

void Player::startJumpCharge() {
    if (!isChargingJump && !isChargingAttack && !isAttackingBool && !isBlocking) {
        isChargingJump = true;
        chargeStart = std::chrono::steady_clock::now();
    }
    if (isChargingJump) {
        chargeTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - chargeStart).count();
    }
}

void Player::startAttackCharge(bool isHighAttack) {
    if (!isChargingJump && !isChargingAttack && !isAttackingBool && !isBlocking) {
        isChargingAttack = true;
        chargingAttackType = isHighAttack ? AttackType::High : AttackType::Low;
        chargeStart = std::chrono::steady_clock::now();
    }
    if (isChargingAttack) {
        chargeTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - chargeStart).count();
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

void Player::draw(sf::RenderWindow& window) const {
    window.draw(body);
    if (isAttackingBool) {
        window.draw(attackHitbox);
    }
    if (isBlocking) {
        sf::CircleShape shield(10.f);
        shield.setFillColor(sf::Color(0, 255, 255, 150));
        shield.setPosition({
            facingRight ? body.getPosition().x + body.getSize().x - 10.f
                       : body.getPosition().x,
            body.getPosition().y + body.getSize().y / 2 - 10.f
            });
        window.draw(shield);
    }
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