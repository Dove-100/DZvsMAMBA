#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <SFML/graphics.hpp>  
#include <cmath>  
#define MAX_SPEED 7
#define BOUNCE_RNDM .1
#define BASE_SPEED 5

class Enemy : public sf::Sprite {
public:
    // 构造函数
    // 参数: tex - 敌人纹理
    Enemy(const sf::Texture& tex);

    sf::Vector2f getVelocity() const { return velocity; }//获取速度矢量

    void update(sf::Vector2u windowSize);  //更新敌人位置、速度、边界检测

    void moderateSpeed();//限制速度不超过最大速度

    void bounce(sf::Vector2u& windowSize);//边界检测

    void setTexture(const sf::Texture& tex);//设置纹理

    void setHealth(int newHealth);//设置生命值

    int getHealth() const;//获取当前生命值

    int getOriginalHealth() const;//获取初始生命值

private:
    sf::Vector2f velocity;  //速度矢量
    float scale; //缩放系数
    sf::Texture texture;//纹理
    int health;//生命值
    int originalHealth;//初始生命值
};

#endif