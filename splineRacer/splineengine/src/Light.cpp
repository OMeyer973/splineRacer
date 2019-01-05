#include <splineengine/Light.hpp>

namespace splineengine {

Light::Light(const unsigned int id,
			 const bool isPoint,
			 const glm::vec3 &posOrDir,
			 const glm::vec3 &Kd,
			 const glm::vec3 &Ks,
			 const float &shininess, 
			 const glm::vec3 &lightIntensity)
	:_id(id)
{
	_properties = {isPoint, posOrDir, Kd, Ks, shininess, lightIntensity};
}

Light::Light(const Light& light)
	:_properties(light._properties),
	_id(light._id)
{
	// if (debug) std::cout << "Light COPY Constructor" << std::endl;
	// if (debug) std::cout << "ID: " << _id << std::endl;
}

Light::~Light()
{}

void Light::sendLightShader(const MultiLightProgram &multiLightProgram, const std::string &uniformArrayName) const 
{
	std::string uniformLightName =  uniformArrayName + "[" + std::to_string(_id) + "]";

	glUniform1ui(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._isPoint").c_str()), _properties._isPoint);	
	glUniform3f(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._posOrDir").c_str()), _properties._posOrDir.x, _properties._posOrDir.y, _properties._posOrDir.z);	
	glUniform3f(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._Kd").c_str()), _properties._Kd.x, _properties._Kd.y, _properties._Kd.z);	
	glUniform3f(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._Ks").c_str()), _properties._Ks.x, _properties._Ks.y, _properties._Ks.z);	
	glUniform1f(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._shininess").c_str()), _properties._shininess);	
	glUniform3f(glGetUniformLocation(multiLightProgram._program.getGLId(), (uniformLightName + "._lightIntensity").c_str()), _properties._lightIntensity.x, _properties._lightIntensity.y, _properties._lightIntensity.z);	

}

}

