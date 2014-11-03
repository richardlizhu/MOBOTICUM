/* To Compile camtest.cpp and create executable camtest:
g++ -O2 `pkg-config --cflags --libs opencv` camtest.cpp -o camtest

To run:
./camtest
*/


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define WIDTH 320
#define HEIGHT 240

double width = 320;
double height = 240;

double im_width;
double im_height;

int main(){
        VideoCapture capture(-1);
        capture.set(CV_CAP_PROP_FRAME_WIDTH,width);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
        im_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
        im_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

        printf("Setup completed\n");

        Mat imgBGR;
        if(!capture.isOpened()){
                cout << "Camera not Working" << endl;
        }
        capture >> imgBGR;
        printf("Captured image\n");
        vector<Mat> bgr;
        split(imgBGR,bgr);

        printf("Split image into components\n");
        imwrite("imgB.png",bgr[0]);
        imwrite("imgG.png",bgr[1]);
        imwrite("imgR.png",bgr[2]);
        imwrite("img.png",imgBGR);
        printf("Wrote images\n");
        return 0;
}
