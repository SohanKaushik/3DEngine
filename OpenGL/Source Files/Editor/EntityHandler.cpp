#include "pch.h"
#include "EntityHandler.h"

void Editor::EntityHandler::render(Shader& shader) {
	m_tsystem->update(entities, shader);
	m_msytem->update(entities, shader);
}
