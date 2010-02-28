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

    // find random indices to initialize centers
    unsigned int index;
    QVector<unsigned int> alreadyAdded(numCenters);
    for(unsigned int i = 0; i < numCenters; i++)
    {
        while(true)
        {
            index = (unsigned int)(double(qrand()) / double(RAND_MAX + 1) * double(points->size()));;
            if(alreadyAdded.indexOf(index) == -1)
            {
                centers[i].first = (*points)[index];
                alreadyAdded.push_back(index);
                break;
            }
        }
    }

    QVector<QVector<QPointF> > closestPoints(numCenters);
    unsigned int closest;
    double closestDist, thisDist;
    bool centersChanged = true;
    QPointF newCenter;

    // calculate new center for each cluster

    while(centersChanged)
    {
        centersChanged = false;

        for(unsigned int i = 0; i < numCenters; i++)
        {
            // upon first iteration of while() loop, centers pairs
            // have no second component (points assigned to that center)
            if(centers[i].second.isEmpty())
            {
                // mark "centers changed" so that further processing occurs
                centersChanged = true;
                break;
            }

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
            for(unsigned int c = 0; c < numCenters; c++)
            {
                closestPoints[c].clear();
            }

            // find center each point is closest to
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
                // save point to closest center's collection
                closestPoints[closest].push_back((*points)[p]);
            }
            // for each center, save its closest points
            for(unsigned int c = 0; c < numCenters; c++)
            {
                centers[c].second = closestPoints[c];
            }
        }
    }

    return centers;
}

double KMeans::dist(QPointF p1, QPointF p2)
{
    return pow(p1.rx() - p2.rx(), 2.0) + pow(p1.ry() - p2.ry(), 2.0);
}
