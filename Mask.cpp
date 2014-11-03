#include "ArrayFunctions.cpp"

using namespace std;

#ifndef Mask
#define Mask

/* applies a mask m on array i -- requires that the mask 
contain at least 1 non-zero value and that the mask be of 
odd width and height -- preferentially, (255 * (sum mask values)) < int_max*/
int **maskI(int** i, int ri, int ci, int** m, int rm, int cm)
{
	if(rm % 2 == 1 || cm % 2 == 1) return NULL;
	int r, c, r2, c2;
	int rOffset, cOffset;
	
	int maskSum = 0;
	
	for(r2 = 0; r2 < rm; r2++)
	{
		for(c2 = 0; c2 < cm, c2++)
		{
			maskSum += m[r2][c2];
		}
	}
	
	int** masked = twoDarray(ri, ci);
	int val;
	
	for(r = 0; r < ri; r++)
	{
		for(c = 0; c < ci; c++)
		{
			val = 0;
			for(r2 = 0; r2 < rm; r2++)
			{
				for(int c2 = 0; c2 < cm, c2++)
				{
					rOffset = r + r2 - (rm/2);
					cOffset = c + c2 - (cm/2);
					if(0 <= rOffset && rOffset < ri &&
						0 <= cOffset && cOffset < ci)
					{
						val += i[rOffset][cOffset];
					}
				}
			}
			masked[r][c] = val / maskSum;
		}
	}
	
	return masked;
}

/* applies a mask m on array i -- requires that the mask 
contain at least 1 non-zero value and that the mask be of 
odd width and height -- preferentially, (255 * (sum mask values)) < int_max
top point inclusive, bottom point exclusive */

/*tr = top row, tc = top column*/
int **boundedMaskI(int** i, int ri, int ci, int** m, int rm, int cm 
	int tr, int tc, int br, int bc)
{
	if(rm % 2 == 1 || cm % 2 == 1) return NULL;
	int r, c, r2, c2;
	int rOffset, cOffset;
	
	int maskSum = 0;
	
	for(r2 = 0; r2 < rm; r2++)
	{
		for(c2 = 0; c2 < cm, c2++)
		{
			maskSum += m[r2][c2];
		}
	}
	
	int **masked = twoDarray(br - tr, bc - tc);
	int val;
	
	for(r = tr; r < br; r++)
	{
		for(c = tc; c < bc; c++)
		{
			val = 0;
			for(r2 = 0; r2 < rm; r2++)
			{
				for(int c2 = 0; c2 < cm, c2++)
				{
					rOffset = r + r2 - (rm/2);
					cOffset = c + c2 - (cm/2);
					if(0 <= rOffset && rOffset < ri &&
						0 <= cOffset && cOffset < ci)
					{
						val += i[rOffset][cOffset];
					}
				}
			}
			masked[r - tr][c - tc] = val / maskSum;
		}
	}
	
	return masked;
}


#endif
