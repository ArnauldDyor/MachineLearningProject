#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT
#endif


#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Eigen/Dense"


using namespace Eigen;
using namespace std;

