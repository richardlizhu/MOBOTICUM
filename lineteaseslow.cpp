/* To Compile camtest.cpp and create executable camtest:
g++ -O2 `pkg-config --cflags --libs opencv` camtest.cpp -o camtest

To run:
./camtest
*/


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "RGB_V_et_al.cpp"

using namespace std;
using namespace cv;

#define WIDTH 320
#define HEIGHT 240

double width = 320;
double height = 240;
uchar red[WIDTH * HEIGHT];
uchar gre[WIDTH * HEIGHT];
uchar blu[WIDTH * HEIGHT];
double im_width;
double im_height;

int countConsec(Mat imgBGR, int r, int x)
{
	int counter=0;
	int pos = WIDTH * r + x; 

	while ((red[pos] / 3 + gre[pos] / 3 + blu[pos] / 3) != 0)
	{
		counter++;
		pos++;
	}
	return counter;
}


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

        //Mat imgHSV(imgBGR.rows, imgBGR.cols, imgBGR.depth());
        //cvtColor(imgBGR, imgHSV, CV_BGR2HSV);
	Mat imgRed(imgBGR.rows, imgBGR.cols, imgBGR.depth());
	Mat imgGre(imgBGR.rows, imgBGR.cols, imgBGR.depth());
	Mat imgBlu(imgBGR.rows, imgBGR.cols, imgBGR.depth());
	cout<<"Begin their conversion:\n";
        cvtColor(imgBGR, imgRed, CV_BGR2HSV);//for some reason needed
        cvtColor(imgBGR, imgGre, CV_BGR2HSV);//for some reason needed
        cvtColor(imgBGR, imgBlu, CV_BGR2HSV);//for some reason needed
        cout<<"done\n";
        cout<<"Begin our conversion:\n";
        rgbToAvgM(&imgBGR, &imgRed, 100, 0, 0);
        rgbToAvgM(&imgBGR, &imgGre, 0, 100, 0);
        rgbToAvgM(&imgBGR, &imgBlu, 0, 0, 100);
        cout<<"done\n";

        printf("Write original image\n");
        imwrite("Images/preImg.png", imgBGR);

        Vec3b intensity;
        int pos;

        uchar sum;
        for(int c = 0; c < WIDTH; c++)
        {
        	for(int r = 0; r < HEIGHT; r++)
        	{
        		intensity = imgBGR.at<Vec3b>(r, c);
        		pos = WIDTH * r + c;
        		red[pos] = intensity.val[2];
        		gre[pos] = intensity.val[1];
        		blu[pos] = intensity.val[0];
        		sum = (red[pos] / 3 + gre[pos] / 3 + blu[pos] / 3);
                //cout<<(uint) sum<<endl;
        		if(sum < 150)
        		{

        			(imgBGR.at<Vec3b>(r, c)).val[0] = 0;
        			(imgBGR.at<Vec3b>(r, c)).val[1] = 0;
        			(imgBGR.at<Vec3b>(r, c)).val[2] = 0;
        		}
        		else
        		{
        			(imgBGR.at<Vec3b>(r, c)).val[0] = 255;
        			(imgBGR.at<Vec3b>(r, c)).val[1] = 255;
        			(imgBGR.at<Vec3b>(r, c)).val[2] = 255;
        		}
        	}
        }


        cout<<"Write color images\n";

        vector<Mat> colors;
        split(imgRed, colors);
        imwrite("Images/imgRed.png", colors[2]);
        split(imgGre, colors);
        imwrite("Images/imgGre.png", colors[2]);	
        split(imgBlu, colors);
        imwrite("Images/imgBlu.png", colors[2]);


        printf("Write altered image\n");
        imwrite("Images/postImg.png", imgBGR);

	/*
	
        
        vector<Mat> hsv;
        split(imgHSV, hsv);
	vector<Mat> hsv2;
        split(imgHSV2, hsv2);
        
		
        printf("Split image into components\n");
        imwrite("imgH.png",hsv[0]);
        imwrite("imgH2.png",hsv2[0]);
        imwrite("imgS.png",hsv[1]);
        imwrite("imgS2.png",hsv2[1]);
        imwrite("imgV.png",hsv[2]);
        imwrite("imgV2.png",hsv2[2]);
        imwrite("img.png",imgHSV);
        imwrite("img2.png",imgHSV2);
	*/

        printf("Wrote images\n");

        for(int r = 0; r < HEIGHT; r++)
        {
        	int posSum = 0;
        	int numSum=0;
        	int consecCount;
        	int consecNum[WIDTH];
        	for (int x = 0; x < WIDTH; x++)
        	{
        		consecNum[x]=countConsec(imgBGR, r, x);
        	}
        	int consecMax=0;
        	int consecMaxPos;
        	for (int x = 0; x < WIDTH; x++)
        	{
        		if (consecNum[x]>consecMax)
        		{
        			consecMax=consecNum[x];
        			consecMaxPos=x;
        		}
        	}
        	for (int x=0; x<WIDTH; x++)
        	{
        		if (!(x>=consecMaxPos && x<=consecMaxPos+consecMax))
        		{
        			(imgBGR.at<Vec3b>(r, x)).val[2] = 0;
        			(imgBGR.at<Vec3b>(r, x)).val[1] = 0;
        			(imgBGR.at<Vec3b>(r, x)).val[0] = 0;
        		}
        	}
        	for(int c = 0; c < WIDTH; c++)
        	{
        		intensity = imgBGR.at<Vec3b>(r, c);
        		pos = WIDTH * r + c;
        		red[pos] = intensity.val[2];
        		gre[pos] = intensity.val[1];
        		blu[pos] = intensity.val[0];
        		sum = (red[pos] / 3 + gre[pos] / 3 + blu[pos] / 3);
                //cout<<(uint) sum<<endl;
        		if(sum > 0)
        		{
        			posSum = posSum+c;
        			numSum++;
        		}
        	}
        	if (numSum != 0)
        	{
        		int posAvg = posSum/numSum;
        		(imgBGR.at<Vec3b>(r, posAvg)).val[2] = 255;
        		(imgBGR.at<Vec3b>(r, posAvg)).val[1] = 0;
        		(imgBGR.at<Vec3b>(r, posAvg)).val[0] = 0;
        	}
        }
        printf("Write lined image\n");
        imwrite("Images/lineImg.png", imgBGR);

        return 0;
    }



