#ifndef Global_CPP
#define Global_CPP
#include "Global.hpp"
#include <fstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <windows.h>
#include <vector>

using namespace std;
using namespace std::chrono;
void gb_logTime()
{
    cout << "\n"
         << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << std::flush;
}

string gb_getCurrentTimeInMilliseconds()
{
    return to_string(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

void gb_setCurrentEnvirnoment(string env)
{
    currentEnvirnoment = env;
}

string gb_getCurrentEnvirnoment()
{
    return currentEnvirnoment;
}

double computeCovarianceVector(std::vector<double> v1, std::vector<double> v2)
{
    double m1 = std::accumulate(v1.begin(), v1.end(), 0.0) / v1.size();
    double m2 = std::accumulate(v2.begin(), v2.end(), 0.0) / v2.size();
    double sum = 0;
    for (unsigned i = 0; i < v1.size(); i++)
    {
        sum += (v1[i] - m1) * (v2[i] - m2);
    }
    double result = sum / (v1.size() - 1);
    return result;
}

void computeCovarianceMatrix(std::vector<std::vector<double>> vec, std::vector<std::vector<double>> &v_cov)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        std::vector<double> tmp;
        for (unsigned j = 0; j < vec.size(); j++)
        {
            double val = computeCovarianceVector(vec[i], vec[j]);
            tmp.push_back(val);
        }
        v_cov.push_back(tmp);
    }
}

double gb_vectorMedian(std::vector<double> scores)
{
    size_t size = scores.size();

    if (size == 0)
    {
        return 0; // Undefined, really.
    }
    else
    {
        sort(scores.begin(), scores.end());
        if (size % 2 == 0)
        {
            return (scores[size / 2 - 1] + scores[size / 2]) / 2;
        }
        else
        {
            return scores[size / 2];
        }
    }
}

void gb_print2DVector(std::vector<std::vector<double>> vec)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        for (unsigned j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void gb_print1DVector(std::vector<double> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

double **vectorTo2DArray(std::vector<std::vector<double>> &vals)
{
    int N = vals.size();
    int M = vals[0].size();
    double **temp;
    temp = new double *[N];
    for (int i = 0; (i < N); i++)
    {
        temp[i] = new double[M];
        for (int j = 0; (j < M); j++)
        {
            temp[i][j] = vals[i][j];
        }
    }

    return temp;
}

double gb_minOfThree(double x, double y, double z)
{
    return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

void test()
{
   
}

#endif // !Global
