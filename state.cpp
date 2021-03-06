#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

#include <QDebug>

#include "state.h"
#include "radialbasisfunction.h"
#include "gaussianbasisfunction.h"
#include "kmeans.h"
#include "rbfnetwork.h"

State::State()
    : sampleStart(0.0), sampleEnd(0.0), eta(0.0),
    noiseStart(0.0), noiseEnd(0.0), numSamples(0), numCenters(0), network(NULL)
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

const QVector<QVector<QPointF> >* State::getBases() const
{
    return &bases;
}

const QVector<QPointF>* State::getEstimated() const
{
    return &estimated;
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
        input = (sampleEnd - sampleStart) * (double(qrand())/double(RAND_MAX)) + sampleStart;
        sample = noise + 0.5 + 0.4*sin(2 * 3.1415926 * input);
        samples[i] = QPointF(input, sample);
    }

    emit newSamples();
}

void State::findCenters()
{
    centers = KMeans::findCenters(&samples, numCenters);
    emit newCenters();

    // find variances
    QVector<double> variances(centers.size(), -1.0);
    double variance;
    for(int c = 0; c < centers.size(); c++)
    {
        // fill these in later (centers with one point)
        if(centers[c].second.size() == 1) continue;

        variance = 0.0;
        for(int i = 0; i < centers[c].second.size(); i++)
        {
            variance += pow(centers[c].second[i].x() - centers[c].first.x(), 2.0);
        }
        variances[c] = variance/double(centers[c].second.size());
    }

    // find average variance
    double avgVariance = 0.0;
    for(int c = 0; c < centers.size(); c++)
    {
        if(variances[c] >= 0.0)
            avgVariance += variances[c];
    }
    avgVariance /= double(centers.size());

    // set in single-point centers to average variance
    for(int c = 0; c < centers.size(); c++)
    {
        if(centers[c].second.size() == 1) variances[c] = avgVariance;
    }

    // create radial basis functions
    basisFunctions.resize(centers.size());
    for(int c = 0; c < centers.size(); c++)
    {
        basisFunctions[c] = new GaussianBasisFunction(centers[c].first.x(), variances[c]);
    }
}

void State::trainNetwork()
{
    if(network != NULL)
        delete network;
    network = new RBFNetwork(basisFunctions, eta);
    network->trainNetwork(samples);
    weights = network->getWeights();

    QVector<double> xs(numSamples);
    for(unsigned int i = 0; i < numSamples; i++)
    {
        xs[i] = samples[i].x();
    }
    qSort(xs);

    bases.clear();
    bases.resize(basisFunctions.size());
    QVector<double> output(numSamples);
    for(int i = 0; i < basisFunctions.size(); i++)
    {
        bases[i].clear();
        bases[i].resize(numSamples);
        output = basisFunctions[i]->sample(xs);
        for(unsigned int j = 0; j < numSamples; j++)
        {
            bases[i][j] = QPointF(xs[j], weights[i] * output[j]);
        }
    }

    estimated.clear();
    estimated.resize(numSamples);
    for(unsigned int i = 0; i < numSamples; i++)
    {
        estimated[i] = QPointF(xs[i], network->processInput(xs[i]));
    }

    emit newBases();
}

void State::reset()
{
    for(int i = 0; i < basisFunctions.size(); i++)
    {
        if(basisFunctions[i] != NULL)
            delete basisFunctions[i];
    }
    basisFunctions.clear();
}

void State::newConfig()
{
    numSamples = 500;
    sampleStart = 0.0;
    sampleEnd = 3.0;
    noiseStart = -0.1;
    noiseEnd = 0.1;
    numCenters = 8;
    eta = 0.01;
}
