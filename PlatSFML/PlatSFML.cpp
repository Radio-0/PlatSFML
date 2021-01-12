// PlatSFML.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <SFML/Graphics.hpp>

using namespace sf;
int ground = 700;
class PLAYER {
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(0,0, 122, 135);
		dx = dy = 0;
		currentFrame = 0;
	}
	void update(float time)
	{
		rect.left += dx * time;
		if (!onGround) dy = dy + 0.005*time;
		rect.top += dy * time;
		onGround = false;
		if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true; }

		currentFrame += 0.005*time;	//скорость анимации
		if (currentFrame > 12)currentFrame -= 12;
		if (dx<0) sprite.setTextureRect(IntRect(98.4*int(currentFrame), 0, 98.4,106));
		if (dx>0) sprite.setTextureRect(IntRect(98.4*int(currentFrame), 0, 98.4, 106));
		sprite.setPosition(rect.left, rect.top);
		dx = 0;
	}
};

int main()
{
	RenderWindow window(VideoMode(1000, 1000), "BMO2");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);
	Texture t;
	t.loadFromFile("BMO2.png");	//загрузка картинки из файла
	float currentFrame = 0;
	PLAYER p(t);
	Clock clock;	//фиксация времени

	while (window.isOpen())
	{
		//Учет производительности процессора
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//Работа с клавиатурой
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -1; p.onGround = false; }
		}
		p.update(time);

		window.clear(Color::White);
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}