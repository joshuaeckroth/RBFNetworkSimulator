#ifndef GAUSSIANBASISFUNCTION_H
#define GAUSSIANBASISFUNCTION_H

#include <QVector>
#include <QPointF>

#include "radialbasisfunction.h"

class GaussianBasisFunction : public RadialBasisFunction
{
public:
    GaussianBasisFunction(double _mean, double _variance);
    QVector<double> sample(QVector<double> xs) const;

private:
    double mean;
    double variance;
};

#endif // GAUSSIANBASISFUNCTION_H
