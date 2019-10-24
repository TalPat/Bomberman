#include "./Menu.hpp"

std::map<Key, std::string> Menu::keyStrings = {
	{ Key::Unknown, "-1"},
	{ Key::A, "A" },
	{ Key::B, "B" },
	{ Key::C, "C" },
	{ Key::D, "D" },
	{ Key::E, "E" },
	{ Key::F, "F" },
	{ Key::G, "G" },
	{ Key::H, "H" },
	{ Key::I, "I" },
	{ Key::J, "J" },
	{ Key::K, "K" },
	{ Key::L, "L" },
	{ Key::M, "M" },
	{ Key::N, "N" },
	{ Key::O, "O" },
	{ Key::P, "P" },
	{ Key::Q, "Q" },
	{ Key::R, "R" },
	{ Key::S, "S" },
	{ Key::T, "T" },
	{ Key::U, "U" },
	{ Key::V, "V" },
	{ Key::W, "W" },
	{ Key::X, "X" },
	{ Key::Y, "Y" },
	{ Key::Z, "Z" },
	{ Key::Num0, "0" },
	{ Key::Num1, "1" },
	{ Key::Num2, "2" },
	{ Key::Num3, "3" },
	{ Key::Num4, "4" },
	{ Key::Num5, "5" },
	{ Key::Num6, "6" },
	{ Key::Num7, "7" },
	{ Key::Num8, "8" },
	{ Key::Num9, "9" },
	{ Key::Escape, "Escape" },
	{ Key::LControl, "LControl" },
	{ Key::LShift, "LShift" },
	{ Key::LAlt, "LAlt" },
	{ Key::LSystem, "LSystem" },
	{ Key::RControl, "RControl" },
	{ Key::RShift, "RShift" },
	{ Key::RAlt, "RAlt" },
	{ Key::RSystem, "RSystem" },
	{ Key::Menu, "Menu" },
	{ Key::LBracket, "[" },
	{ Key::RBracket, "]" },
	{ Key::SemiColon, ";" },
	{ Key::Comma, "," },
	{ Key::Period, "." },
	{ Key::Quote, "'" },
	{ Key::Slash, "/" },
	{ Key::BackSlash, "\\" },
	{ Key::Tilde, "~" },
	{ Key::Equal, "=" },
	{ Key::Dash, "-" },
	{ Key::Space, "Space" },
	{ Key::Return, "Enter / Return" },
	{ Key::BackSpace, "Backspace" },
	{ Key::Tab, "Tab" },
	{ Key::PageUp, "PageUp" },
	{ Key::PageDown, "PageDown" },
	{ Key::End, "End" },
	{ Key::Home, "Home" },
	{ Key::Insert, "Insert" },
	{ Key::Delete, "Delete" },
	{ Key::Add, "+" },
	{ Key::Subtract, "-" },
	{ Key::Multiply, "*" },
	{ Key::Divide, "/" },
	{ Key::Left, "Left Key" },
	{ Key::Right, "Right Key" },
	{ Key::Up, "Up Key" },
	{ Key::Down, "Down Key" },
	{ Key::Numpad0, "Numpad 0" },
	{ Key::Numpad1, "Numpad 1" },
	{ Key::Numpad2, "Numpad 2" },
	{ Key::Numpad3, "Numpad 3" },
	{ Key::Numpad4, "Numpad 4" },
	{ Key::Numpad5, "Numpad 5" },
	{ Key::Numpad6, "Numpad 6" },
	{ Key::Numpad7, "Numpad 7" },
	{ Key::Numpad8, "Numpad 8" },
	{ Key::Numpad9, "Numpad 9" },
	{ Key::F1, "F1" },
	{ Key::F2, "F2" },
	{ Key::F3, "F3" },
	{ Key::F4, "F4" },
	{ Key::F5, "F5" },
	{ Key::F6, "F6" },
	{ Key::F7, "F7" },
	{ Key::F8, "F8" },
	{ Key::F9, "F9" },
	{ Key::F10, "F10" },
	{ Key::F11, "F11" },
	{ Key::F12, "F12" },
	{ Key::F13, "F13" },
	{ Key::F14, "F14" },
	{ Key::F15, "F15" },
	{ Key::Pause, "Pause" }
};

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init(Renderer &renderer, std::vector<MenuItem> &items, MenuAction backOption, bool align)
{
	this->_renderer = &renderer;
	this->_shader = renderer.shader();
	this->_camera = renderer.camera();
	this->backOption = backOption;

	this->menuItems = items;
	if (align)
		this->alignItems();
}

void Menu::drawMenuText(sf::RenderWindow &window, MenuItem &item)
{
	std::string text = item.text;

	if (item.additional.length() > 0)
	{
		text += "      " + item.additional;
	}

	sf::Vector3i color = sf::Vector3i(10, 20, 50);
	sf::Vector2f startLocation = sf::Vector2f(-0.5f, item.offset / 4.0f);
	float scale = 0.15f + item.selected * 0.05f;

	if (item.selected)
		color = sf::Vector3i(250, 250, 250);

	this->_renderer->writeLine(window, text, color, startLocation, scale);
}

MenuAction Menu::handleInput(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case event.KeyPressed:
		{
			sf::Keyboard::Key key = event.key.code;
			switch (key)
			{
				case sf::Keyboard::Up:
					this->menuUp();
					break;
				case sf::Keyboard::Down:
					this->menuDown();
					break;
				case sf::Keyboard::Return:
					return this->select();
					break;
				case sf::Keyboard::Space:
					return this->select();
					break;
				case sf::Keyboard::Escape:
					return this->backOption;
					break;
				default:
					break;
			}
			break;
		}
		case event.Closed:
			return MenuAction::Exit;
			break;
		default:
			return MenuAction::Nothing;
			break;
		}
	}

	return MenuAction::Nothing;
}

void Menu::menuUp()
{
	Sound::playSound(click);
	if (this->menuItems[0].selected)
	{
		this->menuItems[this->menuItems.size() - 1].selected = true;
		this->menuItems[0].selected = false;
		return;
	}

	for (int i = 0; i < this->menuItems.size() - 1; i++)
	{
		if (this->menuItems[i + 1].selected)
		{
			this->menuItems[i].selected = true;
			this->menuItems[i + 1].selected = false;
			break;
		}
	}
}

void Menu::menuDown()
{
	Sound::playSound(click);
	for (int i = 0; i < this->menuItems.size(); i++)
	{
		if (this->menuItems[i].selected)
		{
			this->menuItems[i].selected = false;
			if (i == this->menuItems.size() - 1)
				this->menuItems[0].selected = true;
			else
				this->menuItems[i + 1].selected = true;
			break;
		}
	}
}

MenuAction Menu::select()
{
	Sound::playSound(click);
	for (int i = 0; i < this->menuItems.size(); i++)
	{
		if (this->menuItems[i].selected)
			return this->menuItems[i].option;
	}

	return MenuAction::Nothing;
}

MenuAction Menu::render(sf::RenderWindow &window)
{
	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (MenuItem item : this->menuItems)
		this->drawMenuText(window, item);

	window.display();

	return this->handleInput(window);
}

void Menu::resetSelected()
{
	this->menuItems[0].selected = true;

	for (int i = 1; i < this->menuItems.size(); i++)
		this->menuItems[i].selected = false;
}

void Menu::alignItems()
{
	int offset = 3;

	for (MenuItem &item : this->menuItems)
	{
		item.offset = offset;
		offset -= 2;
	}
}

void Menu::addOption(MenuItem item)
{
	this->menuItems.insert(this->menuItems.begin(), item);
	this->alignItems();
}

void Menu::renameOption(int index, std::string name)
{
	if (index > this->menuItems.size() - 1)
		return;
	else
		this->menuItems[index].text = name;
}
