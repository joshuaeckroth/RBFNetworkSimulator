#ifndef GAUSSIANBASISFUNCTION_H
#define GAUSSIANBASISFUNCTION_H

#include <QVector>
#include <QPointF>

#include "radialbasisfunction.h"

class GaussianBasisFunction : public RadialBasisFunction
{
public:
    GaussianBasisFunction(double _mean, double _variance);
    QVector<QPointF> sample(QVector<double> xs, double weight) const;

private:
    double mean;
    double variance;
};

#endif // GAUSSIANBASISFUNCTION_H
