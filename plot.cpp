#include <cmath>
using namespace std;

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

Plot::Plot(QWidget *parent, State *_state)
    : QwtPlot(parent), state(_state), samples(NULL), centers(NULL),
    sampledFunction(NULL)
{
    connect(state, SIGNAL(newSamples()), this, SLOT(newSamples()));
    connect(state, SIGNAL(newCenters()), this, SLOT(newCenters()));
    connect(state, SIGNAL(newBases()), this, SLOT(newBases()));

    setCanvasBackground(QColor(255,255,255));

    centerCurves.clear();
    centerMemberCurves.clear();
    basisCurves.clear();
    basisColors.clear();
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
    for(int i = 0; i < centerCurves.size(); i++)
    {
        if(centerCurves[i] != NULL)
        {
            centerCurves[i]->detach();
            delete centerCurves[i];
        }
    }
    for(int i = 0; i < centerMemberCurves.size(); i++)
    {
        if(centerMemberCurves[i] != NULL)
        {
            centerMemberCurves[i]->detach();
            delete centerMemberCurves[i];
        }
    }

    centerCurves.clear();
    centers = state->getCenters();

    basisColors.clear();
    basisColors.resize(centers->size());
    centerCurves.resize(centers->size());
    centerMemberCurves.resize(centers->size());
    QVector<QPointF> center(1);
    int r, g, b;
    for(int i = 0; i < centers->size(); i++)
    {
        center[0] = (*centers)[i].first;

        r = qrand() % 256;
        g = qrand() % 256;
        b = qrand() % 256;

        basisColors[i] = QColor(r, g, b);

        centerCurves[i] = new QwtPlotCurve(QString("Centers"));
        centerCurves[i]->setSamples(center);
        centerCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
        centerCurves[i]->setStyle(QwtPlotCurve::NoCurve);
        centerCurves[i]->setSymbol(
                QwtSymbol(QwtSymbol::Ellipse, QBrush(),
                          QPen(basisColors[i], 2.0), QSizeF(15.0, 15.0)));
        centerCurves[i]->attach(this);

        centerMemberCurves[i] = new QwtPlotCurve(QString("Points in XYZ"));
        centerMemberCurves[i]->setSamples((*centers)[i].second);
        centerMemberCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
        centerMemberCurves[i]->setStyle(QwtPlotCurve::NoCurve);
        centerMemberCurves[i]->setSymbol(
                QwtSymbol(QwtSymbol::Ellipse, QBrush(),
                          QPen(basisColors[i]), QSizeF(8.0, 8.0)));
        centerMemberCurves[i]->attach(this);
    }

    replot();
}

void Plot::newBases()
{
    for(int i = 0; i < basisCurves.size(); i++)
    {
        if(basisCurves[i] != NULL)
        {
            basisCurves[i]->detach();
            delete basisCurves[i];
        }
    }

    bases = state->getBases();
    basisCurves.resize(bases->size());
    for(int i = 0; i < bases->size(); i++)
    {
        basisCurves[i] = new QwtPlotCurve(QString("Basis curve"));
        basisCurves[i]->setSamples((*bases)[i]);
        basisCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
        basisCurves[i]->setPen(QPen(basisColors[i]));
        basisCurves[i]->attach(this);
    }

    replot();
}
