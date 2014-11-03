#ifndef ArrayFunctions
#define ArrayFunctions

using namespace std;

/* returns a pointer to a two dimensional array of integers */
int** twoDarray(int rows, int cols)
{
	int **ret = new int*[rows];
	for(int r = 0; r < rows; r++)
	{
		ret[r] = new int[cols];
	}
	return ret;
}

#endif
