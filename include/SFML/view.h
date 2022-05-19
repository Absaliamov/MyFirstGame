//#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;

void getPlayerCoordinateForView(float x,float y)
{ //функция для считывания координат игрока
    view.setCenter(x + 100, y); //следим за игроком, передавая его координаты камере. +100 - сместили камеру по иксу вправо. эксперементируйте
}

void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        view.move(0.1*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        view.move(0, 0.1*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
    }

    if (Keyboard::isKeyPressed(Keyboard::A)) {
        view.move(-0.1*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        view.move(0, -0.1*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }
}