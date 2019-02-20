/*
L�a GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier camera.h
*/

#pragma once

#include "ray.h"

#define M_PI 3.141592653589793 //redefinition de M_PI car je n arrive pas a y acceder

//definition des origines de rayons sur un disque
vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0*vec3(double(rand()) / RAND_MAX, double(rand()) / RAND_MAX, 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}


class camera {
public:
	//constructeurs
	//lookfrom : origine de la camera
	//lookat : point vers lequel la camera regarde
	//vup : vecteur "view up"
	//vfov : angle du haut vers le bas en degres
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
		lens_radius = aperture / 2;
		float theta = vfov * M_PI / 180; //conversion de vfov en radian
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}

	ray get_ray(float s, float t) {
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

	vec3 origin;
	vec3 u, v, w;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
};