/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier ray.h
Classe de rayon
*/

#pragma once

#include "vec3.h"

class ray {
public :
	//constructeurs
	ray() {}
	ray(const vec3& a, const vec3& b) { A = a; B = b; }

	vec3 origin() const { return A; }
	vec3 direction() const {return B; }

	//rayon vu comme une fonction definie par :
	vec3 point_at_parameter(float t) const {return A + t*B;}

	//origine du rayon
	vec3 A;
	//vecteur directeur du rayon
	vec3 B;
};
