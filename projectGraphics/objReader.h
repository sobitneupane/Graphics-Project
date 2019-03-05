#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#define PI 3.14159
using namespace std;
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
    float ly = -10;
    float lz = -10;
    float xlook = -1 / sqrt(2);
    float ylook = -1 / sqrt(2);
    float ylook =
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
    for (int i = 1; i <= xvertices.size(); i++)
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

        x2d.push_back(xvertices[i] * cos(PI / 5.25) - yvertices[i] * cos(PI / 5.25));
        y2d.push_back(xvertices[i] * sin(PI / 5.25) + yvertices[i] * sin(PI / 5.25) + zvertices[i]);
        if (dotProduct())
            dotTemp = dotProduct(xvertices[i], yvertices[i], zvertices[i], xlight[i], ylight[i], zlight[i]);
        if (dotTemp > 0)
        {
            illumIntensity.push_back(0.8 * 30 + 0.8 * 30 * dotTemp);
        }
        else
        {
            illumIntensity.push_back(0.8 * 30);
        }
    }
}