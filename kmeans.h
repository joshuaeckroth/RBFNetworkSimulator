#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>
#include <QPair>
#include <QPointF>

class KMeans
{
public:
    KMeans();

    static QVector<QPair<QPointF, QVector<QPointF> > >
            findCenters(const QVector<QPointF> *points,
                        const unsigned int numCenters);

    static double dist(QPointF p1, QPointF p2);
};

#endif // KMEANS_H
