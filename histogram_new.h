#ifndef HISTOGRAM_NEW_H_INCLUDED
#define HISTOGRAM_NEW_H_INCLUDED
#include <iostream>
#include <vector>
#include <windows.h>
#include <string.h>
#include <sstream>
using namespace std;
void show_histogram_svg(const vector<size_t> bins, size_t number_count);
void svg_begin(double width, double height);
void svg_end();
void svg_rect(double x, double y, double width, double height,string stroke,string fill);
void svg_text(double left, double baseline, string text,size_t bin);
size_t bin_count (size_t MAX_A, size_t max_c, size_t bin);
#endif // HISTOGRAM_NEW_H_INCLUDED
