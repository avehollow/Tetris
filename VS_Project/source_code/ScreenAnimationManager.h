#pragma once

namespace sf_literals
{
	inline sf::Time operator""s(unsigned long long s)noexcept
	{
		return sf::seconds(s);
	};

	inline sf::Time operator""s(long double s)noexcept
	{
		return sf::seconds(s);
	};
	
	inline sf::Time operator""ms(unsigned long long ms)noexcept
	{
		return sf::milliseconds(ms);
	};

	inline sf::Time operator""us(unsigned long long us)noexcept
	{
		return sf::microseconds(us);
	};
}

class ScreenAnimationManager
{
public:

	enum E_MODE
	{
		ENDLESS = 0,
		SINGLE = 1,
		TIME = 2
	};

	ScreenAnimationManager();
	ScreenAnimationManager(sf::RenderWindow* window);

	class Flipbook& operator[](const char* name) { return anim[name]; };

	void ini(sf::RenderWindow* window);
	void loadAnimation(
		const char* name,
		const sf::Vector3i& numAndMaxFrames,
		const sf::Vector2i& sizeOfFrame,
		const sf::Texture& texture,
		const sf::Time& frequency,
		int depth = 0,
		sf::Vector2i startFramePos = { 0 , 0},
		const E_MODE& mode = E_MODE::ENDLESS,
		const sf::Time& lifeTime = sf::milliseconds(0)
	);
	void eraseAnimation(const char* name);
	void play(
		const char* name,
		const sf::Vector2f& pos
	);
	void play(
		const char* name, 
		const sf::Vector2f& pos, 
		bool reverse = false,
		const sf::Vector2f& scale = sf::Vector2f(1, 1)
	);
	void play(
		const char* name, 
		const sf::Vector2f& pos, 
		const sf::Time& frequency,
		bool reverse = false,
		const sf::Vector2f& scale = sf::Vector2f(1, 1)
	);
	void stop(const char* name);
	void update(bool isUpdate = true);
	void render()const;
	void clear();
	void OnCreate();
private:
	sf::Clock clock;
	sf::RenderWindow* wnd;
	std::map<const char*,class Flipbook> anim;
	std::vector<class Flipbook> curr_anim;
};


class Flipbook
{
	friend class ScreenAnimationManager;
public:
	Flipbook() {};
	Flipbook(
		const char* name,
		const sf::Vector2f& position,
		const sf::Vector3i& numAndMaxFrames,
		const sf::Vector2i& sizeOfFrame,
		const sf::Texture& texture,
		const sf::Time& frequency,
		int depth = 0,
		sf::Vector2i start_pos = { 0 , 0},
		const ScreenAnimationManager::E_MODE& mode = ScreenAnimationManager::E_MODE::ENDLESS,
		const sf::Time& life_time = sf::milliseconds(0)
	);
	Flipbook(const Flipbook& other);
	Flipbook& operator=(const Flipbook& other) ;
	~Flipbook();

	void update(const sf::Time& tt);
	void render(sf::RenderWindow* const window)const;
	void restart(bool reverse = false);
	bool finished()const;
	void setPosition(float x, float y);
	int getDepth()const;
	const char* getName()const;
	const sf::Sprite& getSprite()const;

	void OnCreate(const sf::RenderWindow* const window);

private:
	const char* name;
	sf::Sprite sprite;
	sf::Vector3i number_of_frames;
	sf::Vector2i size_of_frame;
	sf::Vector3i curr_frame;
	sf::Vector2i start_pos;
	ScreenAnimationManager::E_MODE mode;
	sf::Time freq_time;
	sf::Time curr_freq_time;
	sf::Time life_time;
	sf::Time curr_life_time;
	
	int depth;
	bool bFinished;
	int reverse;


	float ppX;
	float ppY;

};

inline bool Flipbook::finished()const 
{
	return bFinished;
}
inline void Flipbook::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}
inline int Flipbook::getDepth()const
{
	return depth; 
}
inline const char* Flipbook::getName()const
{
	return name; 
}
inline const sf::Sprite& Flipbook::getSprite()const 
{
	return sprite;
}

inline void Flipbook::OnCreate(const sf::RenderWindow* const window)
{
	sprite.setPosition(ppX * window->getSize().x, ppY * window->getSize().y);
}




