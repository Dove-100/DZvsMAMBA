#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
#include "player.h"
#include "boss.h"
#include "boss_1.h"
#include "background.h"
#include "enemy.h"
#include "Windows.h"
#include "MiscFunction.h"
#include <vector>
#include <string>
#include "bullet.h"
#include "gameOverpage.h"

int main()
{
    /*-------------------------------------------- 加载模块 ---------------------------------------- */
    // 初始化随机数种子
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 初始化窗口并获取窗口尺寸
    sf::RenderWindow window = initWindow();
    sf::Vector2u windowSize = window.getSize();

    // 加载菜单背景音乐
    sf::Music menuMusic;
    menuMusic.openFromFile("danceWeapon4.mp3");  // 加载音乐文件
    menuMusic.setVolume(10);  // 设置音量
    menuMusic.play();  // 播放音乐
    menuMusic.setLooping(true);  // 设置循环播放

    // 加载游戏背景音乐
    sf::Music gameMusic;
    gameMusic.openFromFile("track1.mp3");
    gameMusic.setVolume(15);

    // 加载玩家角色
    Player player = loadPlayer(window);
    Boss boss = loadBoss(window);

    // 加载背景
    Background background = loadBackground();

    // 初始化游戏分数
    int score = 0;

    // 加载激光音效
    sf::Music laserSound;
    laserSound.openFromFile("hit_sound.mp3");

    // 加载碰撞音效
    sf::Music hitSound;
    hitSound.openFromFile("pencil_hit.mp3");

    // 加载boss攻击音效
    //sf::Music bossHitSound;
    //bossHitSound.openFromFile("boss/boss_hit_sound.mp3");

    // 加载boss失败音效
    sf::Music bossSound;
    bossSound.openFromFile("boss/boss_voice.mp3");

    // 加载敌人纹理
    sf::Texture enemyTextures[3];
    enemyTextures[0].loadFromFile("PNG/googly-a.png");
    enemyTextures[1].loadFromFile("PNG/googly-b.png");
    enemyTextures[2].loadFromFile("PNG/googly-c.png");

    //加载Boss纹理
    sf::Texture bossTexture;

    // 创建存储敌人和子弹的容器
    std::vector<Enemy> balls;
    std::vector<Bullet> bullets;

    // 创建第一个敌人对象
    Enemy firstEnemy(enemyTextures[std::rand() % 3]);  // 随机选择纹理
    float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60); // 随机缩放比例(0.1到0.15之间)
    firstEnemy.setScale({ scale, scale });
    balls.push_back(firstEnemy);

    // 加载第一个子弹对象
    sf::Texture bulletTex;
    bulletTex.loadFromFile("red_star.png");
    Bullet bullet(bulletTex, player.getPosition());
    bullets.push_back(bullet);

    // 初始化计时器用于控制生成间隔
    sf::Clock ball_spawn_clock;  // 敌人生成计时器
    sf::Clock bullet_spawn_clock;  // 子弹生成计时器
    sf::Clock hitRestrictor;  // 击中限制计时器

    // 加载字体
    sf::Font font;
    font.openFromFile("PressStart2P-Regular.ttf");
    // 创建文本对象
    sf::Text scoreLabel(font);  // 分数显示
    sf::Text healthLabel(font);  // 生命值显示
    sf::Text highScoreLable(font);  // 最高分显示

    // 设置文本样式
    loadTexts(window, font, scoreLabel, healthLabel, highScoreLable);

    // 设置初始生成速率
    float enemySpawnRate = 4;  // 敌人生成速率(秒)
    float pencilSpawnRate = 0.1;  // 子弹生成速率(秒)

    // 显示开始菜单
    Menu menu(background.getTexture(), player.getTexture(), boss.getTexture(), font, windowSize);
    int level = menu.startMenu(window);
    if (level == 1) {
        bossTexture.loadFromFile("boss/green_boss.png");
    }
    else if (level == 2) {
        bossTexture.loadFromFile("boss/red_boss.png");
    }
    else if (level == 3)
    {
        bossTexture.loadFromFile("boss/blue_boss.png");
    }

    // 创建boss对象
    Boss1 firstBoss(bossTexture);

    if (level == 1) {
        firstBoss.setHealth(100);
    }
    else if (level == 2) {
        firstBoss.setHealth(200);
    }
    else if (level == 3)
    {
        firstBoss.setHealth(300);
    }

    // 停止菜单音乐，开始游戏音乐
    menuMusic.stop();
    gameMusic.play();
    gameMusic.setLooping(true);
    /*-------------------------------------------- 加载模块 ---------------------------------------- */
    // 主游戏循环
    while (window.isOpen())
    {
        // 事件处理循环
        while (const std::optional event = window.pollEvent())
        {
            // 按ESC键关闭窗口
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
                window.close();
        }

        // 敌人生成逻辑
        if (ball_spawn_clock.getElapsedTime().asSeconds() >= enemySpawnRate)
        {
            // 创建新敌人
            Enemy newBall(enemyTextures[std::rand() % 3]);
            float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60);
            newBall.setScale({ scale, scale });
            balls.push_back(newBall);
            ball_spawn_clock.restart();
            // 逐渐增加难度(减少生成间隔)
            if (enemySpawnRate > 1) enemySpawnRate -= 0.1f;
            std::cout << "Number of balls: " << balls.size() << std::endl;
        }

        // 子弹生成逻辑
        if (bullets[bullets.size() - 1].getIsShooting() == true &&
            bullet_spawn_clock.getElapsedTime().asSeconds() >= pencilSpawnRate)
        {
            Bullet newPencil(bulletTex, player.getPosition());
            bullets.push_back(newPencil);
            bullet_spawn_clock.restart();
        }

        // 更新所有游戏对象 //

        //更新boss
        firstBoss.update(window.getSize());

        // 更新所有敌人
        for (auto& ball : balls)
        {
            ball.update(window.getSize());
            if (ball.getHealth() <= 0)  // 如果敌人生命值耗尽
            {
                score += ball.getOriginalHealth() * 8;  // 增加分数
                ball.setHealth(0);
                // 从向量中移除被摧毁的敌人
                balls.erase(std::remove_if(balls.begin(), balls.end(),
                    [](const Enemy& b) { return b.getHealth() <= 0; }), balls.end());
                scoreLabel.setString("Score: " + std::to_string(score));  // 更新分数显示
            }
        }

        // 更新所有子弹
        for (auto& bullet : bullets)
        {
            bullet.update(window, laserSound, player);
            // 如果子弹击中目标或飞出屏幕，且子弹数量大于2
            if ((bullet.getIsHit() || bullet.getPosition().y < 0) && bullets.size() > 2)
            {
                // 从向量中移除子弹
                bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& p) { return p.getIsHit() || p.getPosition().y < 0; }), bullets.end());
            }
        }

        // 碰撞检测
        for (auto& ball : balls)
        {
            // 检测玩家是否被敌人击中
            if (checkIfPlayerIsHit(player, ball) && hitRestrictor.getElapsedTime().asSeconds() >= 1)
            {
                player.setHealth(player.getHealth() - 1);  // 减少生命值
                healthLabel.setString(std::to_string(player.getHealth()) + " HP");  // 更新生命值显示
                hitRestrictor.restart();
                player.setColor(sf::Color::Red);  // 玩家变红表示受伤
            }

            // 检测子弹是否击中敌人
            for (auto& bullet : bullets)
            {
                if (checkShotHit(bullet, ball)) hitSound.play();  // 播放击中音效
            }

            // 受伤后恢复颜色
            if (player.getColor() == sf::Color::Red && hitRestrictor.getElapsedTime().asSeconds() >= 0.5)
            {
                player.setColor(sf::Color::White);
            }
        }
        // 检测子弹是否击中 Boss
        for (auto& bullet : bullets) {
            if (checkShotHitBoss(bullet, firstBoss)) {
                hitSound.play();  // 播放 Boss 被击中的音效
            }
        }

        // 更新玩家位置
        player.movePlayer(window.getSize());

        // 清屏
        window.clear();

        // 绘制所有游戏对象 //

        // 绘制背景和文本
        window.draw(background);
        window.draw(scoreLabel);
        window.draw(healthLabel);
        window.draw(highScoreLable);

        // 绘制所有敌人
        for (const auto& ball : balls)
        {
            window.draw(ball);
        }

        // 绘制所有子弹
        for (const auto& bullet : bullets)
        {
            window.draw(bullet);
        }

        // 绘制玩家
        window.draw(player);
        window.draw(firstBoss);

        // 显示绘制内容
        window.display();

        // 游戏结束检测
        if (firstBoss.getHealth() <= 0 || player.getHealth()<=0)
        {
            bossSound.play();
            std::cout << "GAME OVER!" << std::endl;

            // 重置玩家位置和状态
            player.setPosition({ (float)windowSize.x / 2.f, (float)windowSize.y / 1.5f });
            window.clear();

            // 显示游戏结束画面
            GameOverScreen gameOverScreen(background.getTexture(), player.getTexture(), boss.getTexture(), font, windowSize);
            gameOverScreen.run(window,firstBoss);

            // 重置游戏状态
            enemySpawnRate = 5;
            highScoreLable.setString("High Score: " + std::to_string(checkHighScore(score)));
            score = 0;
            scoreLabel.setString("Score: 0");
            player.setHealth(5);
            healthLabel.setString("5 HP");
            balls.clear();  // 清空所有敌人
        }
    }
    return 0;
}