//
// Created by ricardo on 29-12-2022.
//

#include <cmath>
#include "Position.h"

using namespace std;

Position::Position(): lat(0), lon(0) {}

Position::Position(double px, double py): lat(px), lon(py) {}

double Position::getLat() {return lat;}

double Position::getLon() {return lon;}

double Position::Haversine(Position p2) {
    //distâncias
    double dLat = (p2.getLat() - lat) * M_PI / 180.0;
    double dLon = (p2.getLon() - lon) * M_PI / 180.0;

    // converter lat e lon para radianos
    double lat1 = lat * M_PI / 180.0;
    double lat2 = p2.getLat() * M_PI / 180.0;

    // aplicar fórmula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}