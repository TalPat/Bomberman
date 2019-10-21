#ifndef _Renderer_hpp_
#define _Renderer_hpp_

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GameState.hpp>
#include "../src/Shader.hpp"
#include "../src/Model.hpp"
#include "../src/Square.hpp"
#include "../src/Camera.hpp"
#include "../src/Particle.hpp"
#include "../src/Swarm.hpp"
#include "../src/GuiChar.hpp"

enum modelNames
{
	breakableModel,
	unbreakableModel,
	playerModel,
	bombModel,
	flameModel,
	pigModel,
	robotModel,
	ghostModel,
	giraffeModel,
	shoel,
	shoer
};

enum tileNames
{
	floorTile,
	doorTile,
	bombTile,
	flameTile,
	flameParticle,
	skyboxTile
};

struct Model_st
{
	Model *model;
	glm::vec3 initialPos;
	glm::vec4 initialRot;
	glm::vec3 initialScale;
};

class Renderer
{
private:
	std::vector<Model_st> _models;
	std::map<char, int> fontMap;
	std::vector<GuiChar *> _characters;
	std::vector<Square *> _squares;
	Shader *_shader;
	Shader *_textShader;
	Camera *_camera;
	void pickups(sf::RenderWindow &window, const GameState &state);
	void player(sf::RenderWindow &window, const GameState &state);
	void map(sf::RenderWindow &window, const GameState &state);
	void enemy(sf::RenderWindow &window, const GameState &state);
	void light(sf::RenderWindow &window, const GameState &state, glm::vec4 pos);
	void loadFont();
	Swarm swarm;
	void skybox(sf::RenderWindow &window, const GameState &state);

	//troubleshooting frame counter
	sf::Clock _clock;

public:
	Renderer(/* args */);
	~Renderer();
	void init();
	void render(sf::RenderWindow &window, const GameState &state);
	void writeLine(sf::RenderWindow &window, std::string string, sf::Vector3i color, sf::Vector2f pos, float scale); //only render alpha numeric characters, is displayed as uppercase only

	Shader *shader();
	Camera *camera();
};

#endif