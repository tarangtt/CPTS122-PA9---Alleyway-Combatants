#include "basePlayer.hpp"

Player::Player(const sf::Vector2f& size, const sf::Color& color, bool startFacingRight, int characterChoice) :
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
    currentState(CharacterState::Idle),
    previousState(CharacterState::Idle),
    animationTimer(0.f),
    walkFrame(false),
    currentSprite(nullptr)
{
    body.setFillColor(color);
    attackHitbox.setFillColor(sf::Color(255, 255, 0, 150));

    // Load character sprites
    std::string prefix;
    switch (characterChoice) {
    case 1:  prefix = "Yuta"; break;
    case 2:  prefix = "Tarang"; break;
    case 3:  prefix = "John"; break;
    default: prefix = "Yuta"; break;
    }

    characterTextures.addTexture("Walk1", prefix + "\\" + prefix + "Walk1.png");
    characterTextures.addTexture("Walk2", prefix + "\\" + prefix + "Walk2.png");
    characterTextures.addTexture("Block", prefix + "\\" + prefix + "Block.png");
    characterTextures.addTexture("Jump", prefix + "\\" + prefix + "Jump.png");
    characterTextures.addTexture("HighAttackLaunch", prefix + "\\" + prefix + "Punch2.png");
    characterTextures.addTexture("HighAttackCharge", prefix + "\\" + prefix + "Punch1.png");
    characterTextures.addTexture("LowAttackLaunch", prefix + "\\" + prefix + "Kick2.png");
    characterTextures.addTexture("LowAttackCharge", prefix + "\\" + prefix + "Kick1.png");

    //set start (defualt) as Walk1 texture
    currentSprite = new sf::Sprite(characterTextures.getTexture("Walk1"));

    currentSprite->setOrigin({
        currentSprite->getLocalBounds().size.x / 2,
        currentSprite->getLocalBounds().size.y
        });

}

Player::~Player() {
    delete currentSprite;
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

    updateSprite(frameTime);
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

bool Player::getFacingRight() const {
    return facingRight;
}

float Player::getAttackMultiplier() const {
    return attackMultiplier;
}

void Player::setPosition(const sf::Vector2f& position) {
    body.setPosition(position);
}

void Player::setIsWalking(bool t)
{
    isWalking = t;
}

void Player::updateSprite(float frameTime) {
    previousState = currentState;

    if (isBlocking) currentState = CharacterState::Blocking; 
    else if (isJumping) currentState = CharacterState::Jumping; 
    else if (isChargingAttack) currentState = (chargingAttackType == AttackType::High) ? CharacterState::HighAttackCharge : CharacterState::LowAttackCharge;
    else if (isAttackingBool) currentState = (currentAttack == AttackType::High) ? CharacterState::HighAttackLaunch : CharacterState::LowAttackLaunch;
    else if (isWalking) currentState = CharacterState::Walking; 
    else currentState = CharacterState::Idle;

    //animation timing
    if (currentState == CharacterState::Walking) {
        animationTimer += frameTime;
        if (animationTimer >= animationSwitchTime) {
            animationTimer = 0.f;
            walkFrame = !walkFrame;
        }
    }

    //set sprite texture
    try {
        switch (currentState) {
        case CharacterState::Walking:
            currentSprite->setTexture(walkFrame ? characterTextures.getTexture("Walk1") : characterTextures.getTexture("Walk2"));
            break;
        case CharacterState::Blocking:
            currentSprite->setTexture(characterTextures.getTexture("Block"));
            break;
        case CharacterState::Jumping:
            currentSprite->setTexture(characterTextures.getTexture("Jump"));
            break;
        case CharacterState::HighAttackCharge:
            currentSprite->setTexture(characterTextures.getTexture("HighAttackCharge"));
            break;
        case CharacterState::HighAttackLaunch:
            currentSprite->setTexture(characterTextures.getTexture("HighAttackLaunch"));
            break;
        case CharacterState::LowAttackCharge:
            currentSprite->setTexture(characterTextures.getTexture("LowAttackCharge"));
            break;
        case CharacterState::LowAttackLaunch:
            currentSprite->setTexture(characterTextures.getTexture("LowAttackLaunch"));
            break;
        default:
            currentSprite->setTexture(characterTextures.getTexture("Walk1")); //walk1 for idle
            break;
        }
    }
    catch (...) {
        currentSprite->setTexture(characterTextures.get_MISSING_Texture());
    }

    //flip sprite based on direction player is facing
    currentSprite->setScale(facingRight ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.f));

    //currentSprite->setPosition({
    //    body.getPosition().x + body.getSize().x / 2,
    //    body.getPosition().y + body.getSize().y / 2
    //    });

    if (isBlocking)
    {
        currentSprite->setPosition({
            body.getPosition().x + body.getSize().x / 2,  //horizontal center
            body.getPosition().y + body.getSize().y + 400  //400px from top is blocking
            });
    }
    else
    {
        currentSprite->setPosition({
            body.getPosition().x + body.getSize().x / 2,  //horizontal center
            body.getPosition().y + body.getSize().y + 200  //200px from top
            });
    }


}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(*currentSprite);
    if (isAttackingBool) {
        window.draw(attackHitbox);
    }
}

void Player::drawHealthBar(sf::RenderWindow& window) const {
    float width = body.getSize().x * (health / 100.f);
    sf::RectangleShape bar({ width, 10.f });
    bar.setFillColor(health > 50 ? sf::Color::Green :
        health > 25 ? sf::Color::Yellow : sf::Color::Red);
    bar.setPosition({ body.getPosition().x, body.getPosition().y - 70.f });
    window.draw(bar);
}

void Player::drawChargeBar(sf::RenderWindow& window) const {
    float width = 100.f * getChargePercentage();
    sf::RectangleShape bar({ width, 8.f });
    bar.setFillColor(getChargeType() == ChargeType::Attack ?
        sf::Color(255, 165, 0, 180) : sf::Color(0, 255, 0, 180));
    bar.setPosition({ body.getPosition().x + (body.getSize().x / 2.f - 50.f),
                    body.getPosition().y - 50 - (getChargeType() == ChargeType::Attack ? 40.f : 30.f) });
    window.draw(bar);
}