#include "histogram_new.h"
#include <iostream>
#include <math.h>
using namespace std;

size_t bin_count (size_t MAX_A, size_t max_c, size_t bin)
{
    double param = 0;
    double scaling_factor =1;
    scaling_factor = (double)MAX_A / max_c;
    param = (size_t)(bin * scaling_factor);
    return param;
}


void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end()
{
    cout << "</svg>\n";
}
//svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,stroke,fill);
//svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin),bin);

void svg_rect(double x, double y, double width, double height,string stroke,string fill)
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

void svg_text(double left, double baseline, string text,size_t bin)
{
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<bin<<"</text>";
}

void show_histogram_svg(const vector<size_t> bins,size_t number_count)
{
    const auto IMAGE_WIDTH = 400;
    const auto OTSTUP = IMAGE_WIDTH - 40;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 400 - 30;
    const auto TEXT_BASELINE = 20;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 5;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    string stroke="black";
    string fill="red";
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    //double scaling_factor = 1;

    for (size_t bin : bins)
    {
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin),bin);
        if (scaling_needed)
        {
            bin = bin_count(MAX_ASTERISK, max_count, bin);

        }
        const double bin_width = BLOCK_WIDTH * bin;
        const double RECT_LEFT = OTSTUP - bin_width;
        //svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin),bin);
        svg_rect(RECT_LEFT, top, bin_width, BIN_HEIGHT,stroke,fill);
        top += BIN_HEIGHT;
        }
    svg_end();
}
