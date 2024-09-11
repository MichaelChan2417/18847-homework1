#include "MDArray.H"
#include <cstdio>
#include <cassert>
#include <cmath>
int main(int argc, char* argv[])
{
  /* Test program: compute the Laplacian on a grid. Grid size is input on the command line 
     as DIM integers > 2. Length of the domain in the first dimesnion is 1. */

  assert(argc == DIM+1);
  int hi[DIM];
  int lo[DIM];

  for (int i = 0; i < DIM; i++)
    {
      sscanf(argv[i+1],"%d",&hi[i]);
      lo[i] = 0;
    }
  float h = 1./(hi[0]);
  Box domainWithGhost(lo,hi);
  Box domain = domainWithGhost.grow(-1);
  MDArray phi(domainWithGhost);
  MDArray LOfPhi(domain);
  for (int i=0;i<domainWithGhost.sizeOf();i++)
    {
      int tuple[DIM];
      domainWithGhost.tupleIndex(i,tuple);
      float val = 1.;
      for (int dir = 0;dir < DIM; dir++)
        {
          if (dir%2 == 0)
            {
              val = val*sin(2*M_PI*tuple[dir]*h);
            }
          else
            {
              val = val*sin(2*M_PI*tuple[dir]*h);
            }
        } 
      phi[i] = val;
    }
  
  for (int i=0;i < domain.sizeOf();i++)
    {
      int tuple[DIM];
      LOfPhi[i] = 0.;
      domain.tupleIndex(i,tuple);
      assert (i==domain.linearIndex(tuple));
      for (int dir = 0;dir < DIM; dir++)
        {
          LOfPhi[i] += (phi.indexShift(tuple,dir,1) + phi.indexShift(tuple,dir,-1));
          
        }
       LOfPhi[tuple] -=2*DIM*phi[tuple];
    }
  LOfPhi /= h*h;

  /*  for this simple input of Phi = sin(2*pi*x)sin(2*pi*y) the exact solution
      is Lap(Phi) = -8pi^2 sin(2*pi*x)sin(2*pi*y) = -8pi^2*Phi 

      therefore we can check that error = |Lap(Phi) + 8*pi^2*Phi|

  */
  float scale = 8*M_PI*M_PI;
  float maxerr = 0;
  int imax;
  int tuple[DIM];
  int tuplemax[DIM];
  for(int i=0; i<domain.sizeOf(); i++)
    {
      domain.tupleIndex(i, tuple);
      float err = fabs(LOfPhi[i] + scale*phi[tuple]);
      if(err > maxerr)
        {
          maxerr = err;
          imax = i;
        }
    }
  domain.tupleIndex(imax, tuplemax);
  printf("max error:%le \n", maxerr);
  printf("at location [%d, %d]\n\n", tuplemax[0], tuplemax[1]);
  
}
