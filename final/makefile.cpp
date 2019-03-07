#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    string s(argv[1]);
    auto it = find(s.begin(), s.end(), '.');
    if (it == s.end())
    {
        cout << "Not a valid c++ file" << endl;
        return 0;
    }
    string s2 = s.substr(0, it - s.begin());
    string s5 = "rm -rf " + s2;
    system(s5.c_str());
    string s3 = "g++ -std=c++11 " + s + " -o " + s2 + "-lglfw -lglut -lGLU -lGL";
    system(s3.c_str());
    string s4 = "./" + s2;
    system(s4.c_str());
    return 0;
}