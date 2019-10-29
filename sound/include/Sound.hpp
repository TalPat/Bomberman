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

enum songs
{
	musmen,
	mus1,
	mus2,
	mus3,
	mus4,
	none
};

class Sound
{
private:
	static std::vector<sf::SoundBuffer> buffers;
	static std::vector<sf::Sound> sounds;
	static sf::Music musMen;
	static sf::Music musLvl1;
	static sf::Music musLvl2;
	static sf::Music musLvl3;
	static sf::Music musLvl4;

	static int vol;
	static songs activeSong;

public:
	Sound(/* args */);
	~Sound();
	
	static void playSound(int n);
	static void playMusic(int n);
	static void increaseVol(void);
	static void decreaseVol(void);
	static void setVol(unsigned int volume);
	static int getVol(void);
};

#endif
