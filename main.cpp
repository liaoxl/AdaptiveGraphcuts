#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "AdaptiveGraphcuts.h"

using namespace std;
using namespace cv;

int main()
{
    Mat img=imread("2007_001408.jpg");
    imshow("origin", img);
    AdaptiveGraphcuts *ag=new AdaptiveGraphcuts(img,6);
    img=ag->GetImgSegmented();
    imshow("test", img);
    img=ag->GetKmeansSegmented();
    imshow("kmeans",img);
    waitKey(0);

    Point3f pt3f=(Point3f)img.at<Vec3b>(0,0);
    cout << pt3f << endl;

    Point3f pt3f1(1,1,1);
    Point3f pt3f2(1,2,2);
    cout << pt3f1+pt3f2 << endl;
    cout << "Hello World!" << endl;
    return 0;
}

