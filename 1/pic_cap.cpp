#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "stdio.h"
#include "iostream"
#include <vector>
using namespace std;
using namespace cv;

Mat myFrame;

void onMouse(int event, int x, int y, int flags, void* param)
{
    Mat frame2;

    frame2 = myFrame.clone();

    if (event == CV_EVENT_LBUTTONDOWN)
    {
        Vec3b p = frame2.at<Vec3b>(y,x);
        fprintf(stderr, "===RGB value===\n");
        fprintf(stderr, "x=%d, y=%d\n", x, y);
        fprintf(stderr, "R=%d, G=%d, B=%d\n\n", p[2], p[1], p[0]);
    }
    imshow("frame", frame2);
}

int main(){
	VideoCapture myVideo(0);
	if(!myVideo.isOpened()){
		printf("tidak bisa mengakses kamera");
		return -1;
	}
	int count = 1;
	char myPath[100]; 
	while(1){
		sprintf(myPath,"/home/eros/gambarku%d.jpg",count);
		Mat myPicture;
		myVideo >> myFrame;
		 if(myFrame.empty()){
		 	break;
		 }
		 imshow("Videoku",myFrame);
		 char myKey = waitKey(10);
		 if(myKey == 'w'){
		 	fprintf(stderr,"menyimpan gambar\n");
		 	imwrite(myPath,myFrame);
		 	imshow("gambar yang disimpan",myFrame);
		 	myPicture = imread(myPath);
		 	count++;
		 }
		else if(myKey == 's'){
		 	fprintf(stderr, "selesai\n");
		 	break;
		}
		else if(myKey == 'q'){
			setMouseCallback("frame", onMouse, 0);
		}

	}
	myVideo.release();

	return 0;
}