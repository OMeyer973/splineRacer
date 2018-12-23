#include "splineengine/Model.hpp"

namespace splineengine {

	Model::Model(const std::string &modelName) {
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

	void Model::setVBO(const glimac::Geometry &geometry) {
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, geometry.getVertexCount() * sizeof(glimac::Geometry::Vertex), geometry.getVertexBuffer(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		_VBO = vbo;
	}

	void Model::setIBO(const glimac::Geometry &geometry) {
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.getIndexCount() * sizeof(uint32_t), geometry.getIndexBuffer(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		_IBO = ibo;
	}

	void Model::setVAO() {
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

		const GLuint VERTEX_ATTR_POSITION = 0;
		const GLuint VERTEX_ATTR_NORMAL = 1;
		const GLuint VERTEX_ATTR_TEXCOORD = 2;
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
		glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
		glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_Position));
		glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_Normal));
		glVertexAttribPointer(VERTEX_ATTR_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_TexCoords));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		_VAO = vao;
	};

}
