#include "pch.h"
#include "ScreenFlipbookManager.h"


ScreenFlipbookManager::ScreenFlipbookManager()
	: ScreenFlipbookManager(nullptr)
{
}

ScreenFlipbookManager::ScreenFlipbookManager(sf::RenderWindow* window)
	: wnd(window)
{
	f_current.reserve(35);
	clock.restart();
}




void ScreenFlipbookManager::ini(sf::RenderWindow* window)
{
	wnd = window;
	f_current.clear();
	f_templates.clear();
	f_current.reserve(35);
	clock.restart();
}

void ScreenFlipbookManager::loadAnimation(
	const char* name, 
	const sf::Vector3i& numAndMaxFrames,
	const sf::Vector2i& sizeOfFrame,
	const sf::Texture& texture, 
	const sf::Time& frequency,
	int depth,
	sf::Vector2i startFramePos ,
	const E_MODE& mode,
	const sf::Time& lifeTime)
{
	f_templates.emplace(name, Flipbook(name, {0,0}, numAndMaxFrames, sizeOfFrame, texture, frequency, depth, startFramePos, mode, lifeTime));
}



void ScreenFlipbookManager::eraseAnimation(const char* name)
{
	std::map<const char*, Flipbook>::iterator it = f_templates.find(name);
	if (it != f_templates.end())
	{
		f_templates.erase(it);
	}
}


void ScreenFlipbookManager::stop(const char* name)
{
	std::string n(name);
	auto iitt = std::find_if(f_current.begin(), f_current.end(), [&](const Flipbook& a) { return  n.compare(a.getName()) == 0; });
	if (iitt != f_current.end())
		f_current.erase(iitt);
}

void ScreenFlipbookManager::update(bool isUpdate)
{
	sf::Time t = clock.restart();
	if (isUpdate)
	{
		auto begin = f_current.begin();
		for (int i = f_current.size() - 1; i >= 0; i--)
		{
			f_current[i].update(t);
			if (f_current[i].bFinished)
				f_current.erase(begin + i);
		}
	}
}

void ScreenFlipbookManager::render() const
{
	for (auto& anim : f_current)
		anim.render(wnd);
}

void ScreenFlipbookManager::clear()
{
	f_current.clear();
}

void ScreenFlipbookManager::OnCreate()
{
	for (auto& a : f_current)
	{
		a.OnCreate(wnd);
	}
}



void ScreenFlipbookManager::play(const char* name, const sf::Vector2f& pos)
{
	this->play(name, pos, f_templates[name].freq_time, f_templates[name].reverse, f_templates[name].getSprite().getScale());
}

void ScreenFlipbookManager::play(const char* name, const sf::Vector2f& pos, bool reverse, const sf::Vector2f& scale)
{
	this->play(name, pos, f_templates[name].freq_time, reverse, scale);
}

void ScreenFlipbookManager::play(const char* name, const sf::Vector2f& pos, const sf::Time& frequency, bool reverse, const sf::Vector2f& scale)
{
	f_current.push_back(f_templates[name]);
	auto& fb = f_current.back();
	fb.restart(reverse);
	fb.sprite.setScale(scale);
	fb.sprite.setPosition(pos.x - fb.sprite.getGlobalBounds().width / 2.0f, pos.y - fb.sprite.getGlobalBounds().height / 2.0f);
	fb.freq_time = frequency;

	fb.ppX = fb.getSprite().getPosition().x / wnd->getSize().x;
	fb.ppY = fb.getSprite().getPosition().y / wnd->getSize().y;
	
	std::sort(f_current.begin(), f_current.end(), [](const Flipbook& lhs, const Flipbook& rhs) { return lhs.getDepth() < rhs.getDepth(); });
}
























Flipbook::Flipbook(
	const char* name,
	const sf::Vector2f& position,
	const sf::Vector3i& numAndMaxFrames,
	const sf::Vector2i& sizeOfFrame, 
	const sf::Texture& texture, 
	const sf::Time& frequency,
	int depth,
	sf::Vector2i start_pos,
	const ScreenFlipbookManager::E_MODE& mode,
	const sf::Time& life_time
)
	: name(name)
	, number_of_frames(numAndMaxFrames)
	, size_of_frame(sizeOfFrame)
	, mode(mode)
	, start_pos(start_pos)
	, curr_frame({ 0, 0, 0})
	, freq_time(frequency)
	, curr_freq_time(sf::milliseconds(0))
	, life_time(life_time)
	, curr_life_time(sf::milliseconds(0))
	, depth(depth)
	, bFinished(false)
	, reverse(1)
{

	sprite.setPosition(position);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(
		start_pos.x,
		start_pos.y,
		sizeOfFrame.x, 
		sizeOfFrame.y));


}

Flipbook::Flipbook(const Flipbook& other)
	: name(other.name)
	, number_of_frames(other.number_of_frames)
	, size_of_frame(other.size_of_frame)
	, mode(other.mode)
	, start_pos(other.start_pos)
	, curr_frame(other.curr_frame)
	, freq_time(other.freq_time)
	, curr_freq_time(other.curr_freq_time)
	, life_time(other.life_time)
	, curr_life_time(other.curr_life_time)
	, depth(other.depth)
	, bFinished(other.bFinished)
	, reverse(other.reverse)
{
	sprite.setPosition(other.sprite.getPosition());
	sprite.setTexture(*other.sprite.getTexture());
	sprite.setTextureRect(other.sprite.getTextureRect());
	sprite.setScale(other.sprite.getScale());
}

Flipbook& Flipbook::operator=(const Flipbook& other) 
{
	name = other.name;
	number_of_frames = other.number_of_frames;
	size_of_frame = other.size_of_frame;
	mode = other.mode;
	start_pos = other.start_pos;
	curr_frame = other.curr_frame;
	freq_time = other.freq_time;
	curr_freq_time = other.curr_freq_time;
	life_time = other.life_time;
	curr_life_time = other.curr_life_time;
	depth = other.depth;
	bFinished = other.bFinished;
	reverse = other.reverse;

	sprite.setPosition(other.sprite.getPosition());
	sprite.setTexture(*other.sprite.getTexture());
	sprite.setTextureRect(other.sprite.getTextureRect());
	sprite.setScale(other.sprite.getScale());

	return *this;
}

Flipbook::~Flipbook()
{
}

void Flipbook::update(const sf::Time& tt)
{
	curr_freq_time += tt;
	curr_life_time += tt;
	if (curr_freq_time >= freq_time)
	{
		sprite.setTextureRect(sf::IntRect(
			reverse * (curr_frame.x * size_of_frame.x) + start_pos.x,
			reverse * (curr_frame.y * size_of_frame.y) + start_pos.y,
			size_of_frame.x,
			size_of_frame.y
		));

		// AVE LOOK dla 0s wyswietli co najmniej 1 klatke (umiescic switch poza ifem )
		switch (mode)
		{
		case ScreenFlipbookManager::SINGLE:
			if ((curr_frame.x == number_of_frames.x) && (curr_frame.y == number_of_frames.y ) || (curr_frame.z == number_of_frames.z))
			{
				bFinished = true;
			}
				curr_frame.z++;
			
			break;
		case ScreenFlipbookManager::TIME:
			if (curr_life_time >= life_time)
				bFinished = true;

			break;
		default:
			break;
		}

		if ((curr_frame.y * number_of_frames.y) + curr_frame.x >= number_of_frames.z - 1)
		{
			curr_frame.x = 0;
			curr_frame.y = 0;
		}
		else if (++curr_frame.x >= number_of_frames.x)
		{
			curr_frame.x = 0;
			curr_frame.y = (curr_frame.y + 1) % number_of_frames.y;
		}
		curr_freq_time -= freq_time;
	}
}

void Flipbook::render(sf::RenderWindow* const window)const
{
	window->draw(sprite);
}

void Flipbook::restart(bool reverse)
{
	curr_frame = { 0, 0, 0 };
	curr_freq_time = sf::milliseconds(0);
	curr_life_time = sf::milliseconds(0);
	bFinished = false;
	sprite.setTextureRect(sf::IntRect(
		start_pos.x,
		start_pos.y,
		size_of_frame.x,
		size_of_frame.y));

	sprite.setScale({ 1.0f,1.0f });
	this->reverse = 1;
	if (reverse)
	{
		this->reverse = -1;
		start_pos.x = (number_of_frames.x - 1) * size_of_frame.x;
		start_pos.y = (number_of_frames.y - 1) * size_of_frame.y;
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(start_pos.x, start_pos.y), size_of_frame));
	}
}
