#ifndef SOUND_HPP
#define SOUND_HPP

#include <vector>
#include <SFML/Audio.hpp>

enum clips
{
	beep1,
	beep2,
	boom,
	sad,
	click
};

class Sound
{
private:
	static std::vector<sf::SoundBuffer> buffers;
	static std::vector<sf::Sound> sounds;
	static sf::Music music;

	static int vol;

public:
	Sound(/* args */);
	~Sound();
	
	static void playSound(int n);
	static void playMusic(void);
	static void increaseVol(void);
	static void decreaseVol(void);
};

#endif
