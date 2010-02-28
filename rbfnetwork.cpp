#include <cstdlib>
using namespace std;

#include <QPointF>
#include <QDebug>

#include "gaussianbasisfunction.h"
#include "rbfnetwork.h"

RBFNetwork::RBFNetwork(QVector<RadialBasisFunction *> _basisFunctions, double _eta)
    : basisFunctions(_basisFunctions), eta(_eta)
{
    weights.clear();
    weights.resize(basisFunctions.size());

    // randomize weights [0.0, 1.0]
    for(int i = 0; i < weights.size(); i++)
    {
        weights[i] = 0.0; //double(qrand())/double(RAND_MAX);
    }
    bias = 0.0; //double(qrand())/double(RAND_MAX);
}

QVector<double> RBFNetwork::getWeights() const
{
    return weights;
}

void RBFNetwork::trainNetwork(QVector<QPointF> data)
{
    int index;
    int ordered;
    int *ordering = new int[data.size()];
    bool seen;
    double output;

    // 100 epochs
    for(int epoch = 1; epoch <= 100; epoch++)
    {
        // get a random ordering of the data
        ordered = 0;
        while(ordered < data.size())
        {
            index = qrand() % data.size();

            // check if we've seen this number
            seen = false;
            for(int i = 0; i < ordered; i++)
            {
                if(ordering[i] == index)
                {
                    seen = true;
                    break;
                }
            }
            if(!seen)
            {
                ordering[ordered++] = index;
                output = processInput(data[index].x());
                lms(data[index].x(), output, data[index].y());
            }
        }
    }

    delete [] ordering;
}

double RBFNetwork::processInput(double input)
{
    QVector<double> outputVec;
    QVector<double> inputVec(1);
    double output = 0.0;

    // for each basis function, get an output from a single sample input;
    // then add up all the basis function outputs
    for(int i = 0; i < basisFunctions.size(); i++)
    {
        inputVec[0] = input;
        outputVec = basisFunctions[i]->sample(inputVec);
        output += weights[i] * outputVec[0];
    }
    output += bias;

    return output;
}

void RBFNetwork::lms(double input, double output, double expected)
{
    QVector<double> outputVec;
    QVector<double> inputVec(1);
    inputVec[0] = input;
    for(int i = 0; i < weights.size(); i++)
    {
        outputVec = basisFunctions[i]->sample(inputVec);
        weights[i] += eta * (expected - output) * outputVec[0];
    }
    bias += eta * (expected - output);
}
