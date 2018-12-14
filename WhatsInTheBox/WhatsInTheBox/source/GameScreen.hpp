#pragma once
#ifndef _GAME_SCREEN_HPP_
#define _GAME_SCREEN_HPP_
#include <string>
#include "Scene.hpp"
#include "Box.hpp"

class GameScreen : public Scene
{

private:
	SDL_Texture * m_backgroundA;
	SDL_Texture * m_backgroundB;
	SDL_Texture * m_backgroundC;
	SDL_Texture * m_backgroundD;
	SDL_Texture * m_endBoard;

	Mix_Music * m_gameBGM;
	Mix_Chunk * m_tapSFX;

	Box * m_player;

	int m_taps;
	int m_currentBackground;
	bool m_ended = false;
	bool m_muted = false;

	std::string m_tapsStr;
public:

	GameScreen(int _taps);								// Constructor
	~GameScreen();										// Destructor
	void Start(SDL_Helper * helper) override;			// initialize
	void Draw() override;								// Draw
	void CheckInputs(u64 kDown, u64 kHeld) override;	// CheckInput
	void Update() override;								// Update
	void NextScene() override;
	void AddTap();
	void CheckBG();
	void EndGame();
	void ResetGame();
	void PauseBGM();
	void ResumeBGM();
	void PlayBGM();
};

#endif