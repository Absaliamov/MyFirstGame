#include "SFML/map.h"
using namespace sf;

class Tank { // класс Игрока
private:
    float x, y, speed;
    int dir;
    float dx, dy;
    int Score;
    int lives;
public:
    int shootTimer;

    float w, h; //высота ширина

    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт
    Tank(String F, float X, float Y, float W, float H){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
        dx = 0;dy = 0;speed = 0;dir = 0;Score = 0;shootTimer = 0;lives = 3;
        File = F;//имя файла+расширение
        w = W; h = H;//высота и ширина
        image.loadFromFile("resources/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        image.createMaskFromColor(Color(255, 255, 255));//убираем ненужный фон
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата появления спрайта
        sprite.setTextureRect(IntRect(w, h, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
//        sprite.scale(0.5f, 0.5f);
        sprite.setOrigin(w/2, h/2);
    };
    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    {
        shootTimer += time;
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
        case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }

        x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        y += dy*time;//аналогично по игреку

        speed = 0;//зануляем скорость, чтобы персонаж остановился.
        sprite.setPosition(x + w/2,y + h/2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
        interactionWithMap();
    }

    void interactionWithMap()//ф-ция взаимодействия с картой
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
        {//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (dy>0)//если мы шли вниз,
                    {
                        y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;//аналогично идем влево
                    }
                }
            }
        }
    }
    void setSpeed(float sp){speed = sp;}

    void setDirection(int d){dir = d;}

    int getDirection(){return dir;}
    void kill(){Score += 20;}

    FloatRect getRect(){return FloatRect(x, y, w, h);}

    void shotDown(){--lives;}

    int getLives(){return lives;}

    int getScore(){return Score;}
};



int randomInt(int max, int min)
{
//    srand(time(NULL));
    int b = rand();//непонятно почему, но если брать int из первого рандома, то значение близки к друг другу
    int a = rand() % max + min;
    return a;
}

class Enemy {
private:
    int dir;
    int moveTimer;
    float x;
    float y;
    float speed;
    float dx, dy;

public:
    int shootTimer;
    bool isAlive;
    float w, h;
    int health;

    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт

    Enemy(String F,int W, int H)
    {
        isAlive = true;
        speed = 0.05;
        moveTimer = 0;dir = rand() % 4;shootTimer = 0;
        x = randomInt(1280 - 128, 32); y = randomInt(960 - 128, 32);
        dx = 0;dy = 0;
        File = F;//имя файла+расширение
        w = W; h = H; health = 100;
        image.loadFromFile("resources/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        image.createMaskFromColor(Color(255, 255, 255));//убираем ненужный фон
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        sprite.setColor(sf::Color::Red);
        sprite.setTextureRect(IntRect(w, h, w, h));
        sprite.setOrigin(w/2, h/2);
        sprite.setPosition(x,y);
    }
        void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    {
        moveTimer += time;
        shootTimer += time;
        if(moveTimer > 3000) {dir = rand() % 4; moveTimer = 0;}
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
        case 0:
            dx = speed; dy = 0;
            sprite.setTextureRect(IntRect(240, 80, 90, 80));
            sprite.setOrigin(w/2,h/2);
            break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1:
            dx = -speed; dy = 0;
            sprite.setTextureRect(IntRect(330, 160, -90, -80));
            sprite.setOrigin(w/2,h/2);
            break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2:
            dx = 0; dy = speed;
            sprite.setTextureRect(IntRect(140, 160, -70, -80));
            sprite.setOrigin(w/2,h/2);
            break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3:
            dx = 0; dy = -speed;
            sprite.setTextureRect(IntRect(w, h, w, h));
            sprite.setOrigin(w/2, h/2);
            break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }

        x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        y += dy*time;//аналогично по игреку

//        speed = 0;//зануляем скорость, чтобы персонаж остановился.
        sprite.setPosition(x + w/2,y + h/2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
        interactionWithMap();
    }

    void interactionWithMap()//ф-ция взаимодействия с картой
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
        {//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (dy>0)//если мы шли вниз,
                    {
                        y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа
                        dir = 3;
                        moveTimer = 0;
                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                        dir = 2;
                        moveTimer = 0;
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                        dir = 1;
                        moveTimer = 0;
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;//аналогично идем влево
                        dir = 0;
                        moveTimer = 0;
                    }
                }
            }
        }
    }
    FloatRect getRect(){return FloatRect(x, y, w, h);}

    int getDirection(){return dir;}

    void resetMoveTimer(){moveTimer = 0;}

    void turnAround()
    {
        moveTimer = 0;
        switch(dir)
        {
        case 0:
            dir = 1; break;
        case 1:
            dir = 0; break;
        case 2:
            dir = 3; break;
        case 3:
            dir = 2; break;
        }
    }
};


class Bullet {
private:
    float x, y, speed;
    float dx, dy;
    int dir;

public:
    bool isAlive;
    float w, h;

    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт

    Bullet(String F, float X, float Y, float W, float H, int Direction){
        isAlive = true; speed = 0.3;
        dx = 0; dy = 0; File = F;
        x = X; y = Y;
        w = W; h = H; dir =  Direction;
        image.loadFromFile("resources/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(w/2, h/2);
        sprite.setPosition(x,y);
    }

    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    {
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
        case 0:
            dx = speed; dy = 0;
            sprite.setRotation(90);
            break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1:
            dx = -speed; dy = 0;
            sprite.setRotation(-90);
            break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2:
            dx = 0; dy = speed;
            sprite.setRotation(180);
            break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3:
            dx = 0; dy = -speed;
            break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }

        x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        y += dy*time;//аналогично по игреку

        sprite.setPosition(x + w/2,y + h/2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
        interactionWithMap();
    }

    void interactionWithMap()//ф-ция взаимодействия с картой
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
        {//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    isAlive = false;
                    if (dy>0)//если мы шли вниз,
                    {
                        y = i * 32 - h;

                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;//аналогично идем влево
                    }
                }
            }
        }
    }
    FloatRect getRect(){return FloatRect(x, y, w, h);}
};

/*//effort to do a sound and image destroyed o enemy
class Blast
{
private:
    float x; float y;
    float w; float h;
    int timer;

public:
    bool isAlive;
    String imageFile;
    String soundFile;
    Image image;
    Texture texture;
    Sprite sprite;


    Blast(String png, Vector2f position, float W, float H){
        imageFile = png; //soundFile = flac;
        x = position.x; y = position.y;
        w = W; h = H; timer = 0; isAlive = true;
        image.loadFromFile("resources/" + imageFile);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        sprite.setPosition(position);
//        buffer.loadFromFile("resources/" + soundFile);
//        sound.setBuffer(buffer);
    }

    void update(int time)
    {
        timer += time;
    }

    void show(RenderWindow& window)
    {
        if(timer < 1000)
        {
//            sprite.setTextureRect(IntRect(0, 0, w, h));
        window.draw(sprite);
        } else {isAlive = false;}
    }
};
*/