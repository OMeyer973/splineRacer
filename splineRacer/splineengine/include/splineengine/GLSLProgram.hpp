#pragma once

#include <iostream> 
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <splineengine/Settings.hpp>

namespace splineengine {

// Every key player can use
enum FS {NORMAL, TEXTURE, DIRECTIONAL_LIGHT, MULTI_LIGHT};

// GLSL Program with the normal fragment shader
struct NormalProgram {
    glimac::Program _program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    NormalProgram()
        :_program(glimac::loadProgram(Settings::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                                     Settings::instance().appPath().dirPath() + "shaders/normals.fs.glsl"))
    {
        if (debug) std::cout << "Loading normal program" << std::endl;
        uMVPMatrix = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
    }
};

// GLSL Program with the 3D texture fragment shader
struct TextureProgram {
    glimac::Program _program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uTime;

    TextureProgram()
        :_program(loadProgram(Settings::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                             Settings::instance().appPath().dirPath() + "shaders/tex3D.fs.glsl"))
    {
        std::cout << "Loading texture program" << std::endl;
        uMVPMatrix = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(_program.getGLId(), "uTexture");
        uTime = glGetUniformLocation(_program.getGLId(), "uTime");
    }
};

// GLSL Program with the Directional Light fragment shader
struct DirectionalLightProgram {
    glimac::Program _program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    GLint uColor;

    DirectionalLightProgram()
        :_program(loadProgram(Settings::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                              Settings::instance().appPath().dirPath() + "shaders/directionalLight.fs.glsl"))
    {
        std::cout << "Loading dir light program" << std::endl;
        uMVPMatrix = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(_program.getGLId(), "uTexture");

        // Variables uniformes materiaux
        uKd = glGetUniformLocation(_program.getGLId(), "uKd");
        uKs = glGetUniformLocation(_program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(_program.getGLId(), "uShininess");
        
        // Variables uniformes lumieres
        uLightDir_vs = glGetUniformLocation(_program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(_program.getGLId(), "uLightIntensity");
        uColor = glGetUniformLocation(_program.getGLId(), "uColor");
    }
};

// GLSL Program with the Directional Light fragment shader
struct MultiLightProgram {
    glimac::Program _program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uLights;
    GLint uNbLights;
    GLint uAmbientLight;

    MultiLightProgram()
        :_program(loadProgram(Settings::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                              Settings::instance().appPath().dirPath() + "shaders/multiLight.fs.glsl"))
    {
        std::cout << "Loading MultiLight program" << std::endl;
        uMVPMatrix = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(_program.getGLId(), "uTexture");

        uLights = glGetUniformLocation(_program.getGLId(), "uLights");
        uNbLights = glGetUniformLocation(_program.getGLId(), "uNbLights");
        uAmbientLight = glGetUniformLocation(_program.getGLId(), "uAmbientLight");
    }
};

struct ProgramList {
    NormalProgram normalProgram;
    TextureProgram textureProgram;
    DirectionalLightProgram directionalLightProgram;
    MultiLightProgram multiLightProgram;
};

}