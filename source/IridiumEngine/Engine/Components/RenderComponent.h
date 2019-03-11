#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"

class RenderComponent : public BaseComponent
{
private:
	bool isRendered;
	sf::Sprite sprite;
	sf::Texture texture;

private:
	void LoadDefaultTexture();

public:
	RenderComponent(Gameobject* _owner, bool _isRendered = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	sf::Sprite& GetSprite();

	void SetTexture(std::string _filePath);

	inline void SetVisibility(bool _isRendered) { isRendered = _isRendered; }
	inline bool GetVisibility() const { return isRendered; }


};