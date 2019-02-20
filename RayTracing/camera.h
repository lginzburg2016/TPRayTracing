/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier camera.h
*/

#pragma once

#include "ray.h"

#define M_PI 3.141592653589793 //redefinition de M_PI car je n arrive pas a y acceder


class camera {
public :
	//constructeurs
	//lookfrom : origine de la camera
	//lookat : point vers lequel la camera regarde
	//vup : vecteur "view up"
	//vfov : angle du haut vers le bas en degres
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) { 
		float theta = vfov * M_PI/ 180; //conversion de vfov en radian
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2*half_width*u;
		vertical = 2 * half_height*v;
	}
	
	ray get_ray(float s, float t){ return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin) ;}
	 
	vec3 origin;
	vec3 u, v, w;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};