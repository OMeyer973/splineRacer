#version 330 core

//material variables
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//light variables
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

//texture variables
uniform sampler2D uAvionText;

//position du fragment sur l'écran
in  vec4 vPosition_vs;
//normal du fragment
in  vec4 vFragNormal;
//coordonée u, v du fragment
in  vec2 vFragTexCoords;

out vec3 fFragColor;


vec3 blinnPhong() {
	//Couleur=Li(Kd(wi˙N)+Ks(halfVector˙N)^shininess)
	vec3 Li = uLightIntensity;
	vec3 wi = uLightDir_vs;
	vec3 wo = normalize(vec3(-vPosition_vs));
	vec3 halfVector = 0.5*(wo+wi);
	vec3 N = vec3(vFragNormal);
	return
		Li * (
			uKd*(dot(wi,N))
			+uKs*pow(dot(halfVector,N),uShininess)
		);
}

void main() {
	fFragColor =
		blinnPhong() * (
		      texture(uEarthTexture, vFragTexCoords).xyz
	    );

	//fFragColor = normalize(vFragNormal.xyz);
};
