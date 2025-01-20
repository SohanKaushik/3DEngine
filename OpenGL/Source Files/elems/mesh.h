#pragma once

#include "pch.h"
#include "render/VertexIndexBuffer.h"
#include "elems/Primitive.h"
#include "shader/shader.h"

#include "assimp/scene.h"
#include "render/vertex_holder.h"

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

        void proc_nodes(aiNode* node, const aiScene* scene);
        void proc_mesh(aiMesh* mesh, const aiScene* scene);

        void o_data();

        void set_prim(PrimitiveType type);



        bool load(const std::string& path);
        void draw();

    private:

        std::unique_ptr<render::VertexIndexBuffer> mBuffer = std::make_unique<render::VertexIndexBuffer>();
        std::unique_ptr<elems::Primitive> m_primtv = std::make_unique<elems::Primitive>();
        std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
                                                  
    private:
        std::vector<VertexHolder> m_vertices;
        std::vector<unsigned int> m_indices;
    };
}