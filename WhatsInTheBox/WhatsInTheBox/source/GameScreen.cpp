#include "GameScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"
#include "Settings.h"
#include <cmath>

GameScreen::GameScreen(int _taps) : Scene()
{
	this->m_taps = _taps;
	this->m_changeScene = false;
	this->m_tapsStr = "Taps: 0";
	this->m_currentBackground = 0;

}

GameScreen::~GameScreen()
{
	this->m_helper->SDL_DestroyTexture(this->m_backgroundA);
	this->m_helper->SDL_DestroyTexture(this->m_backgroundB);
	this->m_helper->SDL_DestroyTexture(this->m_backgroundC);
	this->m_helper->SDL_DestroyTexture(this->m_backgroundD);
	this->m_helper->SDL_DestroyTexture(this->m_endBoard);

	this->m_helper->SDL_DestroyMusicAudio(m_gameBGM);
	this->m_helper->SDL_DestroySound(m_tapSFX);

	this->m_player->End(this->m_helper);
	delete(m_player);
}

void GameScreen::Start(SDL_Helper * helper)
{

	m_player = new Box(435, 215, helper, true, 5, 450, m_taps);

	this->m_helper = helper;
	this->m_helper->SDL_LoadImage(&this->m_backgroundA, IMG_BG_GAME);
	this->m_helper->SDL_LoadImage(&this->m_backgroundB, IMG_BG_GAME_B);
	this->m_helper->SDL_LoadImage(&this->m_backgroundC, IMG_BG_GAME_C);
	this->m_helper->SDL_LoadImage(&this->m_backgroundD, IMG_BG_GAME_D);
	this->m_helper->SDL_LoadImage(&this->m_endBoard, IMG_BOARD);
	this->m_helper->SDL_LoadMusicAudio(&this->m_gameBGM, SND_BGM_GAME);
	this->m_helper->SDL_LoadSound(&this->m_tapSFX, SND_SFX_TAP);

	this->m_helper->SDL_ResumeMusic();
	this->m_helper->SDL_PlayMusicAudio(m_gameBGM);
	CheckBG();
}

void GameScreen::EndGame()
{
	this->m_changeScene = true;
}

void GameScreen::Draw()
{
	if (m_currentBackground == 0)
		this->m_helper->SDL_DrawImage(this->m_backgroundA, 0, 0);
	else if (m_currentBackground == 1)
		this->m_helper->SDL_DrawImage(this->m_backgroundB, 0, 0);
	else if (m_currentBackground == 2)
		this->m_helper->SDL_DrawImage(this->m_backgroundC, 0, 0);
	else
		this->m_helper->SDL_DrawImage(this->m_backgroundD, 0, 0);

	if (this->m_ended)
	{
		this->m_helper->SDL_DrawImage(this->m_endBoard, 0, 0);
	}
	else
	{
		this->m_helper->SDL_DrawText(100, 100, 25, WHITE, this->m_tapsStr.c_str());
		this->m_player->Draw(m_helper);
	}
}

void GameScreen::Update()
{
	m_player->Update();
	if (this->m_changeScene)
		NextScene();
}

void GameScreen::AddTap()
{
	if (!m_muted)
		this->m_helper->SDL_PlaySound(m_tapSFX, 2);

	++this->m_taps;
	this->m_tapsStr = "Taps: " + std::to_string(this->m_taps);
	m_player->AddTap();
	CheckBG();
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld)
{
	if (kDown & KEY_A)
		AddTap();

	if (kDown & KEY_TOUCH)
	{
		u32 i;
		hidTouchRead(&touch, i);
		if (m_player->Touched(touch))
			AddTap();
	}

	if (kDown & KEY_R && kDown & KEY_L)
		ResetGame();

	if (kDown & KEY_MINUS)
	{
		if (kDown & KEY_L)
		{
			PlayBGM();
		}
		else
		{
			if (this->m_muted)
				ResumeBGM();
			else
				PauseBGM();
		}
	}

	if (kDown & KEY_PLUS)
		EndGame();
}

// * We go to the next scene = GameScreen
void GameScreen::NextScene()
{	
	SceneManager::Instance()->ExitGame();
}

void GameScreen::CheckBG()
{
	if (m_currentBackground < 1 && m_taps >= FIRSTSTAGE && m_taps < SECONDSTAGE)
	{
		m_currentBackground = 1;
	}
	else if (m_currentBackground < 2 && m_taps >= SECONDSTAGE && m_taps < THIRDSTAGE)
	{
		m_currentBackground = 2;
	}
	else if (m_currentBackground < 3 && m_taps >= THIRDSTAGE && m_taps < OPENEDTAP)
	{
		this->m_currentBackground = 3;
		this->m_ended = true;
	}
	else if (m_currentBackground < 4 && m_taps >= OPENEDTAP)
	{
		ResetGame();
	}
}

void GameScreen::ResetGame()
{
	this->m_ended = false;
	this->m_taps = 0;
	this->m_tapsStr = "Taps: " + std::to_string(this->m_taps);
	this->m_currentBackground = 0;
	this->m_player->Reset();
}

void GameScreen::PauseBGM()
{
	if (!this->m_muted)
	{
		this->m_muted = true;
		this->m_helper->SDL_PauseMusic();
	}
}
void GameScreen::ResumeBGM()
{
	if (this->m_muted)
	{
		this->m_muted = false;
		this->m_helper->SDL_ResumeMusic();
	}
}

void GameScreen::PlayBGM()
{
	this->m_muted = false;
	this->m_helper->SDL_ResumeMusic();
	this->m_helper->SDL_PlayMusicAudio(m_gameBGM);
}