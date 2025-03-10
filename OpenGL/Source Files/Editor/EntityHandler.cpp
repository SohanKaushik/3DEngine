#include "pch.h"
#include "EntityHandler.h"

void Editor::EntityHandler::update(Shader& shader)
{
	for (const auto& entity : entities) {
		m_tsystem->update(entities);
		m_msytem->update(entities);
		_system->update(entities);

	}

	// Entities Manipulations
	// for example
	//entities[0]->GetComponent<Editor::TransformComponent>()->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	//entities[0]->AddComponent<TransformComponent>().SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	//entities[0]->AddComponent<MeshComponent>().loadMesh("Resource Files/Textures/monkey.obj");
};

