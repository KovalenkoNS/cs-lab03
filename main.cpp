#include <iostream>
#include <vector>
#include "histogram.h"
#include "histogram_new.h"

#include <sstream>
#include <string>
#include <curl/curl.h>

#include <string.h>
#include <sstream>
#include <windows.h>

#include <cstdlib>
#include <ctime>

using namespace std;

struct Options
{
    size_t counts;
    bool counts_correct;
    bool use_help;
    char* url;
};

Options parse_args(int argc, char** argv)
{
    Options opt;
    opt.url = 0;
    opt.counts = 0;
    opt.counts_correct = false;
    opt.use_help = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i],"-generate") == 0)
            {
                if(i+1<argc)
                {
                    opt.counts = atoi(argv[i+1]);
                    if (opt.counts)
                    {
                        opt.counts_correct = true;
                        i++;
                    }
                    else
                    {
                        opt.use_help=true;
                    }
                }

                else
                {
                    opt.use_help = true;
                }
            }
        }
        else
        {
            opt.url = argv[i];
        }
    }
    return opt;
}


vector<double> input_numbers(istream& in, size_t count, const Options &opt)
{
    vector<double> result(count);

    if (opt.counts_correct)
    {
        srand ( time(NULL) );

        result.resize(opt.counts);
        for (size_t i = 0; i < opt.counts; i++)
        {
            result[i]= rand() % 10;
        }

    }
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            in >> result[i];
        }
    }
    return result;
}
Input read_input(istream& in,bool prompt, const Options &opt)
{
    Input data;
    size_t number_count;
    if(prompt)
    {
    cerr << "Enter number count: ";
    if ( opt.counts_correct )
    {
        number_count = opt.counts;
    }
    else
    {
        in >> number_count;
    }
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count, opt );
    cerr << "Enter column count: ";
    in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count, opt );
        in >> data.bin_count;
    }
    return data;
}

vector <size_t> make_histogram(Input data)
{
    double min;
    double max;
    find_minmax(data.numbers,min,max);
    vector<size_t> bins(data.bin_count);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return(bins);
}

void show_histogram_text(vector<size_t>bins)
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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input download(const string& address, const Options &opt) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
   curl_easy_cleanup(curl);
   return read_input(buffer, false, opt);
}

int main (int argc, char* argv[])
{

    Input input;

    Options opt;
    opt = parse_args(argc,argv);
    //cerr << "opt.counts=" << opt.counts << " opt.url = "<<opt.url<<"opt.counts.correct = " <<opt.counts_correct;

    if (opt.use_help)
    {
        cerr<<"Error of input: use -generate "<<endl;
        exit (2);
    }
    if (opt.url)
    {
        input = download(opt.url, opt);
    }
    else
    {
        input = read_input(cin, true, opt);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins);

    return 0;
}
