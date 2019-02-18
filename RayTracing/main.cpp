/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier main.cpp
*/


#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <cfloat> //au lieu de "float.h" non reconnu sous windows


using namespace std;


//fonction permettant de trouver un point aleatoire dans une sphere unitaire
vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0*vec3(double(rand()) / RAND_MAX, double(rand()) / RAND_MAX, double(rand()) / RAND_MAX) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}


vec3 color(const ray& r, hitable *world){
	hit_record rec;
	//hit(..., 0.001, ...) pour eliminer les frappes trop proches de 0 qui induisent possibles bugs
	if(world->hit(r, 0.001, FLT_MAX, rec)){ //FLT_MAX au lieu de FLOATMAX sous windows
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color( ray(rec.p, target-rec.p), world );
	}
	else{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	ofstream outputfile;
	//fichier de sortie pour l image coloree souhaitee
	outputfile.open("image.ppm");
	int nx = 200;
	int ny = 100;
	int ns = 100;
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";

	//creation liste d objets
	hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1), 0.5);
	list[1] = new sphere(vec3(0,-100.5,-1), 100);
	hitable *world = new hitable_list(list,2);

	camera cam;

	for (int j = ny-1; j >=0 ; j--){
		for (int i = 0; i < nx; i++){

			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++){
				//utiliser double(rand())/RAND_MAX au lieu de drand48() sous windows
				float u = float(i + double(rand())/RAND_MAX) / float(nx);
				float v = float(j + double(rand())/RAND_MAX) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			
			col /= float(ns);
			//correction gamma, ici gamma 2
			col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}




