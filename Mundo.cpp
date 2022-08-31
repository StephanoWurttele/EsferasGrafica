//
// Created by hgallegos on 24/08/2022.
//

#include "Mundo.h"
void Mundo::Escenario1(){
    c.center=vec3(0,0,0);
    c.up=vec3(0,1,0);
    c.eye=vec3(3,5,30);
    c._near=4;
    c.fov = 60;
    c.w = 600;
    c.h = 400;
    c.inicializar();

    Luz *pLuz = new Luz({10,30,20}, {1,1,1});
    luces.emplace_back(pLuz);

    for(int i = 0; i < sphereNum; ++i){
        Esfera *pEsf = new Esfera(vec3(c.h, c.w), rand()%2+1, vec3(rand()%255/255.0,rand()%255/255.0,rand()%255/255.0), vec3(rand()%100/100.0), vec3(rand()%100/100.0));
        /*std::cout << pEsf->kd.x << " " << pEsf->ks.x << "\n";
        continue;*/
        objetos.emplace_back(pEsf);
    }

    Plano *pPlano = new Plano(vec3(0,1,0), 20);
    pPlano->color=vec3(0,0,1);
    pPlano->kd = vec3{0.7};
    pPlano->ks = vec3();

    objetos.emplace_back( pPlano );

    c.renderizar(objetos, luces);
}