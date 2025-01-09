#pragma once
#include "pch.h"
#include "editor/entity.h"
#include "editor/EntityHandler.h"
#include "editor/maths/ray_intersection.h"  // For the ray-AABB intersection function

namespace Editor {

    class IntersectionHandler {
    public:
        // Constructor that takes the entity handler to work with
        IntersectionHandler(EntityHandler* entityHandler)
            : mEntityHandler(entityHandler) {
        }

        // Method to check intersection with entities in the handler
        //bool CheckIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_direction) {
        //    // Iterate through all entities managed by the handler
        //    for (auto& entity : mEntityHandler->getEnitInfo() {
        //        // Access the TransformComponent of the entity (ensure it's valid)
        //        auto* transform = entity->GetComponent<TransformComponent>();
        //        if (!transform) continue;  // Skip if no TransformComponent exists

        //        // Get the entity position (assuming a TransformComponent exists)
        //        glm::vec3 entity_position = transform->GetPosition();
        //        float entity_size = 1.0f;  // Assume a size for the entity (this can vary based on the entity)

        //        // Define the AABB's min and max points based on the entity's position and size
        //        glm::vec3 min = entity_position - glm::vec3(entity_size);
        //        glm::vec3 max = entity_position + glm::vec3(entity_size);

        //        // Use the Math::intersect_ray_aabb function from maths.h
        //        if (Math::intersect_ray_aabb(ray_origin, ray_direction, min, max)) {
        //            // If the ray intersects with the AABB of the entity, return true
        //            return true;
        //        }
        //    }

        //    // Return false if no intersection was found
        //    return false;
        //}

    private:
        Editor::EntityHandler* mEntityHandler = nullptr;  // Store the reference to the EntityHandler
    };

}
