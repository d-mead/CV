#include <fstream>
#include <iostream>
#include <cmath>
#include <list>

using namespace std;

const int width = 800, height = 800;

int array[800][800] = {0};

int randNumber(){
    int num = rand() % 799 + 1;
    return num;
}

void set_pixel(int x, int y){
    if ((x < 800)&&(y < 800)){
        ::array[x][y] = 1;
    }

}

void draw_line(int x1, int y1, int x2, int y2){
    int dx = (x2-x1);
    int dy = (y2-y1);

    if (abs(dx) > abs(dy)){
        int dj = 1;  // assume the y pixel will be increasing as the x pixel increases
        if (dx < 0) { // if the change in x is negative (going backwards)
            // swap the points
            int a1 = x1;
            x1 = x2;
            x2 = a1;
            int b1 = y1;
            y1 = y2;
            y2 = b1;
            // recalculate dx and dy with new points
            dx = -dx;
            dy = -dy;
        }
        if (dy < 0){ // if the change in y is negative (going down instead of up)
            dj = -1; // make the y pixel decrease as the x pixel increases
            dy = -dy; // adjust the dy to account for this
        }
        int e = dy-dx; // set the e
        int j = y1; // first y pixel

        for (int i = x1; i <= x2-1; i++){ // from starting to final x pixels
            set_pixel(i, j); // add the i, j to the pixels that need to be 'lit'
            if (e>=0){ // if e is less than 0
                j+=dj; // y pixel needs to be changed
                e-=dx; // decrease e
            }
            e+=dy; //increase e because you moved
        }
    } else {
        int di = 1;
        if (dy < 0) {

            int a1 = x1;
            x1 = x2;
            x2 = a1;
            int b1 = y1;
            y1 = y2;
            y2 = b1;

            dy = -dy;
            dx = -dx;
        }
        if (dx < 0){
            di = -1;
            dx = -dx;
        }
        int e = dx-dy;
        int i = x1;

        for (int j = y1; j <= y2-1; j++){
            set_pixel(i, j);
            if (e>=0){
                i+=di;
                e-=dy;
            }
            e+=dx;
        }
    }
}

void draw_circle(int i, int j, int r){
    int x, y, xmax, y2, y2_new, ty;

    xmax = (int)(r/sqrt(2));

    y = r;
    y2 = y*y;
    ty = (2*y)-1;
    y2_new = y2;

    for (x = 0; x <= xmax + 2; x++){
        if ((y2-y2_new) >= ty){
            y2 -= ty;
            y -= 1;
            ty -=2;
        }

        set_pixel (x + i, y + i);
        set_pixel (x + i, -y + i);
        set_pixel (-x + i, y + i);
        set_pixel (-x + i, -y + i);
        set_pixel (y + i, x + i);
        set_pixel (y + i, -x + i);
        set_pixel (-y + i, x + i);
        set_pixel (-y + i, -x + i);

        y2_new -= (2*x)-3;
    }
}



int main() {
    srand(time(NULL));
    ofstream img ("picture.ppm");

    // intro portion of the ppm file
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    //

    // make the random points
    int x1 = randNumber();//114;//
    int y1 = randNumber();//305;//

    int x2 = randNumber();//599;//
    int y2 = randNumber();//659;//

    int x3 = randNumber();//331;//
    int y3 = randNumber();//67;//
    //

    :: array[x1][y1] = 1;
    :: array[x2][y2] = 1;
    :: array[x3][y3] = 1;

//    cout << :: array[x1][y1] << endl;

    draw_line(x1, y1, x3, y3);
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);

    int a, b, c;

    a = (int)sqrt(pow((x2-x1), 2) + pow(y2-y1, 2));
    b = (int)sqrt(pow((x3-x1), 2) + pow(y3-y1, 2));
    c = (int)sqrt(pow((x2-x3), 2) + pow(y2-y3, 2));

    int s = (int)(0.5)*(a + b + c);

    int small_r = (int)(sqrt(((s-a) + (s-b) + (s-c))/s));
    int big_r = (int)(a*b*c)/(4*small_r*s);

    draw_circle(500, 500, 100);

    cout << x1 << " " << y1 << endl;
    cout << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << endl;

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){

            int r = 255;
            int g = 255;
            int b = 255;

            if(::array[x][y] == 1){
                cout << "dark";
                r = 0;
                g = 0;
                b = 0;
                if ((x==x1)&&(y==y1)){
                    r = 253;
                    g = 0;
                    b = 0;
                }
                if ((x==x2)&&(y==y2)){
                    r = 0;
                    g = 254;
                    b = 0;
                }
                if ((x==x3)&&(y==y3)){
                    r = 0;
                    g = 0;
                    b = 255;
                }
            }

            img << r << " " << g << " " << b << " ";
        }
        img << endl;
    }
//
//    system("open picture.ppm");
}





