
void drawScore(Tank& tank, RenderWindow& window, Text& text)
{
    std::ostringstream score;
    score << tank.getScore();
    text.setString("Score:" + score.str());
    text.setPosition(1100, -10);
    window.draw(text);
}

void drawHearts(Tank& tank, RenderWindow& window, Sprite& heart)
{
    for(int i = 0; i <= tank.getLives(); i++)
    {
        heart.setOrigin(heart.getTextureRect().width/2,heart.getTextureRect().height/2);
        heart.setPosition(2 * heart.getTextureRect().width * (i+1), 16);
        window.draw(heart);
    }
}


void intersect(Enemy* a, Enemy* b)
{
    switch(a->getDirection())
    {
        case 0:
            switch(b->getDirection())
            {
                case 1:
                    a->turnAround(); b->turnAround();
                    return;
                case 2:
                case 3:
                    if(a->sprite.getPosition().x < b->sprite.getPosition().x)
                    {
                        a->turnAround();
                    } else
                        b->turnAround();
            }
            return;
        case 1:
            switch(b->getDirection())
            {
                case 0:
                    a->turnAround(); b->turnAround(); return;
                case 2:
                case 3:
                    if(a->sprite.getPosition().x > b->sprite.getPosition().x)
                    {
                        a->turnAround();
                    } else
                        b->turnAround();
            }
            return;
        case 2:
            switch(b->getDirection())
            {
                case 0:
                case 1:
                    if(a->sprite.getPosition().y < b->sprite.getPosition().y)
                    {
                        a->turnAround();
                    } else
                        b->turnAround();
                    return;
                case 3:
                a->turnAround(); b->turnAround(); return;
            }
        case 3:
            switch(b->getDirection())
            {
                case 0:
                case 1:
                    if(a->sprite.getPosition().y > b->sprite.getPosition().y)
                    {
                        a->turnAround();
                    } else
                        b->turnAround();
                    return;
                case 2:
                    a->turnAround(); b->turnAround();
            }
    }
}


inline RectangleShape getRect(Vector2f position)
{
    RectangleShape a;
    a.setSize(Vector2f(400, 100));
    a.setPosition(position);
    return a;
}

Vector2f getResp() //function for get position to appear new enemy
{
    Vector2f p;
    p.y = rand();//непонятно почему, но если брать int из первого рандома, то значение близки к друг другу
    p.x = rand() % (1280 - 128) + 32;
    p.y =  rand() % (960 - 128) + 32;

    return p;
}