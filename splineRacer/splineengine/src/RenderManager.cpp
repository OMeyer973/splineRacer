#include <splineengine/RenderManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/AssetManager.hpp>

namespace splineengine {

void RenderManager::updateMVMatrix(Camera &camera, glm::mat4 transformMatrix) {
    _MVMatrix = camera.getViewMatrix() * transformMatrix;
    _normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
}

void RenderManager::updateGlobalMatrix(Camera &camera, glm::mat4 splineCamMatrix) {
    _globalMatrix =  camera.getViewMatrix() * splineCamMatrix;
}

void RenderManager::useProgram(FS shader) {
	const ProgramList& programList = AssetManager::instance().programList();

    switch (shader)
    {
        case NORMAL:
            programList.normalProgram._program.use();
            break;

        case TEXTURE:
            programList.textureProgram._program.use();
            break;

        case DIRECTIONAL_LIGHT:
            programList.directionalLightProgram._program.use();
            break;

        default:
            programList.normalProgram._program.use();
            break;
    }
    applyTransformations(shader);
}

void RenderManager::applyTransformations(FS shader)
{
    // glm::mat4 lightMatrix = glm::rotate(_globalMatrix, 180.f, glm::vec3(1,1,1));
    glm::mat4 lightMatrix = _globalMatrix;
    glm::vec4 lightVector = glm::normalize(glm::vec4(1,1,1,0)*lightMatrix);

    const ProgramList& programList = AssetManager::instance().programList();

    switch (shader)
    {
        case NORMAL :
            glUniformMatrix4fv(programList.normalProgram.uMVPMatrix, 1, GL_FALSE, 
                glm::value_ptr(_projMatrix * _MVMatrix));

            glUniformMatrix4fv(programList.normalProgram.uMVMatrix, 1, GL_FALSE,
                glm::value_ptr(_MVMatrix));

            glUniformMatrix4fv(programList.normalProgram.uNormalMatrix, 1, GL_FALSE,
                glm::value_ptr(_normalMatrix));
            break;

        case TEXTURE :
            glUniform1i(programList.textureProgram.uTexture, 0);

            glUniform1f(programList.textureProgram.uTime, 0);

            glUniformMatrix4fv(programList.textureProgram.uMVPMatrix, 1, GL_FALSE,
                glm::value_ptr(_projMatrix * _MVMatrix));

            glUniformMatrix4fv(programList.textureProgram.uMVMatrix, 1, GL_FALSE,
                glm::value_ptr(_MVMatrix));

            glUniformMatrix4fv(programList.textureProgram.uNormalMatrix, 1, GL_FALSE,
                glm::value_ptr(_normalMatrix));
            break;

        case DIRECTIONAL_LIGHT :
            glUniform1i(programList.directionalLightProgram.uTexture, 0);
            glUniform3f(programList.directionalLightProgram.uColor, 1.0, 1.0, 1.0);

            glUniform3fv(programList.directionalLightProgram.uLightDir_vs, 1, glm::value_ptr(lightVector));
            glUniform3f(programList.directionalLightProgram.uLightIntensity, 1.f, 1.f, 1.f);
            glUniform3f(programList.directionalLightProgram.uKd, .5, .5, .5);
            glUniform3f(programList.directionalLightProgram.uKs, .5, .5, .5);
            glUniform1f(programList.directionalLightProgram.uShininess, 4);

            glUniformMatrix4fv(programList.directionalLightProgram.uMVPMatrix, 1, GL_FALSE,
                glm::value_ptr(_projMatrix * _MVMatrix));
            glUniformMatrix4fv(programList.directionalLightProgram.uMVMatrix, 1, GL_FALSE,
                glm::value_ptr(_MVMatrix));
            glUniformMatrix4fv(programList.directionalLightProgram.uNormalMatrix, 1, GL_FALSE,
                glm::value_ptr(_normalMatrix));

            break;

        default :
            break;
    }
}

}
