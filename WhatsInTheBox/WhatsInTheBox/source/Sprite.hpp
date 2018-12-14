#pragma once
#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "SDL_Helper.hpp"

class Sprite
{
protected:
	SDL_Texture * m_sprite;
	int m_x;
	int m_y;
	int m_numFrames;
	int m_sizePerFrameX;
	int m_sizePerFrameY;
	int m_currentFrameX;
	int m_currentFrameY;
	int m_secondaryCounter;
	bool m_multipleFrames;

public:
	Sprite() {};
	~Sprite() {};
	virtual void MoveX(int _value);
	virtual void MoveY(int _value);
	virtual void MoveToCoord(int _x, int _y);

	virtual int GetX();
	virtual void SetX(int _value);
	virtual int GetY();
	virtual void SetY(int _value);

	virtual SDL_Texture * GetSprite();
	virtual void SetSprite(SDL_Texture * _sprite);

	virtual void Draw(SDL_Helper * _helper);
	virtual void Update();
	virtual void End(SDL_Helper * _helper);

	virtual void SetNumFrames(int _value);
	virtual int GetNumFrames();
	virtual void SetFrameSize(int _value, bool _xAxis);
	virtual int GetFrameSize(bool _xAxis);

	virtual bool Touched(touchPosition _touch);
};
#endif