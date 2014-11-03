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

double im_width;
double im_height;
uchar red[WIDTH * HEIGHT];
uchar gre[WIDTH * HEIGHT];
uchar blu[WIDTH * HEIGHT];
uchar sumArray[WIDTH * HEIGHT];
int changes[10];

void path(int n, Mat imgBGR, int r)
{
    if (n>2)
    {
        path (1, imgBGR, r);
    }
    if (n==2)
    {
        int changePos1 = (changes[0] + changes[1])/2;
        int changePos2 = (changes[2] + changes[3])/2;
        (imgBGR.at<Vec3b>(r, changePos2)).val[2] = 255;
        (imgBGR.at<Vec3b>(r, changePos2)).val[1] = 0;
        (imgBGR.at<Vec3b>(r, changePos2)).val[0] = 0;
        (imgBGR.at<Vec3b>(r, changePos1)).val[2] = 255;
        (imgBGR.at<Vec3b>(r, changePos1)).val[1] = 0;
        (imgBGR.at<Vec3b>(r, changePos1)).val[0] = 0;
    }
    else
    {
        int changePos = (changes[0] + changes[1])/2;
        (imgBGR.at<Vec3b>(r, changePos)).val[2] = 255;
        (imgBGR.at<Vec3b>(r, changePos)).val[1] = 0;
        (imgBGR.at<Vec3b>(r, changePos)).val[0] = 0;
    }
}

int main()
{
 VideoCapture capture(-1);
 capture.set(CV_CAP_PROP_FRAME_WIDTH,width);
 capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
 im_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
 im_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

 printf("Setup completed\n");

 Mat imgBGR;
 if(!capture.isOpened())
 {
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


      int changeCount=0;
      for(int r = 0; r < HEIGHT; r++)
      {
         int numSum=0;
         pos = WIDTH * r;
                   intensity = imgBGR.at<Vec3b>(r, 0);
          pos = WIDTH * r;
          red[pos] = intensity.val[2];
          gre[pos] = intensity.val[1];
          blu[pos] = intensity.val[0];
         sumArray[pos] = (red[pos] / 3 + gre[pos] / 3 + blu[pos] / 3);
         int whiteCount = 0;
         bool onLine=false;
         int endCount=0;
         int startCount=0;
         changeCount=0;
         for(int c = 1; c < WIDTH; c++)
         {
          intensity = imgBGR.at<Vec3b>(r, c);
          pos = WIDTH * r + c;
          red[pos] = intensity.val[2];
          gre[pos] = intensity.val[1];
          blu[pos] = intensity.val[0];
          sumArray[pos] = (red[pos] / 3 + gre[pos] / 3 + blu[pos] / 3);
          if (sumArray[pos-1]==255)
          {
            whiteCount++;
            if (whiteCount==0)
            {
               startCount=c; 
           }
           if (whiteCount>10)
           {
            onLine=true;
            if (sumArray[pos] == 0)
            {
                            numSum++;
                endCount=c;
                changes[changeCount]=startCount;
                changes[changeCount+1]=endCount;
                changeCount= changeCount+2;
            }
        }
    }
    else
    {
        whiteCount=0;
        onLine=false;
        startCount=c;
        endCount=c;
    }
} 
path(numSum, imgBGR, r);
}


imwrite("Images/lineImg.png", imgBGR);

return 0;
}
