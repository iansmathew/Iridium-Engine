#include "Gameobject.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"

/**
	Constructor that sends out the GO_Created event
 */
Gameobject::Gameobject(bool _isRendered /*= true*/)
{
	renderComponent = new RenderComponent(_isRendered);

	//post GO created event
	std::shared_ptr<EvtDat_On_GO_Created> pEvent(new EvtDat_On_GO_Created(this));
	EventManager::Instance()->QueueEvent(pEvent);
}

/**
	Returns the transform component
 */
Transform* Gameobject::GetTransform() const
{
	return transform;
}

/**
	Return the render component
 */
RenderComponent* Gameobject::GetRenderComponent() const
{
	return renderComponent;
}

/**
	Called on engine graphics initialization.
	Used to set up components
 */
void Gameobject::Start()
{
	renderComponent->Start();
}

/**
	Adds a child to the node
	and set the parent node to this.
 */
void Gameobject::AddChild(Gameobject* _child)
{
	_child->parent = this;
	children.push_back(_child);
}

/**
	Calls draw from the window passed into it.
	Also recursively calls draw for its children
 */
void Gameobject::Draw(sf::RenderWindow& _windowRef)
{
	_windowRef.draw(renderComponent->GetSprite());

	for (auto child : children)
	{
		child->Draw(_windowRef);
	}
}