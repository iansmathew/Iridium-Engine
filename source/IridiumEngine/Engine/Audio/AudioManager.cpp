#include "AudioManager.h"
#include <SFML/Audio.hpp>

/**
	Initializer for audio manager. Used to set up the manager.
 */
void AudioManager::Initialize()
{
	//Sbscribe to request audio player event
	EventListenerDelegate soundDelegateFunc = fastdelegate::MakeDelegate(this, &AudioManager::OnRequestPlaySoundReceived);
	EventManager::Instance()->AddListener(soundDelegateFunc, EvtData_On_Request_Play_Sound::eventType);

	EventListenerDelegate musicDelegateFunc = fastdelegate::MakeDelegate(this, &AudioManager::OnRequestPlayMusicReceived);
	EventManager::Instance()->AddListener(musicDelegateFunc, EvtData_On_Request_Stream_Music::eventType);
}

/**
	Constructor for the audio manager
 */
AudioManager::AudioManager()
{

}

/**
	Event handler func that runs when a request to play a particular sound file is received
 */
void AudioManager::OnRequestPlaySoundReceived(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_Request_Play_Sound> pCastEventData = std::static_pointer_cast<EvtData_On_Request_Play_Sound>(_event);
	pCastEventData->GetSound()->play();

}

/**
	Event handler func that runs when a request to play an sf::Music is received
 */
void AudioManager::OnRequestPlayMusicReceived(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_Request_Stream_Music> pCastEventData = std::static_pointer_cast<EvtData_On_Request_Stream_Music>(_event);
	pCastEventData->GetMusic()->play();
}
