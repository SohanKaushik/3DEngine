#include "pch.h"
#include "EntityHandler.h"

void Editor::EntityHandler::update(Shader& shader)
{
	this->RenderEntities(shader);


	// Entities Manipulations
	// for example
	//entities[0]->GetComponent<Editor::TransformComponent>()->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	//entities[0]->AddComponent<TransformComponent>().SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	//entities[0]->AddComponent<MeshComponent>().loadMesh("Resource Files/Textures/monkey.obj");
};

