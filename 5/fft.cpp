#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char ** argv)
{
    Mat I = imread( "eth.jpeg" , IMREAD_GRAYSCALE);
    Mat I2 = imread( "ethku.jpeg" , IMREAD_GRAYSCALE);
    if( I.empty()){
        cout << "Error opening image" << endl;
        return EXIT_FAILURE;
    }

    Mat padded,padded2;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    
    int m2 = getOptimalDFTSize( I2.rows );
    int n2 = getOptimalDFTSize( I2.cols ); // on the border add zero values

    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    copyMakeBorder(I2, padded2, 0, m2 - I2.rows, 0, n2 - I2.cols, BORDER_CONSTANT, Scalar::all(0));
    
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_8U)};
    Mat planes2[] = {Mat_<float>(padded2), Mat::zeros(padded2.size(), CV_8U)};
    
    Mat complexI;
    merge(planes , 1,complexI);         // Add to the expanded another plane with zeros
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

    Mat complexI2;
    merge(planes2 , 1,complexI2);         // Add to the expanded another plane with zeros
    dft(complexI2, complexI2);            // this way the result may fit in the source matrix
    split(complexI2, planes2);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

    //untuk domain waktu
    Mat Add_time, Sub_time;
    bitwise_or(I,I2, Add_time);
    bitwise_and(I,I2,Sub_time);
    bitwise_not(Sub_time,Sub_time);

    // untuk domain frekuensi
    Mat Add_freq, Sub_freq;
    Add_freq = planes[0] + planes2[0];
    Sub_freq = planes[0] - planes2[0];
    
    Mat back_to_time[4],awal,awal2;
    dft(Add_freq, back_to_time[0], cv::DFT_INVERSE);
    normalize(back_to_time[0], back_to_time[0], 0, 1, CV_MINMAX);
    
    dft(Sub_freq, back_to_time[1], cv::DFT_INVERSE);
    normalize( back_to_time[1],  back_to_time[1], 0, 1, CV_MINMAX);
    
    dft(planes[0], awal, cv::DFT_INVERSE);
    normalize( awal, awal, 0, 1, CV_MINMAX);

    dft(planes2[0], awal2, cv::DFT_INVERSE);
    normalize( awal2, awal2, 0, 1, CV_MINMAX);

    // Show the result
    imshow("Input Image 1 " , I);
    imshow("Input Image 2 " , I2);
    imshow("image1 sesudah inverse fourir", awal);
    imshow("image2 sesudah inverse fourir", awal2);
    
    // imshow("spectrum magnitude", magI);
    imshow("image1 saat fourir transform",planes[0]);
    imshow("image2 saat fourir transform",planes2[0]);

    imshow("image adding domain waktu", Add_time);
    imshow("image subracting domain waktu", Sub_time);
    imshow("image adding domain frekuensi", Add_freq);
    imshow("image subtracting domain frekuensi", Sub_freq);

    imshow("adding fourir in time", back_to_time[0]);
    imshow("subtract fourir in time", back_to_time[1]);
    
    waitKey();
    return EXIT_SUCCESS;
}
