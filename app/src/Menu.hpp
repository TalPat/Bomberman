#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>
#include <Sound.hpp>

#include <vector>

typedef sf::Keyboard::Key Key;

enum MenuAction
{
	StartGame,
	ContinueGame,
	ToControlsMenu,
	ToSettingsMenu,
	ToResolutionMenu,
	ToVolumeMenu,
	ToMainMenu,
	SetResolution800,
	SetResolution1024,
	SetResolutionFullscreen,
	SetUpControl,
	SetDownControl,
	SetLeftControl,
	SetRightControl,
	SetBombControl,
	IncreaseVolume,
	DecreaseVolume,
	Exit,
	Nothing
};

struct MenuItem
{
	int offset;
	std::string text;
	std::string additional = "";
	bool selected;
	MenuAction option;

	MenuItem() {};

	MenuItem(float offset, std::string text, bool selected, MenuAction option)
		: offset(offset), text(text), selected(selected), option(option) {}
	
	MenuItem(float offset, std::string text, bool selected, MenuAction option, std::string additional)
		: offset(offset), text(text), selected(selected), option(option), additional(additional) {}
};

class Menu
{
private:
	MenuAction handleInput(sf::RenderWindow &window);
	void menuUp();
	void menuDown();
	MenuAction select();

protected:
	Renderer *_renderer;
	Shader *_shader;
	Camera *_camera;

	MenuAction backOption;
	std::vector<MenuItem> menuItems;

	void drawMenuText(sf::RenderWindow &window, MenuItem &item);

public:
	Menu();
	~Menu();

	void init(Renderer &renderer, std::vector<MenuItem> &items, MenuAction backOption, bool align);
	MenuAction render(sf::RenderWindow &window);

	void resetSelected();
	void alignItems();
	void addOption(MenuItem item);
	void renameOption(int index, std::string name);

	static std::map<Key, std::string> keyStrings;
};

#endif
