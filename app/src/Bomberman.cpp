#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>
#include <pthread.h>

const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 11;

Bomberman::Bomberman()
		: renderTime(0),
			engineTime(0)
{
	sf::ContextSettings settings;
	settings.depthBits = 32;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.antialiasingLevel = 4;
	settings.attributeFlags = sf::ContextSettings::Core;

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	window->setActive();
	renderer.init();

	std::vector<MenuItem> mainMenuItems;
	mainMenuItems.push_back(MenuItem(2, "Start", true, MenuAction::StartGame));
	mainMenuItems.push_back(MenuItem(0, "Settings", false, MenuAction::ToSettingsMenu));
	mainMenuItems.push_back(MenuItem(-2, "Exit", false, MenuAction::Exit));
	mainMenu.init(renderer, mainMenuItems, MenuAction::Nothing);

	std::vector<MenuItem> pauseMenuItems;
	pauseMenuItems.push_back(MenuItem(1, "Continue", true, MenuAction::StartGame));
	pauseMenuItems.push_back(MenuItem(-1, "Main Menu", false, MenuAction::ToMainMenu));
	pauseMenu.init(renderer, pauseMenuItems, MenuAction::StartGame);

	std::vector<MenuItem> settingsMenuItems;
	settingsMenuItems.push_back(MenuItem(3, "Resolution", true, MenuAction::ToResolutionMenu));
	settingsMenuItems.push_back(MenuItem(1, "Controls", false, MenuAction::ToControlsMenu));
	settingsMenuItems.push_back(MenuItem(-1, "Volume", false, MenuAction::ToVolumeMenu));
	settingsMenuItems.push_back(MenuItem(-3, "Back", false, MenuAction::ToMainMenu));
	settingsMenu.init(renderer, settingsMenuItems, MenuAction::ToMainMenu);

	std::vector<MenuItem> resolutionMenuItems;
	resolutionMenuItems.push_back(MenuItem(3, "800 x 800", true, MenuAction::SetResolution800));
	resolutionMenuItems.push_back(MenuItem(1, "1024 x 1000 ", false, MenuAction::SetResolution1024));
	resolutionMenuItems.push_back(MenuItem(-1, "Fullscreen", false, MenuAction::SetResolutionFullscreen));
	resolutionMenuItems.push_back(MenuItem(-3, "Back", false, MenuAction::ToSettingsMenu));
	resolutionMenu.init(renderer, resolutionMenuItems, MenuAction::ToSettingsMenu);

	std::vector<MenuItem> volumeMenuItems;
	volumeMenuItems.push_back(MenuItem(3, "Increase Volume", true, MenuAction::IncreaseVolume));
	volumeMenuItems.push_back(MenuItem(1, "Decrease Volume", false, MenuAction::DecreaseVolume));
	volumeMenuItems.push_back(MenuItem(-3, "Back", false, MenuAction::ToSettingsMenu));
	volumeMenu.init(renderer, volumeMenuItems, MenuAction::ToSettingsMenu);

	controlsMenu.init(renderer, MenuAction::ToSettingsMenu);

	menuState = MenuState::MainMenu;
	resolution = Resolution::Default;
	gameStarted = false;

	this->deltaClock.restart();
	this->frameClock.restart();

	//thread stuff
	threadActive = false;
	this->gameState.level = 0;
	this->engine.init(this->gameState);
	gameState.sound.playMusic();
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame()
{
	this->start();
}

void Bomberman::handleMenuAction(MenuAction option)
{
	switch (option)
	{
	case MenuAction::StartGame:
		this->menuState = MenuState::Playing;
		if (!this->gameStarted)
		{
			this->gameStarted = true;
			this->mainMenu.addOption(MenuItem(3, "Continue", false, MenuAction::StartGame));
			this->mainMenu.resetSelected();
		}
		break;
	case MenuAction::ToMainMenu:
		this->menuState = MenuState::MainMenu;
		break;
	case MenuAction::ToSettingsMenu:
		this->resolutionMenu.resetSelected();
		this->controlsMenu.resetSelected();
		this->menuState = MenuState::SettingsMenu;
		break;
	case MenuAction::ToResolutionMenu:
		this->menuState = MenuState::ResolutionMenu;
		break;
	case MenuAction::ToControlsMenu:
		this->menuState = MenuState::ControlsMenu;
		break;
	case MenuAction::ToVolumeMenu:
		this->menuState = MenuState::VolumeMenu;
		break;
	case MenuAction::SetResolution800:
		if (this->resolution != Resolution::Default)
		{
			sf::ContextSettings settings = this->window->getSettings();
			this->window->close();
			delete this->window;
			this->window = new sf::RenderWindow(sf::VideoMode(800, 800), WINDOW_TITLE, sf::Style::Default, settings);
			this->renderer.init();
			this->resolution = Resolution::Default;
		}
		break;
	case MenuAction::SetResolution1024:
		if (this->resolution != Resolution::Medium)
		{
			sf::ContextSettings settings = this->window->getSettings();
			this->window->close();
			delete this->window;
			this->window = new sf::RenderWindow(sf::VideoMode(1024, 1000), WINDOW_TITLE, sf::Style::Default, settings);
			this->renderer.init();
			this->resolution = Resolution::Default;
		}
		break;
	case MenuAction::SetResolutionFullscreen:
		if (this->resolution != Resolution::Fullscreen)
		{
			sf::ContextSettings settings = this->window->getSettings();
			this->window->close();
			delete this->window;
			this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), WINDOW_TITLE, sf::Style::Fullscreen, settings);
			this->renderer.init();
			this->resolution = Resolution::Default;
		}
		break;
	case MenuAction::SetUpControl:
		this->settingKey = EngineEvent::move_up;
		break;
	case MenuAction::SetDownControl:
		this->settingKey = EngineEvent::move_down;
		break;
	case MenuAction::SetLeftControl:
		this->settingKey = EngineEvent::move_left;
		break;
	case MenuAction::SetRightControl:
		this->settingKey = EngineEvent::move_right;
		break;
	case MenuAction::SetBombControl:
		this->settingKey = EngineEvent::place_bomb;
		break;
	case MenuAction::IncreaseVolume:
		this->gameState.sound.increaseVol();
		break;
	case MenuAction::DecreaseVolume:
		this->gameState.sound.decreaseVol();
		break;
	case MenuAction::Exit:
		this->stop();
		break;
	default:
		break;
	}
}

void Bomberman::setKey()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		switch (event.type)
		{
		case event.KeyPressed:
			try
			{
				this->input.setKey(this->settingKey, event.key.code);
				this->controlsMenu.setControl(this->settingKey, event.key.code);
				this->settingKey = EngineEvent::unknown;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				this->settingKey = EngineEvent::unknown;
			}
			break;
		case event.Closed:
			this->stop();
			break;
		default:
			break;
		}
	}
}

void *Bomberman::threadFunction(void *arg)
{
	Bomberman *bman = (Bomberman *)arg;

	// uncomment if object must be mutated by renderer
	// pthread_mutex_lock(bman->lock);

	bman->renderer.render(*(bman->window), bman->gameState);
	bman->threadActive = false;
	return (NULL);
	// uncomment if object must be mutated by renderer
	// pthread_mutex_unlock(bman->lock);
}

void Bomberman::updateFunc()
{
	if (!this->window->isOpen())
		this->stop();

	std::vector<EngineEvent> actions;
	if (this->menuState == Playing)
	{
		InputResponse response = this->input.parseKeys(actions, *window);
		switch (response)
		{
		case InputResponse::quit:
			this->stop();
			break;
		case InputResponse::pause:
			// Can be used to pause game with 'Esc' key
			if (this->menuState == MenuState::PauseMenu)
				this->menuState = MenuState::Playing;
			else if (this->menuState == MenuState::Playing)
				this->menuState = MenuState::PauseMenu;
			break;
		default:
			break;
		}
	}

	// Record the time elapsed since starting last render
	this->renderTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	if (this->menuState == MenuState::Playing)
	{
		this->engine.update(this->renderTime + this->engineTime, actions, this->gameState);
	}
	// Record the time taken by the engine
	this->engineTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	MenuAction option = MenuAction::Nothing;

	switch (this->menuState)
	{
	case MenuState::Playing:
		// Only render if required to enforce frameRate
		if (this->frameClock.getElapsedTime().asSeconds() >= this->perFrameSeconds)
		{
			if (!threadActive)
			{
				this->frameClock.restart();
				threadActive = true;
				pthread_create(&myThread, NULL, Bomberman::threadFunction, (void*)this);
			}
		}
		break;
	case MenuState::MainMenu:
		option = this->mainMenu.render(*(this->window));
		this->handleMenuAction(option);
		break;
	case MenuState::PauseMenu:
		option = this->pauseMenu.render(*(this->window));
		this->handleMenuAction(option);
		break;
	case MenuState::SettingsMenu:
		option = this->settingsMenu.render(*(this->window));
		this->handleMenuAction(option);
		break;
	case MenuState::ResolutionMenu:
		option = this->resolutionMenu.render(*(this->window));
		this->handleMenuAction(option);
		break;
	case MenuState::ControlsMenu:
		if (this->settingKey == EngineEvent::unknown)
		{
			option = this->controlsMenu.render(*(this->window));
			this->handleMenuAction(option);
		}
		else
		{
			this->controlsMenu.displaySettingScreen(*(this->window));
			this->setKey();
		}
		break;
	case MenuState::VolumeMenu:
		option = this->volumeMenu.render(*(this->window));
		this->handleMenuAction(option);
		break;
	}
}

void Bomberman::setMutex(pthread_mutex_t *mutex) {
	lock = mutex;
}
