#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

class Bullet : public sf::Sprite
{
public:
    // 构造函数：创建一个子弹对象
    // 参数：
    //   texture - 子弹的纹理
    //   position - 初始位置
    Bullet(const sf::Texture& texture, sf::Vector2f position);

    //更新铅笔状态
    // 参数：
     //   window - 游戏窗口引用
     //   laserSound - 发射音效引用
     //   player - 玩家对象
    void update(const sf::RenderWindow& window, sf::Music& laserSound, Player player);

    //获取射击状态
    bool getIsShooting()const;
    //设置射击状态
    void setIsShooting(bool isShootingNewValue);
    //设置击中状态
    void setIsHit();
    //获取是否击中状态
    const bool getIsHit()const;

private:
    float speed;//模速度
    bool isShooting;//是否发射
    bool isHit;//是否击中
    bool hadShooted;//是否已经击中
    sf::Vector2f velocity_bullet;  //速度矢量
};
#endif // !_BULLET_H_