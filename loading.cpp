//
// Created by andressa on 04/11/17.
//

#include "loading.h"

#include <sstream>

Loading::Loading(string arquivo){
    std::ifstream ifs;

    ifs.open(arquivo, std::ifstream::in);

    string buffer;
    while (getline(ifs,buffer)) {
        istringstream ss(buffer);
        ss >> buffer;
        if(buffer == "v")
        {
            float x[3];
            ss >> x[0] >> x[1] >> x[2];
            std::cout << buffer << " " << x[0] << " " << x[1] << " " << x[2] << std::endl;
        }
    }

    ifs.close();
}