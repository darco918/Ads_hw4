#include <iostream>
#include "vector"
#include "stack"
#include "Point.h"
#include "fstream"

std::ifstream fin("points.txt");


std::ostream& operator<<(std::ostream& os, const Point& obj){
    //this is to print the point more easily
    os<<"("<<obj.getX()<<", "<<obj.getY()<<")";
    return os;
}

int distSq(Point p1, Point p2)
{
    //compute the distance between 2 point using a formula I found online
    return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}


int orientation(Point p1, Point p2, Point p3)
{
    int val = (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) - (p2.getX() - p1.getX()) * (p3.getY() - p2.getY());
    if (val == 0){
        return 0;
    } else if(val > 0){
        return 1;
    } else {
        return 2;
    }
}

Point nextToTop(std::stack<Point> &stack)
{
    Point p = stack.top();
    stack.pop();
    Point res = stack.top();
    stack.push(p);
    return res;
}

Point p0; // intialized with 0,0


int compare(const void *mPoint1, const void *mPoint2) //Function to compare two points for qsort.
{
    auto *p1 = (Point *)mPoint1;
    auto *p2 = (Point *)mPoint2;

    int mOrientation = orientation(p0, *p1, *p2);
    if (mOrientation == 0){
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    } else if (mOrientation == 2) {
        return -1;
    } else {
        return 1;
    }
}

void convexHull(std::vector<Point>& points){
    int yBottomMost = points[0].getY();
    int minY = 0;
    for(std::size_t i=1; i<points.size();i++){ //Finding the lowest point <==> minimal y
        int y = points[i].getY();

        if( (y < yBottomMost) or ( yBottomMost == y and points[i].getX() < points[minY].getX()) ){
            // if two points have the same y, then we choose the one with the smaller x
            yBottomMost = points[i].getY();
            minY = i;
        }
    }

    std::swap(points[0], points[minY]);
    //the first element is now the smallest y

    p0 = points[0];

    std::qsort(&points[1], points.size()-1, sizeof(Point), compare);
    // normal sort did not work. For some reason qsort does..
    int j = 1;
    for(std::size_t i=1; i<points.size();i++){
        while (i < points.size()-1 and orientation(p0, points[i], points[i+1]) == 0){
            i++;
        }

        points[j] = points[i];
        j++;
    }

    if (j < 3) return;

    std::stack<Point> pointStack;
    pointStack.push(points[0]);
    pointStack.push(points[1]);
    pointStack.push(points[2]);

    for(std::size_t i=3; i < j; i++){
        while( orientation(nextToTop(pointStack), pointStack.top(), points[i]) != 2 ){
            pointStack.pop();
        }
        pointStack.push(points[i]);
    }

    while (!pointStack.empty()){
        Point p = pointStack.top();
        std::cout<<p<<" ";
        pointStack.pop();
    }
}


int main() {
    std::vector<Point> points;
    while(!fin.eof()){
        int x,y;
        fin>>x>>y;
        points.push_back(Point(x,y)); //Placing all of the points from the file in the vector.s
    }
    fin.close();
    convexHull(points);
    return 0;
}
