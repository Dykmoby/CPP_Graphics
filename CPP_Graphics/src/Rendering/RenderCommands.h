#pragma once
#include "SFML/Graphics.hpp"

struct SpriteDrawCommand 
{
public:
	sf::Sprite sprite;
public:
	SpriteDrawCommand(sf::Sprite sprite) : sprite(sprite) {};
};

struct TextDrawCommand
{
public:
	sf::Text text;
public:
	TextDrawCommand(sf::Text text) : text(text) {};
};