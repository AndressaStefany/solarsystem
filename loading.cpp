//
// Created by andressa on 04/11/17.
//

#include "loading.h"
#include <sstream>

Loading::Loading(string arquivo)
{
    ifstream ifs(arquivo, ifstream::in);

    vector<vec3> vertices, normais;
    vector<vec2> texturas;
    string buffer;
    object estrutura_obj;

    while (getline(ifs,buffer))
    {
        istringstream ss(buffer);
        ss >> buffer;

        if(buffer == "o")
        {
            ss >> estrutura_obj.name;
            cout << "Objeto: " << estrutura_obj.name << endl;
        }
        else if(buffer == "usemtl")
        {

        }
        else if(buffer == "v")
        {
            vec3 v;
            ss >> v[0] >> v[1] >> v[2];
            vertices.push_back(v);
        }
        else if(buffer == "vt")
        {
            vec2 v;
            ss >> v[0] >> v[1];
            texturas.push_back(v);
        }
        else if(buffer == "vn")
        {
            vec3 v;
            ss >> v[0] >> v[1] >> v[2];
            normais.push_back(v);
        }
        else if(buffer == "f")
        {
            string x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;
        }
        else
        {
            cout << endl;
        }
    }
    ifs.close();
}