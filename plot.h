#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

#include <QVector>
#include <QPointF>
#include <QPair>
#include <QColor>

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
    void newBases();

private:
    State *state;
    const QVector<QPointF> *samples;
    const QVector<QPair<QPointF, QVector<QPointF> > > *centers;
    const QVector<QVector<QPointF> > *bases;
    QwtPlotCurve *sampledFunction;
    QwtPlotCurve *estimatedCurve;
    const QVector<QPointF> *estimated;
    QVector<QwtPlotCurve *> centerCurves;
    QVector<QwtPlotCurve *> centerMemberCurves;
    QVector<QwtPlotCurve *> basisCurves;
    QVector<QColor> basisColors;
};

#endif // PLOT_H
