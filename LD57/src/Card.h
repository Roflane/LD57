#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
#include "settings/GlobalSettings.h"

#include "../base/typedefs.h"
#include "../base/misc.h"
#include "../base/dirs.h"

struct CardState {
	bool isActive;
	bool isHold;
	bool isSelected;
};

class Card {
private:	
	// Fields
	const char* _spritePath;
	Texture2D _sprite;
	Vector2 _pos;
	CardState _cardState;
	int _power;
	bool _exists;
	//std::vector<Card> _cards;
public:
	Card(const char* spritePath, Vector2 pos, int cardPower);
	/*Card(const std::vector<Card> &cardsCollection);*/

	// Properties
	const char* getSpritePath() const { return _spritePath; }

	Vector2 getPos() const { return _pos; }
	Texture2D getSprite() const { return  _sprite; }
	Rectangle getRect() const { return Rectangle(_pos.x, _pos.y, _sprite.width, _sprite.height); }

	void setPosX(float posX)  { _pos.x = posX; }
	void setPosY(float posY)  { _pos.y = posY; }

	float getW() const { return _sprite.width; }
	void setW(float value) { _sprite.width = value; }

	float getH() const { return _sprite.height; }
	void setH(float value) { _sprite.height = value; }

	bool get_isActive() const	  { return _cardState.isActive; }
	void set_isActive(bool value) { _cardState.isActive = value; }

	bool get_isHold() const		{ return _cardState.isHold; }
	void set_isHold(bool value) { _cardState.isHold = value; }

	bool get_isSelected() const		{ return _cardState.isSelected; }
	void set_isSelected(bool value) { _cardState.isSelected = value; }

	int  getPower() const	 { return _power; }
	void setPower(int value) { _power = value; }
	// Methods
	void draw(Color number, Color active);
	void update(Vector2 pos);
	
	void checkCursor(ushort mx, ushort my);
	bool dragCard(ushort mx, ushort my);
	bool select(ushort mx, ushort my);

	void destroy(Card &card);
	bool attack(Card &enemy);
};