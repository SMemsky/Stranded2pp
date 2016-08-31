#pragma once

#include <memory>
#include <string>
#include <vector>

class Engine;
class Graphics;
class Gui;
class Input;
class Network;
class Sound;
class Window;

class Stranded
{
public:
	Stranded();
	~Stranded();

	bool init(const std::vector<std::string>& arguments);
	void run();
private:
	bool parseArguments(const std::vector<std::string>& arguments);
private:
	std::string modification; // Todo

	bool isFullscreen; // Todo

	std::shared_ptr<Window>		window;
	std::shared_ptr<Input>		input;
	std::shared_ptr<Graphics>	graphics;
	std::shared_ptr<Gui>		gui;
	std::shared_ptr<Network>	network;
	std::shared_ptr<Sound>		sound;
	std::shared_ptr<Engine>		engine;
};
