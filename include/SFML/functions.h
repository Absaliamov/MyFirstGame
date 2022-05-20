
void drawScore(const Tank& tank, RenderWindow& window, Text& text)
{
    std::ostringstream score;
    score << tank.getScore();
    text.setString("Score:" + score.str());
    text.setPosition(1100, -10);
    window.draw(text);
}

void drawHearts(const Tank& tank, RenderWindow& window, Sprite& heart)
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

RectangleShape getRect(const Vector2f& position)
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
    p.x = rand() % (1280 - 192) + 32;
    p.y =  rand() % (960 - 192) + 32;

    return p;
}

void viceToPlayer(Enemy* enemy, Tank* tank)
{
    Vector2f e = enemy->sprite.getPosition();
    Vector2f t = tank->sprite.getPosition();
    if(abs(e.y - t.y) < 35)
    {
        switch(enemy->getDirection())
        {
            case 0:
                if(e.x > t.x)
                {
                    enemy->setDirection(1);
                }
                return;
            case 1:
                if(e.x < t.x)
                {
                    enemy->setDirection(0);
                }
                return;
            case 2:
            case 3:
                if(e.x < t.x)
                {
                    enemy->setDirection(0);
                }
                enemy->setDirection(1);
                return;
        }
    }
    if(abs(e.x - t.x) < 35)
    {
        switch(enemy->getDirection())
        {
            case 0:
            case 1:
                if(e.y < t.y)
                {
                    enemy->setDirection(2);
                }
                enemy->setDirection(3);
                return;
            case 2:
                if(e.y > t.y)
                {
                    enemy->setDirection(2);
                }
                return;
            case 3:
                if(e.y < t.y)
                {
                    enemy->setDirection(2);
                }
                return;
        }
    }
}

