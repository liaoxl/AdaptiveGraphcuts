#include "adaptivegraphcuts.h"

AdaptiveGraphcuts::AdaptiveGraphcuts(Mat _img, int _k)
{
    src_img=_img;
    num_k=_k;
}

AdaptiveGraphcuts::~AdaptiveGraphcuts()
{
}

Mat AdaptiveGraphcuts::GetKmeansSegmented()
{
    int src_width=src_img.cols;
    int src_height=src_img.rows;
    Mat samples=Mat::zeros(src_width*src_height,1,CV_32FC3);//创建样本矩阵，CV_32FC3代表32位浮点3通道（彩色图像）
    Mat clusters;//类别标记矩阵
    int k=0;

    for (int i=0;i<src_height;i++)
    {
        for (int j=0;j<src_width;j++,k++)
        {
            //将像素点三通道的值按顺序排入样本矩阵
            samples.at<Vec3f>(k,0)[0]=(float)src_img.at<Vec3b>(i,j)[0];
            samples.at<Vec3f>(k,0)[1]=(float)src_img.at<Vec3b>(i,j)[1];
            samples.at<Vec3f>(k,0)[2]=(float)src_img.at<Vec3b>(i,j)[2];
//            samples.at<Vec3f>(k,0)=(Point3f)src_img.at<Vec3b>;
        }
    }
    int nCluster=num_k;//聚类类别数

    Mat centers(nCluster, 1, CV_32FC3);
    //聚类，KMEANS PP CENTERS Use kmeans++ center initialization by Arthur and Vassilvitskii
    kmeans(samples,nCluster,clusters,TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,1.0),10,KMEANS_PP_CENTERS, centers);

    Mat dst_img=Mat::zeros(src_height,src_width,CV_8UC3);

    k=0;
    int val=0;
    for (int i=0;i<src_height;i++)
    {
        for (int j=0;j<src_width;j++,k++)
        {
            val=clusters.at<int>(k,0);

            dst_img.at<Vec3b>(i,j)[0]=(int)centers.at<Vec3f>(val,0)[0];
            dst_img.at<Vec3b>(i,j)[1]=(int)centers.at<Vec3f>(val,0)[1];
            dst_img.at<Vec3b>(i,j)[2]=(int)centers.at<Vec3f>(val,0)[2];
//            dst_img.at<Vec3b>(i,j)=(Point3i)centers.at<Vec3f>(val,0);
        }
    }
    return dst_img;
}

Mat AdaptiveGraphcuts::GetImgSegmented()
{
    int src_width=src_img.cols;
    int src_height=src_img.rows;
    Mat samples=Mat::zeros(src_width*src_height,1,CV_32FC3);//创建样本矩阵，CV_32FC3代表32位浮点3通道（彩色图像）
    Mat clusters;//类别标记矩阵
    int k=0;

    for (int i=0;i<src_height;i++)
    {
        for (int j=0;j<src_width;j++,k++)
        {
            //将像素点三通道的值按顺序排入样本矩阵
            samples.at<Vec3f>(k,0)[0]=(float)src_img.at<Vec3b>(i,j)[0];
            samples.at<Vec3f>(k,0)[1]=(float)src_img.at<Vec3b>(i,j)[1];
            samples.at<Vec3f>(k,0)[2]=(float)src_img.at<Vec3b>(i,j)[2];
//            samples.at<Vec3f>(k,0)=(Point3f)src_img.at<Vec3b>;
        }
    }
    int nCluster=num_k;//聚类类别数

    Mat centers(nCluster, 1, CV_32FC3);
    //聚类，KMEANS PP CENTERS Use kmeans++ center initialization by Arthur and Vassilvitskii
    kmeans(samples,nCluster,clusters,TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,1.0),10,KMEANS_PP_CENTERS, centers);

    Mat dst_img=Mat::zeros(src_height,src_width,CV_8UC3);

    k=0;
    int val=0;
    for (int i=0;i<src_height;i++)
    {
        for (int j=0;j<src_width;j++,k++)
        {
            val=clusters.at<int>(k,0);

            dst_img.at<Vec3b>(i,j)[0]=(int)centers.at<Vec3f>(val,0)[0];
            dst_img.at<Vec3b>(i,j)[1]=(int)centers.at<Vec3f>(val,0)[1];
            dst_img.at<Vec3b>(i,j)[2]=(int)centers.at<Vec3f>(val,0)[2];
//            dst_img.at<Vec3b>(i,j)=(Point3i)centers.at<Vec3f>(val,0);
        }
    }

    GraphType *mlg=new GraphType(src_height*src_width, 3*src_height*src_width, nCluster);
    for(int i=0; i<src_height; i++)
    {
        for(int j=0; j<src_width; j++)
        {
            mlg->add_node();
        }
    }
    for(int i=0; i<src_height; i++)
    {
        for(int j=0; j<src_width; j++)
        {
            Point3f pt3f_origin=(Point3f)src_img.at<Vec3b>(i,j);
            for(int l=0; l<nCluster; l++)
            {
                Point3f pt3f_cluster=centers.at<Vec3f>(l,0);
                int tcap=getTlink(pt3f_origin,pt3f_cluster);
                mlg->add_tweights(i*src_width+j,l,tcap);
            }
            if(j+1<src_width)
            {
                Point3f pt3f_right=(Point3f)src_img.at<Vec3b>(i,j+1);
                int ncap=getNlink(pt3f_origin, pt3f_right);
                mlg->add_edge(i*src_width+j, i*src_width+j+1, ncap, ncap);
            }
            if(i+1<src_height)
            {
                Point3f pt3f_down=(Point3f)src_img.at<Vec3b>(i+1,j);
                int ncap=getNlink(pt3f_origin, pt3f_down);
                mlg->add_edge(i*src_width+j, (i+1)*src_width+j, ncap, ncap);
            }
        }
    }
    int energy=mlg->maxflow();
    // cout << energy << endl;

    Point3f* ptMean=new Point3f[nCluster];
    memset(ptMean, 0, sizeof(Point3f)*nCluster);

    for(int l=0; l<nCluster; l++)
    {
        int count=0;
        int r=0,g=0,b=0;
        for(int i=0; i<src_height; i++)
        {
            for(int j=0; j<src_width; j++)
            {
                if(mlg->what_segment(i*src_width+j)==l+1)
                {
                    r += src_img.at<Vec3b>(i,j)[0];
                    g += src_img.at<Vec3b>(i,j)[1];
                    b += src_img.at<Vec3b>(i,j)[2];
                    count++;
                }
            }
        }
        count = count==0?1:count;
        ptMean[l].x=(float)r/count;
        ptMean[l].y=(float)g/count;
        ptMean[l].z=(float)b/count;
    }

    for(int i=0; i<src_height; i++)
    {
        for(int j=0; j<src_width; j++)
        {
            int l=mlg->what_segment(i*src_width+j)-1;
            dst_img.at<Vec3b>(i,j)[0]=(int)ptMean[l].x;
            dst_img.at<Vec3b>(i,j)[1]=(int)ptMean[l].y;
            dst_img.at<Vec3b>(i,j)[2]=(int)ptMean[l].z;
        }
    }
    delete [] ptMean;
    delete mlg;
    return dst_img;
}

int AdaptiveGraphcuts::getTlink(Point3f p1, Point3f p2)
{
    float tLamda=12000;
    float tBeta=0.03;
    int cap=(int)tLamda*exp((-1)*norm(p1-p2)*tBeta);
    return cap;
}

int AdaptiveGraphcuts::getNlink(Point3f p1, Point3f p2)
{
    float tLamda=12000;
    float tBeta=0.03;
    int cap=(int)tLamda*exp((-1)*norm(p1-p2)*tBeta);
    return cap;
}
