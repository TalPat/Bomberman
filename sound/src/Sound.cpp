#include "Sound.hpp"
#include <iostream>


int Sound::vol = 50;

std::vector<sf::SoundBuffer> Sound::buffers(5, sf::SoundBuffer());
std::vector<sf::Sound> Sound::sounds(5, sf::Sound());
sf::Music Sound::musMen = sf::Music();
sf::Music Sound::musLvl1 = sf::Music();
sf::Music Sound::musLvl2 = sf::Music();
sf::Music Sound::musLvl3 = sf::Music();
sf::Music Sound::musLvl4 = sf::Music();
songs Sound::activeSong = none;

Sound::Sound(/* args */)
{
	for (size_t i = 0; i < 5; i++)
	{
		buffers.push_back(sf::SoundBuffer());
		sounds.push_back(sf::Sound());
	}
	musMen.openFromFile(std::string(SOUNDRES_DIR) + "/music.wav");
	musMen.setLoop(true);
	musLvl1.openFromFile(std::string(SOUNDRES_DIR) + "/lvl1.wav");
	musLvl1.setLoop(true);
	musLvl2.openFromFile(std::string(SOUNDRES_DIR) + "/lvl2.wav");
	musLvl2.setLoop(true);
	musLvl3.openFromFile(std::string(SOUNDRES_DIR) + "/lvl3.wav");
	musLvl3.setLoop(true);
	musLvl4.openFromFile(std::string(SOUNDRES_DIR) + "/lvl4.wav");
	musLvl4.setLoop(true);
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

void Sound::playMusic(int n)
{
	if (n != activeSong)
	{
		musMen.stop();
		musLvl1.stop();
		musLvl2.stop();
		musLvl3.stop();
		musLvl4.stop();
		
		switch (n)
		{
		case 0:
			musMen.play();
			break;
		case 1:
			musLvl1.play();
			break;
		case 2:
			musLvl2.play();
			break;
		case 3:
			musLvl3.play();
			break;
		case 4:
			musLvl4.play();
			break;
		
		default:
			break;
		}

		activeSong = static_cast<songs>(n);
	}
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
	musMen.setVolume(vol);
	musLvl1.setVolume(vol);
	musLvl2.setVolume(vol);
	musLvl3.setVolume(vol);
	musLvl4.setVolume(vol);
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
	musMen.setVolume(vol);
	musLvl1.setVolume(vol);
	musLvl2.setVolume(vol);
	musLvl3.setVolume(vol);
	musLvl4.setVolume(vol);
}

void Sound::setVol(unsigned int volume)
{
	if (volume > 100)
		return;
	else
		vol = volume;

	for (auto &mysound : sounds)
	{
		mysound.setVolume(vol);
	}
	musMen.setVolume(vol);
	musLvl1.setVolume(vol);
	musLvl2.setVolume(vol);
	musLvl3.setVolume(vol);
	musLvl4.setVolume(vol);
}

int Sound::getVol(void)
{
	return Sound::vol;
}
