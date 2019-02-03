#pragma once
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"

class AudioManager : public BaseSingleton<AudioManager>
{
private:

public:
#pragma region GAME_FLOW_FUNCS

	void Initialize();

#pragma endregion GAME_FLOW_FUNCS

private:
	friend BaseSingleton;
	AudioManager();

#pragma region EVENT_HANDLERS

	void OnRequestPlaySoundReceived(IEventDataPtr _event);

#pragma endregion EVENT_HANDLERS
};