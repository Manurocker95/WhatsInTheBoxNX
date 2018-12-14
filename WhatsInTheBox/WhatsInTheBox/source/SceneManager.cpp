#include "SceneManager.hpp"
#include "SplashScreen.hpp"
#include "GameScreen.hpp"
#include "LoadingScreen.hpp"
#include "Colors.h"

SceneManager * SceneManager::instance = NULL;

SceneManager * SceneManager::Instance()
{
	if (instance == NULL)
		instance = new SceneManager;

	return instance;
}

// Scene Manager Data initialization
void SceneManager::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_out = false;
	ReadData();
}

// We read the data from our .sav
void SceneManager::ReadData()
{
	this->m_times_we_have_run_the_program = 1;
	this->m_actualScene = new SplashScreen();
	this->m_actualScene->Start(m_helper);
}

// We set the new scene
void SceneManager::SetActualScene(SCENES _scene)
{
	// We delete the pointer of the actual scene
	delete (this->m_actualScene);

	// We set the new scene
	switch (_scene)
	{
	case SPLASH:
		this->m_actualScene = new SplashScreen();
		break;
	case GAME:
		m_actualScene = new GameScreen(0);
		break;
	}

	this->m_actualScene->Start(m_helper);
}

void SceneManager::LoadScene(SCENES _scene)
{
	// We delete the pointer of the actual scene
	if (this->m_actualScene != NULL)
		delete (this->m_actualScene);

	this->m_actualScene = new LoadingScreen(_scene);
	this->m_actualScene->Start(m_helper);
}

// We call every function needed: Check User inputs, Update the game, and of course, paint everything
void SceneManager::Update()
{
	this->CheckInputs();
	this->m_actualScene->Update();
	this->Draw();
}

// We check if we are exiting
bool SceneManager::IsOut()
{
	return this->m_out;
}

// Simple exiting
void SceneManager::ExitGame()
{
	this->m_out = true;
}

void SceneManager::Draw()
{
	this->m_actualScene->Draw();
}
void SceneManager::CheckInputs()
{
	// Scan all the inputs. This should be done once for each frame
	hidScanInput();

	// hidKeysDown returns information about which buttons have been
	// just pressed in this frame compared to the previous one
	u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	// hidKeysDown returns information about which buttons are being held
	u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

	this->m_actualScene->CheckInputs(kDown, kHeld);
}

// We save and exit the program
void SceneManager::SaveDataAndExit()
{
	this->m_times_we_have_run_the_program++;

	this->m_out = true;
}

void SceneManager::Exit()
{
	delete(this);
}

SDL_Helper * SceneManager::GetHelper()
{
	return this->m_helper;
}