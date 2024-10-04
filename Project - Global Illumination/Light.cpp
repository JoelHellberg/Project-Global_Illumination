// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Light.h"
#include <random>


glm::vec3 Light::RandomPointOnLight(){

	float si = static_cast<float>(rand()) / RAND_MAX;
	float ti = static_cast<float>(rand()) / RAND_MAX;
     
    glm::vec3 E1 = ReturnE1();
    glm::vec3 E2 = ReturnE2();


    glm::vec3 di = coordinates[0] + si * E1 + ti * E2; //Oklart om den är rätt


    /*std::cout << "( " << di[0] << " , " << di[1] <<  " , "  << di[2] << " )" << "\n";*/

    return di;
}

