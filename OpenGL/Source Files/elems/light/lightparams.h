#pragma once
#include "pch.h"

namespace elems{
	struct LightParams {
		glm::vec3 albedo = glm::vec3(1.0f);
		float strength = 1.0f;

		// for directional light
		glm::vec3 angle = glm::vec3(1.0f);

		// for spotlight


		// for pointlight
	};

}
