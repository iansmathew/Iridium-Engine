#define _DEBUG
#include "irincludes.h"

#include "Components/AudioComponent.h"
#include "Components/RigidbodyComponent.h"
#include <pybind11/pybind11.h>
#include "Components/BaseComponent.h"
#include "../PyComponent.h"


namespace py = pybind11;


PYBIND11_MODULE(IridiumPython, IridiumModule) {
	py::class_<Gameobject , std::unique_ptr<Gameobject, py::nodelete>>gameobject (IridiumModule, "GameObject");
	gameobject.def_property("Name", &Gameobject::GetName, &Gameobject::SetName);
	gameobject.def_property_readonly("InstanceID", &Gameobject::GetInstanceID);
	gameobject.def_property_readonly("IsActive", &Gameobject::IsActive);

	gameobject.def("HasComponentRenderer", &Gameobject::HasComponent<RenderComponent>);
	gameobject.def("HasComponentAudio", &Gameobject::HasComponent<AudioComponent>);
	gameobject.def("HasComponentMusic", &Gameobject::HasComponent<MusicComponent>);
	gameobject.def("HasComponentRigidbody", &Gameobject::HasComponent<RigidbodyComponent>);
	gameobject.def("HasComponentTransform", &Gameobject::HasComponent<TransformComponent>);
	
	gameobject.def("GetTransform", &Gameobject::GetTransform);
	
	gameobject.def("AddChild", &Gameobject::AddChild);
	gameobject.def("RemoveChild", &Gameobject::RemoveChild);

	//gameobject.def("AddComponentRenderer", &Gameobject::AddComponent<RenderComponent>);
	//gameobject.def("AddComponentAudio", &Gameobject::AddComponent<AudioComponent>, py::arg("GameObject"));
	//gameobject.def("AddComponentMusic", &Gameobject::AddComponent<MusicComponent>, py::arg("GameObject"));
	//gameobject.def("AddComponentRigidbody", &Gameobject::AddComponent<RigidbodyComponent>, py::arg("GameObject"));
	//gameobject.def("AddComponentTransform", &Gameobject::AddComponent<TransformComponent>, py::arg("GameObject"));
	//
	//gameobject.def("GetComponentRenderer", &Gameobject::GetComponent<RenderComponent>);
	//gameobject.def("GetComponentAudio", &Gameobject::GetComponent<AudioComponent>);
	gameobject.def("GetComponentMusic", &Gameobject::GetMusicComponent);
	//gameobject.def("GetComponentRigidbody", &Gameobject::GetComponent<RigidbodyComponent>);
	//gameobject.def("GetComponentTransform", &Gameobject::GetComponent<TransformComponent>);


	py::class_<BaseComponent , PyComponent> baseComponent(IridiumModule, "PyBaseComponent");
	baseComponent.def(py::init<Gameobject*>());
	baseComponent.def("Start", &BaseComponent::Start);
	baseComponent.def("Update", &BaseComponent::Update);
	baseComponent.def("Shutdown", &BaseComponent::Shutdown);
	baseComponent.def("GetGameObject", &BaseComponent::GetGameobject);

	py::class_<MusicComponent>musicComponent (IridiumModule, "MusicComponent" , baseComponent);
	baseComponent.def(py::init<Gameobject*>());
	musicComponent.def("PlayMusic", &MusicComponent::PlayMusic);
	musicComponent.def("StopMusic", &MusicComponent::StopMusic);
	musicComponent.def("AddMusicClip", &MusicComponent::AddMusicClip);

}