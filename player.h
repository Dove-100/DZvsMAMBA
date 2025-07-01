#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SFML/Audio.hpp>
#include <SFML/graphics.hpp>
#include <string>

using std::string;
#define PLAYER_SCALE 0.15f
#define PLAYER_SPEED 13.f

class Player : public sf::Sprite
{
public:
    Player(sf::Vector2f position = { 0.f, 0.f }, const sf::Texture& playerTexture = sf::Texture());//初始化：玩家的位置和图片

    void movePlayer(sf::Vector2u windowSize);//移动

    void decrementPlayerHealth();//减少健康值

    int getHealth() const { return health; }//获取健康值

    void setHealth(int newHealth) { health = newHealth; }//设置健康值

private:
    sf::Texture texture;//图片
    float speed;//速度
    int health;//健康值
};

#endif