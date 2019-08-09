#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>
#include <thread>
// #include "modules\socket\SocketServer.cpp"
// #include "modules\algorithm\MyAlgo.cpp"
#include "..\lib\dlib\all\source.cpp"
// #include "dlib\matrix.h"

using namespace dlib;
using namespace std;

int main()
{
	// SocketServer socketServer;
	// MyAlgo m;
	matrix<double> M(4, 4);
	M = 0., 0., 0., 0.,
	0., 0.17111133, 0., 0.0445714,
	0., 0., 0., 0.,
	0., 0.0445714, 0., 0.02959689;

	cout << pinv(M) << endl;
	return 0;
}
