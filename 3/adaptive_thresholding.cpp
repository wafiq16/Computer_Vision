#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int count_image = 0;

void draw_hist(Mat src, Mat dst);

int main( int argc, char** argv )
{
  Mat src, dst;

  /// Load image
  src = imread("eth.jpeg");
  Mat imageContrastHigh2;
  src.convertTo(imageContrastHigh2, -1, 4, 0); //increase the contrast by 2
  
  if( !src.data )
    { return -1; }
  draw_hist(src,dst);
  draw_hist(imageContrastHigh2,dst);
  return 0;
}

void draw_hist(Mat src, Mat dst){
   /// Separate the image in 3 places ( B, G and R )
  vector<Mat> bgr_planes;
  split( src, bgr_planes );

  cvtColor(src,src, CV_BGR2GRAY);
  /// Establish the number of bins
  int histSize = 256;

  /// Set the ranges ( for B,G,R) )
  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;


  Mat b_hist, g_hist, r_hist;

  /// Compute the histograms:
  calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

  // Draw the histograms for B, G and R
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  /// Normalize the result to [ 0, histImage.rows ]
  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

  /// Draw for each channel
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
  }
  adaptiveThreshold(src, dst,255,ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,15,-5);
  /// Display
  count_image++;
  char string_image[30];
  //namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
  sprintf(string_image,"histogram %d", count_image);
  imshow(string_image, histImage);
  sprintf(string_image,"image src %d", count_image);
  imshow(string_image, src);
  sprintf(string_image,"image dst %d", count_image);
  imshow(string_image, dst);
  waitKey(0);
}