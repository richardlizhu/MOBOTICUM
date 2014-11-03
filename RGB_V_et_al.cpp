#include<iostream>
#include<opencv2/opencv.hpp>
#include "ArrayFunctions.cpp"

using namespace std;
using namespace cv;

#ifndef RGB_V_et_al
#define RGB_V_et_al

//takes a Mat* and returns a Mat* pointing to a Mat with the same dimensions
Mat* sameDimensionsM(Mat* input)
{
	return new Mat(input->rows, input->cols, input->depth());
}


/* takes an image in the form of Mat* and converts it into a velociraptor
	image of the form Mat* */
void rgbToVM(Mat* input, Mat* V)
{
	int rows = input->rows;
	int cols = input->cols;
	uchar red, gre, blu;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			red = vals.val[2];
			gre = vals.val[1];
			blu = vals.val[0];
			if(red > gre)
			{
				if(red > blu)
				{
					(V->at<Vec3b>(r, c)).val[2] = red;
				}
				else
				{
					(V->at<Vec3b>(r, c)).val[2] = blu;
				}
			}
			else if(gre > blu)
			{
				(V->at<Vec3b>(r, c)).val[2] = gre;
			}
			else
			{
				(V->at<Vec3b>(r, c)).val[2] = blu;
			}
		}
	}
}


/* takes an image in the form of Mat* and converts it into an Avg
	image of the form Mat* */
void rgbToAvgM(Mat* input, Mat* Avg)
{
	int rows = input->rows;
	int cols = input->cols;
	uchar red, gre, blu;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			(Avg->at<Vec3b>(r, c)).val[2] = 
				(vals.val[2] / 3) + (vals.val[1] / 3) + (vals.val[0] / 3);
		}
	}
	
}


/* takes an image in the form of Mat* and converts it into an Avg
	image of the form Mat* (weighted average) 
	_r, _g, and _b are percents*/
void rgbToAvgM(Mat* input, Mat* Avg, int _r, int _g, int _b)
{
	int rows = input->rows;
	int cols = input->cols;
	uchar red, gre, blu;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			(Avg->at<Vec3b>(r, c)).val[2] = (((int) vals.val[2]) * _r) / 100 
			+ (((int) vals.val[1]) * _g) /100 + (((int) vals.val[0]) * _b) /100;
		}
	}
	
}



/* returns a pointer to a two dimensional array of integers with the same 
	dimensions as the Mat denoted by input */
int **sameDimensionsI(Mat* input)
{
	return twoDarray(input->rows, input->cols);
}


/* takes an image in the form of Mat* and converts it to a velociraptor
	image in the form of int ** */
void rgbToVI(Mat* input, int** V)
{
	int rows = input->rows;
	int cols = input->cols;
	uchar red, gre, blu;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			red = vals.val[2];
			gre = vals.val[1];
			blu = vals.val[0];
			if(red > gre)
			{
				if(red > blu)
				{
					V[r][c] = red;
				}
				else
				{
					V[r][c] = blu;
				}
			}
			else if(gre > blu)
			{
				V[r][c] = gre;
			}
			else
			{
				V[r][c] = blu;
			}
		}
	}
	
}

	

/* takes an image in the form of Mat* and converts it to an Avg
	image in the form of int ** */
void rgbToAvgI(Mat* input, int** Avg)
{
	int rows = input->rows;
	int cols = input->cols;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			Avg[r][c] = (vals.val[2] / 3) + (vals.val[1] / 3) + (vals.val[0] / 3);
		}
	}
	
}



/* takes an image in the form of Mat* and converts it to an Avg
	image in the form of int ** (weighted average) 
	_r, _g, and _b are percents */
void rgbToAvgI(Mat* input, int** Avg, int _r, int _g, int _b)
{
	int rows = input->rows;
	int cols = input->cols;
	Vec3b vals;
	
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			vals = input->at<Vec3b>(r, c);
			Avg[r][c] = (((int) vals.val[2]) * _r) / 100
			+ (((int) vals.val[1]) * _g) /100 + (((int) vals.val[0]) * _b) /100;
		}
	}
}

#endif
