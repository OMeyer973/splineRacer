#include <splineengine/RenderManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/AssetManager.hpp>

namespace splineengine {

void RenderManager::updateMVMatrix(Camera &camera, glm::mat4 transformMatrix) {
    // std::cout <<"camera.getViewMatrix(): " << camera.getViewMatrix() << std::endl;
    // std::cout <<"transformMatrix: " << transformMatrix << std::endl;
    _MVMatrix = camera.getViewMatrix() * transformMatrix;
    _normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
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
}

void RenderManager::applyTransformations(FS shader, glm::mat4 matrix)
{
    glm::mat4 lightMatrix;
    glm::vec4 lightVector;

    const ProgramList& programList = AssetManager::instance().programList();

    switch (shader)
    {
        case NORMAL :
            glUniformMatrix4fv(programList.normalProgram.uMVPMatrix, 1, GL_FALSE, 
                glm::value_ptr(_projMatrix * matrix));

            glUniformMatrix4fv(programList.normalProgram.uMVMatrix, 1, GL_FALSE,
                glm::value_ptr(matrix));

            glUniformMatrix4fv(programList.normalProgram.uNormalMatrix, 1, GL_FALSE,
                glm::value_ptr(glm::transpose(glm::inverse(matrix))));
            break;

        case TEXTURE :
            glUniform1i(programList.textureProgram.uTexture, 0);

            glUniform1f(programList.textureProgram.uTime, 0);

            glUniformMatrix4fv(programList.textureProgram.uMVPMatrix, 1, GL_FALSE,
            glm::value_ptr(_projMatrix * matrix));

            glUniformMatrix4fv(programList.textureProgram.uMVMatrix, 1, GL_FALSE,
            glm::value_ptr(matrix));

            glUniformMatrix4fv(programList.textureProgram.uNormalMatrix, 1, GL_FALSE,
            glm::value_ptr(glm::transpose(glm::inverse(matrix))));
            break;

        case DIRECTIONAL_LIGHT :
            glUniform1i(programList.directionalLightProgram.uTexture, 0);
            // White Color to keep the correct color
            glUniform3f(programList.directionalLightProgram.uColor, 1.0,1.0,1.0);

            //lightMatrix = glm::rotate(_MVMatrix, 180.f, glm::vec3(1,1,1));
            lightMatrix = glm::mat4();
            lightVector = glm::normalize(glm::vec4(1,1,1,0)*lightMatrix);
            glUniform3f(programList.directionalLightProgram.uLightDir_vs, lightVector.x, lightVector.y, lightVector.z);

            glUniform3f(programList.directionalLightProgram.uLightIntensity, 2.0,2.0,2.0);

            glUniformMatrix4fv(programList.directionalLightProgram.uMVPMatrix, 1, GL_FALSE,
            glm::value_ptr(_projMatrix * matrix));

            glUniformMatrix4fv(programList.directionalLightProgram.uMVMatrix, 1, GL_FALSE,
            glm::value_ptr(matrix));

            glUniformMatrix4fv(programList.directionalLightProgram.uNormalMatrix, 1, GL_FALSE,
            glm::value_ptr(glm::transpose(glm::inverse(matrix))));
            break;

        default :
            break;
    }
}

}
