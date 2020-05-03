#include "histogram.h"
#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_2()
{
    double min =0;
    double max =0;
    find_minmax({-1, -2, -3}, min, max);
    assert (min == -3);
    assert (max == -1);
}

void test_3()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert (min == 1);
    assert (max == 1);
}

void test_4()
{
    double min =0;
    double max =0;
    find_minmax({1}, min, max);
    assert (min == 1);
    assert (max == 1);
}

void test_5()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert (min == 0);
    assert (max == 0);
}

int main()
{
    test_positive();
    test_2();
    test_3();
    test_4();
    test_5();
}
