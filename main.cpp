#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "adaptivegraphcuts.h"

using namespace std;
using namespace cv;

int main()
{
    Mat img=imread("moondark.jpg");
    imshow("origin", img);
    AdaptiveGraphcuts *ag=new AdaptiveGraphcuts(img,3);
    img=ag->GetKmeansSegmented();
    imshow("kmeans",img);
	imwrite("SegmentByKmeans.png", img);
    img=ag->GetImgSegmented();
    imshow("test", img);
	imwrite("SegmentByMultiLayerGraph.png", img);
    waitKey(0);

    return 0;
}

