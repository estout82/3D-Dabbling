//
//  MeshNode.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/30/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef MESH_NODE_H
#define MESH_NODE_H

#include <vector>
#include <assimp/mesh.h>
#include "Texture.hpp"
#include "VertexArrayObject.hpp"

class MeshNode
{
public:
    MeshNode();
    MeshNode(const MeshNode& meshNode);
    
    ~MeshNode();
    
    bool create(const std::vector<Vertex>& vertecies,
                const std::vector<unsigned int>& indicies);
    bool create(const aiMesh* mesh);
    
    void dispose();
    
    void render();
    
private:
    VertexBuffer m_vertexBuffer;
    ElementBuffer m_elementBuffer;
};

#endif // MESH_NODE_HPP