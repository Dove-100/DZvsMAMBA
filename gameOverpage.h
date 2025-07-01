#pragma once
#ifndef _GAMEOVERPAGE_H_
#define _GAMEOVERPAGE_H_
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "menu.h"
#include "player.h"
#include "boss.h"
#include "boss_1.h"
#include "background.h"
/**
 * @class GameOverScreen
 * @brief 游戏结束画面类，继承自Menu基类
 *
 * 显示游戏结束界面，提供重新开始或退出游戏选项
 */
class GameOverScreen : public Menu {
public:
    /**
     * @brief 构造函数
     * @param backgroundTexture 背景纹理引用
     * @param playerTexture 玩家纹理引用
     * @param font 字体引用
     * @param windowSize 窗口尺寸
     */
    GameOverScreen(const sf::Texture& backgroundTexture, const sf::Texture& playerTexture, const sf::Texture& bossTexture, const sf::Font& font, sf::Vector2u windowSize);

    /**
    * @brief 运行游戏结束画面主循环
    * @param window 渲染窗口引用
    */
    void run(sf::RenderWindow& window, Boss1& boss);

private:
    Background background;
    Player player;
    sf::Text gameOverText;
    sf::Text escapeCont;
    sf::Text menuCont;
    sf::Text credits;
};
#endif