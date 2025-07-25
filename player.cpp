#include "player.h"


//相当于.cpp文件
Player::Player(sf::Vector2f position, const sf::Texture& playerTexture)
    : sf::Sprite(playerTexture), texture(playerTexture)
{
    setTexture(texture);//设置玩家角色图片
    setPosition({ position.x / 2, position.y / 1.5f });//设置位置
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// 获取桌面分辨率
    setScale({ PLAYER_SCALE * desktop.size.x / 1920, PLAYER_SCALE * desktop.size.x / 1920 });//设置分辨率
    speed = PLAYER_SPEED * (static_cast<float>(desktop.size.x) / 1920);//设置速度
    health = 5;//设置健康值
};

//成员函数
void Player::movePlayer(sf::Vector2u windowSize)
{
    float radius = getGlobalBounds().size.x / 2.f;
    sf::Vector2u spriteSize = (getTexture().getSize());//设置大小

    sf::Vector2f position = getPosition();//位置
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        if (position.x > 0)//检查左边界
            move({ -speed, 0 });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        if (position.x + PLAYER_SCALE * spriteSize.x < windowSize.x) //检查右边界
            move({ speed, 0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        if (position.y > 0)//检查上边界
            move({ 0,-speed });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        if (position.y + PLAYER_SCALE * spriteSize.y < windowSize.y * 0.84) //检查下边界
            move({ 0,speed });



}

//生命值减少
void Player::decrementPlayerHealth()
{
    if (health > 0)
    {
        health -= 1;

    }
}

