#pragma once

namespace Settings
{
	enum KEY_ACTION
	{
		FLUSH = 0,
		ROTATE,
		FAST_DROP,
		MOVE_LEFT,
		MOVE_RIGHT
	};
	struct Audio
	{
		unsigned short soundVolume;
		unsigned short musicVolume;
	};
	struct Graphics
	{

	};
	struct Movement
	{
		int control_keys[5];
	};
}
