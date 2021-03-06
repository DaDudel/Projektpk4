#include <SFML/Graphics.hpp>
#include"Classes.h"
#include"Menu.h"
#include<vector>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<sstream>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

using namespace std;
using namespace sf;

int main()
{
	srand(time(NULL));
	/////////////////
	Menu gra;
	gra.wczytaj();
	gra.items.push_back(new Gracz(600, 750));
	gra.items.push_back(new Podloga(600, 650));
	Scoreboard scr(600, 400);
	Zycie lif(117.5, 57.5);
	/////////////////

	Start s(300, 600);
	Exit ex(900, 600);

	int ite = 0;
	int hit = 0;


	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Strzelanka");
	window.setFramerateLimit(60);

	Texture lo1;
	lo1.loadFromFile("tlo1.png");
	Sprite tlo1;
	tlo1.setTexture(lo1);

	Texture lo2;
	lo2.loadFromFile("tlo2.png");
	Sprite tlo2;
	tlo2.setTexture(lo2);

	Texture lo3;
	lo3.loadFromFile("tlo3.png");
	Sprite tlo3;
	tlo3.setTexture(lo3);

	Event event;
	window.clear(Color::White);
	window.pollEvent(event);
	int pom1 = 1;
	int pom2 = 1;
	int wyj = 1;
	int wyj2 = 1;
	int pstryk = 1;

	String playerinput;

	gra.hs();

	while (wyj)
	{
		while (pom1)
		{
			window.clear(Color::White);
			window.pollEvent(event);
			window.draw(tlo1);
			window.draw(gra.men);
			

			s.update();
			ex.update();


			if (event.type == Event::Closed)
			{
				wyj = 0;
				window.close();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				pom1 = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				wyj = 0;
				window.close();
				break;
			}
			window.draw(s);
			window.draw(ex);
			window.display();
		}
		pom1 = 1;
		gra.wcz();

		while (wyj && pom2)
		{
			window.clear(Color::White);
			window.pollEvent(event);
			gra.resp();
			gra.strzalS();
			gra.BossB();

			gra.strzal();

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					gra.licz = 0;
				}
			}


			stringstream ss1;
			ss1 << gra.zycie;
			gra.zycko.setString("Lives: " + ss1.str());

			stringstream ss2;
			ss2 << gra.punkty;
			gra.pkt.setString("Points: " + ss2.str());

			if (event.type == Event::Closed)
			{
				wyj = 0;
				window.close();
				break;
			}
			if (gra.zycie <= 0)
			{
				pom2 = 0;
			}
			while (Keyboard::isKeyPressed(Keyboard::Key::Tab))
			{
				window.draw(tlo3);
				window.draw(scr);
				window.draw(gra.t);
				window.draw(gra.t1);
				window.draw(gra.t2);
				window.draw(gra.t3);
				window.display();
				window.clear(Color::White);

			}
			gra.update();
			window.draw(tlo2);
			
			for (auto it : gra.items)
			{
				window.draw(*it);
			}

			for (auto it : gra.enemies)
			{
				window.draw(*it);
			}
			for (auto it : gra.bullets)
			{
				window.draw(*it);
			}

			window.draw(lif);
			window.draw(gra.zycko);
			window.draw(gra.pkt);

			gra.kolizje();
			gra.usun();
			
			window.display();
		}
		pom2 = 1;
		while (wyj && wyj2)
		{
			window.clear(Color::White);
			window.pollEvent(event);
			if (event.type == Event::Closed)
			{
				wyj = 0;
				window.close();
				break;
			}

			if (event.type == Event::TextEntered&&pstryk)
			{
				playerinput += event.text.unicode;
				gra.playertext.setString(playerinput);
				pstryk = 0;
			}

			if (event.type == Event::KeyReleased)
			{
				pstryk = 1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Backspace)&&pstryk)
			{
				if (playerinput.getSize() > 0)
				{
					playerinput.erase(playerinput.getSize() - 1);
					gra.playertext.setString(playerinput);
					pstryk = 0;
				}
			}

			if (event.type == Event::KeyReleased)
			{
				pstryk = 1;
				if (event.key.code == Keyboard::Enter)
				{
					wyj2 = 0;
				}
			}
			stringstream ss3;
			ss3 << gra.punkty;
			gra.kon.setString("Zdobyte punkty: " + ss3.str());
			window.draw(tlo1);
			window.draw(gra.kon);
			window.draw(gra.spa);
			window.draw(gra.kla);
			window.draw(gra.playertext);
			gra.kla.move(3.f, 0.f);
			if (gra.kla.getPosition().x > SCREEN_WIDTH)
			{
				gra.kla.setPosition(-0.5f * SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f);
			}
			window.display();
			
		}
		if (wyj)
		{
			string ps = playerinput;
			ps.pop_back();
			if (ps == "")
			{
				ps = "NoName";
			}
			Score wyn(ps, gra.punkty);
			//cout << wyn.nickname << "   " << wyn.score << endl;
			gra.ldodaj(wyn);
			//gra.wypiszliste();
			gra.lzapisz();
			gra.playertext.setString("");
			playerinput = "";
		}
		wyj2 = 1;
		gra.wyczysc();
	}
	gra.items.clear();
	gra.enemies.clear();
	gra.bullets.clear();
	return 0;
}