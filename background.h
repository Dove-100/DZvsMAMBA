#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SFML/graphics.hpp>  // 包含SFML图形模块
#include <string>             // 包含字符串库

// 背景类，继承自SFML的Sprite类
class Background : public sf::Sprite
{
public:
    // 构造函数
    // 参数：
    //   texture - 背景纹理引用
    //   position - 背景初始位置，默认为(0,0)
    Background(const sf::Texture& texture, sf::Vector2f position = { 0.f, 0.f });

private:
    sf::Texture texture;  // 存储背景纹理
    float scale;          // 背景缩放比例
};

#endif