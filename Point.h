//
// Created by murja on 27-May-20.
//

#ifndef ADS4_POINT_H
#define ADS4_POINT_H



class Point {
private:
    int x;
    int y;
public:
    Point();
    Point(int, int);
    Point(const Point&);
    int getX() const;
    void setX(int);
    int getY() const;
    void setY(int);
};

#endif //ADS4_POINT_H
