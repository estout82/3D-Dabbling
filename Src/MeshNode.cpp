//
//  MeshNode.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/30/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include <iostream>
#include "MeshNode.hpp"
#include "OpenGL.hpp"

MeshNode::MeshNode() :
m_vertexBuffer(),
m_elementBuffer()
{
    
}

MeshNode::MeshNode(const MeshNode& meshNode) :
m_vertexBuffer(meshNode.m_vertexBuffer),
m_elementBuffer(meshNode.m_elementBuffer)
{
    
}

MeshNode::~MeshNode()
{
    dispose();
    
    // ~m_vertexBuffer()
    // ~m_elementBuffer()
}

bool MeshNode::create(const std::vector<Vertex>& vertecies,
                      const std::vector<unsigned int>& indicies)
{
    if (!m_vertexBuffer.create(vertecies))
        return false;
    
    if (!m_elementBuffer.create(indicies))
        return false;
    
    return true;
}

bool MeshNode::create(const aiMesh* mesh)
{
    std::vector<Vertex> vertecies;
    vertecies.reserve(mesh->mNumVertices);
    
    const aiVector3D zero(0.0f, 0.0f, 0.0f);
    
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        const aiVector3D* pos = &mesh->mVertices[i];
        const aiVector3D* texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero;
        const aiVector3D* norm = mesh->HasNormals() ? &mesh->mNormals[i] : &zero;
        
        vertecies.push_back(Vertex(Vector3f(pos->x, pos->y, pos->z),
                                   Vector2f(texCoord->x, texCoord->y),
                                   Vector3f(norm->x, norm->y, norm->z)));
    }
    
    std::vector<unsigned int> indicies;
    indicies.reserve(mesh->mNumFaces * 3);
    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace* face = &mesh->mFaces[i];
        
        indicies.push_back(face->mIndices[0]);
        indicies.push_back(face->mIndices[1]);
        indicies.push_back(face->mIndices[2]);
    }
    
    return create(vertecies, indicies);
}

void MeshNode::dispose()
{
    // empty
}

void MeshNode::render()
{
    m_vertexBuffer.bind();
    m_elementBuffer.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)20 );
    
    glDrawElements(GL_TRIANGLES, m_elementBuffer.getNumElements(), GL_UNSIGNED_INT, 0);
    
    m_vertexBuffer.unbind();
    m_elementBuffer.unbind();
}











