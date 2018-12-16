#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <string>
#include <fstream>
#include <sstream>
#include "Scene.hpp"


class SceneManager
{
public:

	enum SCENES { SPLASH, GAME, LOADING };	// Scenes: Splashcreen, Gamescreen, Loadingscreen

private:					
	static SceneManager * instance;			// Singleton Instance
	Scene * m_actualScene;					// Scene running
	SDL_Helper * m_helper;					// SDL Helper instance

	int m_taps;								// number of tabs
	bool m_out;								// if we ended or not the program

public:
	static SceneManager * Instance();		// Property to get the singleton instance
	void LoadScene(SCENES _scene);
	void SetActualScene(SCENES _scene);		// Method to set a new scene (E.G: SplashScreen -> GameScreen)
	void Start(SDL_Helper * helper);		// Method for initialization
	void Update();							// Method called every frame. It calls to scene Draw, Update and CheckInput functions
	void Draw();							// Method called every frame. It calls to scene Draw, Update and CheckInput functions
	void CheckInputs();						// Method called every frame. It calls to scene Draw, Update and CheckInput functions
	bool IsOut();							// Method that returns if we are exiting the game from scene (normal exiting)
	void ExitGame(int _taps = -1);			// Method to exit the game (Out = true)
	void ReadData();						// Method for reading data from our save
	void Exit();
	SDL_Helper * GetHelper();

private:
	SceneManager() {};						// Private so that it can  not be called
};

#endif