#include "Sound.hpp"
#include <iostream>


int Sound::vol = 50;

std::vector<sf::SoundBuffer> Sound::buffers(5, sf::SoundBuffer());
std::vector<sf::Sound> Sound::sounds(5, sf::Sound());
sf::Music Sound::music = sf::Music();

Sound::Sound(/* args */)
{
	music.openFromFile(std::string(SOUNDRES_DIR) + "/music.wav");
	music.setLoop(true);
	for (size_t i = 0; i < 5; i++)
	{
		buffers.push_back(sf::SoundBuffer());
		sounds.push_back(sf::Sound());
	}
	buffers[beep1].loadFromFile(std::string(SOUNDRES_DIR) + "/beep1.wav");
	buffers[beep2].loadFromFile(std::string(SOUNDRES_DIR) + "/beep2.wav");
	buffers[boom].loadFromFile(std::string(SOUNDRES_DIR) + "/boom.wav");
	buffers[sad].loadFromFile(std::string(SOUNDRES_DIR) + "/sad.wav");
	buffers[click].loadFromFile(std::string(SOUNDRES_DIR) + "/click.wav");
	for (size_t i = 0; i < 5; i++)
	{
		sounds[i].setBuffer(buffers[i]);
	}
	increaseVol();
}

Sound::~Sound()
{
}

void Sound::playSound(int n)
{
	sounds[n].play();
}

void Sound::playMusic(void)
{
	music.play();
}

void Sound::increaseVol(void)
{
	vol += 10;
	if (vol > 100)
		vol = 100;
	for (auto &mysound : sounds)
	{
		mysound.setVolume(vol);
	}
	music.setVolume(vol);
}

void Sound::decreaseVol(void)
{
	vol -= 10;
	if (vol < 0)
		vol = 0;
	for (auto &mysound : sounds)
	{
		mysound.setVolume(vol);
	}
	music.setVolume(vol);
}
