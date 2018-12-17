#pragma once
#ifndef __MODEL__HPP
#define __MODEL__HPP

#include <GL/glew.h>
#include <glimac/Geometry.hpp>
#include <glimac/Geometry.hpp>
#include "Collider.hpp"

namespace splineengine {

/// \brief Represents the 3D model of an object
class Model {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default model Constructor
		Model()
		{};

		/// \brief model Constructor
		Model(glimac::Geometry &geometry)
			:
			_geometry(geometry)
		{
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

		void draw();

	private:
		/// \brief Contains the vertices and materials of the model
		glimac::Geometry _geometry;
		GLuint _VBO;
		GLuint _IBO;
		GLuint _VAO;
		Collider _collider;
};

}

#endif