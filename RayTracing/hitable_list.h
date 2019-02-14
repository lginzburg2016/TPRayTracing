/*
L�a GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier hitable_list.h
Classe : liste d objets "frappables"
*/

#pragma once

#include "hitable.h"

//classe liste d objets herite de la classe hitable
class hitable_list: public hitable  {
public:
	//constructeurs
	hitable_list() {}
	hitable_list(hitable **l, int n) {list = l; list_size = n; }

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	hitable **list;
	int list_size;
};

//fonction calcul si collision ou non entre le rayon et les objets
bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}