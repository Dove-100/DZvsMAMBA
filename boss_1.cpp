#include "boss_1.h"

// 构造函数
// 参数: tex - 书籍纹理
Boss1::Boss1(const sf::Texture& tex) : sf::Sprite(tex)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();//获取屏幕分辨率
    setOrigin(sf::Vector2f{ tex.getSize().x / 2.0f , tex.getSize().y / 2.f });//设置Book的原点位置
    setPosition({getGlobalBounds().size.x , getGlobalBounds().size.y / 2 });//设置出现位置  x坐标随机
    originalHealth = health = 100;//随机生命值

}

void Boss1::setTexture(const sf::Texture& tex) { texture = tex; }//设置纹理

void Boss1::setHealth(int newHealth) { health = newHealth; }//设置生命值

int Boss1::getHealth() const { return health; }//获取当前生命值

int Boss1::getOriginalHealth() const { return originalHealth; }//获取初始生命值



void Boss1::update(sf::Vector2u windowSize) {

    move({vx,0}); // move the ball

    bounce(windowSize); // check for bounces

}


void Boss1::bounce(sf::Vector2u& windowSize)
{
    sf::Vector2f pos = getPosition();
    float radius = getGlobalBounds().size.x / 2.f;

    //left bounce
    if (pos.x - radius <= 0.f) {
        setPosition({ radius, pos.y });
        vx = -vx;
    }

    //right bounce
    if (pos.x + radius >= static_cast<float>(windowSize.x)) {
        setPosition({ static_cast<float>(windowSize.x) - radius, pos.y });
        vx = -vx;
    }
}
