#include "enemy.h"
    // 构造函数
    // 参数: tex - 书籍纹理
Enemy::Enemy(const sf::Texture& tex) : sf::Sprite(tex), velocity(sf::Vector2f{ -BASE_SPEED, -BASE_SPEED })
    {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();//获取屏幕分辨率
        setOrigin(sf::Vector2f{ static_cast<float>(tex.getSize().x / 2) , static_cast<float>(tex.getSize().y) / 2.f });//设置Book的原点位置
        setPosition(sf::Vector2f{ static_cast<float> (std::rand() % desktop.size.x) , -getGlobalBounds().size.y });//设置出现位置  x坐标随机
        scale = (float)desktop.size.x / 1920;//缩放系数
        float scales[2] = { scale, -scale };
        velocity.x *= (float)scales[rand() % 30]; // random x axis direction at start 随机速度方向（对x轴分量）
        velocity.y *= scale;
        setScale({ scale, scale });//设置精灵缩放
        originalHealth = health = rand() % 10 + 5;//随机生命值
    }

void Enemy::setTexture(const sf::Texture& tex) { texture = tex; }//设置纹理

void Enemy::setHealth(int newHealth) { health = newHealth; }//设置生命值

int Enemy::getHealth() const { return health; }//获取当前生命值

int Enemy::getOriginalHealth() const { return originalHealth; }//获取初始生命值

void Enemy::update(sf::Vector2u windowSize) 
{
    moderateSpeed(); // 限制最大速度
    move(velocity); // 移动
    bounce(windowSize); // check for bounces
}

void Enemy::moderateSpeed()
{
    if (velocity.x > MAX_SPEED * scale)
        velocity.x = MAX_SPEED * scale;
    else if (velocity.x < -MAX_SPEED * scale)
        velocity.x = MAX_SPEED * scale;
    if (velocity.y > MAX_SPEED * scale)
        velocity.y = MAX_SPEED * scale;
    else if (velocity.y < -MAX_SPEED * scale)
        velocity.y = MAX_SPEED * scale;
}

void Enemy::bounce(sf::Vector2u& windowSize)
{
    sf::Vector2f pos = getPosition();
    float radius = getGlobalBounds().size.x / 2.f;

    //bottom bounce
    if (pos.y + radius >= static_cast<float>(windowSize.y) * (float).88) {
        setPosition({ pos.x, static_cast<float>(windowSize.y) * (float).88 - radius });
        velocity.y = -velocity.y; //bounce the ball
        velocity.x -= BOUNCE_RNDM; //slow down the ball slightly on bounce
    }

    //top bounce
    if (pos.y - radius <= 0.f) {
        setPosition({ pos.x, radius });
        velocity.y = -velocity.y;
        velocity.x -= BOUNCE_RNDM;
    }

    //left bounce
    if (pos.x - radius <= 0.f) {
        setPosition({ radius, pos.y });
        velocity.x = -velocity.x;
        velocity.y -= BOUNCE_RNDM;
    }

    //right bounce
    if (pos.x + radius >= static_cast<float>(windowSize.x)) {
        setPosition({ static_cast<float>(windowSize.x) - radius, pos.y });
        velocity.x = -velocity.x;
        velocity.y -= BOUNCE_RNDM;
    }
}
