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
    /*-------------------------------------------- ����ģ�� ---------------------------------------- */
    // ��ʼ�����������
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // ��ʼ�����ڲ���ȡ���ڳߴ�
    sf::RenderWindow window = initWindow();
    sf::Vector2u windowSize = window.getSize();

    // ���ز˵���������
    sf::Music menuMusic;
    menuMusic.openFromFile("danceWeapon4.mp3");  // ���������ļ�
    menuMusic.setVolume(10);  // ��������
    menuMusic.play();  // ��������
    menuMusic.setLooping(true);  // ����ѭ������

    // ������Ϸ��������
    sf::Music gameMusic;
    gameMusic.openFromFile("track1.mp3");
    gameMusic.setVolume(15);

    // ������ҽ�ɫ
    Player player = loadPlayer(window);
    Boss boss = loadBoss(window);

    // ���ر���
    Background background = loadBackground();

    // ��ʼ����Ϸ����
    int score = 0;

    // ���ؼ�����Ч
    sf::Music laserSound;
    laserSound.openFromFile("hit_sound.mp3");

    // ������ײ��Ч
    sf::Music hitSound;
    hitSound.openFromFile("pencil_hit.mp3");

    // ����boss������Ч
    //sf::Music bossHitSound;
    //bossHitSound.openFromFile("boss/boss_hit_sound.mp3");

    // ����bossʧ����Ч
    sf::Music bossSound;
    bossSound.openFromFile("boss/boss_voice.mp3");

    // ���ص�������
    sf::Texture enemyTextures[3];
    enemyTextures[0].loadFromFile("PNG/googly-a.png");
    enemyTextures[1].loadFromFile("PNG/googly-b.png");
    enemyTextures[2].loadFromFile("PNG/googly-c.png");

    //����Boss����
    sf::Texture bossTexture;

    // �����洢���˺��ӵ�������
    std::vector<Enemy> balls;
    std::vector<Bullet> bullets;

    // ������һ�����˶���
    Enemy firstEnemy(enemyTextures[std::rand() % 3]);  // ���ѡ������
    float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60); // ������ű���(0.1��0.15֮��)
    firstEnemy.setScale({ scale, scale });
    balls.push_back(firstEnemy);

    // ���ص�һ���ӵ�����
    sf::Texture bulletTex;
    bulletTex.loadFromFile("red_star.png");
    Bullet bullet(bulletTex, player.getPosition());
    bullets.push_back(bullet);

    // ��ʼ����ʱ�����ڿ������ɼ��
    sf::Clock ball_spawn_clock;  // �������ɼ�ʱ��
    sf::Clock bullet_spawn_clock;  // �ӵ����ɼ�ʱ��
    sf::Clock hitRestrictor;  // �������Ƽ�ʱ��

    // ��������
    sf::Font font;
    font.openFromFile("PressStart2P-Regular.ttf");
    // �����ı�����
    sf::Text scoreLabel(font);  // ������ʾ
    sf::Text healthLabel(font);  // ����ֵ��ʾ
    sf::Text highScoreLable(font);  // ��߷���ʾ

    // �����ı���ʽ
    loadTexts(window, font, scoreLabel, healthLabel, highScoreLable);

    // ���ó�ʼ��������
    float enemySpawnRate = 4;  // ������������(��)
    float pencilSpawnRate = 0.1;  // �ӵ���������(��)

    // ��ʾ��ʼ�˵�
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

    // ����boss����
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

    // ֹͣ�˵����֣���ʼ��Ϸ����
    menuMusic.stop();
    gameMusic.play();
    gameMusic.setLooping(true);
    /*-------------------------------------------- ����ģ�� ---------------------------------------- */
    // ����Ϸѭ��
    while (window.isOpen())
    {
        // �¼�����ѭ��
        while (const std::optional event = window.pollEvent())
        {
            // ��ESC���رմ���
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
                window.close();
        }

        // ���������߼�
        if (ball_spawn_clock.getElapsedTime().asSeconds() >= enemySpawnRate)
        {
            // �����µ���
            Enemy newBall(enemyTextures[std::rand() % 3]);
            float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60);
            newBall.setScale({ scale, scale });
            balls.push_back(newBall);
            ball_spawn_clock.restart();
            // �������Ѷ�(�������ɼ��)
            if (enemySpawnRate > 1) enemySpawnRate -= 0.1f;
            std::cout << "Number of balls: " << balls.size() << std::endl;
        }

        // �ӵ������߼�
        if (bullets[bullets.size() - 1].getIsShooting() == true &&
            bullet_spawn_clock.getElapsedTime().asSeconds() >= pencilSpawnRate)
        {
            Bullet newPencil(bulletTex, player.getPosition());
            bullets.push_back(newPencil);
            bullet_spawn_clock.restart();
        }

        // ����������Ϸ���� //

        //����boss
        firstBoss.update(window.getSize());

        // �������е���
        for (auto& ball : balls)
        {
            ball.update(window.getSize());
            if (ball.getHealth() <= 0)  // �����������ֵ�ľ�
            {
                score += ball.getOriginalHealth() * 8;  // ���ӷ���
                ball.setHealth(0);
                // ���������Ƴ����ݻٵĵ���
                balls.erase(std::remove_if(balls.begin(), balls.end(),
                    [](const Enemy& b) { return b.getHealth() <= 0; }), balls.end());
                scoreLabel.setString("Score: " + std::to_string(score));  // ���·�����ʾ
            }
        }

        // ���������ӵ�
        for (auto& bullet : bullets)
        {
            bullet.update(window, laserSound, player);
            // ����ӵ�����Ŀ���ɳ���Ļ�����ӵ���������2
            if ((bullet.getIsHit() || bullet.getPosition().y < 0) && bullets.size() > 2)
            {
                // ���������Ƴ��ӵ�
                bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& p) { return p.getIsHit() || p.getPosition().y < 0; }), bullets.end());
            }
        }

        // ��ײ���
        for (auto& ball : balls)
        {
            // �������Ƿ񱻵��˻���
            if (checkIfPlayerIsHit(player, ball) && hitRestrictor.getElapsedTime().asSeconds() >= 1)
            {
                player.setHealth(player.getHealth() - 1);  // ��������ֵ
                healthLabel.setString(std::to_string(player.getHealth()) + " HP");  // ��������ֵ��ʾ
                hitRestrictor.restart();
                player.setColor(sf::Color::Red);  // ��ұ���ʾ����
            }

            // ����ӵ��Ƿ���е���
            for (auto& bullet : bullets)
            {
                if (checkShotHit(bullet, ball)) hitSound.play();  // ���Ż�����Ч
            }

            // ���˺�ָ���ɫ
            if (player.getColor() == sf::Color::Red && hitRestrictor.getElapsedTime().asSeconds() >= 0.5)
            {
                player.setColor(sf::Color::White);
            }
        }
        // ����ӵ��Ƿ���� Boss
        for (auto& bullet : bullets) {
            if (checkShotHitBoss(bullet, firstBoss)) {
                hitSound.play();  // ���� Boss �����е���Ч
            }
        }

        // �������λ��
        player.movePlayer(window.getSize());

        // ����
        window.clear();

        // ����������Ϸ���� //

        // ���Ʊ������ı�
        window.draw(background);
        window.draw(scoreLabel);
        window.draw(healthLabel);
        window.draw(highScoreLable);

        // �������е���
        for (const auto& ball : balls)
        {
            window.draw(ball);
        }

        // ���������ӵ�
        for (const auto& bullet : bullets)
        {
            window.draw(bullet);
        }

        // �������
        window.draw(player);
        window.draw(firstBoss);

        // ��ʾ��������
        window.display();

        // ��Ϸ�������
        if (firstBoss.getHealth() <= 0 || player.getHealth()<=0)
        {
            bossSound.play();
            std::cout << "GAME OVER!" << std::endl;

            // �������λ�ú�״̬
            player.setPosition({ (float)windowSize.x / 2.f, (float)windowSize.y / 1.5f });
            window.clear();

            // ��ʾ��Ϸ��������
            GameOverScreen gameOverScreen(background.getTexture(), player.getTexture(), boss.getTexture(), font, windowSize);
            gameOverScreen.run(window,firstBoss);

            // ������Ϸ״̬
            enemySpawnRate = 5;
            highScoreLable.setString("High Score: " + std::to_string(checkHighScore(score)));
            score = 0;
            scoreLabel.setString("Score: 0");
            player.setHealth(5);
            healthLabel.setString("5 HP");
            balls.clear();  // ������е���
        }
    }
    return 0;
}