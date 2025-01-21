#include "pch.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "render/vertex_holder.h"

namespace elems {

    // Constructor for primitives
    Mesh::Mesh(PrimitiveType type): m_vertices(0), m_indices(0){

        this->initialize_primitive(type);
        mBuffer->create(m_vertices, m_indices);
    }

    // Load mesh using Assimp
    void Mesh::load(const std::string& filepath) {

        //// Define Assimp import flags
        const uint32_t cMeshImportFlags =
          aiProcess_CalcTangentSpace | // Calculate tangent space for normal mapping
          aiProcess_Triangulate |       // Triangulate meshes for rendering
          aiProcess_GenNormals;         // Generate normals for meshes

      Assimp::Importer Importer;

      // Load the file
      const aiScene* pScene = Importer.ReadFile(filepath.c_str(), cMeshImportFlags);

      if (!pScene || !pScene->HasMeshes()) {
          // Log error and return false
          std::cerr << "Error: Unable to load mesh from file [" << filepath << "]." << std::endl;
          std::cerr << "Assimp Error: " << Importer.GetErrorString() << std::endl;
          return ;
      }


      // Access the first mesh in the file
      const aiMesh* mesh = pScene->mMeshes[0];

      // Extract vertices
      m_vertices.clear();
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
          VertexHolder vertex;
          vertex.position[0] = mesh->mVertices[i].x;
          vertex.position[1] = mesh->mVertices[i].y;
          vertex.position[2] = mesh->mVertices[i].z;

          if (mesh->mNormals) {
              vertex.normal[0] = mesh->mNormals[i].x;
              vertex.normal[1] = mesh->mNormals[i].y;
               vertex.normal[2] = mesh->mNormals[i].z;
           }
           else {
               vertex.normal[0] = 0.0f;
               vertex.normal[1] = 0.0f;
               vertex.normal[2] = 0.0f;
           }

           m_vertices.push_back(vertex);
       }

       // Extract indices
       m_indices.clear();
       for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
           const aiFace& face = mesh->mFaces[i];

           // Ensure the face is a triangle
           if (face.mNumIndices == 3) {
               for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                   m_indices.push_back(face.mIndices[j]);
               }
           }
       }
       this->comp_mesh_data();
       if (mBuffer) {
           mBuffer->create(m_vertices, m_indices);
       }
       else {
           std::cerr << "Error: mBuffer is not initialized." << std::endl;
       }
    }

  
    void Mesh::comp_mesh_data() {
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

    void Mesh::initialize_primitive(PrimitiveType type) {

        m_primtv = std::make_unique<elems::Primitive>(); 
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

        if (m_vertices.empty() && m_indices.empty()) {
            return;
        }
        mBuffer->bind();
        mBuffer->draw(GL_TRIANGLES);
        mBuffer->unbind();
    }

} // namespace elems
