#include "LoadingScreen.hpp"

#include "Filepaths.h"
#include "Settings.h"
#include "Colors.h"

LoadingScreen::LoadingScreen(SceneManager::SCENES  _nextScene) : Scene()
{
	this->m_nextScene = _nextScene;
	this->m_loadingText = "Loading...";
	this->m_loading = true;
	this->m_lastTime = 0;
	this->m_currentTime = 0;
	this->m_delay = 0;
	this->m_changeScene = false;
}

LoadingScreen::~LoadingScreen()
{
	m_helper->SDL_DestroyTexture(m_loadingBG);
	m_helper->SDL_DestroyFont(m_font);
}

void LoadingScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_helper->SDL_LoadImage(&this->m_loadingBG, IMG_BG_LOADING);
	this->m_helper->SDL_PauseMusic();
}

void LoadingScreen::Draw()
{
	this->m_helper->SDL_DrawImage(this->m_loadingBG, 0, 0);
	this->m_helper->SDL_DrawText(1100, 670, 15, WHITE, m_loadingText.c_str());
}

void LoadingScreen::Update()
{
	if (this->m_loading)
	{
		this->m_currentTime = SDL_GetTicks();

		if (this->m_currentTime > m_lastTime + 1000)
		{
			++this->m_delay;
			if (this->m_delay >= LOADING_DELAY)
			{
				this->m_loading = false;
				this->m_changeScene = true;
			}
			else
			{
				this->m_lastTime = this->m_currentTime;
			}				
		}
	}

	if (this->m_changeScene)
		NextScene();
}

void LoadingScreen::CheckInputs(u64 kDown, u64 kHeld)
{
	// While we are in Loading Screen we DON'T need any input 
	//if (kDown & KEY_A)
	//	SceneManager::Instance()->SetActualScene(m_nextScene);
}

// * We go to the next scene = GameScreen
void LoadingScreen::NextScene()
{
	m_helper->SDL_SetMusicVolume(MIX_MAX_VOLUME);
	SceneManager::Instance()->SetActualScene(this->m_nextScene);
}

