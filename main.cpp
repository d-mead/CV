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

void draw_line(int x1, int y1, int x2, int y2){
    int dx = (x2-x1);
    int dy = (y2-y1);

    if (dx > dy){
        int j = y1;
        int e = dy-dx;

        for (int i = x1; i <= x2-1; i++){
            ::array[i][j]=1;
            if (e>=0){
                j+=1;
                e-=dx;
            }
            e+=dy;
        }
    } else {
        int i = x1;
        int e = dx-dy;

        for (int j = y1; j <= y2-1; j++){
            ::array[i][j]=1;
            if (e>=0){
                i+=1;
                e-=dy;
            }
            e+=dx;
        }
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

//    cout << :: array[x1][y1] << endl;

    draw_line(x1, y1, x2, y2);
    draw_line(x1, y1, x3, y3);
    draw_line(x2, y2, x3, y3);

    cout << x1 << " " << y1 << endl;
    cout << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << endl;

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){

            int r = 255;
            int g = 255;
            int b = 255;

            if(::array[x][y] == 1){
//                cout << "dark";
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





