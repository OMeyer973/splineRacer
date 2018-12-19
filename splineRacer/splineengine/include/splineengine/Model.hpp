#pragma once
#ifndef __MODEL__HPP
#define __MODEL__HPP

#include <iostream>
#include <GL/glew.h>
#include <glimac/Geometry.hpp>
#include <glimac/FilePath.hpp>
#include "Collider.hpp"

namespace splineengine {

/// \brief Represents the 3D model of an object
class Model {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default model Constructor
		Model()
		{
			std::cout << "model constructor " << std::endl;
		};

		/// \brief model Constructor
		Model(const glimac::FilePath &applicationPath, const std::string &modelName)
		{
			glimac::Geometry geometry;
			glimac::FilePath modelPath = applicationPath.dirPath() + "../../splineRacer/assets/models/" + modelName + "/" + modelName;
			glimac::FilePath objPath(modelPath.addExt(".obj")); // Constructeur par copie
			glimac::FilePath mtlPath(modelPath.addExt(".mtl")); // Constructeur par copie
			bool ret = geometry.loadOBJ(objPath, mtlPath, true);
			if (!ret)
				exit(1); // Lancer Exception : OBJ loading failed

			// OBJ is correctly loaded
			_geometry = geometry;
			setVBO(geometry);
			setIBO(geometry);
			setVAO();
		};

		/// \brief model Destructor
		~Model()
		{
			glDeleteBuffers(1, &_VBO);
			glDeleteVertexArrays(1, &_VAO);
		};

		/// \brief set VBO of the model
		/// \param geometry geometry of the model
		void setVBO(const glimac::Geometry &geometry);

		/// \brief set IBO of the model
		/// \param geometry geometry of the model
		void setIBO(const glimac::Geometry &geometry);

		/// \brief set VAO based on the VBO and VAO
		void setVAO();

		/// \brief get VAO
		GLuint getVAO() const {
			return _VAO;
		};

		/// \brief get Geometry
		glimac::Geometry geometry() const {
			return _geometry;
		};

		void draw();

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
};

}

#endif