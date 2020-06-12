//Edge detection gradient
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
using namespace cv;
using namespace std;

void gradient(Mat src);
void sobel(Mat src);

int main(){
	string path = "eth.jpeg";
	Mat src = imread(path, IMREAD_COLOR);
    if(src.empty())
    {
        printf("Cannot read image file: %s\n", path.c_str());
        return -1;
    }
    imshow("gambar mula-mula", src);
    // robert(src);
    sobel(src);
    // prewit(src);
    gradient(src);
    // canny(src);
 	  waitKey(0);   
    return 0;
}

void gradient(Mat src)
{
    cv::Mat dstX, dstY, dstXY;
    cv::Mat kernelX = (cv::Mat_<int>(1, 3) << -1, 0, 1);
    cv::Mat kernelY = (cv::Mat_<int>(3, 1) << -1, 0, 1);
    cv::filter2D(src, dstX, -1, kernelX);
    cv::filter2D(src, dstY, -1, kernelY);
    cv::bitwise_or(dstX, dstY, dstXY);
    cv::imshow("Gradient Method", dstXY);
    
}

//edge detection sobel

/** @function main */
void sobel( Mat src)
{
	Mat src_gray, grad;
  int ddepth = CV_16S;
  int scale = 1;
  int delta = 0;
  string window_name = "filter sobel";
  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// Gradient Y
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

  imshow( window_name, grad );
  
  }