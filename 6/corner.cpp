#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
    Mat src, src_gray;
    int blockSize = 10, apertureSize = 15, k = 0.02,thresh = 180;
    src = imread("lap.jpg");
    if ( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    Mat dst = Mat::zeros( src.size(), CV_32FC1 );
    cornerHarris( src_gray, dst, blockSize, apertureSize, k );
    Mat dst_norm, dst_norm_scaled;
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int i = 0; i < dst_norm.rows ; i++ )
    {
        for( int j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                circle( dst_norm_scaled, Point(j,i), 5,  255, 2, 8, 0 );
            }
        }
    }
    imshow( "hasil deteksi", dst_norm_scaled );
    imshow("gambar awal", src);
    waitKey();
    return 0;
}