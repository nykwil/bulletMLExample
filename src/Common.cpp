#include "Common.h"

double sq(double d1)
{
    return d1 * d1;
}

double distSq(double dx1, double dy1, double dx2, double dy2)
{
    return sq(dx1 - dx2) + sq(dy1 - dy2);
}

void distanceFromLine(double cx, double cy, double ax, double ay ,
                      double bx, double by, double &distanceSegment,
                      double &distanceLine)
{
    double r_numerator = (cx-ax)*(bx-ax) + (cy-ay)*(by-ay);
    double r_denomenator = (bx-ax)*(bx-ax) + (by-ay)*(by-ay);
    double r = r_numerator / r_denomenator;
    //
    double px = ax + r*(bx-ax);
    double py = ay + r*(by-ay);
    //     
    double s =  ((ay-cy)*(bx-ax)-(ax-cx)*(by-ay) ) / r_denomenator;

    distanceLine = fabs(s)*sqrt(r_denomenator);

    //
    // (xx,yy) is the point on the lineSegment closest to (cx,cy)
    //
    double xx = px;
    double yy = py;

    if ( (r >= 0) && (r <= 1) )
    {
        distanceSegment = distanceLine;
    }
    else
    {

        double dist1 = (cx-ax)*(cx-ax) + (cy-ay)*(cy-ay);
        double dist2 = (cx-bx)*(cx-bx) + (cy-by)*(cy-by);
        if (dist1 < dist2)
        {
            xx = ax;
            yy = ay;
            distanceSegment = sqrt(dist1);
        }
        else
        {
            xx = bx;
            yy = by;
            distanceSegment = sqrt(dist2);
        }


    }

    return;
}
