#pragma once
#include "pch.h"

namespace Math {

    // Check if a ray intersects with an AABB
    bool intersect_ray_aabb(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& min, const glm::vec3& max) {
        float tmin = (min.x - ray_origin.x) / ray_direction.x;
        float tmax = (max.x - ray_origin.x) / ray_direction.x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (min.y - ray_origin.y) / ray_direction.y;
        float tymax = (max.y - ray_origin.y) / ray_direction.y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if (tmin > tymax || tymin > tmax) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (min.z - ray_origin.z) / ray_direction.z;
        float tzmax = (max.z - ray_origin.z) / ray_direction.z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if (tmin > tzmax || tzmin > tmax) return false;

        return true;
    }

}
