// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "/usr/include/graphics.h"
// -lXbgi -lX11 -lm

void DoArc(long X0,long Y0,long X1,long Y1,long R,long E)
{
  long D,D2,Dold,H,H2,Hold,S,AX,AY;

  R=abs(R);
  // d=sqrt((X1-X0)*(X1-X0)+(Y1-Y0)*(Y1-Y0));
  // H=sqrt(R*R-D*D/4);
  AX=abs(X1-X0);
  AY=abs(Y1-Y0);
  D2=AX*AX+AY*AY;
  if (AX>AY) {
    D=AY/2+AX;
  } else {
    D=AX/2+AY;
  }
  while (Dold=D,D=(Dold+D2/Dold)/2,D!=Dold);

  H2=R*R-D2/4;
  if (H2>0) {
    H=R+D/2;
    while (Hold=H,H=(Hold+H2/Hold)/2,H!=Hold);
    S=R-H;
    AX=(X0+X1)/2+E*S*(Y1-Y0)/D;
    AY=(Y0+Y1)/2-E*S*(X1-X0)/D;
  } else {
    S=0;
    AX=(X0+X1)/2;
    AY=(Y0+Y1)/2;
  }
  if (S>1) {
    DoArc(X0,Y0,AX,AY,R,E);
    DoArc(AX,AY,X1,Y1,R,E);
  } else {
    line(X0,600-Y0,AX,600-AY);
    line(AX,600-AY,X1,600-Y1);
    delay(500);
  }
}
int main(void) {

  // Display results
  initwindow(700,700);
  setbkcolor(WHITE);
  cleardevice();
  setcolor(BLACK);
  setlinestyle(SOLID_LINE,EMPTY_FILL,NORM_WIDTH);

  DoArc(100.0,500.0,500.0,100.0,500.0,-1); // CW
  DoArc(100.0,500.0,500.0,100.0,500.0,1);  // CCW

  printf("Done - Enter to exit");
  getchar();
  closegraph();

  return(0);
}
