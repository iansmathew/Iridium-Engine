#include "AudioComponent.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"

/**
	Constructor for component
 */
AudioComponent::AudioComponent(Gameobject* _owner)
	: BaseComponent(_owner)
{

}

AudioComponent::~AudioComponent()
{

}

/**
	Called before any update is run
 */
void AudioComponent::Start()
{

}

/**
	Iterates through sound list, stop sounds and calls delete on pointers
 */
void AudioComponent::Shutdown()
{
	for (SoundClipList::iterator it = soundClipList.begin(); it != soundClipList.end(); ++it)
	{
		it->second->sound.stop();

		delete it->second;
		it->second = nullptr;
	}
}

/**
	Sends a request to play the given sound clip
 */
void AudioComponent::PlaySound(std::string _clipName)
{
	SoundClip* clipToPlay = soundClipList[_clipName];
	
	//post GO created event
	std::shared_ptr<EvtData_On_Request_Play_Sound> pEvent(new EvtData_On_Request_Play_Sound(&clipToPlay->sound));
	EventManager::Instance()->QueueEvent(pEvent);
}

void AudioComponent::AddSoundClip(std::string _soundNameId, std::string _filePath)
{
	//Create an instance of sound clip that will hold all necessary member
	SoundClip* soundClip = new SoundClip();

	if (!soundClip->buffer.loadFromFile(_filePath))
	{
		std::runtime_error("Could not locate sound file.");
		return;
	}

	//Set buffer 
	soundClip->sound.setBuffer(soundClip->buffer);

	//Add to map
	soundClipList.insert(std::pair<std::string, SoundClip*>(_soundNameId, soundClip));
}
