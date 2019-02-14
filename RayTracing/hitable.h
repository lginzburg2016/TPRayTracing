/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier hitable.h
Classe pour les objets "frappables"
*/

#pragma once

#include "ray.h"

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
};

class hitable {
public :
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
