//
// Created by hgallegos on 17/08/2022.
//

#ifndef INC_20222_RAYTRACING_VECTOR_H
#define INC_20222_RAYTRACING_VECTOR_H

#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

class vec3 {
public:
    float x,y,z;
    vec3() { x=y=z=0; }
    vec3(float val) { x=y=z=val; }
    vec3(float h, float w) { x = rand()%20-10; y = rand()%20-10; z = rand()%20-10;};
    vec3(float _x, float _y, float _z) {x=_x;y=_y;z=_z;}
    vec3 operator+(vec3 v) { return vec3( x+v.x, y+v.y, z+v.z); }
    vec3 operator*(vec3 v) { return vec3( x*v.x, y*v.y, z*v.z); }

    vec3 cruz(vec3 v) {
        return vec3(y*v.z - z*v.y,
                    z*v.x - x*v.z,
                    x*v.y - y*v.x);
    }
    float punto(vec3 v){
        return x*v.x + y*v.y + z*v.z;
    }
    void normalize(){
        double m = modulo();
        x = x/m;
        y = y/m;
        z = z/m;
    }
    double modulo() {
        return sqrt(x*x + y*y + z*z);
    }
    // para los colores
    void max_to_one(){
        float maxValue = std::max({x ,y, z});
        if(maxValue > 1){
            x /= maxValue;
            y /= maxValue;
            z /= maxValue;
        }
    }
    vec3 operator-(vec3 v){
        return vec3(x-v.x, y-v.y,z-v.z);
    }
    bool isblack(){
        return x == 0 && y == 0 && z == 0;
    }
    void toblack(){
        x = y = z = 0;
        return;
    }
};

vec3 operator/(float f, vec3 v);
vec3 operator*(float f, vec3 v);
vec3 operator+(float f, vec3 v);

#endif //INC_20222_RAYTRACING_VECTOR_H
