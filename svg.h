#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
void svg_rect(double x, double y, double width, double height, string stroke, string fill );


void
svg_text(double left, double baseline, string text);

void
svg_begin(double width, double height);

void
svg_end();

double three( size_t number_count, size_t BLOCK_WIDTH);

double shirina(  size_t numer_count);

void
show_histogram_svg(const vector<size_t>& bins, size_t IMAGE_WIDTH);



#endif // SVG_H_INCLUDED
