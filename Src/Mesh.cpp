//
//  Mesh.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/29/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Mesh.hpp"
#include "MacOSX.hpp"

Mesh::Mesh() :
m_meshNodes()
{
    
}

Mesh::Mesh(const Mesh& mesh) :
m_meshNodes(mesh.m_meshNodes)
{
    
}

Mesh::~Mesh()
{
    // ~m_meshNodes()
    // ~m_vertexArrayObject()
}

bool Mesh::createFromFile(const std::string& path)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(path, aiProcess_GenSmoothNormals | aiProcess_Triangulate);
    
    if (!scene)
        return false;
    
    m_meshNodes.reserve(scene->mNumMeshes);
    
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        MeshNode meshNode;
        
        if (!meshNode.create(scene->mMeshes[i]))
            continue; // MeshNode failed to create so skip to top and loop again
        
        m_meshNodes.push_back(meshNode);
    }
    
    return true;
}

void Mesh::dispose()
{
    // empty
}

void Mesh::render()
{
    for (unsigned int i = 0; i < m_meshNodes.size(); i++)
        m_meshNodes[i].render();
}