/* This file is part of Evolution Saved Me NX!

Copyright (C) 2018/2019 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"

// * Constructor 
SplashScreen::SplashScreen() : Scene()
{
	this->m_splashOpeningState = OPENING;
	this->m_scTimer = 0;
	this->m_splashOpacity = 0;
	this->m_sfxSplash = false;
	this->m_changeScene = false;
}

// * Destructor
SplashScreen::~SplashScreen()
{
	m_helper->SDL_DestroySound(m_SFX);
	m_helper->SDL_DestroyTexture(m_splash);
}

// * Start - We initialize the variables
void SplashScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_helper->SDL_LoadImage(&this->m_splash, IMG_SPLASHSCREEN);
	this->m_helper->SDL_LoadSound(&this->m_SFX, SND_SFX_SPLASH);
}

// * Draw the images every frame
void SplashScreen::Draw()
{
	this->m_helper->SDL_DrawImageOpacity(this->m_splash, 0, 0, this->m_splashOpacity);
}

// * Update game stuff (SplashScreen opacity)
void SplashScreen::Update()
{
	switch (this->m_splashOpeningState)
	{
	case OPENING:

		this->m_splashOpacity += 3;

		if (this->m_splashOpacity >= 255)
		{
			this->m_splashOpacity = 255;
			this->m_splashOpeningState = STAY;

			if (!this->m_sfxSplash)
			{
				this->m_sfxSplash = true;
				this->m_helper->SDL_PlaySound(m_SFX, 2);
			}
		}

		break;
	case STAY:

		this->m_scTimer += 5;

		if (this->m_scTimer >= 300)
		{
			this->m_splashOpeningState = ENDING;
		}

		break;
	case ENDING:

		this->m_splashOpacity -= 3;

		if (this->m_splashOpacity <= 0)
		{
			this->m_changeScene = true;
		}
		break;
	}

	if (this->m_changeScene)
	{
		NextScene();
	}

}

// * We go to the next scene = TitleScreen
void SplashScreen::NextScene()
{
	SceneManager::Instance()->LoadScene(SceneManager::GAME);
}

// * We check the inputs
void SplashScreen::CheckInputs(u64 kDown, u64 kHeld)
{
	if (kDown & KEY_A || kDown & KEY_TOUCH)
	{
		this->m_changeScene = true;
	}
}