#include <cstdlib>
#include <cmath>
using namespace std;

#include <QObject>
#include <QDebug>

#include "kmeans.h"

KMeans::KMeans()
{
}

QVector<QPair<QPointF, QVector<QPointF> > >
        KMeans::findCenters(const QVector<QPointF> *points,
                            const unsigned int numCenters)
{
    QVector<QPair<QPointF, QVector<QPointF> > > centers(numCenters);

    QVector<int> indices(numCenters, numCenters);

    // find random indices to initialize centers
    unsigned int index;
    for(unsigned int i = 0; i < numCenters; i++)
    {
        while(true)
        {
            index = (unsigned int)(double(qrand()) / double(RAND_MAX + 1) * double(points->size()));;
            if(indices.indexOf(index) == -1)
            {
                indices[i] = index;
                break;
            }
        }
    }

    // create initial centers structure using random centers chosen above
    QVector<QPointF> closestPoints;
    unsigned int closest;
    double closestDist, thisDist;

    for(unsigned int i = 0; i < numCenters; i++)
    {
        // find the points closest to this center
        closestPoints.clear();
        for(int p = 0; p < points->size(); p++)
        {
            // assume the point is closest to the first center
            closest = 0;
            closestDist = dist((*points)[p], (*points)[indices[0]]);

            // determine if the point is closer to any other center
            for(unsigned int c = 0; c < numCenters; c++)
            {
                thisDist = dist((*points)[p], (*points)[indices[c]]);

                // if the point is closer to a different center, remember it
                if(dist((*points)[p], (*points)[indices[c]]) < closestDist)
                {
                    closest = c;
                    closestDist = thisDist;
                }
            }
            // if the point was closest to the current center, save it
            if(closest == i) closestPoints.push_back((*points)[p]);
        }
        // for the current center, save the center point and the closest points
        centers[i] = QPair<QPointF, QVector<QPointF> >((*points)[indices[i]], closestPoints);
    }

    // calculate new center for each cluster
    bool centersChanged = true;
    QPointF newCenter;
    while(centersChanged)
    {
        centersChanged = false;

        for(unsigned int i = 0; i < numCenters; i++)
        {
            newCenter.setX(0.0);
            newCenter.setY(0.0);
            for(int p = 0; p < centers[i].second.size(); p++)
            {
                newCenter += centers[i].second[p];
            }
            newCenter /= double(centers[i].second.size());

            if(newCenter != centers[i].first) centersChanged = true;
            centers[i].first = newCenter;
        }

        if(centersChanged)
        {
            for(unsigned int i = 0; i < numCenters; i++)
            {
                // find points closest to this center
                closestPoints.clear();
                for(int p = 0; p < points->size(); p++)
                {
                    // assume the point is closest to the first center
                    closest = 0;
                    closestDist = dist((*points)[p], centers[0].first);

                    // determine if the point is closer to any other center
                    for(unsigned int c = 0; c < numCenters; c++)
                    {
                        thisDist = dist((*points)[p], centers[c].first);

                        // if the point is closer to a different center, remember it
                        if(thisDist < closestDist)
                        {
                            closest = c;
                            closestDist = thisDist;
                        }
                    }
                    // if the point was closest to the current center, save it
                    if(closest == i) closestPoints.push_back((*points)[p]);
                }
                // for the current center, save the center point and the closest points
                centers[i].second = closestPoints;
            }
        }
    }

    return centers;
}

double KMeans::dist(QPointF p1, QPointF p2)
{
    return pow(p1.rx() - p2.rx(), 2.0) + pow(p1.ry() - p2.ry(), 2.0);
}
