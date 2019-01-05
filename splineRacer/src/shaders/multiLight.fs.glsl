#version 330 core

precision mediump float;
precision mediump int;

in vec4 vFragPosition;
in vec4 vFragNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

const int MAX_NB_LIGHTS = 10;

struct Light {
	bool _isPoint;
	vec3 _posOrDir;
	vec3 _Kd;
	vec3 _Ks;
	float _shininess;
	vec3 _lightIntensity;
};

uniform sampler2D uTexture;
uniform Light uLights[MAX_NB_LIGHTS];
uniform int uNbLights;
uniform vec3 uAmbientLight;

vec3 blinnPhong()
{	
	vec3 wi, halfVector, specular, diffuse; 

	vec3 resultingLight = vec3(0.0, 0.0, 0.0);
	vec3 wo = normalize(-vFragPosition.xyz);
	vec3 posOrDir;

	float d;

	for (int i = 0; i < uNbLights; ++i)
	{
		if (uLights[i]._isPoint) 
		{
			wi = normalize(uLights[i]._posOrDir - vFragPosition.xyz);
			halfVector = normalize((wo+wi)/2.0);
			d = distance(vFragPosition.xyz, uLights[i]._posOrDir);

			diffuse = uLights[i]._Kd*max(0.0, dot(wi, vFragNormal.xyz));
			specular = uLights[i]._Ks*pow(max(0.0, dot(halfVector, vFragNormal.xyz)), uLights[i]._shininess);

			resultingLight += uLights[i]._lightIntensity * (diffuse + specular) / (d * d);
		}
		else 
		{
			wi = normalize(uLights[i]._posOrDir);
			halfVector = normalize((wo+wi)/2.0);

			diffuse = uLights[i]._Kd*max(0.0, dot(wi, vFragNormal.xyz));
			specular = uLights[i]._Ks*pow(max(0.0, dot(halfVector, vFragNormal.xyz)), uLights[i]._shininess);

			resultingLight += uLights[i]._lightIntensity*(diffuse + specular);
		}
	}
	return resultingLight;
}


void main() 
{
	fFragColor = uAmbientLight + blinnPhong() * (texture(uTexture, vFragTexCoords).rgb);
}
