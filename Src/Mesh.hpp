//
//  Mesh.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/29/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>
#include "Math.hpp"
#include "Texture.hpp"
#include "VertexArrayObject.hpp"

class Mesh
{
public:
    Mesh();
    Mesh(const std::string& path);
    
    void create(const std::string& path);
    void create(const std::vector<Vertex>& vertecies,
                const std::vector<unsigned int>& indicies,
                const Texture& texture);
    
    ~Mesh();
    
private:
    struct SubMesh
    {
        SubMesh();
        SubMesh(const std::vector<Vertex>& vertecies,
                const std::vector<unsigned int>& indicies);
        
        ~SubMesh();
        
        Texture m_texture;
        VertexArrayObject m_vao;
    };
    
    void loadFromAiScene(const ai)
};

#endif // MESH_HPP