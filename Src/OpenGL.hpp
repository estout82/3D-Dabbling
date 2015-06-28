//
//  OpenGL.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef OPENGL_HPP
#define OPENGL_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#else // (NOT) __APPLE__
#include <GL/glew.h>

#endif // __APPLE__

#endif // OPENGL_HPP