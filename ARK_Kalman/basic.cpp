#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "matrix.h"
#include <unistd.h>

float vel=0.3,dt=0.02,r=0,theta=45;



int main()
{
  float **A_mat,**X_mat,**H_mat,**P_mat,**Q_mat,**R_mat,**W_mat;

  A_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    A_mat[i]=(float*)malloc(3*sizeof(float));

  for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
	A_mat[i][j]=0;
    }
 
  A_mat[1][1]=1;
  A_mat[0][0]=1;
  A_mat[2][2]=1;
  A_mat[0][1]=dt;

 
  matrix A(3,3);  
 A =  A.con_to_mtrx(A_mat,3,3);

  A.show();


  X_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    X_mat[i]=(float*)malloc(1*sizeof(float));

  for(int i=0;i<3;i++)
    {
      for(int j=0;j<1;j++)
	X_mat[i][j]=0;
    }

  X_mat[1][0]=vel;
  X_mat[0][0]=r;
  X_mat[2][0]=theta;
 
  

  matrix X(3,1);  
  X = X.con_to_mtrx(X_mat,3,1);

  X.show();


  H_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    H_mat[i]=(float*)malloc(3*sizeof(float));

  for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
	{
	  
	   H_mat[i][j]=0;
	}
    }
   // H_mat[0][0]= 1;
  H_mat[2][2] = 1;

  matrix H(3,3);  
  H = H.con_to_mtrx(H_mat,3,3);

  H.show();


  P_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    P_mat[i]=(float*)malloc(3*sizeof(float));

  for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
	{
	  if(i==j)
	    P_mat[i][j]=50;	
	  else P_mat[i][j]=0;
	}
    }

  matrix P(3,3);  
  P = P.con_to_mtrx(P_mat,3,3);

  P.show();


  Q_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    Q_mat[i]=(float*)malloc(3*sizeof(float));

  for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
	{
	  if(i==j)
	    Q_mat[i][j]=0;	
	  else Q_mat[i][j]=0;
	}
    }

  Q_mat[2][2]=400;
  matrix Q(3,3);  
  Q = Q.con_to_mtrx(Q_mat,3,3);

  Q.show();

 R_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    R_mat[i]=(float*)malloc(3*sizeof(float));

  for(int i=0;i<3;i++)
  {
      for(int j=0;j<3;j++)
		{
		  if(i==j)
		    R_mat[i][j]=0;	
		  else R_mat[i][j]=0;
		}
  }


  R_mat[0][0] = .01;
  R_mat[1][1] = .01;
  R_mat[2][2] = 10;
  matrix R(3,3);
  R = R.con_to_mtrx(R_mat,3,3);

  R.show();
  R.transpose();


  W_mat=(float**)malloc(3*sizeof(float*));

  for(int i=0;i<3;i++)
    W_mat[i]=(float*)malloc(1*sizeof(float));

  for(int i=0;i<3;i++)
  {
      for(int j=0;j<1;j++)
    {
      if(i==j)
        W_mat[i][j]=0;  
      else R_mat[i][j]=0;
    }
  }

  W_mat[0][0] = .01;
  W_mat[1][0] = .01;
  W_mat[2][0] = 1;
  matrix W(3,1);
  W = W.con_to_mtrx(W_mat , 3,1);


  R.show();
   float flag=0;
  int temp=1;

  matrix HT(3,3);

  matrix S(3,3);

  matrix SI(3,3);

  matrix K(3,3);
  matrix A1(3,3);
  matrix I(3,3);
  I.identity(3);
  matrix Z(3,3);

  while(flag<=20)
    {
      flag=temp*dt;
       std::cout << "New X" << "\n";
      X.show();
      std::cout << "PPPPPPPPPPPPPP" << "\n";
      P.show();

     
    
      
      
      //matrix S(3,3);
   
      if((flag == (int)flag) && ((int)flag%5 == 0))
      {

      // A1=A.transpose();
        std::cout << "NOISE NOISE NOISE NOISE!!!!!";

        P=(A*P)*A.transpose() + Q;
        X=A*X;
       // break;

        flag+=0.8;

    }

   else
  {

        P=(A*P)*A.transpose();
    X=A*X;

  
   

  }

   Z = H*X ;
    
     S = H*(P*H.transpose()) + R;
     
     K = P*H.transpose()*S.inv();
     X = X + K*(Z - H*X);
     P = (I - K*H)*P;


    //flag++;

      
     usleep(700000);
      temp++;



      

      
    }





 return 0;


}


    
 

  
