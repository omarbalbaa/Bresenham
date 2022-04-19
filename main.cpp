#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<math.h>
/*
        Omar Balbaa
Line drawing using Bresenham
*/


int phyWidth= 700;
int phyHeight= 700;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2;
int centerY=logHeight/2;

void init2D (float r, float g, float b){
    glClearColor(r,g,b,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}

void addPixel(int x,int y){
    glBegin(GL_POLYGON);
    glVertex2i(x,y);
    glVertex2i(x+1,y);
    glVertex2i(x+1,y+1);
    glVertex2i(x,y+1);
    glEnd();
}
void BresenhamLine(int x0, int y0, int xEnd, int yEnd){

    int dx = xEnd - x0, dy = yEnd - y0;

    float m = dy / dx;

    if (dx < 0){
        dx = -dx;
    }
    if (dy < 0 ){
        dy = -dy;
    }
    int p;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
    int x = x0, y = y0;
    if (dx > dy){
        addPixel(x,y);
        p = 2*dy - dx;
        for (int i = 0; i<dx; i++){
            if (p>=0){
                if(m < 0)
                    y -- ;
                else
                    y ++;
                p += twoDyMinusDx ;
            }
            else
                p += twoDy;
            x ++;
            addPixel(x,y);
        }
    }
    else {
        addPixel(x,y);
        p = 2*dx-dy;
        for (int i =0 ; i<dy ; i++){
            if (p>=0){
                if (m < 0)
                    x--;
                else
                    x++;
                p += twoDxMinusDy;
            }
            else
                p+=twoDx;
            y++;
            addPixel(x,y);
        }
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    BresenhamLine(30,30,80,70);
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char*argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(phyWidth, phyHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("lines applying Bresenham");
    init2D(0,0,0);
    glutDisplayFunc(display);
    glutMainLoop();

}
