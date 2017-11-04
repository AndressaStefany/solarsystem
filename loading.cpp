//
// Created by andressa on 04/11/17.
//

#include "loading.h"
#include <sstream>

Loading::Loading(string arquivo)
{
    std::ifstream ifs;

    ifs.open(arquivo, std::ifstream::in);

    string buffer;

    while (getline(ifs,buffer))
    {
        istringstream ss(buffer);
        ss >> buffer;

        if(buffer == "o")
        {
            string objeto;
            ss >> objeto;

            cout << "objeto: " << objeto << endl;
        }
        else if(buffer == "v")
        {
            float x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;
        }
        else if(buffer == "vt")
        {
            float x[2];
            ss >> x[0] >> x[1];
            cout << buffer << " " << x[0] << " " << x[1] << endl;
        }
        else if(buffer == "vn")
        {
            float x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;
        }
        else if(buffer == "f")
        {
            string x[3];
            ss >> x[0] >> x[1] >> x[2];
            cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << endl;
        }
        else
        {
            cout <<"outra coisa"<<endl;

        }

    }

    ifs.close();
}