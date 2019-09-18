//
// Created by David Mead on 9/17/19.
//

#include <fstream>
//#include <iostream>
#include <cmath>
#include <list>

//David Mead 9/17/2019 Project 1

using namespace std;

const int width = 800, height = 800;

int array[800][800] = {0};

double randNumber(){
    double num = ((double) rand() / (RAND_MAX));//rand() % 1 + 1;
    return num;
}

void set_pixel(double x, double y){
    x = x*800;
    y = y*800;
    if ((x < 800)&&(y < 800)&&(x > -1)&&(y > -1)){
        ::array[(int)x][(int)y] = 1;
    }

}

void draw_line(double x1, double y1, double x2, double y2){
    double dx = (x2-x1);
    double dy = (y2-y1);

    if (abs(dx) > abs(dy)){
        double dj = 1.0/800;  // assume the y pixel will be increasing as the x pixel increases
        if (dx < 0) { // if the change in x is negative (going backwards)
            // swap the points
            double a1 = x1;
            x1 = x2;
            x2 = a1;
            double b1 = y1;
            y1 = y2;
            y2 = b1;
            // recalculate dx and dy with new points
            dx = -dx;
            dy = -dy;
        }
        if (dy < 0){ // if the change in y is negative (going down instead of up)
            dj = -1.0/800; // make the y pixel decrease as the x pixel increases
            dy = -dy; // adjust the dy to account for this
        }
        double e = dy-dx; // set the e
        double j = y1; // first y pixel

        for (double i = x1; i <= x2-1.0/800; i+= 1.0/800){ // from starting to final x pixels
            set_pixel(i, j); // add the i, j to the pixels that need to be 'lit'
            if (e>=0){ // if e is less than 0
                j+=dj; // y pixel needs to be changed
                e-=dx; // decrease e
            }
            e+=dy; //increase e because you moved
        }
    } else {
        double di = 1.0/800;
        if (dy < 0) {

            double a1 = x1;
            x1 = x2;
            x2 = a1;
            double b1 = y1;
            y1 = y2;
            y2 = b1;

            dy = -dy;
            dx = -dx;
        }
        if (dx < 0){
            di = -1.0/800;
            dx = -dx;
        }
        double e = dx-dy;
        double i = x1;

        for (double j = y1; j <= y2-1.0/800; j+= 1.0/800){
            set_pixel(i, j);
            if (e>=0){
                i+=di;
                e-=dy;
            }
            e+=dx;
        }
    }
}

double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow((x1-x2), 2) + pow(y1-y2, 2));
}

void draw_circle(double i, double j, double r){
    double x, y, xmax, y2, y2_new, ty;

    xmax = (double)(r/sqrt(2));

    y = r;
    y2 = y*y;
    ty = (2*y)-1.0/800;
    y2_new = y2;

    for (x = 0; x <= xmax+2.0/800; x+= 1.0/800){
        if ((y2-y2_new) >= ty){
            y2 -= ty;
            y -= 1.0/800;
            ty -=2.0/800;
        }

        set_pixel (x + i, y + j);
        set_pixel (x + i, -y + j);
        set_pixel (-x + i, y + j);
        set_pixel (-x + i, -y + j);
        set_pixel (y + i, x + j);
        set_pixel (y + i, -x + j);
        set_pixel (-y + i, x + j);
        set_pixel (-y + i, -x + j);

        y2_new -= (2*x)-3.0/800;
    }
}

void midpoint_circles(double x1, double y1, double x2, double y2){
    double midx, midy, r;

    midx = (x1 + x2)/2;
    midy = (y1 + y2)/2;

    r = distance(midx, midy, x1, y1);

    draw_circle(midx, midy, r);
}



int main() {
    srand(time(NULL));
    ofstream img ("picture2.ppm");

    // intro portion of the ppm file
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    //

    double x1, y1, x2, y2, x3, y3, x4, y4;
    // make the random points
    x1 = randNumber();//114;//
    y1 = randNumber();//305;//

    x2 = randNumber();//599;//
    y2 = randNumber();//659;//

    x3 = randNumber();//331;//
    y3 = randNumber();//67;//

    x4 = randNumber();//331;//
    y4 = randNumber();//67;//
    //



    //draws endpoints
    set_pixel(x1, y1);
    set_pixel(x2, y2);
    set_pixel(x3, y3);
    set_pixel(x4, y4);
    //

    midpoint_circles(x1, y1, x2, y2);
    draw_line(x1, y1, x2, y2);

    midpoint_circles(x3, y3, x2, y2);
    draw_line(x3, y3, x2, y2);

    midpoint_circles(x3, y3, x4, y4);
    draw_line(x3, y3, x4, y4);

    midpoint_circles(x1, y1, x4, y4);
    draw_line(x1, y1, x4, y4);


    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){

            int r = 255;
            int g = 255;
            int b = 255;

            if(::array[x][y] == 1){
//                cout << "x";
                r = 0;
                g = 0;
                b = 0;
//                if ((x==x1)&&(y==y1)){
//                    r = 253;
//                    g = 0;
//                    b = 0;
//                }
//                if ((x==x2)&&(y==y2)){
//                    r = 0;
//                    g = 254;
//                    b = 0;
//                }
//                if ((x==x3)&&(y==y3)){
//                    r = 0;
//                    g = 0;
//                    b = 255;
//                }
            }

            img << r << " " << g << " " << b << " ";
        }
        img << endl;
    }
}