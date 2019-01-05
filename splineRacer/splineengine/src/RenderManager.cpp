#include <splineengine/RenderManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/AssetManager.hpp>
#include <glimac/Program.hpp>

namespace splineengine {

void RenderManager::updateMVMatrix(Camera &camera, glm::mat4 transformMatrix, glm::vec3 scale) {
	_MVMatrix = camera.getViewMatrix() * transformMatrix;
	_normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
	_MVMatrix = glm::scale(_MVMatrix, scale);
}

void RenderManager::updateGlobalMatrix() {
	_globalMatrix = _MVMatrix;

	// Light depends on globalMatrix
	if (_lights.size() == 0) {
		initLights();
	}
	updateLights();
}

void RenderManager::drawObject(GameObject& obj, Camera& camera) {
	glm::mat4 transformMatrix = _splineCamMatrix * obj.matrix();
	updateMVMatrix(camera, transformMatrix, obj.scale());
	useProgram(MULTI_LIGHT);
	obj.draw();
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

		case MULTI_LIGHT:
			programList.multiLightProgram._program.use();
			break;

		default:
			programList.normalProgram._program.use();
			break;
	}
	sendUniformsToShaders(shader);
}

void RenderManager::sendUniformsToShaders(FS shader)
{
	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	const std::string refLight = "uLights";
	glm::vec3 ambientLight;

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

			lightMatrix = glm::transpose(_globalMatrix);
			lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

			glUniform1i(programList.directionalLightProgram.uTexture, 0);
			glUniform3f(programList.directionalLightProgram.uColor, 1.0, 1.0, 1.0);

			glUniform3fv(programList.directionalLightProgram.uLightDir_vs, 1, glm::value_ptr(lightVector));
			glUniform3f(programList.directionalLightProgram.uLightIntensity, 1.f, 1.f, 1.f);
			glUniform3f(programList.directionalLightProgram.uKd, .5, .5, .5);
			glUniform3f(programList.directionalLightProgram.uKs, .5, .5, .5);
			glUniform1f(programList.directionalLightProgram.uShininess, .5);

			glUniformMatrix4fv(programList.directionalLightProgram.uMVPMatrix, 1, GL_FALSE,
				glm::value_ptr(_projMatrix * _MVMatrix));
			glUniformMatrix4fv(programList.directionalLightProgram.uMVMatrix, 1, GL_FALSE,
				glm::value_ptr(_MVMatrix));
			glUniformMatrix4fv(programList.directionalLightProgram.uNormalMatrix, 1, GL_FALSE,
				glm::value_ptr(_normalMatrix));

			break;

		case MULTI_LIGHT :
			ambientLight = glm::vec3(0.2);

			// updateLights();

			// lights.push_back(Light(true, glm::vec3(0.0, -3.0, -7.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
			// lights.push_back(Light(true, glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
			// lights.push_back(Light(true, glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
			// lights.push_back(Light(false, glm::vec3(lightVector), glm::vec3(0.0, 0.4, 0.9), glm::vec3(1.0), 8, glm::vec3(1.0)));
			// lights.push_back(Light(false, glm::vec3(lightVector), glm::vec3(0.8, 0.1, 0.4), glm::vec3(1.0), 8, glm::vec3(1.0)));

			for (int i = 0; i < _lights.size(); ++i) {
				_lights[i].sendLightShader(programList.multiLightProgram, refLight);
			}

			glUniform3f(glGetUniformLocation(programList.multiLightProgram._program.getGLId(), "uAmbientLight"), ambientLight.x, ambientLight.y, ambientLight.z); 
			glUniform1i(glGetUniformLocation(programList.multiLightProgram._program.getGLId(), "uNbLights"), _lights.size());

			glUniformMatrix4fv(programList.multiLightProgram.uMVPMatrix, 1, GL_FALSE,
				glm::value_ptr(_projMatrix * _MVMatrix));
			glUniformMatrix4fv(programList.multiLightProgram.uMVMatrix, 1, GL_FALSE,
				glm::value_ptr(_MVMatrix));
			glUniformMatrix4fv(programList.multiLightProgram.uNormalMatrix, 1, GL_FALSE,
				glm::value_ptr(_normalMatrix));

			glUniform1i(programList.multiLightProgram.uTexture, 0);

			break;

		default:
			break;
	}
}

void RenderManager::initLights() {
	if (debug) std::cout << "init Lights" << std::endl;
	glm::mat4 lightMatrix;
	glm::vec4 lightVector;
	glm::vec3 ambientLight = glm::vec3(0.2);

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	/* Orange Directional Light */
	_lights.push_back(Light(false, glm::vec3(lightVector), glm::vec3(1.0), glm::vec3(1.0), 64, glm::vec3(1, 0.8, 0.5)));

	lightMatrix = glm::rotate(lightMatrix, 180.f, glm::vec3(0, 1, 0));
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	/* Blue Directional Light */
	_lights.push_back(Light(false, glm::vec3(lightVector), glm::vec3(.5), glm::vec3(.5), 8, glm::vec3(0.8, 0.5, 0.0)));


	/* Points Lights */
	_lights.push_back(Light(true, glm::vec3(0.0, -3.0, -7.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
	_lights.push_back(Light(true, glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
	_lights.push_back(Light(true, glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0), 64, glm::vec3(1.0)));
}

void RenderManager::updateLights() {
	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	_lights[0].posOrDir() = glm::vec3(lightVector);
	_lights[1].posOrDir() = glm::vec3(-lightVector);
}

void RenderManager::clearLights() {
	_lights.clear();
}

}
