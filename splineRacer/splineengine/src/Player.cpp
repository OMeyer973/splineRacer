#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "splineengine/Player.hpp"

namespace splineengine {

void Player::updateSpeed(const float dt) {
	// component-wise linear interpolation of the speed toward it's speed target (_sMaxSpeed * _sInput)
	_sSpeed = glm::mix(_sSpeed, _sMaxSpeed * _sInput, _sAcceleration * dt);
}

void Player::updatePosition(const float dt) {
	_sPosition += _sSpeed * dt;
}

void Player::update(const float dt) {
	_sInput[LEFT] = glm::clamp(_sInput[LEFT], -1.f, 1.f);
	_sInput[UP] = glm::clamp(_sInput[UP], -1.f, 1.f);
	updateSpeed(dt);	
	updatePosition(dt);	
}

void Player::draw() const {
	// // Dessin de l'OBJ Plane
	// glBindVertexArray(planeModel.getVAO());

	// /* On boucle sur les meshs de l'object pour les afficher un par un et
	//    appliquer des textures ou des tranformations différentes pour chaque mesh. */
	// for (int i = 0; i < planeModel.geometry().getMeshCount(); ++i)
	// {
	// 	const Geometry::Mesh* currentMesh = (planeModel.geometry().getMeshBuffer()+i);
	// 	GLint indexCount = currentMesh->m_nIndexCount;
	// 	GLint indexOffset = currentMesh->m_nIndexOffset;
	// 	if (currentMesh->m_sName == "propeller") // Si le mesh courant correspond aux hélices
	// 	{
	// 		glBindTexture(GL_TEXTURE_2D, textures[1]);
	// 		glUniform1i(textureLocation, 0);
	// 		MVMatrix = cameras[chosenCamera]->getViewMatrix(); // Init MVMatrix based on the camera
	// 		// MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -5)); // Translation
	// 		// MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
	// 		MVMatrix = glm::rotate(MVMatrix, 15*windowManager.getTime(), glm::vec3(0, 0, 1)); // Translation * Rotation
	// 		glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
	// 		glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
	// 		glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
	// 	}

	// 	// => On utilise glDrawElements à la place de glDrawArrays
	// 	// Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
	// 	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const GLvoid*) (indexOffset * sizeof(GLuint)));
	// }
	// // glDrawElements(GL_TRIANGLES, planeModel.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
	// glBindVertexArray(0);
}

}
