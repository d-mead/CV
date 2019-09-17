#include <fstream>
#include <iostream>
#include <cmath>
#include <list>

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

void draw_full_line(double x1, double y1, double x2, double y2){
    double m = (y2-y1)/(x2-x1);
    double y0, y800;

    y0 = m*(0.0-x1)+y1;
    y800 = m*(1.0-x1)+y1;

    draw_line(0.0, y0, 1.0, y800);

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

void circumcircle(double x1, double y1, double x2, double y2, double x3, double y3){
    double ma, mb;
    double x, y, r;
    ma = (y2 - y1)/(x2 - x1);
    mb = (y3 - y2)/(x3 - x2);

    x = ((x1*x1 + y1*y1)*(y2 - y3) + (x2*x2 + y2*y2)*(y3 - y1) + (x3*x3 + y3*y3)*(y1 - y2))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));
    y = ((x1*x1 + y1*y1)*(x3 - x2) + (x2*x2 + y2*y2)*(x1 - x3) + (x3*x3 + y3*y3)*(x2 - x1))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));

    r = sqrt(pow((x1-x), 2) + pow((y1-y), 2));

    draw_circle(x, y, r);
}

void incircle(double x1, double y1, double x2, double y2, double x3, double y3){
    double a, b, c;
    a = sqrt(pow((x3-x2), 2) + pow(y3-y2, 2));
    b = sqrt(pow((x3-x1), 2) + pow(y3-y1, 2));
    c = sqrt(pow((x2-x1), 2) + pow(y2-y1, 2));

    double x, y, r;

    x = (a*x1 + b*x2 + c*x3)/(a + b + c);
    y = (a*y1 + b*y2 + c*y3)/(a + b + c);

    double s = (a + b + c)/2;
    r = (sqrt(((s-a) * (s-b) * (s-c))/s));

    draw_circle(x, y, r);

}

void ninecircle(double x1, double y1, double x2, double y2, double x3, double y3){

    double xa, ya, xb, yb, xc, yc, xd, yd, xe, ye, r;

    //centroid
    xa = (x1 + x2 + x3)/3;
    ya = (y1 + y2 + y3)/3;

    //circumcenter
    xb = ((x1*x1 + y1*y1)*(y2 - y3) + (x2*x2 + y2*y2)*(y3 - y1) + (x3*x3 + y3*y3)*(y1 - y2))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));
    yb = ((x1*x1 + y1*y1)*(x3 - x2) + (x2*x2 + y2*y2)*(x1 - x3) + (x3*x3 + y3*y3)*(x2 - x1))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));

    //orthocenter
    xc = xa - (xb-xa)*2;
    yc = ya - (yb-ya)*2;

    //nine point center
    xd = (xc + xb)/2;
    yd = (yc + yb)/2;

    //mid
    xe = (x1 + x2)/2;
    ye = (y1 + y2)/2;

    r = sqrt(pow((xd-xe), 2) + pow(yd-ye, 2));

    draw_circle(xd, yd, r);

}

void eulerline(double x1, double y1, double x2, double y2, double x3, double y3){

    double z1, z2;

    z1 = (y2 + y3 -2*y1)/(x2 + x3 - 2*x1);
    z2 = (y1 + y3 -2*y2)/(x1 + x3 - 2*x2);

    double xa, ya;

    xa = (x1 + x2 + x3)/3;
    ya = (y1 + y2 + y3)/3;

    double xb, yb;

    xb = ((x1*x1 + y1*y1)*(y2 - y3) + (x2*x2 + y2*y2)*(y3 - y1) + (x3*x3 + y3*y3)*(y1 - y2))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));
    yb = ((x1*x1 + y1*y1)*(x3 - x2) + (x2*x2 + y2*y2)*(x1 - x3) + (x3*x3 + y3*y3)*(x2 - x1))/(2*(x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));

    draw_full_line(xa, ya, xb, yb);

}

int main() {
    srand(time(NULL));
    ofstream img ("picture.ppm");

    // intro portion of the ppm file
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    //

    double x1, y1, x2, y2, x3, y3;
    // make the random points
    x1 = randNumber();//114;//
    y1 = randNumber();//305;//

    x2 = randNumber();//599;//
    y2 = randNumber();//659;//

    x3 = randNumber();//331;//
    y3 = randNumber();//67;//
    //

    //draws endpoints
    set_pixel(x1, y1);
    set_pixel(x2, y2);
    set_pixel(x3, y3);
    //

    //draws lines of the triangle
    draw_line(x1, y1, x3, y3);
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    //

    circumcircle(x1, y1, x2, y2, x3, y3);

    incircle(x1, y1, x2, y2, x3, y3);

    eulerline(x1, y1, x2, y2, x3, y3);

    ninecircle(x1, y1, x2, y2, x3, y3);

//    cout << x1 << " " << y1 << endl;
//    cout << x2 << " " << y2 << endl;
//    cout << x3 << " " << y3 << endl;

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
//
//    system("open picture.ppm");
}





