//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_AIRLINE_H
#define UNTITLED1_AIRLINE_H

#include <string>

using namespace std;

class Airline {
    string code;
    string name;
    string callsign;
    string country;

public:
    Airline(string cod, string nome, string sign, string pais);
};
#endif //UNTITLED1_AIRLINE_H
