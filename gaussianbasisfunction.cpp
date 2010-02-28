#include <cassert>
#include <cmath>
using namespace std;

#include <QtAlgorithms>

#include "gaussianbasisfunction.h"
#include "kmeans.h"

GaussianBasisFunction::GaussianBasisFunction(double _mean, double _variance)
    : mean(_mean), variance(_variance)
{
}

QVector<QPointF> GaussianBasisFunction::sample(QVector<double> xs, double weight) const
{
    qSort(xs);

    QVector<QPointF> samples(xs.size());
    for(int i = 0; i < xs.size(); i++)
    {
        samples[i] = QPointF(xs[i],
            weight * (exp(-1.0/(2*variance)*pow(mean - xs[i], 2.0))));
    }

    return samples;
}

