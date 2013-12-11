#ifndef AdaptiveGraphcuts_H
#define AdaptiveGraphcuts_H

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "MultiLayerGraph/multilayergraph.h"

using namespace cv;

typedef MultiLayerGraph<int,int,int> GraphType;
class AdaptiveGraphcuts
{
public:
    AdaptiveGraphcuts(Mat _img, int _k);
    ~AdaptiveGraphcuts();

    Mat GetImgSegmented();
    Mat GetKmeansSegmented();
    int getTlink(Point3f p1, Point3f p2);
    int getNlink(Point3f p1, Point3f p2);

private:
    Mat src_img;
    int num_k;
};

#endif // AdaptiveGraphcuts_H
