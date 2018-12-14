#pragma once
#ifndef _LOADING_SCREEN_HPP_
#define _LOADING_SCREEN_HPP_

#include "Scene.hpp"
#include "SceneManager.hpp"
#include <string>

class LoadingScreen : public Scene
{
private:
	SDL_Texture * m_loadingBG;
	SDL_Texture * m_animatedImg;
	std::string m_loadingText;
	FC_Font * m_font;
	SceneManager::SCENES m_nextScene;


private:
	unsigned int m_lastTime;
	unsigned int m_currentTime;
	bool m_loading;
	int m_delay;
public:

	LoadingScreen(SceneManager::SCENES  _nextScene);	// Constructor
	~LoadingScreen();									// Destructor
	void Start(SDL_Helper * helper) override;			// initialize
	void Draw() override;								// Draw
	void CheckInputs(u64 kDown, u64 kHeld) override;	// CheckInput
	void Update() override;								// Update
	void NextScene() override;
};

#endif