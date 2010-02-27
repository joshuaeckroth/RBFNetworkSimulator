#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>
#include <qwt_legend.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>

#include <QWidget>
#include <QString>
#include <QDebug>

#include "plot.h"
#include "state.h"
#include "kmeans.h"

Plot::Plot(QWidget *parent, State *_state)
    : QwtPlot(parent), state(_state), samples(NULL), centers(NULL),
    sampledFunction(NULL), centersCurve(NULL)
{
    connect(state, SIGNAL(newSamples()), this, SLOT(newSamples()));
    connect(state, SIGNAL(newCenters()), this, SLOT(newCenters()));

    setCanvasBackground(QColor(255,255,255));
}

void Plot::newSamples()
{
    samples = state->getSamples();
    if(sampledFunction != NULL)
    {
        sampledFunction->detach();
        delete sampledFunction;
    }
    sampledFunction = new QwtPlotCurve(QString("Sampled Function"));
    sampledFunction->setSamples(*samples);
    sampledFunction->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
    sampledFunction->setStyle(QwtPlotCurve::NoCurve);
    sampledFunction->setSymbol(
            QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor("black")),
                      QPen(QColor("black")), QSizeF(3.0, 3.0)));
    sampledFunction->attach(this);
    replot();
}

void Plot::newCenters()
{
    centers = state->getCenters();
    QVector<QPointF> justCenters(centers->size());
    QVector<double> maxDists(centers->size());
    double dist;
    double tmpDist;
    for(int i = 0; i < centers->size(); i++)
    {
        justCenters.push_back((*centers)[i].first);
        dist = 0;
        for(int j = 0; j < (*centers)[i].second.size(); j++)
        {
            tmpDist = KMeans::dist((*centers)[i].first, (*centers)[i].second[j]);
            if(tmpDist > dist)
                dist = tmpDist;
        }
        maxDists[i] = dist;
        qDebug() << QString("max dist: %1").arg(dist);
    }

    if(centersCurve != NULL)
    {
        centersCurve->detach();
        delete centersCurve;
    }
    centersCurve = new QwtPlotCurve(QString("Centers"));
    centersCurve->setSamples(justCenters);
    centersCurve->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
    centersCurve->setStyle(QwtPlotCurve::NoCurve);
    centersCurve->setSymbol(
            QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor("blue")),
                      QPen(QColor("blue")), QSizeF(3.0, 3.0)));
    centersCurve->attach(this);
    replot();
}
