#include<vector>
#include "Classes.h"
#include<fstream>
#include<iostream>
#include<iterator>



Gracz::Gracz(float t_x, float t_y)
{
	pt.loadFromFile("40x40/okularki.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({this->graczWidth, this->graczHeight});
	shape.setOrigin(graczWidth / 2.f, graczHeight / 2.0f);
}

void Gracz::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Gracz::update()
{
	this->shape.move(this->velocity);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
	{
		velocity.x = -graczVelocity;
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 1200)
		{
			velocity.x = graczVelocity;
		}
		else
		{
			velocity.x = 0;
		}
	}
}

float Obiekt::left()
{
	return this->shape.getPosition().x - (this->shape.getSize().x / 2.f);
}

float Obiekt::right()
{
	return this->shape.getPosition().x + (this->shape.getSize().x / 2.f);
}

float Obiekt::top()
{
	return this->shape.getPosition().y - (this->shape.getSize().y / 2.f);
}

float Obiekt::bottom()
{
	return this->shape.getPosition().y + (this->shape.getSize().y / 2.f);
}

Zwykly::Zwykly(float t_x, float t_y)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->zwyklyWidth, this->zwyklyHeight });
	try
	{
		if (!pt.loadFromFile("40x40/10.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Red);
	}
	//pt.loadFromFile("40x40/10.png");
	shape.setTexture(&pt);
	shape.setOrigin(zwyklyWidth / 2.f, zwyklyHeight / 2.0f);
}

void Zwykly::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Zwykly::update()
{
	this->shape.move(this->velocity);
	velocity.x = 0;
	velocity.y = zwyklyVelocity;
}

void Zwykly::spawn()
{
	if (this->c % 180 == 0)
	{

	}
	else
	{
		this->c++;
		return;
	}
}

Vector2f Obiekt::getPosition()
{
	return shape.getPosition();
}

bool Blok::isDestroyed()
{
	return this->destroyed;
}

void Blok::destroy()
{
	//cout << "destroy" << endl;
	this->destroyed = true;
}

Vector2f Obiekt::getsize()
{
	return shape.getSize();
}

Mirror::Mirror(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/13.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Green);
	}
	//pt.loadFromFile("40x40/13.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->mirrorWidth, this->mirrorHeight });
	//shape.setFillColor(Color::Magenta);
	shape.setOrigin(mirrorWidth / 2.f, mirrorHeight / 2.0f);
}

void Mirror::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Mirror::update()
{
	this->shape.move(this->velocity);
	velocity.y = mirrorVelocity / 6;
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->right() < 1200)
	{
		velocity.x = mirrorVelocity;
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->left() > 0)
		{
			velocity.x = -mirrorVelocity;
		}
		else
		{
			velocity.x = 0;
		}
	}
}

Boss::Boss(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("boss.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Black);
	}
	//pt.loadFromFile("boss.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->bossWidth, this->bossHeight });
	//shape.setFillColor(Color::Red);
	shape.setOrigin(bossWidth / 2.f, bossHeight / 2.0f);
}

void Boss::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Boss::update()
{
	this->shape.move(this->velocity);
	velocity.y = bossVelocity / 12;

	if (this->left() < 1)
	{
		velocity.x = bossVelocity;
	}
	else
	{
		if (this->right() > 1199)
		{
			velocity.x = -bossVelocity;
		}
	}
}

Slow::Slow(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/3.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Blue);
	}
	//pt.loadFromFile("40x40/3.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->slowWidth, this->slowHeight });
	shape.setOrigin(slowWidth / 2.f, slowHeight / 2.0f);
}

void Slow::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Slow::update()
{
	this->shape.move(this->velocity);
	velocity.y = slowVelocity/3;
	int r = rand() % 601 + 1;


	if (r % 60 == 0)
	{
		velocity.x = -velocity.x;
	}
	if (this->left() < 1)
	{
		velocity.x = slowVelocity/2;
	}
	else
	{
		if (this->right() > 1199)
		{
			velocity.x = -velocity.x;
		}
	}

	
}

Speed::Speed(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/5.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("40x40/5.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->speedWidth, this->speedHeight });
	shape.setOrigin(speedWidth / 2.f, speedHeight / 2.0f);
}

void Speed::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Speed::update()
{
	this->shape.move(this->velocity);
	velocity.x = speedVelocity;
	velocity.y = -speedVelocity / 5.0;
	if (this->getPosition().x > 1200)
	{
		this->destroy();
	}
}

Dmg::Dmg(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/6.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("40x40/6.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->dmgWidth, this->dmgHeight });
	//shape.setFillColor(Color::Yellow);
	shape.setOrigin(dmgWidth / 2.f, dmgHeight / 2.0f);
}

void Dmg::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Dmg::update()
{
	this->shape.move(this->velocity);
	velocity.x = -dmgVelocity;
	velocity.y = -dmgVelocity / 5.0;
	if (this->getPosition().x < 0)
	{
		this->destroy();
	}
}

Pocisk::Pocisk(float t_x, float t_y)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pW, this->pH });
	shape.setFillColor(Color::Black);
	shape.setOrigin(pW / 2.0, pH / 2.0);
}

void Pocisk::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Pocisk::update()
{
	this->shape.move(this->velocity);
	velocity.x = 0;
	velocity.y = -pV;
	if (this->getPosition().y < 0)
	{
		this->destroy();
	}
}

void Pocisk::destroy()
{
	this->destroyed = true;
}

Podloga::Podloga(float t_x, float t_y)
{

	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pWidth, this->pHeight });
	shape.setOrigin(pWidth / 2.f, pHeight / 2.0f);
	shape.setFillColor(Color::Red);
}

void Podloga::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Podloga::update()
{
}

bool Bonus::isDestroyed()
{
	return this->destroyed;
}

void Bonus::destroy()
{
	this->destroyed = true;
}

PociskS::PociskS(float t_x, float t_y)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pW, this->pH });
	shape.setFillColor(Color::Blue);
	shape.setOrigin(pW / 2.f, pH / 2.0f);
}

void PociskS::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void PociskS::update()
{
	this->shape.move(this->velocity);
	velocity.x = 0;
	velocity.y = pV;
	if (this->getPosition().y > 800)
	{
		this->destroy();
	}
}

void PociskS::destroy()
{
	this->destroyed = true;
}

Exit::Exit(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("exit.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::White);
	}
	//pt.loadFromFile("exit.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pWidth, this->pHeight });
	shape.setOrigin(pWidth / 2.f, pHeight / 2.0f);
}

void Exit::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Exit::update()
{
}

Start::Start(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("start.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::White);
	}
	//pt.loadFromFile("start.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pWidth, this->pHeight });
	shape.setOrigin(pWidth / 2.f, pHeight / 2.0f);
}

void Start::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Start::update()
{
}

Linia::Linia(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/7.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("40x40/7.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->lWidth, this->lHeight });
	shape.setOrigin(lWidth / 2.f, lHeight / 2.0f);
}

void Linia::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Linia::update()
{
	this->shape.move(this->velocity);
	velocity.x = -lVelocity;
	velocity.y = 0.0;
	if (this->getPosition().x < 0)
	{
		this->destroy();
	}
}

Doub::Doub(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/8.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("40x40/8.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->dWidth, this->dHeight });
	shape.setOrigin(dWidth / 2.f, dHeight / 2.0f);
}

void Doub::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Doub::update()
{
	this->shape.move(this->velocity);
	if (this->left() < 0)
	{
		velocity.x = dVelocity;
	}
	else
	{
		if (this->right() > 1199)
		{
			velocity.x = -dVelocity;
		}
	}
	velocity.y = 0.0;
	if (this->left() <= 0)
	{
		this->destroy();
	}
}

Life::Life(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("40x40/5.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("40x40/5.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->lWidth, this->lHeight });
	shape.setOrigin(lWidth / 2.f, lHeight / 2.0f);
}

void Life::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Life::update()
{
	this->shape.move(this->velocity);
	velocity.x = 0;
	velocity.y = -lVelocity;
	if (this->top() <= 0)
	{
		this->destroy();
	}
}

Score::Score()
{
}

Score::Score(string s, int pkt)
{
	this->nickname = s;
	this->score = pkt;
}

void Score::wypisz()
{
	cout << nickname << "   " << score << endl;
}

Scoreboard::Scoreboard(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("tabelka.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::Yellow);
	}
	//pt.loadFromFile("tabelka.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pWidth, this->pHeight });
	shape.setOrigin(pWidth / 2.f, pHeight / 2.0f);
}

void Scoreboard::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Scoreboard::update()
{
}

Zycie::Zycie(float t_x, float t_y)
{
	try
	{
		if (!pt.loadFromFile("zycie.png"))
		{
			throw invalid_argument("blad wczytywania tekstury");
		}
	}
	catch (const std::invalid_argument& e)
	{
		shape.setFillColor(Color::White);
	}
	//pt.loadFromFile("zycie.png");
	shape.setTexture(&pt);
	shape.setPosition(t_x, t_y);
	shape.setSize({ this->pWidth, this->pHeight });
	shape.setOrigin(pWidth / 2.f, pHeight / 2.0f);
}

void Zycie::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

void Zycie::update()
{
}
