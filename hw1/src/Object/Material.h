#pragma once
#include <string>
#include "head.h"
#include "Texture.h"
#include <vector>

enum Type {
	PHONG = 0,
	LIGHT = 1
};

class Material {
public:
	Type mType;

	glm::vec3 mKa;       //Ambient Color
	glm::vec3 mKd;		//Diffuse Color
	glm::vec3 mKs;		//Specular Color
	glm::vec3 mKe;

	float mNs;			//Specular Exponent
	float mNi;			//Optical Density
	float md;			//Dissoluv
	int mIllum;			//Illumination

	std::string mMap_Ka;     //Ambient Texture Map
	std::string mMap_Kd;	    //Diffuse Texture Map
	std::string mMap_Ks;		//Specular Texture Map

	std::string mMap_bump;    //bump map

	Texture mTexture;
	std::string mName;

	Material();
	Material(const Type& _type);
	~Material();
	Material(const Type& _type
		, const glm::vec3& _ka
		, const glm::vec3& _kd
		, const glm::vec3& _ks);

	void Unload();
};
