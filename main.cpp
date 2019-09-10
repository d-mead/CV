#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

const int width = 800, height = 800;

int array[800][800] = {0};

int randNumber(){
    int num = rand() % 799 + 1;
    return num;
}

void draw_line(int a1, int b1, int a2, int b2){
    int dx = a2-a1;
    int dy = b2-b1;
    int m = dy/dx;
    int j = b1;
    int e = dy-dx;


    for (int i = a1; i < (a2-1); i++) {
        ::array[i][j] = 1;
        if (e >= 0){
            j += 1;
            e -= dx;
        }
        e += dy;
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
    int x1 = randNumber();
    int y1 = randNumber();

    int x2 = randNumber();
    int y2 = randNumber();

    int x3 = randNumber();
    int y3 = randNumber();
    //

    :: array[x1][y1] = 1;
    :: array[x2][y2] = 1;
    :: array[x3][y3] = 1;

    cout << :: array[x1][y1] << endl;

    draw_line(x1, y1, x2, y2);
    draw_line(x3, y3, x2, y2);
//    draw_line(x1, y1, x3, y3);

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
                    r = 255;
                    g = 0;
                    b = 0;
                }
                if ((x==x2)&&(y==y2)){
                    r = 255;
                    g = 0;
                    b = 0;
                }
                if ((x==x3)&&(y==y3)){
                    r = 255;
                    g = 0;
                    b = 0;
                }
            }

            img << r << " " << g << " " << b << " ";
        }
        img << endl;
    }
//
//    system("open picture.ppm");
}





