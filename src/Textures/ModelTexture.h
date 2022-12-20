#pragma once

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class ModelTexture
{
public:
	ModelTexture(GLuint InTextureID);
	GLuint GetTextureID() const;

	float GetShineDamper() { return ShineDamper; }
	void SetShineDamper(float InShineDamper) { ShineDamper = InShineDamper; }

	float GetReflectivity() { return Reflectivity; }
	void SetReflectivity(float InReflectivity) { Reflectivity = InReflectivity; }

private:
	GLuint TextureID;

	float ShineDamper = 1.f;
	float Reflectivity = 0.f;
};