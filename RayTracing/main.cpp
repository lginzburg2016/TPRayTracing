/*
L�a GINZBURG - Vivien FARGETTE
Suivi du document "Ray Tracing in One Weekend" de Peter Shirley

Fichier main.cpp
*/


#include <iostream>
#include <fstream>
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
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}




