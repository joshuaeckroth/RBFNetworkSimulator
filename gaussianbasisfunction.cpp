#include <vector>
#include <cassert>
using namespace std;

#include "gaussianbasisfunction.h"

GaussianBasisFunction::GaussianBasisFunction()
{
}

vector<double> GaussianBasisFunction::sample(vector<double> xs) const
{
    assert(xs.size() == getDim());

    return vector<double>();
}

unsigned int GaussianBasisFunction::getDim() const
{
    return 1;
}
