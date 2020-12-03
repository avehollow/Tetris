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

class ScreenFlipbookManager
{
public:

	enum E_MODE
	{
		ENDLESS = 0,
		SINGLE = 1,
		TIME = 2
	};

	ScreenFlipbookManager();
	ScreenFlipbookManager(sf::RenderWindow* window);

	class Flipbook& operator[](const char* name) { return f_templates[name]; };

	void ini(sf::RenderWindow* window);
	void loadAnimation(
		const char* name,
		const sf::Vector3i& numAndMaxFrames,
		const sf::Vector2i& sizeOfFrame,
		const sf::Texture& texture,
		const sf::Time& frequency,
		const int& depth = 0,
		const sf::Vector2i& startFramePos = { 0 , 0},
		const E_MODE& mode = E_MODE::ENDLESS,
		const sf::Time& lifeTime = sf::milliseconds(0)
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

	class Flipbook* temporary_back()const;
	void eraseAnimation(const char* name);
	void stop(const char* name);
	void update(bool isUpdate = true);
	void render()const;
	void clear_current();
	void OnCreate();
private:
	sf::Clock clock;
	sf::RenderWindow* wnd;
	std::unordered_map<const char*,class Flipbook> f_templates;
	std::vector<class Flipbook> f_current;
	std::size_t idx_of_last_added_flipbook;
};


class Flipbook
{
	friend class ScreenFlipbookManager;
public:
	Flipbook();
	Flipbook(
		const char* name,
		const sf::Vector2f& position,
		const sf::Vector3i& numAndMaxFrames,
		const sf::Vector2i& sizeOfFrame,
		const sf::Texture& texture,
		const sf::Time& frequency,
		const int& depth = 0,
		const sf::Vector2i& start_pos = { 0 , 0},
		const ScreenFlipbookManager::E_MODE& mode = ScreenFlipbookManager::E_MODE::ENDLESS,
		const sf::Time& life_time = sf::milliseconds(0)
	);
	//Flipbook(const Flipbook& other);
	Flipbook& operator=(const Flipbook& other) ;
	~Flipbook();

	void update(const sf::Time& tt);
	void render(sf::RenderWindow* const window)const;

	void restart(bool reverse = false);
	void setPosition(float x, float y);

	bool finished()const;
	int getId()const;
	int getDepth()const;
	const char* getName()const;
	const sf::Sprite& getSprite()const;

	void OnCreate(const sf::RenderWindow* const window);

private:
	sf::Sprite sprite;
	sf::Vector3i number_of_frames;
	sf::Vector2i size_of_frame;
	sf::Vector3i curr_frame;
	sf::Vector2i start_pos;
	ScreenFlipbookManager::E_MODE mode;
	sf::Time freq_time;
	sf::Time curr_freq_time;
	sf::Time life_time;
	sf::Time curr_life_time;
	
	const char* name;
	bool bFinished;

	int id;
	int depth;
	int reverse;

	float ppX;
	float ppY;

	double psX;
	double psY;

};

inline bool Flipbook::finished()const 
{
	return bFinished;
}
inline void Flipbook::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}
inline int Flipbook::getId()const
{
	return id;
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
	sprite.setPosition(ppX * window->getSize().x , ppY * window->getSize().y );
	sprite.setScale(psX * window->getSize().x, psY * window->getSize().y);
}




