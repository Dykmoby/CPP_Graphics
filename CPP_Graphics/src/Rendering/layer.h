#pragma once
#include "SFML/Graphics.hpp"

enum LayerType {
	IMAGE,
	TEXTURE,
	SPRITE,
	TEXT
};

class Layer {
public:
	virtual ~Layer() {}
	virtual LayerType getType() const = 0;
};

class LayerImage : public Layer {
public:
	LayerImage(sf::Image image) : image(image) {};
	LayerType getType() const override {
		return LayerType::IMAGE;
	}
	sf::Image image;
};

class LayerTexture : public Layer {
public:
	LayerTexture(sf::Texture texture) : texture(texture) {};
	LayerType getType() const override {
		return LayerType::TEXTURE;
	}
	sf::Texture texture;
};

class LayerSprite : public Layer {
public:
	LayerSprite(sf::Sprite sprite) : sprite(sprite) {};
	LayerType getType() const override {
		return LayerType::SPRITE;
	}
	sf::Sprite sprite;
};

class LayerText : public Layer {
public:
	LayerText(sf::Text text) : text(text) {};
	LayerType getType() const override {
		return LayerType::TEXT;
	}
	sf::Text text;
};