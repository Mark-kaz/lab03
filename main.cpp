#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
using namespace std;



vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector <size_t> make_histogram(const vector<double>& numbers,size_t bin_count)
{
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    for (double number : numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * bin_count;
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

int main()
{
    DWORD info = GetVersion();
    printf("info = %lu\n",info);
    DWORD mask = 0x0000ffff;
    DWORD build;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    printf("M_version10 = %lu\n",version_major);
    printf("M_version16 = %08lx\n",version_major);
    printf("m_version10 = %lu\n",version_minor);
    printf("m_version16 = %08lx\n",version_minor);
    if ((info & 0x80000000) == 0)
    {
        build = platform;
    }
    else
        printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
    return 0;
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min, max;
    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
}
