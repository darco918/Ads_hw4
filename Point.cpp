//
// Created by murja on 27-May-20.
//

#include "Point.h"

int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

void Point::setX(int n) {
    this->x = n;
}

void Point::setY(int n) {
    this->y = n;
}

Point::Point()
        :x(0),y(0) {
}

Point::Point(int, int):x(x),y(y) {
}

Point::Point(const Point &mPoint)
        :x(mPoint.x), y(mPoint.y){
}

