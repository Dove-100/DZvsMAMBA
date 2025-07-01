#include "gameOverpage.h"


/**
 * @class GameOverScreen
 * @brief 游戏结束画面类，继承自Menu基类
 *
 * 显示游戏结束界面，提供重新开始或退出游戏选项
 */

    /**
     * @brief 构造函数
     * @param backgroundTexture 背景纹理引用
     * @param playerTexture 玩家纹理引用
     * @param font 字体引用
     * @param windowSize 窗口尺寸
     */
GameOverScreen::GameOverScreen(const sf::Texture& backgroundTexture, const sf::Texture& playerTexture, const sf::Texture& bossTexture, const sf::Font& font, sf::Vector2u windowSize)
        : Menu(backgroundTexture, playerTexture, bossTexture, font, windowSize), // Initialize the base class (Menu) 初始化基类
        background(backgroundTexture),
        player({ (float)windowSize.x, (float)windowSize.y }, playerTexture),
        gameOverText(font, "GAME OVER", 100),// 游戏结束标题
        escapeCont(font, "Press E To Play Again", 50),//ESC再次开始
        menuCont(font, "Or Press ESCAPE to Exit", 50),//E退出游戏
        credits(font, "Credits: \nDylan Hale \nIsaiah Foster \nAaron Sanchez \nJustin Scofield", 20)//制作者名单
    {
        // Set up the background
        background.setPosition({ 0, 0 });
        background.setScale({
            (float)windowSize.x / background.getTextureRect().size.x,
            (float)windowSize.y / background.getTextureRect().size.y
            });

        // Set up the player
        player.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 2 });
        player.setScale({ 0.5f, 0.5f }); // Adjust scale as needed
        player.setOrigin({ player.getGlobalBounds().size.x / 1, player.getGlobalBounds().size.y / 2 });

        // Set up the "Game Over" text
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOrigin({ gameOverText.getGlobalBounds().size.x / 2, gameOverText.getGlobalBounds().size.y / 2 });
        gameOverText.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 5.5f });

        // Set up escape text
        escapeCont.setFillColor(sf::Color::Red);
        escapeCont.setOrigin({ escapeCont.getGlobalBounds().size.x / 2, escapeCont.getGlobalBounds().size.y / 2 });
        escapeCont.setPosition({ (float)windowSize.x / 2, (float)windowSize.y / 3.45f });

        // Set up go-to-menu option text
        menuCont.setFillColor(sf::Color::Red);
        menuCont.setOrigin({ escapeCont.getGlobalBounds().size.x / 2, escapeCont.getGlobalBounds().size.y / 2 });
        menuCont.setPosition({ (float)windowSize.x / 1.7f, (float)windowSize.y / 2.8f });

        // Set up credits
        credits.setFillColor(sf::Color::Red);
        credits.setOrigin({ credits.getGlobalBounds().size.x / 2, credits.getGlobalBounds().size.y / 2 });
        credits.setPosition({ (float)windowSize.x / 4.0f, (float)windowSize.y / 2.0f });
    }

    /**
    * @brief 运行游戏结束画面主循环
    * @param window 渲染窗口引用
    */
    void GameOverScreen::run(sf::RenderWindow& window,Boss1& boss) {
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            // E再来一次
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                boss.setHealth(100);
                return;
            }
            // Escape退出
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                exit(0);
            }

            // Draw the game over screen
            window.clear();
            window.draw(background);
            window.draw(player);
            window.draw(gameOverText);
            window.draw(escapeCont);
            window.draw(menuCont);
            window.draw(credits);
            window.display();
        }
        return; // If the window is closed, do not restart
    }
