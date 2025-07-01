#pragma once
#ifndef _BOSS_1_H_
#define _BOSS_1_H_
#include <SFML/graphics.hpp>  
#include <cmath>  

class Boss1 : public sf::Sprite {
public:
    // 构造函数
    // 参数: tex - Boss1纹理
    Boss1(const sf::Texture& tex);

    void update(sf::Vector2u windowSize);  //更新Boss1位置、速度、边界检测

    void bounce(sf::Vector2u& windowSize);//边界检测

    void setTexture(const sf::Texture& tex);//设置纹理

    void setHealth(int newHealth);//设置生命值

    int getHealth() const;//获取当前生命值

    int getOriginalHealth() const;//获取初始生命值

private:
    float vx = 5;  //速度
    float vy = 0;
    sf::Texture texture;//纹理
    int health;//生命值
    int originalHealth;//初始生命值
};

#endif