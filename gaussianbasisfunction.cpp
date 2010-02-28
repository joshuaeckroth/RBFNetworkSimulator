#include <cassert>
#include <cmath>
using namespace std;

#include "gaussianbasisfunction.h"
#include "kmeans.h"

GaussianBasisFunction::GaussianBasisFunction(double _mean, double _variance)
    : mean(_mean), variance(_variance)
{
}

QVector<double> GaussianBasisFunction::sample(QVector<double> xs) const
{
    QVector<double> samples(xs.size());
    for(int i = 0; i < xs.size(); i++)
    {
        samples[i] = exp(-1.0/(2*variance)*pow(xs[i] - mean, 2.0));
    }

    return samples;
}

