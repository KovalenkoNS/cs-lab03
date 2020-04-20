#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
using namespace std;
void find_minmax(const vector<double> numbers, double& min, double& max);
void show_histogram_svg(const vector<size_t> bins);
#endif // HISTOGRAM_H_INCLUDED
