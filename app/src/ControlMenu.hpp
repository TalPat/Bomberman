#ifndef _ControlMenu_hpp_
#define _ControlMenu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include "./Input.hpp"
#include "./Menu.hpp"

#include <vector>

class ControlMenu : public Menu
{
private:

public:
	ControlMenu();
	~ControlMenu();

	void init(Renderer &renderer, MenuAction backOption);
	void setControl(EngineEvent event);
};

#endif
