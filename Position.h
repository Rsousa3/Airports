//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_POSITION_H
#define UNTITLED1_POSITION_H

using namespace std;

class Position {
    double lat;
    double lon;

public:
    Position();
    Position(double px, double py);
    double getLat();
    double getLon();
    double Haversine(Position p2); //Calcula a distância em kms de 2 posições
};
#endif //UNTITLED1_POSITION_H
