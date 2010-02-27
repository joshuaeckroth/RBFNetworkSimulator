#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

#include <QVector>
#include <QPointF>
#include <QPair>

class QWidget;

class State;
class QwtPlotCurve;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot(QWidget *parent, State *_state);

private slots:
    void newSamples();
    void newCenters();

private:
    State *state;
    const QVector<QPointF> *samples;
    const QVector<QPair<QPointF, QVector<QPointF> > > *centers;
    QwtPlotCurve *sampledFunction;
    QVector<QwtPlotCurve *> centerCurves;
    QVector<QwtPlotCurve *> centerMemberCurves;
};

#endif // PLOT_H
