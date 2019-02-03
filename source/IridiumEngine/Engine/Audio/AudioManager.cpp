#include "AudioManager.h"
#include <SFML/Audio.hpp>

/**
	Initializer for audio manager. Used to set up the manager.
 */
void AudioManager::Initialize()
{
	//Sbscribe to request audio player event
	EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &AudioManager::OnRequestPlaySoundReceived);
	EventManager::Instance()->AddListener(delegateFunc, EvtData_On_Request_Play_Sound::eventType);
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
	pCastEventData->GetSoundClip().play();
}
