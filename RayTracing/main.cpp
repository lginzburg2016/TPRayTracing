/*
Léa GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier main.cpp
*/


#include <iostream>
#include <fstream>
#include "vec3.h"

using namespace std;


int main() {
	ofstream outputfile;
	//fichier de sortie pour l image coloree souhaitee
	outputfile.open("image.ppm");
	int nx = 200;
	int ny = 100;
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny-1; j >=0 ; j--){
		for (int i = 0; i < nx; i++){
			//definition vecteur couleurs RGB
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}




