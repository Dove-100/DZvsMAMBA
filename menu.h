#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "boss.h"
#include "player.h"
#include "background.h"
enum class gameStateClass {
    mainMenu,
    Mode,
    Help,
    Exit,
};
enum class levelsClass {
    Default,
    Easy,
    Normal,
    Hard,
    Exit
};
class Menu
{
public:
    // 构造函数
    // 参数:
    //   backgroundTexture - 背景纹理引用
    //   playerTexture - 玩家纹理引用
    //   font - 字体引用
    //   windowSize - 窗口大小
    Menu(const sf::Texture& backgroundTexture, const sf::Texture& playerTexture, const sf::Texture& bossTexture, const sf::Font& font, sf::Vector2u windowSize);
    //菜单开始页面
    int startMenu(sf::RenderWindow& window);
private:
    Background background;//背景
    Player player;//玩家
    Boss boss;//Boss
    sf::Text gameTitleText;//游戏结束文本
    sf::Text playCont;//开始游戏提示文本
    sf::Text helpCont;//帮助提升文本
    sf::Text modeCont;//模式选择文本
    sf::Text exitCont;//退出文本
    sf::Text easyText;//简单模式
    sf::Text normalText;//正常模式
    sf::Text hardText;//困难模式
    sf::Text rulescontextText;//游戏玩法
    int selectedOptionMainMenu = 0; // mainMenu = 0, play = 1, levels = 2, exit = 3
    const int totalOptionsMainMenu = 3;
    gameStateClass gameState = gameStateClass::mainMenu;

    int selectedOptionLevelsMenu = 0;
    const int totalOptionsLevelsMenu = 3;
    levelsClass level = levelsClass::Default;

    int exit_help = 0;
};
#endif