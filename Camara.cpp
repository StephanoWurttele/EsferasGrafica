//
// Created by hgallegos on 17/08/2022.
//

#include "Camara.h"
#include <vector>
#include <iostream>
#include <cmath>

void Camara::renderizar(std::vector<Objeto*> objetos, std::vector<Luz*> luces){
    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva ");
    // Algoritmo de Ray Casting
    vec3 color, normal, N, L;
    Rayo rayo;
    rayo.ori = eye;
    float t_tmp;
    float mindist;
    float fs = 1;
    for (int x=0; x < w; x++){
        for (int y=0; y < h; y++){
            rayo.dir = -f*ze + a*(y/h -0.5)*ye + b*(x/w-0.5)*xe;
            color = vec3(1,1,0);
            mindist = std::numeric_limits<float>::max();
            Objeto* closest;
            for(auto& objeto : objetos) {
//                std::cout << "Centro: " << esfera.cen.x << " " << esfera.cen.y << " " << esfera.cen.z << "\n";
                if (objeto->interseccion(rayo, t_tmp, normal)) {
                    if(t_tmp < mindist){
                        mindist = t_tmp;
                        N = normal;
                        closest = objeto;
                    }
                }
            }

            if(mindist != std::numeric_limits<float>::max()){
                vec3 pi = rayo.ori + mindist * rayo.dir;

                // SOMBRA
                for(auto& _objeto : objetos){
                    fs=1;
                    vec3 pi_to_light = luces[0]->pos - pi;
                    pi_to_light.normalize();
                    if (_objeto->interseccion(Rayo(pi + 0.01 * N , pi_to_light), t_tmp, normal)){
                        color.toblack();
                        break;
                    }
                }
                // END SOMBRA
                if(!color.isblack()){
                    L = luces[0]->pos - pi;
                    L.normalize();
                    // DIFUSA
                    vec3 difuse;
                    float factor_difuso = N.punto(L);
                    if(factor_difuso > 0){
                        difuse = factor_difuso * luces[0]->color * closest->kd;
                    }
                    // DIFUSA
                    // ESPECULAR
                    vec3 especular;
                    vec3 r = 2*L.punto(N)*N-L;
                    vec3 v = vec3{0,0,0}-rayo.dir;
                    r.normalize();
                    v.normalize();
                    float factor_especular = r.punto(v);
                    if(factor_especular > 0){
                        especular = pow(factor_especular, 4) * luces[0]->color * closest->ks;
                    }
                    // ESPECULAR
                    //REFLEXION
                    
                    //REFLEXION
                    color = closest->color * (difuse + especular);
                    color.max_to_one();
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