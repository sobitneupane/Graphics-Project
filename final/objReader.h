#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#define PI 3.14159
using namespace std;
float anglz = 0.7, anglx = 0, angly = 0;
float scal = 300;
float Ia = 30;
float Id = 30;
float transx = 0, transy = 0, transz = 0;
float zprp = 4;
float zvp = 2;
float xprp = 0;
float yprp = 0;
float Ka = 0.8;
float Kd = 0.8;
typedef struct Vertex
{
    float x, y, z;
} Vertex;

//

float dotProduct(float a1, float a2, float a3, float b1, float b2, float b3)
{
    return a1 * b1 + a2 * b2 + a3 * b3;
}
class File
{
    string path;

  public:
    vector<float> xvertices;
    vector<float> yvertices;
    vector<float> zvertices;
    vector<float> xnormal;
    vector<float> ynormal;
    vector<float> znormal;
    vector<float> xvecnormal;
    vector<float> yvecnormal;
    vector<float> zvecnormal;
    vector<float> xlight;
    vector<float> ylight;
    vector<float> zlight;
    vector<float> illumIntensity;
    vector<float> x2d;
    vector<float> y2d;
    vector<unsigned int> indices;
    vector<unsigned int> normalIndices;
    float lx = -10;
    float ly = 2;
    float lz = 0;

    File(string x);
    void import_obj();
};

//defining class methods

File::File(string x)
{
    path = x;
    File::import_obj();
}
void File::import_obj()
{
    ifstream my_file;
    my_file.open(path);

    if (!my_file)
    {
        cout << "cannot open file" << endl;
        exit(1);
    }

    string line;
    while (getline(my_file, line))
    {
        string type;
        istringstream in(line);
        in >> type;

        if (type == "v")
        {
            float x, y, z;
            in >> x >> y >> z;
            xvertices.push_back(x / 3);
            yvertices.push_back(y / 3);
            zvertices.push_back(z / 3);

            continue;
        }
        else if (type == "f")
        {
            int a, b, c;
            char d;
            for (int i = 0; i < 3; i++)
            {
                in >> a >> d >> d >> c;
                indices.push_back(--a);
                normalIndices.push_back(--c);
            }
            continue;
        }
        else if (type == "vn")
        {
            float x, y, z;
            in >> x >> y >> z;
            xnormal.push_back(x);
            ynormal.push_back(y);
            znormal.push_back(z);

            continue;
        }
    }
    for (int i = 0; i < xvertices.size(); i++)
    {
        int counter = 0;
        float xtemp = 0;
        float ytemp = 0;
        float ztemp = 0;
        float ampTemp = 0;
        for (int j = 0; j < indices.size(); j++)
        {
            if (indices[j] == i)
            {
                xtemp += xnormal[normalIndices[j]];
                ytemp += ynormal[normalIndices[j]];
                ztemp += znormal[normalIndices[j]];
                counter++;
            }
        }
        ampTemp = sqrt(pow(xtemp, 2) + pow(ytemp, 2) + pow(ztemp, 2));
        xvecnormal.push_back(xtemp / ampTemp);
        yvecnormal.push_back(ytemp / ampTemp);
        zvecnormal.push_back(ztemp / ampTemp);
    }
    for (int i = 0; i < xvertices.size(); i++)
    {
        float xtemp = lx - xvertices[i];
        float ytemp = ly - yvertices[i];
        float ztemp = lz - zvertices[i];
        float temp = sqrt(pow(xtemp, 2) + pow(ytemp, 2) + pow(ztemp, 2));
        xlight.push_back(xtemp / temp);
        ylight.push_back(ytemp / temp);
        zlight.push_back(ztemp / temp);
    }
    float dotTemp;
    for (int i = 0; i < xvertices.size(); i++)
    {

        float d = (zprp - zvp) / (zprp - zvertices[i]);
        float xtemp = xvertices[i] * cos(anglz) - yvertices[i] * sin(anglz) + transx;
        float ytemp = xvertices[i] * sin(anglz) + yvertices[i] * cos(anglz) + transy;
        float xtemp1 = xtemp * d + xprp * (zvp - zvertices[i]) / (zprp - zvertices[i]);
        float ytemp1 = ytemp * d + yprp * (zvp - zvertices[i]) / (zprp - zvertices[i]);

        x2d.push_back(xtemp1);
        y2d.push_back(ytemp1);

        dotTemp = dotProduct(xvecnormal[i], yvecnormal[i], zvecnormal[i], xlight[i], ylight[i], zlight[i]);

        if (dotTemp > 0)
        {
            illumIntensity.push_back(Ka * Ia + Kd * Id * dotTemp);
        }
        else
        {
            illumIntensity.push_back(Ka * Ia);
        }
    }
}