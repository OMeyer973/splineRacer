#pragma once

#include <iostream> 
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <splineengine/Settings.hpp>

namespace splineengine {

// Every key player can use
enum FS {NORMAL, TEXTURE, DIRECTIONAL_LIGHT, SKYBOX, MULTITEXTURE, POINT_LIGHT, BLACK_AND_WHITE};

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
        std::cout << "loading normal program" << std::endl;
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
        std::cout << "loading texture program" << std::endl;
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
        std::cout << "loading dir light program" << std::endl;
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

// GLSL Program for Skybox
struct SkyboxProgram {
    glimac::Program _program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    SkyboxProgram()
        :_program(loadProgram(Settings::instance().appPath().dirPath() + "shaders/cubemap.vs.glsl",
                              Settings::instance().appPath().dirPath() + "shaders/cubemap.fs.glsl"))
    {
        std::cout << "loading Skybox program" << std::endl;
        uMVPMatrix = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(_program.getGLId(), "uTexture");
    }
};

struct ProgramList {
    NormalProgram normalProgram;
    TextureProgram textureProgram;
    DirectionalLightProgram directionalLightProgram;
    SkyboxProgram skyboxProgram;
};

}