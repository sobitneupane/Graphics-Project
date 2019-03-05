
#include "algos.h"
#include "objReader.h"

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

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600 / 2.0, 600 / 2.0, -600 / 2.0, 600 / 2.0);
    glBegin(GL_POINTS);
    //glEnable(GL_DEPTH_TEST);
    File f("/home/sobit/Documents/GraphicsProject/projectGraphics/sobit.obj");
    for (int i = 0; i < f.indices.size(); i++)
    {
        fillTriangle(100 * f.x2d[f.indices[i]], 100 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0, 100 * f.x2d[f.indices[++i]], 100 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0, 100 * f.x2d[f.indices[++i]], 100 * f.y2d[f.indices[i]], f.illumIntensity[f.indices[i]] * 1.0 / 30, 0.0, 0.0);
        //cout << f.illumIntensity[f.indices[i]] << endl;
    }

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

    //gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Window");
    init();
    //glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    exitWindow();
    return 0;
}