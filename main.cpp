#include <iostream>
#include <vector>
#include "histogram.h"
#include "histogram_new.h"
#include <string.h>
#include <sstream>
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
vector <size_t> make_histogram(vector <double> numbers,size_t bin_count,double min,double max)
{
    vector<size_t> bins(bin_count);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return(bins);
}
void show_histogram_text(vector<size_t>bins,size_t number_count)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";
        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }
        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout<<' ';
        cout << '\n';
    }
}

string make_info_text()
{
    stringstream buffer;
    /*printf("Version is  %x\n", GetVersion());
    printf("Version is  %u\n", GetVersion());*/
    //printf("info = %lu\n",info);
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD build;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    /*printf("M_version10 = %lu\n",version_major);
    printf("M_version16 = %08lx\n",version_major);
    printf("m_version10 = %lu\n",version_minor);
    printf("m_version16 = %08lx\n",version_minor);*/

    if ((info & 0x80000000) == 0)
    {
    //printf("minor_bit = %u",0);
    build = platform;
    }
    else printf("minor_bit = %u",1);

    //printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);

    char system_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system_name);
    GetComputerNameA(system_name, &Size);
    buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << " " << "Computer name: " << system_name;
    return buffer.str();
}
int main ()
{
    //printf("System name: %s", system_name);
    string info = make_info_text();
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers=input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min;
    double max;
    find_minmax(numbers,min,max);
    const auto bins = make_histogram(numbers, bin_count,min,max);
    show_histogram_svg(bins,number_count, info);
    return 0;
}
