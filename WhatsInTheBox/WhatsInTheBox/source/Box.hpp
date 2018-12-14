
#pragma once
#ifndef _BOX_HPP_
#define _BOX_HPP_

#include "Sprite.hpp"

class Box : public Sprite
{
public:
	enum BOX_STATES 
	{ 
		CLOSED, 
		SEMI_OPENED, 
		SEMI_SEMI_OPENED, 
		ALMOST_OPENED, 
		OPENED, 
		NONE 
	};

private:

	BOX_STATES m_state;
	bool m_moving;
	int m_taps;

public:	
	Box (int _x, int _y, SDL_Helper * _helper, bool _multipleFrames, int _numFrames, int _sizePerFrame, int _taps);

	void Update() override;

	bool SetMoving(bool _value);
	void Animate();

	Box::BOX_STATES GetState();
	void SetState(Box::BOX_STATES _value);

	void AddTap();
	void Reset();
	void CheckOpen();
	void SetCurrentFrameY(int _value);

};

#endif