#pragma once
#include "BaseComponent.h"
#include <SFML/Audio.hpp>
#include <map>
#include <string>

struct SoundClip
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

//Typedefs
typedef std::map<std::string, SoundClip*> SoundClipList;

class AudioComponent : public BaseComponent
{
private:
	SoundClipList soundClipList;

public:
	AudioComponent(Gameobject* _owner);
	~AudioComponent();

	void Start();

	void PlaySound(std::string _clipName);

	void AddSoundClip(std::string _soundNameId, std::string _filePath);
};