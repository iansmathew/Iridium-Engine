#pragma once
#include "BaseComponent.h"
#include <SFML/Audio.hpp>
#include <map>
#include <string>

typedef std::map<std::string, sf::Music*> MusicClipList;

class MusicComponent : public BaseComponent<MusicComponent>
{
private:
	MusicClipList musicClipList;

public:
	MusicComponent(Gameobject* _owner);
	~MusicComponent();

#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;

	virtual void Shutdown() override;

#pragma endregion GAME_FLOW_FUNCS

	void PlayMusic(std::string _clipName);

	void StopMusic(std::string _clipName);

	void AddMusicClip(std::string _musicNameId, std::string _filePath);
};

