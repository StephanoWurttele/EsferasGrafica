//
// Created by hgallegos on 24/08/2022.
//

#ifndef INC_20222_RAYTRACING_MUNDO_H
#define INC_20222_RAYTRACING_MUNDO_H

#include <vector>
#include "Camara.h"
#include "Luz.h"

using namespace std;
class Mundo {
public:
    vector<Objeto*> objetos;
    vector<Luz*> luces;
    Camara c;
    long sphereNum = 10;

    void Escenario1();
};
#endif //INC_20222_RAYTRACING_MUNDO_H