#ifndef Global_CPP
#define Global_CPP
#include "Global.hpp"
#include <fstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

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

void print2DVector(vector<vector<double>> vec)
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

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(double A[N][N], double temp[N][N], int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(double A[N][N], int n)
{
    int D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    double temp[N][N]; // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(double A[N][N], double adj[N][N])
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    double temp[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(double A[N][N], double (&inverse)[N][N])
{
    // Find determinant of A[][]
    int det = determinant(A, N);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // Find adjoint
    double adj[N][N];
    adjoint(A, adj);

    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = adj[i][j] / float(det);

    return true;
}


double **vectorTo2DArray(vector<vector<double>> &vals)
{
    int N = vals.size();
    int M = vals[0].size();
    double **temp;
    temp = new double *[N];
    for (unsigned i = 0; (i < N); i++)
    {
        temp[i] = new double[M];
        for (unsigned j = 0; (j < M); j++)
        {
            temp[i][j] = vals[i][j];
        }
    }

    return temp;
}

#endif // !Global
