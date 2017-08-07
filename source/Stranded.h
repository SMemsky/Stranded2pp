#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "common/CmdLineArgs.h"
#include "common/Resources.h"
#include "common/Modification.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "state/MainMenu.h"
#include "state/Intro.h"
#include "state/State.h"
#include "window/Window.h"

class Stranded
{
public:
	Stranded(std::vector<std::string> const & arguments);

	void run();
	void stopLoop();

	void setState(state::Type stateType);
	void pushState(state::Type stateType);
	void popState();

	gfx::Graphics & getGraphics() { return graphics; };
	Engine & getEngine() { return engine; };
private:
	void printWelcomeMessage();
private:
	common::CmdLineArgs cmdLineArgs;

	Modification modification;

	Resources resources;

	Window window;

	Input input;

	gfx::Graphics graphics;

	Network network;

	Sound sound;

	Engine engine;

	state::MainMenu mainMenu;
	state::Intro intro;

	std::stack<state::State *> currentStates;

	bool shouldStop;
};
