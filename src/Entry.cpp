/**
 *
 *	This file is part of FreeDungeon.
 *	Copyright 2019-2026 Andreas Rönnquist
 *
 *	FreeDungeon is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FreeDungeon is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with FreeDungeon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// #include <boost/shared_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"

#include "GusGame/EventLib.h"
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

#include "GusGui/GusGui.h"

using namespace GusGui;

#include "Items/Item.h"

#include "Gui/TextButton.h"

#include "Gui/MiniMap.h"
#include "Gui/MainMenuPanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/ItemTextPanel.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/GamePanel.h"

#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateExplore.h"

#include "GameStates/GameStateHandler.h"

#include "GameEventHandler.h"

#include "Global.h"

#include "Data.h"

#include "Dungeon/DungeonData.h"


#include "Items/Item.h"
#include "Items/ItemHandler.h"

#include "MousePointer.h"

#include "Characters/CharacterHandler.h"


/**
 * main - the standard c++ program main entry point
 */
int main(int argc, char **argv)
{
	// Global::globalEventHandler = std::shared_ptr<GlobalEventHandler>();
	
	GraphicsLib::Font *font = nullptr;
	// std::vector<GuiObjectPtr> *guiList = NULL;

	// std::shared_ptr<GuiObject> panel; // = boost::shared_ptr<ExamplePanel>();

	try {
		// init the log - this function takes a string (the log file filename) as
		// indata, if none is inserted, "log.txt" is assumed. If you give the
		// empty string "" as filename for the log, no log will be used.
		//
		// The second indata is a boolean to determine to print the log to
		// std::cout or not in addition to to the file.
		LogHandler::initLog("log.txt", true);

		// init system stuff
		System::initSystem();

      FileHelper::addDataFolder("script/");
      FileHelper::addDataFolder("../script/");
      FileHelper::addDataFolder("../../script/");

		// set up a screen with resolution of 640x480, and not fullscreen
		GraphicsHandler::instance().initGraphicsHandler();
		GraphicsHandler::instance().setGraphicsMode(Vector2d(1280, 800), Vector2d(640, 400), false, false);
		//GraphicsHandler::instance().setGraphicsMode(Vector2d(320, 200), Vector2d(320, 200), false, false);
      
		Primitives::initPrimitives();

		// set a window title
		GraphicsHandler::instance().setWindowTitle("Dungeon");

		FontHandler::initFontHandler();

      LOG("Load data");
      Data::instance();
      
      EventSystem::initEventSystem();
      
      MousePointer::instance().initMouse();




		font = new GraphicsLib::Font("FreeSans.ttf", 12, true);
      

		GuiData::setGuiFont(font);

		// userEvent = new UserEvent();

		// This must be initialized before the Examplepanel
		// EventData::instance();

		//guiList=new std::vector<boost::shared_ptr<GuiObject> >;
		// panel = std::make_shared<MainMenuPanel>();

		//guiList->push_back((GuiObject*)panel);
		//guiList->push_back(panel);
      
      /* ---------------------*/
		// GuiHandler::instance()->addGuiObject(panel);

		EventSystem::initEventSystem();

		// Create an EventHandler for our "custom" events
		// which inherits from the GUI event handler, this for it
		// to handle both GUI events, and our own custom ones for
		// just this example
		//eventHandler = boost::shared_ptr<EventHandler>(new ExampleEventHandler());
		// GlobalEventHandler::instance();
      Global::gameEventHandler  = std::make_shared<GameEventHandler>();

      LOG("Add global event handler");
      EventSystem::addEventHandler(Global::gameEventHandler);      
      
      LOG("-----------------------");
      LOG("Init game mode handler");
      
      ItemHandler::instance().initItemHandler();
      CharacterHandler::instance().initCharacterHandler();
      
      GameModeHandler::instance().initGameModeHandler();
      
      DungeonData::instance();

	}
	catch (Exception &e)
	{
		// If we get any problems with the code in the throw block, it will be
		// caught here
		std::cerr << "Exception: " << e.getString() << std::endl;

		return EXIT_FAILURE;
	}

	LOG("Enter main loop.");

	// the main loop
	do {
		// Update the timer
		Timer::updateFrame();

		GuiHandler::instance()->update();

		// Handle events (see the class just above this main
		//EventHelper::instance()->handleEvents();
		EventSystem::handleEvents();

		// Clear the screen every sync
		GraphicsHandler::instance().clearScreen();

		GuiHandler::instance()->draw();

		/*
		// Draw the mouse cursor
		System::instance()->getMouse()->draw();
		*/
      
      MousePointer::instance().draw();

		// Update the screen
		GraphicsHandler::instance().updateScreen();
	} while(!Global::quit);

	LOG("All done...");

	EventSystem::removeEventHandler(Global::gameEventHandler);
   
   GameModeHandler::instance().doneGameModeHandler();

	// mainMenuEventHandler.reset();
   // GlobalEventHandler::instance()->destroy();
   Global::gameEventHandler.reset();

	delete font;

	// delete userEvent;
   
   ItemHandler::instance().doneItemHandler();
   
   CharacterHandler::instance().doneCharacterHandler();


	GuiHandler::destroy();

	Primitives::donePrimitives();

   MousePointer::instance().doneMouse();
   
   DungeonData::instance().doneDungeonData();
   
   Data::instance().doneDataHandler();
   
   // kill the font handler
   FontHandler::doneFontHandler();
   
   GraphicsHandler::instance().doneGraphicsHandler();
   
   EventSystem::doneEventSystem();

	// done with system stuff
	System::doneSystem();

	// done with the Log
	LogHandler::doneLog();

	return EXIT_SUCCESS;
}
