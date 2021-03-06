#include<vector>
#include "Menu.h"
#include "Classes.h"
#include<fstream>
#include<iostream>
#include<iterator>
#include<sstream>
void Menu::resp()
{
	int los;
	
	los = rand() % 180;
	if (los % 179 == 0 && czyb == false)
	{
		enemies.push_back(new Zwykly(rand() % 1200, 0));
		//cout << "Dodano zwyklego" << endl;
	}

	los = rand() % 420;
	if (los % 419 == 0 && czyb == false)
	{
		enemies.push_back(new Mirror(rand() % 1200, 0));
		//cout << "Dodano mirror" << endl;
	}

	los = rand() % 420;
	if (los % 419 == 0 && czyb == false)
	{
		enemies.push_back(new Slow(rand() % 1200, 0));
		//cout << "Dodano slow" << endl;
	}

	if ((punkty > 0 && ((punkty % 100 == 0 || punkty % 101 == 0) || (punkty % 102 == 0 || punkty % 103 == 0))) && czyb == false)
	{
		enemies.push_back(new Boss(rand() % 1200, 0));
		//cout << "Dodano boss" << endl;
		czyb = true;
	}

	los = rand() % 3000;
	if (los % 2999 == 0 && czyb == false)
	{
		enemies.push_back(new Speed(0, 200));
		//cout << "Dodano B Speed" << endl;
	}

	los = rand() % 3000;
	if (los % 2999 == 0 && dmg == 1 && czyb == false)
	{
		enemies.push_back(new Dmg(1200, 200));
		//cout << "Dodano B Dmg" << endl;
	}

	los = rand() % 3000;
	if (los % 2999 == 0 && dmg == 1 && czyb == false && dynamic_cast<Podloga*>(items[1])->getPosition().y < 700)
	{
		enemies.push_back(new Linia(1200, rand() % 401));
		//cout << "Dodano B Linia" << endl;
	}

	los = rand() % 3000;
	if (los % 2999 == 0 && dmg == 1 && czyb == false && czyd == false)
	{
		enemies.push_back(new Doub(20, 100));
		//cout << "Dodano B Doub" << endl;
	}

	los = rand() % 1200;
	if (los % 1199 == 0 && zycie < 3 && czyb==false)
	{
		enemies.push_back(new Life(rand() % 1200, (rand() % 200) + 400));
		//cout << "Dodano B Life" << endl;
	}

}

void Menu::update()
{
	for (auto a : items)
	{
		a->update();
	}
	for (auto e : enemies)
	{
		e->update();
	}
	for (auto b : bullets)
	{
		b->update();
	}
}

void Menu::wczytaj()
{
	string s = "";
	int pkt = 0;
	Score wynik;
	ifstream plo;
	plo.open("save.txt");
	if (plo.good())
	{
		while (plo.good())
		{
			getline(plo, s);
			plo >> pkt;
			plo.ignore();
			wynik.nickname = s;
			wynik.score = pkt;
			if (!(wynik.nickname==""))
				lista.push_back(wynik);
		}
	}
	plo.close();
}

void Menu::wypiszliste()
{
	for (Score i : lista)
	{
		cout << i.nickname << " " << i.score << endl;
	}
}

void Menu::strzal()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		if (licz % 15 == 0)
		{
			if (!czyd)
			{
				bullets.push_back(new Pocisk(dynamic_cast<Gracz*>(items[0])->shape.getPosition().x - 15, 720));
			}
			else
			{
				bullets.push_back(new Pocisk(dynamic_cast<Gracz*>(items[0])->left() - 15, 720));
				bullets.push_back(new Pocisk(dynamic_cast<Gracz*>(items[0])->right() - 15, 720));
			}
		}
		licz++;
	}
}

void Menu::strzalS()
{
	int r = 0;
	for (auto a : enemies)
	{
		if (typeid(*a) == typeid(Slow))
		{
			int r = rand() % 241;
			if (r % 240 == 0)
			{
				bullets.push_back(new PociskS(dynamic_cast<Slow*>(a)->shape.getPosition().x - 15, dynamic_cast<Slow*>(a)->shape.getPosition().y + 25));
			}
		}
	}
}

void Menu::BossB()
{
	int r = 0;
	vector <Obiekt*>::iterator iter = enemies.begin();
	vector <Obiekt*>::iterator iter2 = enemies.begin();
	bool bul = false;
	for (iter; iter != enemies.end(); iter++)
	{
		auto a = *iter;

		if (typeid(*a) == typeid(Boss))
		{
			r = rand() % 181;
			if (r % 180 == 0)
			{
				bullets.push_back(new PociskS(dynamic_cast<Boss*>(a)->shape.getPosition().x, dynamic_cast<Boss*>(a)->shape.getPosition().y + 105));
				bullets.push_back(new PociskS(dynamic_cast<Boss*>(a)->left(), dynamic_cast<Boss*>(a)->shape.getPosition().y + 105));
				bullets.push_back(new PociskS(dynamic_cast<Boss*>(a)->right(), dynamic_cast<Boss*>(a)->shape.getPosition().y + 105));
			}
			r = rand() % 421;
			if (r % 420 == 0)
			{
				iter2 = iter;
				bul = true;
			}
		}
	}
	if (bul)
	{
		auto a = *iter2;
		enemies.push_back(new Zwykly(dynamic_cast<Boss*>(a)->shape.getPosition().x, dynamic_cast<Boss*>(a)->shape.getPosition().y));
		enemies.push_back(new Zwykly(dynamic_cast<Boss*>(a)->left(), dynamic_cast<Boss*>(a)->shape.getPosition().y));
		enemies.push_back(new Zwykly(dynamic_cast<Boss*>(a)->right(), dynamic_cast<Boss*>(a)->shape.getPosition().y));
		iter2 = enemies.begin();
		//cout << "POMOCNIK" << endl;
	}
}

bool Menu::ct(Zwykly* A, Podloga* B)
{
	if (!(A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()))
	{
		return false;
	}

	A->destroy();
}

bool Menu::ct(Boss* A, Podloga* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
}

bool Menu::ct(Slow* A, Podloga* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
}

bool Menu::ct(Mirror* A, Podloga* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
}

bool Menu::ct(Zwykly* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	punkty++;
}

bool Menu::ct(Boss* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	B->destroy();
	A->hp = A->hp - dmg;
	if (A->hp <= 0)
	{
		A->destroy();
		punkty = punkty + 10;
		czyb = false;
	}
}

bool Menu::ct(Slow* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	B->destroy();
	A->hp = A->hp - dmg;
	if (A->hp <= 0)
	{
		A->destroy();
		punkty = punkty + 2;
	}
}

bool Menu::ct(Mirror* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}


	B->destroy();
	A->hp = A->hp - dmg;
	if (A->hp <= 0)
	{
		A->destroy();
		punkty = punkty + 4;
	}
}

bool Menu::ct(PociskS* A, Gracz* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->graczVelocity = (B->graczVelocity) * 0.9;
	//cout << "SPEED " << B->graczVelocity << endl;
}

bool Menu::ct(Speed* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	dynamic_cast<Gracz*>(items[0])->graczVelocity = (dynamic_cast<Gracz*>(items[0])->graczVelocity) * 1.1;
}

bool Menu::ct(Dmg* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	dmg = 2;
}

bool Menu::ct(Linia* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	if (dynamic_cast<Podloga*>(items[1])->getPosition().y < 700)
	{
		vector <Obiekt*>::iterator p = items.begin();
		p++;
		int h = dynamic_cast<Podloga*>(items[1])->getPosition().y;
		items.erase(p);
		items.push_back(new Podloga(600, h + 10));
	}
}

bool Menu::ct(Doub* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	czyd = true;
}

bool Menu::ct(Life* A, Pocisk* B)
{
	if ((A->right() >= B->left() && A->left() <= B->right() && A->bottom() >= B->top() && A->top() <= B->bottom()) == false)
	{
		return false;
	}

	A->destroy();
	B->destroy();
	zycie++;
}

void Menu::hs()
{
	f.loadFromFile("comic.ttf");
	t.setString("Top 3 najlepsze wyniki:");
	t1.setString("");
	t2.setString("");
	t3.setString("");
	kon.setString("");
	t.setFont(f);
	t1.setFont(f);
	t2.setFont(f);
	t3.setFont(f);
	kon.setFont(f);
	
	t.setFillColor(Color::Black);
	t1.setFillColor(Color::Black);
	t2.setFillColor(Color::Black);
	t3.setFillColor(Color::Black);
	kon.setFillColor(Color::Black);
	t.setCharacterSize(32);
	t1.setCharacterSize(32);
	t2.setCharacterSize(32);
	t3.setCharacterSize(32);
	kon.setCharacterSize(32);
	t.setPosition({ 400, 200 });
	t1.setPosition({ 400,300 });
	t2.setPosition({ 400,400 });
	t3.setPosition({ 400,500 });
	kon.setPosition({ 430,300 });

	spa.setFont(f);
	spa.setCharacterSize(24);
	spa.setFillColor(Color::Black);
	spa.setString("Podaj swoj pseudonim:");
	spa.setPosition(Vector2f(1200 / 2.0f - 150.0, 800 / 3.0f * 2.f - 50.f));

	pkt.setFont(f);
	pkt.setCharacterSize(32);
	pkt.setFillColor(Color::Black);
	pkt.setPosition(Vector2f(10.0, 50));

	zycko.setFont(f);
	zycko.setCharacterSize(32);
	zycko.setFillColor(Color::Black);
	zycko.setPosition(Vector2f(10.0, 10.0));

	men.setFont(f);
	men.setCharacterSize(48);
	men.setFillColor(Color::Red);
	men.setStyle(Text::Bold);
	men.setString("GRA - STRZELANKA");
	FloatRect textRect = men.getLocalBounds();
	men.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	men.setPosition(Vector2f(1200 / 2.0f, 800 / 3.0f));

	kla.setFont(f);
	kla.setCharacterSize(48);
	kla.setFillColor(Color::Red);
	kla.setString("GAME OVER");
	kla.setPosition(-0.5 * 1200 / 2.0f, 800 / 4.0f);

	playertext.setFont(f);
	playertext.setCharacterSize(24);
	playertext.setFillColor(Color::Black);
	playertext.setPosition(Vector2f(1200 / 2.0f - 150.0, 800 / 3.0f * 2.0f));
}

void Menu::wyczysc()
{
	czyb = false;
	czyd = false;
	dmg = 1;
	zycie = 3;
	punkty = 0;
	items.clear();
	enemies.clear();
	bullets.clear();
	items.push_back(new Gracz(600, 750));
	items.push_back(new Podloga(600, 650));
}

void Menu::kolizje()
{
	int hit = 0;
	for (auto a : enemies)
	{

		if (typeid(*a) == typeid(Zwykly))
		{
			if (ct(dynamic_cast<Zwykly*>(a), dynamic_cast<Podloga*>(items[1])))
			{
				zycie--;
				break;
			}
		}

		if (typeid(*a) == typeid(Mirror))
		{
			if (ct(dynamic_cast<Mirror*>(a), dynamic_cast<Podloga*>(items[1])))
			{
				zycie--;
				break;
			}
		}

		if (typeid(*a) == typeid(Slow))
		{
			if (ct(dynamic_cast<Slow*>(a), dynamic_cast<Podloga*>(items[1])))
			{
				zycie--;
				break;
			}
		}

		if (typeid(*a) == typeid(Boss))
		{
			if (ct(dynamic_cast<Boss*>(a), dynamic_cast<Podloga*>(items[1])))
			{
				zycie--;
				break;
			}
		}



		hit = 0;

		for (auto b : bullets)
		{
			if (typeid(*a) == typeid(Zwykly) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Zwykly*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Slow) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Slow*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Mirror) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Mirror*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Boss) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Boss*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Speed) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Speed*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Dmg) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Dmg*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Linia) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Linia*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Doub) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Doub*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}
			if (typeid(*a) == typeid(Life) && typeid(*b) == typeid(Pocisk))
			{
				if (ct(dynamic_cast<Life*>(a), dynamic_cast<Pocisk*>(b)))
				{
					hit++;
					break;
				}
			}

		}

		if (hit)
		{
			break;
		}

	}
	for (auto b : bullets)
	{
		if (hit)
		{
			break;
		}
		if (typeid(*b) == typeid(PociskS))
		{
			if (ct(dynamic_cast<PociskS*>(b), dynamic_cast<Gracz*>(items[0])))
			{
				break;
			}
		}
	}
}

void Menu::usun()
{
	vector <Obiekt*>::iterator it = enemies.begin();

	for (auto a : enemies)
	{

		if (typeid(*a) == typeid(Zwykly))
		{
			if (dynamic_cast<Zwykly*>(a)->destroyed == true)
			{
				enemies.erase(it);
				break;
			}
		}


		if (typeid(*a) == typeid(Boss))
		{
			if (dynamic_cast<Boss*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}


		if (typeid(*a) == typeid(Mirror))
		{
			if (dynamic_cast<Mirror*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}


		if (typeid(*a) == typeid(Slow))
		{
			if (dynamic_cast<Slow*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}

		if (typeid(*a) == typeid(Speed))
		{
			if (dynamic_cast<Speed*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}
		if (typeid(*a) == typeid(Dmg))
		{
			if (dynamic_cast<Dmg*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}
		if (typeid(*a) == typeid(Linia))
		{
			if (dynamic_cast<Linia*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}
		if (typeid(*a) == typeid(Doub))
		{
			if (dynamic_cast<Doub*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}
		if (typeid(*a) == typeid(Life))
		{
			if (dynamic_cast<Life*>(a)->destroyed)
			{
				enemies.erase(it);
				break;
			}
		}
		it++;
	}

	vector <Obiekt*>::iterator bul = bullets.begin();

	for (auto b : bullets)
	{
		if (typeid(*b) == typeid(Pocisk))
		{
			if (dynamic_cast<Pocisk*>(b)->destroyed)
			{
				bullets.erase(bul);
				break;
			}
		}
		if (typeid(*b) == typeid(PociskS))
		{
			{
				if (dynamic_cast<PociskS*>(b)->destroyed)
				{
					bullets.erase(bul);
					break;
				}
			}
		}
		if (bul != bullets.end())
		{
			bul++;
		}
	}
}

void Menu::ldodaj(Score wyn)
{
	list<Score>::iterator it1 = lista.begin();
	list<Score>::iterator it2 = it1;
	bool czyb = false;
	
	for (it1; it1 != lista.end(); it1++)
	{
		if (it1->nickname == wyn.nickname)
		{
			if (it1->score < wyn.score)
			{
				it1->score = wyn.score;
			}
			czyb = true;
		}
	}

	if (!czyb)
	{
		lista.push_back(wyn);
	}

	it1 = lista.begin();
	
	for (it1; it1 != lista.end(); it1++)
	{
		for (it2=it1; it2 != lista.end(); it2++)
		{
			if (it1->score < it2->score)
			{
				swap(*it1, *it2);
			}
		}
	}
	if(lista.size()>3)
		lista.pop_back();
	
}

void Menu::lzapisz()
{
	list<Score>::iterator it = lista.begin();
	ofstream plz;
	plz.open("save.txt");
	for (it; it != lista.end(); it++)
	{
		plz << it->nickname << endl;
		plz << it->score<<endl;
	}
	plz.close();
}

void Menu::wcz()
{
	stringstream s1;
	int sc;
	string nick;
	list<Score>::iterator it1 = lista.begin();
	if (it1!=lista.end())
	{
		sc = it1->score;
		nick = it1->nickname;
		t1.setString(nick + ": " + to_string(sc));
		it1++;
	}


	if (it1 != lista.end())
	{
		sc = it1->score;
		nick = it1->nickname;
		t2.setString(nick + ": " + to_string(sc));
		it1++;
	}


	if (it1 != lista.end())
	{
		sc = it1->score;
		nick = it1->nickname;
		t3.setString(nick + ": " + to_string(sc));
	}
}
