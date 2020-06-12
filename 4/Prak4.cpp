// - Tugas4(Edge detection gradient, sobel, canny, prewitt, Robert)
// - Makalah (edge detection)

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
using namespace cv;
using namespace std;

//Edge detection gradient
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

//edge detection canny

void canny(Mat src)
{
    Mat gray,blurImage,cedge,edge1,edge2;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    // Create a window
    string window_name1 = "hasil Canny";
    string window_name2 = "hasil Scharr";
    int edgeThresh = 1;
	int edgeThreshScharr=1;
    namedWindow(window_name1, 1);
    namedWindow(window_name2, 1);
    // create a toolbar
    blur(src, blurImage, Size(3,3));
    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh*3, 3);
    cedge = Scalar::all(0);
    src.copyTo(cedge, edge1);
    imshow(window_name1, cedge);
    Mat dx,dy;
    Scharr(blurImage,dx,CV_16S,1,0);
    Scharr(blurImage,dy,CV_16S,0,1);
    Canny( dx,dy, edge2, edgeThreshScharr, edgeThreshScharr*3 );
    cedge = Scalar::all(0);
    src.copyTo(cedge, edge2);
    imshow(window_name2, cedge);
    cedge.create(src.size(), src.type());
    // Show the image
    
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

//edge detection prewitt
void prewit(Mat src)
{
    cv::Mat dstX, dstY, dstXY;
    cv::Mat kernelX = (cv::Mat_<int>(3, 3) << 1, 0, -1, 1, 0, -1, 1, 0, -1);
    cv::Mat kernelY = (cv::Mat_<int>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
    cv::filter2D(src, dstX, -1, kernelX);
    cv::filter2D(src, dstY, -1, kernelY);
    cv::bitwise_or(dstX, dstY, dstXY);
    cv::imshow("Prewitt Combine", dstXY);
    
}

//edge detection robert

void robert(Mat src)
{
    cv::Mat dstX, dstY, dstXY;
    cv::Mat kernelX = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
    cv::Mat kernelY = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);
    cv::filter2D(src, dstX, -1, kernelX);
    cv::filter2D(src, dstY, -1, kernelY);
    cv::bitwise_or(dstX, dstY, dstXY);
    cv::imshow("Robert Combine", dstXY);
    
}

int main(){
	string path = "eth.jpeg";
	Mat src = imread(path, IMREAD_COLOR);
    if(src.empty())
    {
        printf("Cannot read image file: %s\n", path.c_str());
        return -1;
    }
    imshow("gambar mula-mula", src);
    robert(src);
    sobel(src);
    prewit(src);
    gradient(src);
    canny(src);
 	waitKey(0);   
    return 0;
}