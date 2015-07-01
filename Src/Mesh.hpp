//
//  Mesh.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/29/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "MeshNode.hpp"

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh& mesh);
    
    ~Mesh();
    
    bool createFromFile(const std::string& path);
    
    void dispose();
    
    void render();
    
private:
    std::vector<MeshNode> m_meshNodes;
};

#endif // MESH_HPP