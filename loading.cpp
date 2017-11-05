//
// Created by andressa on 04/11/17.
//

#include "loading.h"
#include <sstream>

Loading::Loading(string arquivo)
{
    int vertice=0, normal=0, textura=0, face=0, conj_face=0;
    ifstream ifs;

    ifs.open(arquivo, ifstream::in);

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
        else if(buffer == "v")
        {
//            ss >> estrutura_obj.meshs[conj_face].faces[face].v[0]
//               >> estrutura_obj.meshs[conj_face].faces[face].v[1]
//               >> estrutura_obj.meshs[conj_face].faces[face].v[2];

//            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;

            vertice++;
        }
        else if(buffer == "vt")
        {
            float x[2];
            ss >> x[0] >> x[1];
            cout << buffer << " " << x[0] << " " << x[1] << endl;

            textura++;
        }
        else if(buffer == "vn")
        {
            float x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;

            normal++;
        }
        else if(buffer == "f")
        {
            string x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;

            face++;
        }
        else
        {
            cout << endl;

        }

    }

    ifs.close();
}