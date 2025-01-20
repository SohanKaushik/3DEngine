#include "mesh.h"
#include "shader/shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace elems {

    // Constructor for primitives
    Mesh::Mesh(PrimitiveType type){

        this->set_prim(type);
        this->o_data();
        mBuffer->create(m_vertices, m_indices);
    }

    // Load mesh using Assimp
    bool Mesh::load(const std::string& filepath) {
        // Define Assimp import flags
        const uint32_t cMeshImportFlags =
            aiProcess_CalcTangentSpace | // Calculate tangent space for normal mapping
            aiProcess_Triangulate |       // Triangulate meshes for rendering
            aiProcess_GenNormals;         // Generate normals for meshes

        Assimp::Importer Importer;
        const aiScene* pScene = Importer.ReadFile(filepath.c_str(), cMeshImportFlags);

        if (!pScene || !pScene->HasMeshes()) {
            // Log error and return false
            std::cerr << "Error: Unable to load mesh from file [" << filepath << "]." << std::endl;
            std::cerr << "Assimp Error: " << Importer.GetErrorString() << std::endl;
            return false;
        }

        // Clear existing vertex and index data
        m_vertices.clear();
        m_indices.clear();

        // Get the first mesh in the scene
        auto* mesh = pScene->mMeshes[0];
        if (!mesh->mVertices || !mesh->mFaces) {
            // Log error and return false
            std::cerr << "Error: Mesh is missing essential data (vertices or faces)." << std::endl;
            return false;
        }

        // Load vertex data
        for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
            VertexHolder vh;
            vh.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vh.normal = mesh->mNormals ?
                glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z } : glm::vec3(0.0f);
            m_vertices.push_back(vh);
        }

        // Load index data
        for (size_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; j++) {
                m_indices.push_back(face.mIndices[j]);
            }
        }

        // Create vertex/index buffer
        if (!mBuffer) {
            mBuffer = std::make_unique<render::VertexIndexBuffer>();
        }
        // Create vertex/index buffer
        if (!mBuffer) {
            mBuffer = std::make_unique<render::VertexIndexBuffer>();
        }
        try {
            mBuffer->create(m_vertices, m_indices);
        }
        catch (const std::exception& e) {
            // Log error and return false
            std::cerr << "Error: Failed to create vertex/index buffer." << std::endl;
            std::cerr << "Exception: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

    void Mesh::proc_nodes(aiNode* node, const aiScene* scene) {
        // Process all meshes in the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            this->proc_mesh(mesh, scene);
        }

        // Recursively process child nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            this->proc_nodes(node->mChildren[i], scene); 
        }
    }

    void Mesh::proc_mesh(aiMesh* mesh, const aiScene* scene) {
        std::cout << "Processing mesh: " << mesh->mName.C_Str() << std::endl;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            glm::vec3 position(
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            );

            glm::vec3 normal(0.0f);
            if (mesh->mNormals) {  // Check before accessing
                normal = glm::vec3(
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                );
            }

            glm::vec2 texCoords(0.0f);
            if (mesh->mTextureCoords[0]) {  // Check before accessing
                texCoords = glm::vec2(
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                );
            }

            // Print the VertexHolder data
            std::cout << "VertexHolder " << i << ": Position: ("
                << position.x << ", " << position.y << ", " << position.z
                << "), Normal: (" << normal.x << ", " << normal.y << ", " << normal.z
                << "), TexCoords: (" << texCoords.x << ", " << texCoords.y << ")" << std::endl;
        }

    }

    void Mesh::o_data() {
        unsigned int vertices = m_vertices.size();
        unsigned int faces = m_indices.size() / 3;
        unsigned int edges = (3 * faces) / 2;
        unsigned int triangle = m_indices.size() / 3;

        std::cout << " |" << std::endl;
        std::cout << "Vertices : [" << vertices << "]" << std::endl;
        std::cout << "Faces : [" << faces << "]" << std::endl;
        std::cout << "Edges : [" << edges << "]" << std::endl;
        std::cout << "Triangles : [" << triangle << "]" << std::endl;
    }

    void Mesh::set_prim(PrimitiveType type) {

        switch (type) {
        case PrimitiveType::cube:
            m_primtv->cube();
            break;
        case PrimitiveType::plane:
            m_primtv->plane();
            break;
        case PrimitiveType::sphere:
            std::cerr << "Sphere is not implemented yet.\n";
            return;
        default:
            throw std::runtime_error("Unsupported PrimitiveType!");
        }
        m_vertices = m_primtv->get_vertx();
        m_indices = m_primtv->get_indices();
    }

    // Render the mesh
    void Mesh::draw() {
        mBuffer->bind();
        mBuffer->draw(GL_TRIANGLES);
        mBuffer->unbind();
    }

} // namespace elems
