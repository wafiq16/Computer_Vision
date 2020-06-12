#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <iostream>

using namespace std;
using namespace cv;
int main(){
	VideoCapture myVideo(0);
	if(!myVideo.isOpened()){
		printf("cant open device\n");
		return -1;
	}

	int frame_width = static_cast<int>(myVideo.get(CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
    int frame_height = static_cast<int>(myVideo.get(CAP_PROP_FRAME_HEIGHT));
	
	Size frame_size(frame_width,frame_height);
	int fps = 3;

	VideoWriter writeVideo("/home/eros/myvideo.avi",VideoWriter::fourcc('M','J','P','G'),fps,frame_size,true); 
	if(!writeVideo.isOpened()){
		printf("gagal menyimpan video");
		return -1;
	}
	while(1){
		Mat myFrame;
		myVideo >> myFrame;
		imshow("myVideo",myFrame);
		myVideo.read(myFrame);
		if(!myVideo.read(myFrame)){
			printf("tidak dapat membaca frame");
		}
		char myKey = waitKey(10);
		// if(myKey == 'w'){
			writeVideo.write(myFrame);
			fprintf(stderr, "mulai merekam\n");
			if(myKey == 's'){
				fprintf(stderr, "menyimpan video\n");
				break;
			}
		// }
	}
	writeVideo.release();
	return 0;
}