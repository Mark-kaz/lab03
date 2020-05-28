#include <iostream>
#include <vector>
#include "svg.h"
using namespace std;
void svg_rect(double x, double y, double width, double height,string stroke = "black",string fill = "black")
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";
}

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}
double three( size_t number_count, size_t BLOCK_WIDTH)
{
   return  ((number_count*BLOCK_WIDTH)/3.0) ;
}
double  shirina(  size_t number_count)
{
    const auto BLOCK_WIDTH = 10;
    size_t IMAGE_WIDTH;
    do
    {
        cerr << "Enter IMAGE_WIDTH: ";
        cin >> IMAGE_WIDTH;

        if ( IMAGE_WIDTH < 70 )
        {
            cerr  << "< 70" << endl;

        }

        if (IMAGE_WIDTH > 800 )
        {
            cerr  << "> 800 " << endl;

        }
        if ( IMAGE_WIDTH < three(number_count,BLOCK_WIDTH ))
        {
            cerr << three << endl;

        }

    }
    while (IMAGE_WIDTH < 70 || IMAGE_WIDTH > 800 || IMAGE_WIDTH < (number_count*BLOCK_WIDTH)/3.0);

}
void show_histogram_svg(const vector<size_t>& bins,  size_t number_count)
{



    const auto BLOCK_WIDTH = 10;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;

    double top = 0;
    size_t IMAGINE_WIDTH=shirina (number_count);
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"chartreuse","#7FFF00");
        top += BIN_HEIGHT;
    }
    svg_end();
}
