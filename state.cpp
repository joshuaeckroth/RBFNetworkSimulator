#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "state.h"
#include "radialbasisfunction.h"
#include "gaussianbasisfunction.h"
#include "kmeans.h"

State::State()
    : basis(NULL), sampleStart(0.0), sampleEnd(0.0),
    noiseStart(0.0), noiseEnd(0.0), numSamples(0), numCenters(0)
{
    qsrand(time(NULL));
}

const QVector<QPointF>* State::getSamples() const
{
    return &samples;
}

const QVector<QPair<QPointF, QVector<QPointF> > >* State::getCenters() const
{
    return &centers;
}

void State::sampleFunction()
{
    samples.clear();
    samples.resize(numSamples);
    double noise;
    double input;
    double sample;
    for(unsigned int i = 0; i < numSamples; i++)
    {
        noise = (noiseEnd - noiseStart) * (double(qrand())/double(RAND_MAX)) + noiseStart;
        input = double(qrand())/double(RAND_MAX);
        sample = noise + 0.5 + 0.4*sin(2 * 3.1415926 * input);
        samples[i] = QPointF(input, sample);
    }

    emit newSamples();
}

void State::findCenters()
{
    centers = KMeans::findCenters(&samples, numCenters);
    emit newCenters();
}

void State::trainNetwork()
{
}

void State::reset()
{
}

void State::newConfig()
{
    if(basis != NULL)
        delete basis;
    basis = new GaussianBasisFunction;
    numSamples = 75;
    sampleStart = 0.0;
    sampleEnd = 1.0;
    noiseStart = -0.1;
    noiseEnd = 0.1;
    numCenters = 5;
}
