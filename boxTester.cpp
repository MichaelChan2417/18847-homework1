#include "Box.H"
#include <cstdio>
#include <cstdlib>

int size(int lo[], int hi[], int dim)
{
  if(dim==0) return 1;
  int val = hi[dim-1]-lo[dim-1] +1;
  return val*size(lo, hi, dim-1);
}


int main(int argc, char** argv)
{

  int returnCode = 0;

  int lo1[4] = {4,0,0,0};
  int hi1[4] = {12,6,22,5};

  int lo2[4] = {8,0,0,0};

  Box box1(lo1, hi1);
  Box box2(lo2, hi1);

  if(size(lo1, hi1, DIM) != box1.sizeOf())
    {
      printf("Box::size function has an error in box1\n");
      returnCode += 1;
    }
  if(size(lo2, hi1, DIM) != box2.sizeOf())
    {
      printf("Box::size function has an error in box2\n");
      returnCode += 1;
    }

  Box box3 = box1 && box2;

  // box1.print(); box2.print(); box3.print();
  
  if(size(lo2, hi1, DIM) != box3.sizeOf())
    {
      printf("Box::size function has an error in box3\n");
      returnCode += 1;
    }

  box3.shift(0,-4);

  Box box4 = box3 && box1;

  int hi4[4] = {8,6,22,5};
  if(size(lo1, hi4, DIM) != box4.sizeOf())
    {
      printf("Box::size function has an error in box4\n");
      returnCode += 1;
    } 

  Box box5 = box3;
  box3 = box3.shift(0,-12);
  Box box6 = box3 && box5;

  if(!box6.isEmpty())
    {
      printf("Box::size function has an error in box6\n");
      returnCode += 1;
    }

  int n = box5.sizeOf();
  int* dataArray = new int[n];
  for(int i=0; i<n; i++) dataArray[i] = 0;

  int outsideCount=0;
  for(int i=0; i<n; i++)
    {
      int tuple[DIM];
      box5.tupleIndex(i, tuple);
      int index = box5.linearIndex(tuple);
      if(!box5.contains(tuple)) outsideCount++;
      dataArray[index]++;
    }

  if(outsideCount > 0)
    {
      printf("box5 tupleIndex created %d tuple[s] outside box5\n", outsideCount);
      returnCode++;
    }
  
  int errorCount = 0;
  for(int i=0; i<n; i++)
    {
      if(dataArray[i] != 1) errorCount++;
    }

  if(errorCount > 0)
    {
      printf("tuple indexing for box5 did not create a one-to-one and onto mapping\n");
      printf("Counted %d error locations in array access\n", errorCount);
      returnCode++;
    }
  
  printf("detected %d errors in this test program\n", returnCode);
  return returnCode;
}
  
  
