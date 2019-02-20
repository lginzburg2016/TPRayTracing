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
#include "material.h"
#include <cfloat> //au lieu de "float.h" non reconnu sous windows


using namespace std;



vec3 color(const ray& r, hitable *world, int depth){
	hit_record rec;
	//hit(..., 0.001, ...) pour eliminer les frappes trop proches de 0 qui induisent possibles bugs
	if(world->hit(r, 0.001, FLT_MAX, rec)){ //FLT_MAX au lieu de MAXFLOAT sous windows
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered) ) {
			return attenuation*color(scattered, world, depth+1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}


//creation d une scene aleatoire avec de nombreuses spheres
hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, 1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = double(rand()) / RAND_MAX;
			vec3 center(a + 0.9*(double(rand()) / RAND_MAX), 0.2, b + 0.9*(double(rand()) / RAND_MAX));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) { //diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3( (double(rand())/RAND_MAX)*(double(rand()) / RAND_MAX), (double(rand()) / RAND_MAX)*(double(rand()) / RAND_MAX), (double(rand()) / RAND_MAX)*(double(rand()) / RAND_MAX))));
				}
				else if (choose_mat < 0.95) { //metal
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + (double(rand()) / RAND_MAX)), 0.5*(1 + (double(rand()) / RAND_MAX)), 0.5*(1 + (double(rand()) / RAND_MAX))), 0.5*(double(rand()) / RAND_MAX)));
				}
				else{ //verre
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}

		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4,0.2,0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7,0.6,0.5), 0.0));

	return new hitable_list(list, i);
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
	hitable *list[5];
	list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list,5);
	
	world = random_scene();

	//prise en compte ouverture camera
	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	//champ de vision 20 degres
	camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus );

	for (int j = ny-1; j >=0 ; j--){
		for (int i = 0; i < nx; i++){

			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++){
				//utiliser double(rand())/RAND_MAX au lieu de drand48() sous windows
				float u = float(i + double(rand())/RAND_MAX) / float(nx);
				float v = float(j + double(rand())/RAND_MAX) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
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




