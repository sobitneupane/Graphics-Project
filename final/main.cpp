#include "shading.h"
#include "objReader.h"
float xlook = 0,
      ylook = 0,
      zlook = 4;
void init(void)
{
    glClearColor(9.0, 9.0, 9.0, 0.0);
    //glShadeModel(GL_FLAT);
}

void exitWindow()
{
    glEnd();
    glFlush();
    glutMainLoop();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == 'a' || key == 'A')
    {
        transx -= 0.5;
    }
    else if (key == 'd' || key == 'D')
    {
        transx += 0.5;
    }
    else if (key == 'w' || key == 'W')
    {
        transy += 0.5;
    }
    else if (key == 's' || key == 'S')
    {
        transy -= 0.5;
    }
    else if (key == 'i')
    {
        Ia += 2;
    }
    else if (key == 'I')
    {
        Ia -= 2;
    }
}

void specialKeyFunction(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
        anglz -= 0.05;
    else if (key == GLUT_KEY_RIGHT)
        anglz += 0.05;
    else if (key == GLUT_KEY_DOWN)
        scal -= 2;
    else if (key == GLUT_KEY_UP)
        scal += 2;
    glutPostRedisplay();
}

void display(void)
{

    float x1, y1, r1, g1, x2, y2, r2, g2, x3, y3, r3, g3;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000 / 2.0, 1000 / 2.0, -600 / 2.0, 600 / 2.0);
    glBegin(GL_POINTS);
    File f("/home/sobit/Documents/GraphicsProject/projectGraphics/sobit.obj");

    for (int i = 0; i < f.indices.size(); i++)
    {
        if (f.xnormal[f.normalIndices[i]] * xlook + f.ynormal[f.normalIndices[i]] * ylook + f.znormal[f.normalIndices[i]] * zlook < 0)
        {
            x1 = f.x2d[f.indices[i]] * scal;
            y1 = f.y2d[f.indices[i]] * scal;
            r1 = f.illumIntensity[f.indices[i]] * 1.0 / 40.0;
            g1 = 0;
            x2 = (f.x2d[f.indices[++i]]) * scal;
            y2 = (f.y2d[f.indices[i]]) * scal;
            r2 = f.illumIntensity[f.indices[i]] * 1.0 / 40.0;
            g2 = 0;
            x3 = (f.x2d[f.indices[++i]]) * scal;
            y3 = (f.y2d[f.indices[i]]) * scal;
            r3 = f.illumIntensity[f.indices[i]] * 1.0 / 40.0;
            g3 = 0;
            //fillTriangle(30 * f.x2d[f.indices[i]], 30 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0, 30 * f.x2d[f.indices[++i]], 30 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0, 30 * f.x2d[f.indices[++i]], 30 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0);
            shader(x1, y1, r1, g1, 0.0, x2, y2, r2, g2, 0.0, x3, y3, r3, g3, 0.0);
        }
    }
    //fillTriangle(100, 100, 0, 1, 0, -100, -100, 0, 1, 0, -100, 0, 0, 1, 0);
    //fillTriangle(100, 0, 1, 0, 0, 100, -100, 1, 0, 0, -100, 100, 1, 0, 0);
    // float zprp = 400;
    // float zvp = 300;
    // float d = (zprp - zvp) / (zprp - 200);
    // float xtemp1 = 100 * d;
    // float ytemp1 = 100 * d;
    // cout << xtemp1 << endl;
    // cout << ytemp1 << endl;
    // float xtemp2 = -100 * d;
    // float ytemp2 = (-100) * d;
    // float xtemp3 = -100 * d;
    // float ytemp3 = 0 * d;

    // float xtemp12 = 100 * d;
    // float ytemp12 = 0 * d;
    // float xtemp22 = 100 * d;
    // float ytemp22 = (-100) * d;
    // float xtemp32 = -100 * (zprp - zvp) / (zprp - 0);
    // float ytemp32 = 100 * (zprp - zvp) / (zprp - 0);
    // float xtemp12 = 100 * cos(PI / 5.25) - 0 * cos(PI / 5.25);
    // float ytemp12 = 100 * sin(PI / 5.25) + 0 * sin(PI / 5.25) + 0;
    // float xtemp22 = 100 * cos(PI / 5.25) - (-100) * cos(PI / 5.25);
    // float ytemp22 = 100 * sin(PI / 5.25) + (-100) * sin(PI / 5.25) + 0;
    // float xtemp32 = -100 * cos(PI / 5.25) - 100 * cos(PI / 5.25);
    // float ytemp32 = -100 * sin(PI / 5.25) + 100 * sin(PI / 5.25) + 0;

    //fillTriangle(xtemp1, ytemp1, 1, 0, 0, xtemp2, ytemp2, 1, 0, 0, xtemp3, ytemp3, 1, 0, 0);
    // fillTriangle(xtemp12, ytemp12, 1, 0, 0, xtemp22, ytemp22, 1, 0, 0, xtemp32, ytemp32, 1, 0, 0);
    glEnd();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w * 1.0f / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(40.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Window");
    init();
    //glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(specialKeyFunction);
    glutMainLoop();
    exitWindow();
    return 0;
}