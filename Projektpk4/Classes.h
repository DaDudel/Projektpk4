#pragma once
#include<vector>
#include<list>
#include<string>
#include<SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Obiekt:public::sf::Drawable
{
public:
	virtual void update()=0;
	Texture pt;
	RectangleShape shape;
	float left();
	float right();
	float top();
	float bottom();
	Vector2f getPosition();
	Vector2f getsize();
};

class Ruch :public Obiekt
{

};

class Nieruch : public Obiekt
{

};

class Blok :public Ruch
{
public:
	bool destroyed=false;
	bool isDestroyed();
	void destroy();
};

class Zwykly :public Blok
{
public:
	int c = 0;
	Zwykly(float t_x, float t_y);
	Zwykly() = delete;
	~Zwykly() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();
	void spawn();
	

	const float zwyklyWidth{ 40.0f };
	const float zwyklyHeight{ 40.0f };
	const float zwyklyVelocity{ 0.8f };
	Vector2f velocity{ zwyklyVelocity, 0.f };

	
};

class Boss :public Blok
{
public:
	Boss(float t_x, float t_y);
	Boss() = delete;
	~Boss() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float bossWidth{ 200.0f };
	const float bossHeight{ 200.0f };
	const float bossVelocity{ 0.7f };
	Vector2f velocity{ bossVelocity, 0.f };

	int hp = 80;
};

class Mirror :public Blok
{
public:
	Mirror(float t_x, float t_y);
	Mirror() = delete;
	~Mirror() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float mirrorWidth{ 40.0f };
	const float mirrorHeight{ 40.0f };
	const float mirrorVelocity{ 1.5f };
	Vector2f velocity{ mirrorVelocity, 0.f };

	int hp = 4;
};

class Slow :public Blok
{
public:
	Slow(float t_x, float t_y);
	Slow() = delete;
	~Slow() = default;
	void draw(RenderTarget& target, RenderStates state) const override;
	void update();

	const float slowWidth{ 40.0f };
	const float slowHeight{ 40.0f };
	const float slowVelocity{ 2.0f };
	Vector2f velocity{ slowVelocity, 0.f };

	int hp = 2;
};

class Gracz : public Ruch
{
public:
	Gracz(float t_x, float t_y);
	Gracz() = delete;
	~Gracz() = default;
	void draw(RenderTarget& target, RenderStates state) const override;
	void update();

	const float graczWidth{ 40.0f };
	const float graczHeight{ 40.0f };
	float graczVelocity{ 11.0f };
	Vector2f velocity{ graczVelocity, 0.f };
};

class Pocisk :public Ruch
{
public:
	Pocisk(float t_x, float t_y);
	Pocisk() = delete;
	~Pocisk() = default;
	void draw(RenderTarget& target, RenderStates state) const override;
	void update();

	float pW{ 10.0f };
	float pH{ 10.0f };
	float pV{ 15.0f };
	Vector2f velocity{ pV, 0.f };
	//Vector2f getPosition();
	bool destroyed = false;
	//bool isDestroyed();
	void destroy();
};

class PociskS :public Ruch
{
public:
	PociskS(float t_x, float t_y);
	PociskS() = delete;
	~PociskS() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	float pW{ 10.0f };
	float pH{ 10.0f };
	float pV{ 5.0f };
	Vector2f velocity{ pV, 0.f };
	//Vector2f getPosition();

	bool destroyed = false;
	void destroy();
};

class Bonus :public Ruch
{
public:
	bool destroyed{ false };
	bool isDestroyed();
	void destroy();
};

class Speed : public Bonus
{
public:
	Speed(float t_x, float t_y);
	Speed() = delete;
	~Speed() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float speedWidth{ 40.0f };
	const float speedHeight{ 40.0f };
	float speedVelocity{ 3.0f };
	Vector2f velocity{ speedVelocity, 0.f };
};

class Dmg :public Bonus
{
public:
	Dmg(float t_x, float t_y);
	Dmg() = delete;
	~Dmg() = default;
	void draw(RenderTarget& target, RenderStates state) const override;
	void update();

	const float dmgWidth{ 40.0f };
	const float dmgHeight{ 40.0f };
	float dmgVelocity{ 4.0f };
	Vector2f velocity{ dmgVelocity, 0.f };
};

class Linia :public Bonus
{
public:
	Linia(float t_x, float t_y);
	Linia() = delete;
	~Linia() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float lWidth{ 40.0f };
	const float lHeight{ 40.0f };
	float lVelocity{ 4.0f };
	Vector2f velocity{ lVelocity, 0.f };
};

class Doub :public Bonus
{
public:
	Doub(float t_x, float t_y);
	Doub() = delete;
	~Doub() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float dWidth{ 40.0f };
	const float dHeight{ 40.0f };
	float dVelocity{ 4.0f };
	Vector2f velocity{ dVelocity, 0.f };
};

class Life :public Bonus
{
public:
	Life(float t_x, float t_y);
	Life() = delete;
	~Life() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float lWidth{ 40.0f };
	const float lHeight{ 40.0f };
	float lVelocity{ 6.0f };
	Vector2f velocity{ lVelocity, 0.f };
};

class Zycie :public Nieruch
{
public:
	Zycie(float t_x, float t_y);
	Zycie() = delete;
	~Zycie() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();
	const float pWidth{ 235.0f };
	const float pHeight{ 115.0f };
};

class Podloga :public Nieruch
{
public:
	Podloga(float t_x, float t_y);
	Podloga() = delete;
	~Podloga() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();

	const float pWidth{ 1200.0f };
	const float pHeight{ 10.0f };
};

class Guzik : public Nieruch
{
public:
	const float pWidth{ 350.0f };
	const float pHeight{ 100.0f };
};

class Start :public Guzik
{
public:
	Start(float t_x, float t_y);
	Start() = delete;
	~Start() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();
};

class Exit :public Guzik
{
public:
	Exit(float t_x, float t_y);
	Exit() = delete;
	~Exit() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();
};

class Scoreboard:public Nieruch
{
public:
	Scoreboard(float t_x, float t_y);
	Scoreboard() = delete;
	~Scoreboard() = default;
	void draw(RenderTarget & target, RenderStates state) const override;
	void update();
	const float pWidth{ 500.0f };
	const float pHeight{ 450.0f };
};

class Score
{
public:
	string nickname;
	int score;
	Score();
	Score(string s, int pkt);
	void wypisz();
};

