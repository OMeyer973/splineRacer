#pragma once
#ifndef __MODEL__HPP
#define __MODEL__HPP

#include <GL/glew.h>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Program.hpp>

#include <splineengine/Collider.hpp>
#include <splineengine/Settings.hpp>
#include <splineengine/common.hpp>
#include <splineengine/Texture.hpp>

namespace splineengine {

/// \brief Represents the 3D model of an object
class Model {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default model Constructor
		Model();

		/// \brief Model Constructor by model name
		/// \param modelName : std::string& name of the model
		Model(const std::string& modelName, const std::string& textureName);

		/// \brief Model Copy constructor
		/// \param model : Model Model to copy
		Model(const Model &model);

		/// \brief model Destructor
		~Model();

		// GETTERS
		/// \brief get VAO
		const GLuint VAO() const { return _VAO; };

		/// \brief get VBO
		const GLuint VBO() const { return _VBO; };

		/// \brief get IBO
		const GLuint IBO() const { return _IBO; };

		/// \brief get Geometry
		const glimac::Geometry geometry() const { return _geometry; };

		/// \brief get Texture ID
		const GLuint textureID() const { return _textureID; };

		/// \brief collider const getter
		const Collider& collider() const { return _collider; };

		// SETTERS // TODO : change for non-const getters ?
		// NON-CONST GETTERS (can be used as setters)
		/// \brief set VBO of the model
		/// \param geometry geometry of the model
		void setVBO(const glimac::Geometry &geometry);

		/// \brief set IBO of the model
		/// \param geometry geometry of the model
		void setIBO(const glimac::Geometry &geometry);

		/// \brief set VAO based on the VBO and VAO
		void setVAO();

		void setTexture(const std::string textureName);



		/// \brief collider non-const getter (to use as setter)
		Collider& collider() { return _collider; };

	private:
		/// \brief Contains the vertices and materials of the model
		glimac::Geometry _geometry;
		/// \brief Represent the VBO of the model
		GLuint _VBO;
		/// \brief Represent the IBO of the model
		GLuint _IBO;
		/// \brief Represent the VAO of the model
		GLuint _VAO;
		/// \brief Collider of the model
		Collider _collider;
		/// \brief Texture ID of the model
		GLuint _textureID;
		//Texture& _texture;
		std::string _textureName;
};

}

#endif
