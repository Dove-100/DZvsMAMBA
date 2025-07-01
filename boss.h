#pragma once
#ifndef _BOSS_H_
#define _BOSS_H_
#include <SFML/Audio.hpp>
#include <SFML/graphics.hpp>
class Boss : public sf::Sprite
{
public:
    Boss(sf::Vector2f position = { 0.f, 0.f }, const sf::Texture& bossTexture = sf::Texture());//初始化：boss的位置和图片

    int getHealth() const { return health; }//获取健康值

    void setHealth(int newHealth) { health = newHealth; }//设置健康值

private:
    sf::Texture texture;//图片
    int health;//健康值
};


#endif // !_BOSS_H_
