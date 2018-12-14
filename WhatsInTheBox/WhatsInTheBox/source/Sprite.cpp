#include "Sprite.hpp"
#include "Filepaths.h"
#include "Settings.h"

void Sprite::Draw(SDL_Helper * _helper)
{
	if (this->m_multipleFrames)
		_helper->SDL_DrawImageRect(this->m_sprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX, this->m_currentFrameY * this->m_sizePerFrameY, this->m_sizePerFrameX, this->m_sizePerFrameY);
	else
		_helper->SDL_DrawImage(this->m_sprite, this->m_x, this->m_y);
}

void Sprite::Update()
{
	if (this->m_multipleFrames)
	{
		Uint32 ticks = SDL_GetTicks();
		this->m_currentFrameX = (ticks / 200) % this->m_numFrames;
	}
}

void Sprite::MoveToCoord(int _x, int _y)
{
	this->m_x = _x;
	this->m_y = _y;
}

void Sprite::MoveX(int _value)
{
	if ((_value > 0 && m_x + _value <= SWITCH_SCREEN_WIDTH) || (_value < 0 && m_x + _value >= 0))
		this->m_x += _value;
}

void Sprite::MoveY(int _value)
{
	if ((_value > 0 && this->m_y + _value <= SWITCH_SCREEN_HEIGHT) || (_value < 0 && this->m_y + _value >= 0))
		this->m_y += _value;
}

SDL_Texture * Sprite::GetSprite()
{
	return this->m_sprite;
}

void Sprite::SetSprite(SDL_Texture * _sprite)
{
	this->m_sprite = _sprite;
}


void Sprite::SetX(int _value)
{
	this->m_x = _value;
}

int Sprite::GetX()
{
	return this->m_x;
}

void Sprite::SetY(int _value)
{
	this->m_y = _value;
}

int Sprite::GetY()
{
	return this->m_y;
}

void Sprite::End(SDL_Helper * _helper)
{
	if (this->m_sprite != NULL)
		_helper->SDL_DestroyTexture(this->m_sprite);
}


void Sprite::SetNumFrames(int _value)
{
	this->m_numFrames = _value;
	this->m_currentFrameX = 0;
}

int Sprite::GetNumFrames()
{
	return this->m_numFrames;
}

void Sprite::SetFrameSize(int _value, bool _xAxis)
{
	if (_xAxis)
		this->m_sizePerFrameX = _value;
	else
		this->m_sizePerFrameY = _value;
}

int Sprite::GetFrameSize(bool _xAxis)
{
	if (_xAxis)
		return this->m_sizePerFrameX;
	else
		return this->m_sizePerFrameY;
}

bool Sprite::Touched(touchPosition _touch)
{
	return (_touch.px > this->m_x && _touch.px < this->m_x + this->m_sizePerFrameX) && (_touch.py > this->m_y && _touch.py < this->m_y + this->m_sizePerFrameY);
}