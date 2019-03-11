#include "MusicComponent.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"

MusicComponent::MusicComponent(Gameobject* _owner) :
	BaseComponent(_owner)
{

}

MusicComponent::~MusicComponent()
{

}

/**
	Called before any updates are run. Used for initialization.
 */
void MusicComponent::Start()
{

}

void MusicComponent::Update()
{

}

/**
	Stops all music and destroys them
 */
void MusicComponent::Shutdown()
{
	//Iterate throug music list, stop and delete all sf::Music pointers.
	for (MusicClipList::iterator it = musicClipList.begin(); it != musicClipList.end(); ++it)
	{
		it->second->stop();

		delete it->second;
		it->second = nullptr;
	}
}

/**
	Plays the music file identified by clip name.
 */
void MusicComponent::PlayMusic(std::string _clipName)
{
	sf::Music* musicToPlay = musicClipList[_clipName];

	//post GO created event
	std::shared_ptr<EvtData_On_Request_Stream_Music> pEvent(new EvtData_On_Request_Stream_Music(musicToPlay));
	EventManager::Instance()->QueueEvent(pEvent);
}

/**
	Stops the music file identified by clip name.
 */
void MusicComponent::StopMusic(std::string _clipName)
{
	musicClipList[_clipName]->stop();
}

/**
	Adds a music clip to the list of clips
 */
void MusicComponent::AddMusicClip(std::string _musicNameId, std::string _filePath)
{
	sf::Music* musicClip = new sf::Music();

	if (!musicClip->openFromFile(_filePath))
	{
		std::runtime_error("Could not locate music file.");
		return;
	}

	musicClipList.insert(std::pair<std::string, sf::Music*>(_musicNameId, musicClip));
}
