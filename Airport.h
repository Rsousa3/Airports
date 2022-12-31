//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_AIRPORT_H
#define UNTITLED1_AIRPORT_H

#include <string>
#include "City.h"
#include "Position.h"

using namespace std;

class Airport {
    string code;
    string name;
    City city;
    Position position;

public:
    Airport();
    Airport(string codigo, string nome, City cidade, Position pos);
    Position getPosition();
    City getCity();
    string getCityName();
    string getCode();
    string getName();
};


#endif //UNTITLED1_AIRPORT_H
