#include "background.h"
using std::string;            // 使用标准库中的string


// 构造函数实现
Background::Background(const sf::Texture& texture, sf::Vector2f position)
    : sf::Sprite(texture),   // 初始化基类Sprite
    texture(texture)       // 初始化成员texture
    {
        // 设置精灵使用的纹理
        setTexture(this->texture);

        // 设置精灵位置
        setPosition(position);

        // 获取当前桌面分辨率
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        // 计算并设置缩放比例，使背景填满整个屏幕
        // 计算方法：屏幕宽度/纹理宽度，屏幕高度/纹理高度
        setScale({
            (float)desktop.size.x / texture.getSize().x,  // 水平缩放比例
            (float)desktop.size.y / texture.getSize().y   // 垂直缩放比例
            });
    }