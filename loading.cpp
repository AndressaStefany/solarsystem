//
// Created by andressa on 04/11/17.
//

#include "loading.h"
#include <sstream>

vector<string> split(string name, char limite)
{
    string aux;
    vector<string> retorno;

    for(int i=0; i<name.size();i++)
    {
        if(name[i]==limite)
        {
            retorno.push_back(aux);
            aux = "";
        } else {
            aux += name[i];
        }
    }
    //salva a ultima string
    retorno.push_back(aux);

    return retorno;
}

Loading::Loading(string arquivo)
{
    ifstream ifs(arquivo, ifstream::in);

    vector<vec3> vertices, normais;
    vector<vec2> texturas;
    string buffer;

    // percorre o arquivo de linha em linha
    while (getline(ifs,buffer))
    {
        // pega primeira string
        istringstream ss(buffer);
        ss >> buffer;

        if(buffer == "o")// nome objeto
        {
            // alocando
            obj.resize(obj.size()+1);

            ss >> obj.back().name;
        }
        else if(buffer == "usemtl")// material
        {
            // alocando meshs
            obj.back().meshs.resize(obj.back().meshs.size()+1);
            ss >> obj.back().meshs.back().name_mat;
        }
        else if(buffer == "v")// vertices
        {
            vec3 v;
            ss >> v[0] >> v[1] >> v[2];
            vertices.push_back(v);
        }
        else if(buffer == "vt")// vertices da textura
        {
            vec2 v;
            ss >> v[0] >> v[1];
            texturas.push_back(v);
        }
        else if(buffer == "vn")// normal
        {
            vec3 v;
            ss >> v[0] >> v[1] >> v[2];
            normais.push_back(v);
        }
        else if(buffer == "f")// faces
        {
            vector<string> aux;
            face f;
            string x[3];
            //separa dos espaços
            ss >> x[0] >> x[1] >> x[2];
            for (int i = 0; i < 3; i++)
            {
                aux = split(x[i], '/');
                int d = stoi(aux[0]) - 1;
                f.v[i] = vertices[d];
                if(aux[1]!="") {
                    d = stoi(aux[1]) - 1;
                    f.t[i] = texturas[d];
                }
                d = stoi(aux[2]) - 1;
                f.n[i] = normais[d];
            }
            //add nova face
            obj.back().meshs.back().faces.push_back(f);
        }
        else
        {}
    }
    ifs.close();
}

#include <time.h>
#include <cstdlib>

void Loading::draw() {
    srand(time(NULL));

    glPushMatrix();
    for(auto& o:obj){
        for(auto& m:o.meshs) {
            for(auto& f:m.faces) {
                glPushMatrix();
                //criar cor aleatoria
                glColor3f(rand()%100/100.0,rand()%100/100.0,rand()%100/100.0);
                glBegin(GL_TRIANGLES);
                glNormal3dv(f.n[0].n);
                glVertex3dv(f.v[0].n);

                glNormal3dv(f.n[1].n);
                glVertex3dv(f.v[1].n);

                glNormal3dv(f.n[2].n);
                glVertex3dv(f.v[2].n);
                glEnd();
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}
