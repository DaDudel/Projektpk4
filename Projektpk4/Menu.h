#pragma once
#include<vector>
#include<list>
#include<string>
#include<SFML\Graphics.hpp>
#include"Classes.h"

using namespace std;
using namespace sf;

class Menu
{
public:
	vector<Obiekt*>enemies;
	vector<Obiekt*>items;
	vector<Obiekt*>bullets;
	list<Score>lista;
	int zycie{ 3 };
	int punkty{ 0 };
	int dmg = 1;
	int licz = 0;
	bool czyb = false;
	bool czyd = false;
	Font f;
	Text t;
	Text t1;
	Text t2;
	Text t3;
	Text kon;
	Text spa;
	Text pkt;
	Text zycko;
	Text men;
	Text kla;
	Text playertext;
	void resp();
	void update();
	//void dodaj(Score el);
	void wczytaj();
	void wypiszliste();
	//strzelanie gracza
	void strzal();
	//strzelanie przeciwnikow
	void strzalS();
	//zachowanie bossa
	void BossB();
	//sprawdzanie kolizji
	bool ct(Zwykly* A, Podloga* B);
	bool ct(Boss* A, Podloga* B);
	bool ct(Slow* A, Podloga* B);
	bool ct(Mirror* A, Podloga* B);
	bool ct(Zwykly* A, Pocisk* B);
	bool ct(Boss* A, Pocisk* B);
	bool ct(Slow* A, Pocisk* B);
	bool ct(Mirror* A, Pocisk* B);
	bool ct(PociskS* A, Gracz* B);
	bool ct(Speed* A, Pocisk* B);
	bool ct(Dmg* A, Pocisk* B);
	bool ct(Linia* A, Pocisk* B);
	bool ct(Doub* A, Pocisk* B);
	bool ct(Life* A, Pocisk* B);
	//wczytanie tekstow
	void hs();
	void wyczysc();
	//usuwanie obiektow po kolizji
	void kolizje();
	void usun();
	void ldodaj(Score wyn);
	void lzapisz();
	void wcz();
};