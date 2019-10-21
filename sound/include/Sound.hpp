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
	std::vector<sf::SoundBuffer> buffers;
	std::vector<sf::Sound> sounds;
	sf::Music music;

	static int vol;

public:
	Sound(/* args */);
	~Sound();
	
	void playSound(int n);
	void playMusic(void);
	void increaseVol(void);
	void decreaseVol(void);
};

#endif
