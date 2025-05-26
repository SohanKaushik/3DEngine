#pragma once

#include "pch.h"

namespace Engine {

	namespace Maths {

		class Ray {
			glm::vec3 _direction;
			glm::vec3 _origin;
			float _distance;

		public:
			Ray() = default;
			Ray(const glm::vec3& _origin, const glm::vec3& _dir) : _origin(_origin), _direction(_dir)
			{}

			glm::vec3 GetPoint(float distance = 1.0f) {
				_distance = distance;
				return _origin + (_direction * _distance);
			}

			std::string toString() {
				
				return glm::to_string(GetPoint(_distance));
			}
		};
	}
}

