#ifndef RBFNETWORK_H
#define RBFNETWORK_H

#include <QVector>
#include <QPointF>

class RadialBasisFunction;

class RBFNetwork
{
public:
    RBFNetwork(QVector<RadialBasisFunction *> _basisFunctions, double _eta);
    void trainNetwork(QVector<QPointF> data);
    double processInput(double input);
    QVector<double> getWeights() const;

private:
    QVector<RadialBasisFunction *> basisFunctions;
    QVector<double> weights;
    double eta;
    double bias;

    void lms(double input, double output, double expected);
};

#endif // RBFNETWORK_H
