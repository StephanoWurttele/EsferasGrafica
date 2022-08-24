//
// Created by hgallegos on 17/08/2022.
//

#include "Camara.h"
#include "Objeto.h"
#include <vector>
#include <iostream>
#include <cmath>

const long SPHERENUM = 15;
void Camara::renderizar(){
    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva ");
    // Algoritmo de Ray Casting
    std::vector<Esfera> esferas;
    for(int i = 0; i < SPHERENUM; ++i){
        esferas.emplace_back(vec3(this->h, this->w), rand()%5+1, vec3(rand()%255/255.0,rand()%255/255.0,rand()%255/255.0), vec3(0.9, 0.9, 0.9), vec3(0.9, 0.9, 0.9));
//        std::cout << esferas[i].radio << " " << esferas[i].cen.x << " " << esferas[i].cen.y<< " " << esferas[i].cen.z << "\n";
    }
    vec3 color, normal, N, L;
    Rayo rayo;
    rayo.ori = eye;
    float t_tmp;
    float mindist;
    float fs;
    Luz luz({10,30,20}, {1,1,1});
    for (int x=0; x < w; x++){
        for (int y=0; y < h; y++){
            rayo.dir = -f*ze + a*(y/h -0.5)*ye + b*(x/w-0.5)*xe;
            color = vec3(1,1,0);
            mindist = std::numeric_limits<float>::max();
            for(auto& esfera : esferas) {
//                std::cout << "Centro: " << esfera.cen.x << " " << esfera.cen.y << " " << esfera.cen.z << "\n";
                if (esfera.interseccion(rayo, t_tmp, normal)) {
                    if(t_tmp < mindist){
                        mindist = t_tmp;
                        vec3 pi = rayo.ori + t_tmp * rayo.dir;
                        N = normal;
                        L = luz.pos - pi;
                        L.normalize();
                        // DIFUSA
                        vec3 difuse;
                        float factor_difuso = N.punto(L);
                        if(factor_difuso > 0){
                            difuse = factor_difuso * luz.color * esfera.kd;
                        }
                        // DIFUSA
                        // ESPECULAR
                        vec3 especular;
                        vec3 r = 2*L.punto(N)*N-L;
                        vec3 v = vec3{0,0,0}-pi;
                        r.normalize();
                        v.normalize();
                        float factor_especular = r.punto(v);
                        if(factor_especular > 0){
                            especular = pow(factor_especular, 4) * luz.color * esfera.ks;
                        }
                        // ESPECULAR
                        color = esfera.color * (difuse + especular);
                        color.max_to_one();

                        // SOMBRA
                        for(auto& _esfera : esferas){
                            fs=1;
                            vec3 pi_to_light = luz.pos - pi;
                            if (_esfera.interseccion(Rayo(pi, pi_to_light), t_tmp, normal)){
                                fs = 0;
                                break;
                            }
                        }
                        color = fs * color;
                        // SOMBRA
                    }
                }

            }
            // pintar el pixel con el color
            (*pImg)(x,h-1-y,0) = (BYTE)(color.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color.z * 255);
        }
        dis_img.render((*pImg));
        dis_img.paint();
    }
    while (!dis_img.is_closed()) {
        dis_img.wait();
    }
    }