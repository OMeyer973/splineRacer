#pragma once
#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

struct Light {
    glm::vec3 intensity;
    glm::vec3 direction;

    Light(glm::vec3 inIntensity, glm::vec3 inDirection) {
        intensity = inIntensity;
        direction = inDirection;
    }
};


struct Material {
    glm::vec3 diffuse;
    glm::vec3 glossy;
    float shininess;

    Material (glm::vec3 inDiffuse, glm::vec3 inGlossy, float inShininess) {
        diffuse = inDiffuse;
        glossy = inGlossy;
        shininess = inShininess;
    }
};

struct PlaneProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    //material input variables
    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //light variables
    GLint uLightIntensity;
    GLint uLightDir_vs;

    GLint uAvionTexture;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionalLight.fs.glsl")) {

        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");

        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");

        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");

        uAvionTexture = glGetUniformLocation(m_Program.getGLId(), "uAvionTexture");
    }
};


#endif
