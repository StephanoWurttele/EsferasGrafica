//
// Created by hgallegos on 18/08/2022.
//

#ifndef INC_20222_RAYTRACING_OBJETO_H
#define INC_20222_RAYTRACING_OBJETO_H
#include "vector.h"
#include "Rayo.h"
#include <iostream>

class Objeto {
public:
    vec3 color;
    vec3 kd, ks;
    Objeto(){}
    Objeto(vec3 _color): color(_color){};
    Objeto(vec3 _color, vec3 _kd, vec3 _ks): color(_color), kd(_kd), ks(_ks){};
    virtual bool interseccion(Rayo rayo, float &t, vec3 &normal) = 0;
};

class Esfera : public Objeto {
public:
    vec3 cen;
    float radio;
    Esfera(vec3 _cen, float _radio) {
        cen = _cen;
        radio = _radio;
    };
    Esfera(vec3 _cen, float _radio, vec3 _color):Objeto(_color) {
        cen = _cen;
        radio = _radio;
    }

    Esfera(vec3 _cen, float _radio, vec3 _color, vec3 _kd, vec3 _ks):Objeto(_color, _kd, _ks) {
        cen = _cen;
        radio = _radio;
    }
    bool interseccion(Rayo rayo, float &t, vec3 &normal);
};

#endif //INC_20222_RAYTRACING_OBJETO_H
