#include <iostream>
#include <GL/glew.h>
#include "splineengine/Model.hpp"

namespace splineengine {

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
