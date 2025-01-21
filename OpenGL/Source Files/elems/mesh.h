#pragma once

#include "pch.h"
#include "render/VertexIndexBuffer.h"
#include "elems/Primitive.h"
#include "shader/shader.h"

#include "assimp/scene.h"
#include "render/vertex_holder.h"
#include "vector"

namespace elems {

    enum class PrimitiveType {
        cube,
        plane,
        sphere,
        monkey
    };

    class Mesh {
    public:

        Mesh(PrimitiveType type);
        Mesh() = default;


        void proc_nodes(aiNode* node, const aiScene* scene);
        void proc_mesh(aiMesh* mesh, const aiScene* scene);

        void comp_mesh_data();
        void initialize_primitive(PrimitiveType type);

        void load(const std::string& path);
        void draw();

    private:

        std::unique_ptr<render::VertexIndexBuffer> mBuffer = std::make_unique<render::VertexIndexBuffer>();
        std::unique_ptr<elems::Primitive> m_primtv;
                                                  
    
        std::vector<VertexHolder> m_vertices;       // Vertex data
        std::vector<unsigned int> m_indices;        // Index data
    };
}