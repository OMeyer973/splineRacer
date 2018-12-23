#pragma once
#ifndef __MODEL__HPP
#define __MODEL__HPP

#include <iostream>
#include <GL/glew.h>
#include "Collider.hpp"
#include <iostream>
#include <glimac/Geometry.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <splineengine/Settings.hpp>
#include <splineengine/common.hpp>

namespace splineengine {

/// \brief Represents the 3D model of an object
class Model {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default model Constructor
		Model() {
			std::cout << "Model: Default constructor" << std::endl;
		};

		/// \brief model Constructor by model name
		/// \param modelName : std::string& name of the model
		Model(const std::string &modelName) {
			std::cout << "Model: Constructor by Model Name" << std::endl;
			glimac::FilePath modelPath = Settings::instance().appPath().dirPath() + "../../splineRacer/assets/models/" + modelName + "/" + modelName;
			glimac::FilePath objPath(modelPath.addExt(".obj")); // Constructeur par copie
			glimac::FilePath mtlPath(modelPath.addExt(".mtl")); // Constructeur par copie
			bool ret = _geometry.loadOBJ(objPath, mtlPath, true);
			if (!ret) {
				exit(1); // Throw Exception : OBJ loading failed
			}

			// OBJ is correctly loaded
			setVBO(_geometry);
			setIBO(_geometry);
			setVAO();

			// _program = glimac::loadProgram(
			// 	Settings::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
			// 	Settings::instance().appPath().dirPath() + "shaders/normals.fs.glsl"
			// );
		};

		/// \brief model Constructor by model name
		/// \param modelName : std::string& name of the model
		Model(const Model &model)
			:
			_geometry(model._geometry),
			_VBO(model._VBO),
			_IBO(model._IBO),
			_VAO(model._VAO)
			// _program(model._program)
		{
			std::cout << "Model: Copy Constructor" << std::endl;
		};

		/// \brief model Destructor
		~Model() {
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

		/// \brief get IBO
		GLuint getIBO() const {
			return _IBO;
		};

		/// \brief get Geometry
		glimac::Geometry geometry() const {
			return _geometry;
		};

		/// \brief get Program
		// const glimac::Program& program() const {
		// 	return _program;
		// };

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
		/// \brief Program of the object
		// glimac::Program _program;
};

}

#endif