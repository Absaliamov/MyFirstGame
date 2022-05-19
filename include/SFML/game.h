#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "SFML/objects.h"
#include "SFML/functions.h"
#include <math.h>
#include <list>

using namespace sf;

int window_a = 1280;
int window_b = 960;


bool menu(RenderWindow & window) {
    Music music;
    music.openFromFile("resources/menu_music.flac");
    music.play();music.setLoop(true);
    music.setVolume(80);
    Texture menuTexture1, menuTexture2,menuBackground;
    menuTexture1.loadFromFile("resources/start.png");
    menuTexture2.loadFromFile("resources/exit.png");
    menuBackground.loadFromFile("resources/back.jpg");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menuBg.setPosition(0, 0);

    while (1)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return true;
            }
        }
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1){music.stop(); return false;}//если нажали первую кнопку, то выходим из меню 
            if (menuNum == 2){window.close();music.stop(); return true;}
        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.display();
    }
}



Tank tank("tank.png", window_a / 2, window_b / 2, 70, 80);

std::list<Bullet*> bullets;
std::list<Bullet*>::iterator it1;

std::list<Enemy*> enemies;
std::list<Enemy*>::iterator it2;
std::list<Enemy*>::iterator it22;

std::list<Pos*> positions;
std::list<Pos*>::iterator it3;

bool startGame()
{
    sf::RenderWindow window(sf::VideoMode(window_a,window_b), "Simple tanks");
    bool ans = menu(window);

    Music music;
    music.openFromFile("resources/music.flac");
    music.play();music.setLoop(true);music.setVolume(50);

    Font font;
    font.loadFromFile("resources/font.ttf");
    Text text("", font, 40);
    text.setStyle(Text::Style::Bold);

    Image i_heart;
    i_heart.loadFromFile("resources/heart1.png");
    i_heart.createMaskFromColor(Color::Black);
    Texture t_heart;
    t_heart.loadFromImage(i_heart);
    Sprite heart;
    heart.setTexture(t_heart);

    SoundBuffer buffer;
    Sound sound;
    buffer.loadFromFile("resources/blast_sound.flac");
    sound.setBuffer(buffer);
    sound.setVolume(30);

    Texture t_wall;
    t_wall.loadFromFile("resources/stone.png");
    Sprite s_wall;
    s_wall.setTexture(t_wall);

    enemies.push_back(new Enemy(getResp()));
    int enemyTimer = 0;
    int Timer = 0;

    Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        enemyTimer += time;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Space)
                {
                    if(tank.shootTimer > 1200)
                    {
                        tank.shootTimer = 0;
                        int X = tank.sprite.getPosition().x;
                        int Y = tank.sprite.getPosition().y;
                        int d = tank.getDirection();
                        switch(d)
                        {
                        case 0:
                            bullets.push_back(new Bullet(X + 50, Y - 7, d)); break;
                        case 1:
                            bullets.push_back(new Bullet(X - 55, Y - 12, d)); break;
                        case 2:
                            bullets.push_back(new Bullet(X - 20, Y + 45, d)); break;
                        case 3:
                            bullets.push_back(new Bullet(X, Y - 60, d)); break;
                        }
                    }
                }
            }
        }

        {//управление игроком клавишами
            if ((Keyboard::isKeyPressed(Keyboard::Left)))
            {
                tank.setDirection(1);tank.setSpeed(0.1);
                tank.sprite.setTextureRect(IntRect(330, 160, -90, -80));
                goto L1;
            }
            if ((Keyboard::isKeyPressed(Keyboard::Right)))
            {
                tank.setDirection(0);tank.setSpeed(0.1);
                tank.sprite.setTextureRect(IntRect(240, 80, 90, 80));
                goto L1;
            }
            if ((Keyboard::isKeyPressed(Keyboard::Up)))
            { 
                tank.setDirection(3);tank.setSpeed(0.1);
                tank.sprite.setTextureRect(IntRect(70, 80, 70, 80));
                goto L1;
            }
            if ((Keyboard::isKeyPressed(Keyboard::Down)))
            {
                tank.setDirection(2);tank.setSpeed(0.1);
                tank.sprite.setTextureRect(IntRect(140, 160, -70, -80));
            }
        }


        L1:
        for(it1 = bullets.begin(); it1 != bullets.end(); it1++)
        {
            if((*it1)->getRect().intersects(tank.getRect()))
            {
                tank.shotDown();
                bullets.remove(*it1);
                continue;
            }
            for(it2 = enemies.begin(); it2 != enemies.end(); it2++)
            {
                if((*it1)->getRect().intersects((*it2)->getRect()))
                {
                    (*it2)->health -= 50;
                    bullets.remove(*it1);
                }
            }
        }
        if(tank.getLives() == -1)
        {
            break;
        }
        window.clear();
        for(int i = 0;i < HEIGHT_MAP; ++i)
        {
            for(int j = 0; j < WIDTH_MAP; ++j)
            {
                if(TileMap[i][j] == '0')
                {
                    s_wall.setPosition(j*32, i*32);
                    window.draw(s_wall);
                }
            }
        }


        tank.update(time);

        if((enemyTimer > 7000 && enemies.size() < 5) || enemies.size() == 0)
        {
            enemies.push_back(new Enemy(getResp()));
            enemyTimer = 0;
        }

        for(it1 = bullets.begin();it1 != bullets.end(); it1++)
        {
            (*it1)->update(time);
            if(!(*it1)->isAlive){bullets.remove((*it1)); continue;}
            window.draw((*it1)->sprite);
        }

        for(it2 = enemies.begin(); it2 != enemies.end(); it2++)
        {
//            int dis = getDistance((*it2), &tank, 40); //effort to do a blast when player and enemy near each other
//            if(dis < 40){(*it2)->isAlive = false; tank.shotDown();}
            if((*it2)->shootTimer > 3000)
            {
                (*it2)->shootTimer = 0;
                int X = (*it2)->sprite.getPosition().x;
                int Y = (*it2)->sprite.getPosition().y;
                int d = (*it2)->getDirection();
                switch(d)
                {
                case 0:
                    bullets.push_back(new Bullet(X + 50, Y - 7, d)); break;
                case 1:
                    bullets.push_back(new Bullet(X - 55, Y - 12, d)); break;
                case 2:
                    bullets.push_back(new Bullet(X - 20, Y + 45, d)); break;
                case 3:
                    bullets.push_back(new Bullet(X, Y - 60, d));
                }
            }

            for(it22 = enemies.begin(); it22 != enemies.end(); it22++)
            {
                if((*it2)->getRect().intersects((*it22)->getRect()))
                {
                    intersect(*it2, *it22);
                }
            }
            if((*it2)->getRect().intersects(tank.getRect()))
            {
                tank.shotDown();goto L2;
            }

            if((*it2)->health <= 0){tank.kill(); goto L2;}
            if(!(*it2)->isAlive)
            {
                L2:
                positions.push_back(new Pos((*it2)->sprite.getPosition()));
                enemies.remove((*it2));
                sound.play();
                continue;
            }
            (*it2)->update(time);
            window.draw((*it2)->sprite);
        }

        for(it3 = positions.begin(); it3 != positions.end(); it3++)
        {
            if((*it3)->timer < 300)
                window.draw((*it3)->blast);
            else
            {
                positions.remove(*it3);
                continue;
            }
            (*it3)->update(time);
        }

        drawHearts(tank, window, heart);
        drawScore(tank, window, text);
        window.draw(tank.sprite);

        window.display();
    }
    music.stop();
    SoundBuffer loseBuffer;
    loseBuffer.loadFromFile("resources/gameOverSound.flac");
    Sound loseSound;
    loseSound.setBuffer(loseBuffer);
    loseSound.play();
    Image i_lose;
    i_lose.loadFromFile("resources/gameOver.png");
    i_lose.createMaskFromColor(Color(247, 247, 247));
    i_lose.createMaskFromColor(Color(255, 255, 255));
    Texture t_lose;
    t_lose.loadFromImage(i_lose);
    Sprite lose;
    lose.setTexture(t_lose);
    lose.setOrigin(270, 200);
    lose.setPosition(window_a/2, window_b/2);
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time/800;
    Timer = 0;
    while (window.isOpen())
    {
        Timer += time;
        window.draw(lose);
        window.display();
        if(Timer > 30000)
            window.close();
    }
    tank.newGame();
    enemies.clear();
    positions.clear();
    bullets.clear();
    return (true + ans) % 2;//because of in menu if we press exit, menu will appear again
}