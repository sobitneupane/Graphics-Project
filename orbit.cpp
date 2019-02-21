#include <iostream>
#include <cmath>

#include <GL/glut.h>

int refreshmill = 1;
int counterForRevolution = 0;

void init(void)
{
    glClearColor(9.0, 9.0, 9.0, 0.0);
    glShadeModel(GL_FLAT);
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshmill, timer, 0);
}

//drawOrbitPlanet function draws an orbit along with a planet revolving around the center
void drawOrbitPlanet(float rx, float ry, float radiusPlanet)
{
    float x = 0, y = ry; //starting from point (0,ry)
    float pointX[10000]; //x-coordinates
    float pointY[10000]; //y-coordinates
    float decisionParameter;
    int counter = 0;
    float xStep = 0.1, yStep = 0.1;
    decisionParameter = pow(ry, 2) - pow(rx, 2) * ry + 0.25 * pow(rx, 2);

    while (pow(ry, 2) * x <= pow(rx, 2) * y)
    {
        pointX[counter] = x;
        pointY[counter] = y;
        counter++;

        // pointX[counter] = y;
        // pointY[counter] = x;
        // counter++;
        x = x + xStep;
        if (decisionParameter < 0)
        {
            decisionParameter = decisionParameter + 2 * pow(ry, 2) * x + pow(ry, 2);
        }
        else
        {
            y = y - yStep;
            decisionParameter = decisionParameter + 2 * pow(ry, 2) * x - 2 * pow(rx, 2) * y + pow(ry, 2);
        }
    }
    //for region 2;
    /*  x = rx;
    y = 0; */
    decisionParameter = pow(ry, 2) * pow((x + 0.5), 2) + pow(rx, 2) * pow(y - 1, 2) - rx * rx * ry * ry;
    //decisionParameter = pow(rx, 2) - rx * pow(ry, 2) + 0.25 * pow(ry, 2);
    //while (pow(ry, 2) * x > pow(rx, 2) * y)
    while (y > 0)
    {
        pointX[counter] = x;
        pointY[counter] = y;
        counter++;

        // y = y + yStep;
        y = y - yStep;
        if (decisionParameter >= 0)
        {
            decisionParameter = decisionParameter - 2 * y * rx * rx + rx * rx;

            /* x = x - xStep;
            decisionParameter = decisionParameter - 2 * x * pow(ry, 2) + 2 * y * pow(rx, 2) + pow(rx, 2); */
        }
        else
        {
            x = x + xStep;
            decisionParameter = decisionParameter - 2 * y * rx * rx + rx * rx + 2 * ry * ry * x;

            //decisionParameter = decisionParameter + 2 * y * pow(rx, 2) + pow(rx, 2);
        }
    }
    for (int i = 0; i < counter; i++)
    {
        pointX[counter + i] = pointX[counter - i - 1];
        pointY[counter + i] = -pointY[counter - i - 1];
    }
    for (int i = 0; i < counter; i++)
    {
        pointX[2 * counter + i] = -pointX[i];
        pointY[2 * counter + i] = -pointY[i];
    }
    for (int i = 0; i < counter; i++)
    {
        pointX[3 * counter + i] = -pointX[counter - i - 1];
        pointY[3 * counter + i] = pointY[counter - i - 1];
    }
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < 4 * counter; i++)
    {
        glVertex2f(pointX[i], pointY[i]);
    }
    glEnd();
    glPushMatrix();
    glColor3f(0.0, 100.0, 100.0);
    //glRotatef(angle, 0, 0, 1);
    glTranslatef(pointX[counterForRevolution], pointY[counterForRevolution], 0);
    glutSolidSphere(radiusPlanet, 100, 100);
    glPopMatrix();
    counterForRevolution += 4;
    if (counterForRevolution >= 4 * counter)
    {
        counterForRevolution = 0;
    }
}
//drawOrbitPlanet function ends here

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    drawOrbitPlanet(30, 15, 3);
    //drawSphere(30, 0);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0, w / (GLfloat)h, 3.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 60.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 700);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
