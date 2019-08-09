#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;
#include <vector>

double computeCovarianceVector(vector<double> v1, vector<double> v2)
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

void computeCovarianceMatrix(vector<vector<double>> vec, vector<vector<double>> &v_cov)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        vector<double> tmp;
        for (unsigned j = 0; j < vec.size(); j++)
        {
            double val = computeCovarianceVector(vec[i], vec[j]);
            tmp.push_back(val);
        }
        v_cov.push_back(tmp);
    }
}

void outer_product(vector<double> row, vector<double> col, vector<vector<double>> &dst)
{
    for (unsigned i = 0; i < row.size(); i++)
    {
        for (unsigned j = 0; j < col.size(); i++)
        {
            dst[i][j] = row[i] * col[j];
        }
    }
}

//computes row[i] - val for all i;
void subtract(vector<double> row, double val, vector<double> &dst)
{
    for (unsigned i = 0; i < row.size(); i++)
    {
        dst[i] = row[i] - val;
    }
}

//computes m[i][j] + m2[i][j]
void add(vector<vector<double>> m, vector<vector<double>> m2, vector<vector<double>> &dst)
{
    for (unsigned i = 0; i < m.size(); i++)
    {
        for (unsigned j = 0; j < m[i].size(); j++)
        {
            dst[i][j] = m[i][j] + m2[i][j];
        }
    }
}

double mean(std::vector<double> &data)
{
    double mean = 0.0;

    for (unsigned i = 0; (i < data.size()); i++)
    {
        mean += data[i];
    }

    mean /= data.size();
    return mean;
}

void scale(vector<vector<double>> &d, double alpha)
{
    for (unsigned i = 0; i < d.size(); i++)
    {
        for (unsigned j = 0; j < d[i].size(); j++)
        {
            d[i][j] *= alpha;
        }
    }
}

void compute_covariance_matrix(vector<vector<double>> &d, vector<vector<double>> &dst)
{
    for (unsigned i = 0; i < d.size(); i++)
    {
        double y_bar = mean(d[i]);
        vector<double> d_d_bar(d[i].size());
        subtract(d[i], y_bar, d_d_bar);
        vector<vector<double>> t(d.size());
        outer_product(d_d_bar, d_d_bar, t);
        add(dst, t, dst);
    }
    scale(dst, 1 / (d.size() - 1));
}

double vectorMedian(vector<double> scores)
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