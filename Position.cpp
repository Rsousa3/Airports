//
// Created by ricardo on 29-12-2022.
//

#include "Position.h"

using namespace std;

Position::Position(double px, double py): lat(px), lon(py) {}

double Position::getLat() {return lat;}

double Position::getLon() {return lon;}