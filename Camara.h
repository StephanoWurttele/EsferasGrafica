//
// Created by hgallegos on 17/08/2022.
//

#ifndef INC_20222_RAYTRACING_CAMARA_H
#define INC_20222_RAYTRACING_CAMARA_H

#include <cmath>
#include "CImg.h"
#include "Luz.h"
#include "Objeto.h"
using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
public:
    float fov, w, h, _near;
    vec3 eye, center, up;
    float f, a, b;
    vec3 xe, ye, ze;
    CImg<BYTE> *pImg;

    void inicializar() {
        f = _near;
        a = 2 * f * tan(fov*M_PI/180/2);
        b = w / h * a;
        ze = eye-center;
        ze.normalize();
        xe = up.cruz(ze);
        xe.normalize();
        ye = ze.cruz(xe);
    }
    void renderizar(std::vector<Objeto*> objetos, std::vector<Luz*> luces) ;
};


#endif //INC_20222_RAYTRACING_CAMARA_H
