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
		case TEXT:
			programList.textProgram._program.use();
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
			ambientLight = glm::vec3(.05);

			// for (int i = 0; i < _lightsCount; ++i) {
			// 	_lights[i].sendLightShader(programList.multiLightProgram, refLight);
			// }
			for (std::vector<Light>::iterator it = _lights.begin(); it != _lights.end(); ++it) {
				it->sendLightShader(programList.multiLightProgram, refLight);
			}

			glUniform3f(glGetUniformLocation(programList.multiLightProgram._program.getGLId(), "uAmbientLight"), ambientLight.x, ambientLight.y, ambientLight.z);
			glUniform1i(glGetUniformLocation(programList.multiLightProgram._program.getGLId(), "uNbLights"), _lightsCount);

			glUniformMatrix4fv(programList.multiLightProgram.uMVPMatrix, 1, GL_FALSE,
				glm::value_ptr(_projMatrix * _MVMatrix));
			glUniformMatrix4fv(programList.multiLightProgram.uMVMatrix, 1, GL_FALSE,
				glm::value_ptr(_MVMatrix));
			glUniformMatrix4fv(programList.multiLightProgram.uNormalMatrix, 1, GL_FALSE,
				glm::value_ptr(_normalMatrix));

			glUniform1i(programList.multiLightProgram.uTexture, 0);

			break;
			case TEXT :

				glUniformMatrix4fv(programList.textProgram.uMVPMatrix, 1, GL_FALSE,
					glm::value_ptr(_projMatrix * _MVMatrix));
				glUniformMatrix4fv(programList.textProgram.uMVMatrix, 1, GL_FALSE,
					glm::value_ptr(_MVMatrix));
				glUniformMatrix4fv(programList.textProgram.uNormalMatrix, 1, GL_FALSE,
					glm::value_ptr(_normalMatrix));
				

				glUniform1i(programList.textProgram.uTexture, 0);

				break;

		default:
			break;
	}
}

void RenderManager::initGameLights() {
	if (debug) std::cout << "init Lights" << std::endl;

	clearLights();

	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	/* Orange Directional Light */
	addLight(
		false,
		glm::vec3(lightVector),
		glm::vec3(1, 0.8, 0.5),
		glm::vec3(1, 0.75, .35),
		64,
		glm::vec3(1.0)
	);

	/* Blue Directional Light */
	addLight(
		false,
		glm::vec3(lightVector),
		glm::vec3(.2),
		glm::vec3(0.0, 0.1, 0.2),
		2,
		glm::vec3(.25)
	);

	/* Red Point Lights under the plane */
	addLight(
		true,
		glm::vec3(0.0, 0.0, -13.0),
		glm::vec3(1, .0,  0),
		glm::vec3(1, .8, .1),
		6,
		glm::vec3(2.0)
	);
}

void RenderManager::initMenuLights() {
	if (debug) std::cout << "init Lights" << std::endl;

	clearLights();

	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(0, 0, 1, 0) * lightMatrix);

	/* Orange Directional Light */
	addLight(
		false,
		glm::vec3(0, 0, 1),
		glm::vec3(.3f),
		glm::vec3(.3f),
		64,
		glm::vec3(1, 0.6, .2)
	);

	/* Blue Directional Light */
	// addLight(
	// 	false,
	// 	glm::vec3(lightVector),
	// 	glm::vec3(1.f),
	// 	glm::vec3(1.f),
	// 	32,
	// 	glm::vec3(.05, 0.05, .1)
	// );

	/* Orange Point Light on top */
	addLight(
		true,
		glm::vec3(0.f, 2.6f, -5.f),
		glm::vec3(1.f),
		glm::vec3(1.f, .5f, .05f),
		32,
		glm::vec3(3.f)
	);

	/* Blue Point Lights in front of the menu */
	addLight(
		true,
		glm::vec3(0.f,  -2.6f, -5.f),
		glm::vec3(.1f, .2f, .9f),
		glm::vec3(1.f),
		16,
		glm::vec3(3.f)
	);
}

void RenderManager::addLight(const bool isPoint,
							 const glm::vec3 &posOrDir,
							 const glm::vec3 &Kd,
							 const glm::vec3 &Ks,
							 const float &shininess,
							 const glm::vec3 &lightIntensity)
{
	_lights.push_back( Light(_lightsCount, isPoint, posOrDir, Kd, Ks, shininess, lightIntensity) );
	_lightsCount++;
}

void RenderManager::updateMenuLights() {
	// Leave this method empty if you want the lights to follow the camera
	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	// TODO: throw exception
	if (_lightsCount > 0) {
		// _lights[0].posOrDir() = glm::vec3(lightVector);
		// _lights[1].posOrDir() = glm::vec3(-lightVector);

		// // lightMatrix = glm::translate(_MVMatrix, _lights[2].posOrDir());
		// lightVector = _MVMatrix * glm::vec4(_lights[2].posOrDir(), 1);
		// std::cout << "Debug" << std::endl;
		// std::cout << lightVector << std::endl;
		// std::cout << _globalMatrix << std::endl;
		// std::cout << _MVMatrix << std::endl;
		// // _lights[2].posOrDir() = glm::vec3(lightVector);
	}
}

void RenderManager::updateGameLights() {
	glm::mat4 lightMatrix;
	glm::vec4 lightVector;

	lightMatrix = glm::transpose(_globalMatrix);
	lightVector = glm::normalize(glm::vec4(1, 1, 1, 0) * lightMatrix);

	// TODO: throw exception
	if (_lightsCount > 0) {
		_lights[0].posOrDir() = glm::vec3(lightVector);
		_lights[1].posOrDir() = glm::vec3(-lightVector);
	}
}

void RenderManager::clearLights() {
	_lights.clear();
	_lightsCount = 0;
}

}
