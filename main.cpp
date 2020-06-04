#include <curl/curl.h>
#include<sstream>
#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
#include <string.h>
#include <sstream>
using namespace std;

vector<double> input_numbers(istream& in, const size_t count)

{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt)
{
    Input input;
    size_t number_count;
    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        input.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> input.bin_count;

    }

    else
    {
        in >> number_count;
        input.numbers = input_numbers(in, number_count);
        in >> input.bin_count;
    }

    return input;
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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address)
{
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
    {
        double total;
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res!=CURLE_OK)
        {
            cout<<curl_easy_strerror(res);
            exit(1);
        }
        if(CURLE_OK == res)
        {
            res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
            if(CURLE_OK == res)
            {
                printf("Time: %.1f", total);
            }
        }
        curl_easy_cleanup(curl);
    };

    return read_input(buffer, false);
}



int main(int argc, char* argv[])
{

    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }

    size_t number_count;
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, number_count);
    return 0;
}
