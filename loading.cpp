//
// Created by andressa on 04/11/17.
//

#include "loading.h"

Loading::Loading(string arquivo){
    std::ifstream ifs;

    ifs.open("/home/andressa/Área\ de\ Trabalho/solarsystem/"+arquivo, std::ifstream::in);

    string buffer;
    while (ifs >> buffer) {
        std::cout << buffer << std::endl;
    }

    ifs.close();
}