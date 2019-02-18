/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier hitable.h
Classe pour les objets "frappables"
*/

#pragma once

#include "ray.h"

//on fait le lien avec la classe material 
//pour avoir une donnee de materiau dans la structure hit_record
class material;

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hitable {
public :
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
