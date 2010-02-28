#ifndef RADIALBASISFUNCTION_H
#define RADIALBASISFUNCTION_H

#include <QVector>
#include <QPointF>

class RadialBasisFunction
{
public:
    RadialBasisFunction();
    virtual QVector<double> sample(QVector<double> xs) const = 0;
};

#endif // RADIALBASISFUNCTION_H
