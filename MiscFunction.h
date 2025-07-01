#pragma once
#ifndef _MISCFUNCTION_H_
#define _MISCFUNCTION_H_
#include <SFML/Graphics.hpp>
#include "background.h"
#include "player.h"
#include "boss.h"
#include "boss_1.h"
#include <cstdlib>
#include <ctime>
#include "bullet.h"
#include "enemy.h"
#include <iostream>
#include <fstream>
/**
 * ��ʼ����Ϸ����
 * @return ȫ��ģʽ����Ⱦ���ںʹ��ڳߴ�
 */
sf::RenderWindow initWindow();

/**
*����ģ��
* @param window ��Ϸ�������ã����ڻ�ȡ���ڳߴ磩
* @return ��ʼ����Ķ���
* */
Player loadPlayer(sf::RenderWindow& window);

Boss loadBoss(sf::RenderWindow& window);

Background loadBackground();

 /**
  * ����ӵ��Ƿ���е���
  * @param bullet ����
  * @param enemy ���˶���
  * @return �Ƿ����
  */
extern bool checkShotHit(Bullet& bullet, Enemy& enemy);

extern bool checkShotHitBoss(Bullet& bullet, Boss1& boss);

/**
 * �������Ƿ񱻵��˻���
 * @param player ��Ҷ���
 * @param ball ���˶���
 * @return �Ƿ�����ײ
 */
extern bool checkIfPlayerIsHit(Player& player, const Enemy& ball);

/**
 * ��鲢������߷�
 * @param cur ��ǰ����
 * @return �µ���߷�
 */
int checkHighScore(int cur);
/**
 * ���ز���ʼ����Ϸ�ı���ǩ
 * @param window ��Ϸ����
 * @param font �������
 * @param scoreLabel ������ǩ
 * @param healthLabel ����ֵ��ǩ
 * @param highScoreLable ��߷ֱ�ǩ
 */
void loadTexts(sf::RenderWindow& window, sf::Font& font, sf::Text& scoreLabel, sf::Text& healthLabel, sf::Text& highScoreLable);


//boss�����ͷ�

#endif // !_MISCFUNCTION_H_