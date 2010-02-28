#ifndef RADIALBASISFUNCTION_H
#define RADIALBASISFUNCTION_H

#include <QVector>
#include <QPointF>

class RadialBasisFunction
{
public:
    RadialBasisFunction();
    virtual QVector<QPointF> sample(QVector<double> xs, double weight) const = 0;
};

#endif // RADIALBASISFUNCTION_H
