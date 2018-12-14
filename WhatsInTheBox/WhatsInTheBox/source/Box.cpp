#include "Box.hpp"
#include "Settings.h"
#include "Filepaths.h"

Box::Box (int _x, int _y, SDL_Helper * _helper, bool _multipleFrames, int _numFrames, int _sizePerFrame, int _taps)
{
	this->m_x = _x;
	this->m_y = _y;
	_helper->SDL_LoadImage(&this->m_sprite, IMG_BOX);
	this->m_multipleFrames = _multipleFrames;
	this->m_numFrames = _numFrames;
	this->m_sizePerFrameX = _sizePerFrame;
	this->m_sizePerFrameY = _sizePerFrame;
	this->m_moving = false;
	this->m_currentFrameX = 0;
	this->m_currentFrameY = 0;
	this->m_secondaryCounter = 0;
	this->m_taps = _taps;

	CheckOpen();
}

void Box::CheckOpen()
{
	if (m_taps < FIRSTSTAGE)
	{
		this->m_currentFrameY = 0;
		this->m_state = CLOSED;
	}
	else if (m_taps < SECONDSTAGE && m_taps >= FIRSTSTAGE)
	{
		this->m_currentFrameY = 1;
		this->m_state = SEMI_OPENED;
	}
	else if (m_taps < THIRDSTAGE && m_taps >= SECONDSTAGE)
	{
		this->m_currentFrameY = 2;
		this->m_state = SEMI_SEMI_OPENED;
	}
	else if (m_taps >= THIRDSTAGE && m_taps < OPENEDTAP)
	{
		this->m_currentFrameY = 3;
		this->m_state = ALMOST_OPENED;
	}
	else
	{
		this->m_currentFrameY = 4;
		this->m_state = OPENED;
	}
}

void Box::Reset()
{
	m_taps = 0;
	SetCurrentFrameY(0);
}

void Box::Update()
{
	if (this->m_moving)
	{
		this->m_secondaryCounter++;

		if (this->m_secondaryCounter > FRAMECOUNTER)
		{
			this->m_currentFrameX++;
			this->m_secondaryCounter = 0;
		}

		if (this->m_currentFrameX >= this->m_numFrames)
		{
			this->m_moving = false;
			this->m_currentFrameX = 0;
			CheckOpen();
		}
	}
}

void Box::SetCurrentFrameY(int value)
{
	m_currentFrameY = value;
	m_moving = false;
	m_currentFrameX = 0;
	m_secondaryCounter = 0;
	m_state = static_cast<BOX_STATES>(m_currentFrameY);
}

void Box::Animate()
{
	m_moving = true;
	m_currentFrameX = 0;
	m_secondaryCounter = 0;
}

Box::BOX_STATES Box::GetState()
{
	return this->m_state;
}

void Box::SetState(Box::BOX_STATES value)
{
	this->m_state = value;
}

bool Box::SetMoving(bool value)
{
	this->m_moving = value;
}

void Box::AddTap()
{
	++m_taps;
	Animate();
	CheckOpen();
}