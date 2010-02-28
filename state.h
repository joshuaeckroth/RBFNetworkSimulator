#ifndef STATE_H
#define STATE_H

#include <QVector>
#include <QObject>
#include <QPointF>
#include <QPair>

class RadialBasisFunction;

class State : public QObject
{
    Q_OBJECT

public:
    State();
    const QVector<QPointF>* getSamples() const;
    const QVector<QPair<QPointF, QVector<QPointF> > >* getCenters() const;
    const QVector<QVector<QPointF> >* getBases() const;

signals:
    void newSamples();
    void newCenters();
    void newBases();

public slots:
    void sampleFunction();
    void findCenters();
    void trainNetwork();
    void reset();
    void newConfig();

private:
    double sampleStart;
    double sampleEnd;
    double noiseStart;
    double noiseEnd;
    unsigned int numSamples;
    unsigned int numCenters;
    QVector<QPointF> samples;
    QVector<QPair<QPointF, QVector<QPointF> > > centers;
    QVector<RadialBasisFunction *> basisFunctions;
    QVector<QVector<QPointF> > bases;
};

#endif // STATE_H
