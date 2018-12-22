
#include <time.h>
#include <intrin.h>
#include <stdio.h> 
#define NN 4000 //在此改变矩阵大小 

#include<thread>
using namespace std;

void AVX(int n,int bg,int seeu, float **a, float **b, float **e);
void AVX1(int n,int bg,int seeu, float **a, float **b, float **d);
int main() {
	float **a, **b, **c ,**d,**e;
    double  msecs,msecs1,msecs2;
    clock_t startt, finish,startt1, finish1,startt2, finish2; 
    float tmp=0.0;
    int i=0;
    int j=0;
    int N=0;
    if(NN%2==1)
    {
    	N=NN+1;
    }else
    {
    	N=NN;
    }
    float __attribute__((aligned(32))) temp[8] ={0};//对齐 
   
     double sum=0; 
    
	                                                       
    a = (float**) malloc(N*sizeof(float*));
    b = (float**) malloc(N*sizeof(float*));
    c = (float**) malloc(N*sizeof(float*));
    d = (float**) malloc(N*sizeof(float*));
    e = (float**) malloc(N*sizeof(float*));
    
   
    //初始化数组 
    
    
    srand((unsigned) time(NULL)); 
  
      for(i=0; i<N; i++) {
   	    a[i]=(float*) malloc(N*sizeof(float));
    	b[i]=(float*) malloc(N*sizeof(float));
    	c[i]=(float*) malloc(N*sizeof(float));
    	d[i]=(float*) malloc(N*sizeof(float));
    	e[i]=(float*) malloc(N*sizeof(float));
    
    	
    	for (j=0;j<N;j++){
    		 a[i][j] = (float)(rand() % 10);
    		  b[i][j] =(float)(rand() % 10);
    		  c[i][j] =0;
    		  d[i][j]=0;
    		  e[i][j]=0;
    
    	}    
		 
        
    }
    	if (N%2==1)
    	{
    		for (j=0;j<N;j++)
    		
    	{
    		a[j][N]=0;
    		b[j][N]=0;
    		a[N][j]=0;
    		b[N][j]=0;
    	}
    	}
 
    startt1 = clock(); 
     for(i=0;i<N;i++){
     
        for(j=0;j<N;j++){
            	for(int k=0;k<N;k++){
                c[i][k]=c[i][k]+a[i][j]*b[j][k]; 
                
            } 
       
        } 
    
    }
    finish1 = clock(); 
    msecs1=(double)(finish1-startt1) / CLOCKS_PER_SEC;
    printf("Normal:Execution time = %2.3lf s\n", msecs1);
   
 
    // 先转置数组
    if(N%2==0){ 
 for (i = 0;i<N;i++)
	{
		
		for (j = 0;j<i;j++)
		{
			
			tmp = b[j][i];
			
			b[j][i] = b[i][j];
			
			b[i][j] = tmp;
		
		}
	}
	} else{
		 for (i = 0;i<N-1;i++)
	{
		
		for (j = 0;j<i;j++)
		{
			
			tmp = b[j][i];
			
			b[j][i] = b[i][j];
			
			b[i][j] = tmp;
		
		}
	} 
}
//开始算数    
    
   
   
   startt = clock(); 
   AVX1(N,0,N, a, b, d);
   /*
   for (i = 0;i<N;i++)
		{
			
			for (j =0 ;j<N;j++)
			{
			    
				sum = 0;
				
				D =_mm256_setzero_ps();//初始化D
			    
				for (int k = 0;k<test;k+=8)
				
				{   
				    
				    
					A = _mm256_loadu_ps(&a[i][k]);
				
					B = _mm256_loadu_ps(&b[j][k]);
					 
				
					C = _mm256_mul_ps(A, B);				
				  	D = _mm256_add_ps(C, D);										 				      
				}
				
				_mm256_storeu_ps(temp, D);
			
				for (int m = 0;m<8;m++)
				
				{  
					d[i][j] += temp[m];
		
				}
			
			     for (int k=test;k<N;k++){
			     	d[i][j]+=a[i][k]*b[j][k];
			     
			     }
			  
			}
		
		}*/
	    
		finish = clock(); 
		
	
 

    
  
    msecs=(double)(finish-startt) / CLOCKS_PER_SEC;
   
    printf("AVX:Execution time = %2.3lf s\n", msecs);
    
    printf("%d行列AVX矩阵加速比：%f\n",NN,msecs1/msecs);
    
    
    
    startt2 = clock(); 
    /* thread thread1( AVX,N,0,N/4, a, b, e);
	thread thread2( AVX,N,N/4,N/2, a, b, e);
	thread thread3( AVX,N,N/2,3*N/4, a, b, e);
	thread thread4( AVX,N,N*3/4,N, a, b, e);	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();*/
  
   if ((N/4)%2==1&&N%4==0){
    //	printf("1");
    thread thread1( AVX,N,0,N/4-1, a, b, e);
	thread thread2( AVX,N,N/4-1,N/2, a, b, e);
	thread thread3( AVX,N,N/2,3*N/4-1, a, b, e);
	thread thread4( AVX,N,N*3/4-1,N, a, b, e);	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	
    }
else if ((N/4)%2==0&&N%4==2)
    {
    	//	printf("3");
    thread thread1( AVX,N,0,N/4-1, a, b, e);
	thread thread2( AVX,N,N/4-1,N/2, a, b, e);
	thread thread3( AVX,N,N/2,3*N/4-1, a, b, e);
	thread thread4( AVX,N,N*3/4-1,N, a, b, e);	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
    }	else 
    {
    //	printf("2");
    thread thread1( AVX,N,0,N/4, a, b, e);
	thread thread2( AVX,N,N/4,N/2, a, b, e);
	thread thread3( AVX,N,N/2,3*N/4, a, b, e);
	thread thread4( AVX,N,N*3/4,N, a, b, e);	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
  
    } 
    
   finish2 = clock();
  	 msecs2=(double)(finish2-startt2) / CLOCKS_PER_SEC;
    printf("AVX多线程:Execution time = %2.3lf s\n", msecs2);
    
    printf("%d行列AVX矩阵多线程加速比：%f\n",NN,msecs1/msecs2);
    
   
     for (j=0;j<N;j++){
    	     
    for(i=0; i<N; i++) {
    	
       if(d[j][i]!=c[j][i] || e[j][i]!=c[j][i])
       {
       	printf("c[%d][%d]:%f\n",i,j,c[i][j]);
       	printf("d[%d][%d]:%f\n",i,j,d[i][j]);
       	printf("e[%d][%d]:%f\n",i,j,e[i][j]);
       	break;
       }
     
      
       
    }
   // printf("\n");
    }
    
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    system("pause");
    return 0;
    
}

void AVX(int n,int bg,int seeu, float **a, float **b, float **e)
{
	__m256 A, B, C, D,A1,B1,C1,D1,C01,D01,C11,D11;
	int i=0;
    int j=0;
    double sum=0;
    double sum1=0;
    double sum01=0;
    double sum11=0;
    int test1=n-n%8;
  //  double sum2=0;
  
 //  printf("bg:%d,see:%d\n",bg,seeu);
    float __attribute__((aligned(32))) temp[8] ={0};
    float __attribute__((aligned(32))) temp1[8] ={0};
     float __attribute__((aligned(32))) temp01[8] ={0};
     float __attribute__((aligned(32))) temp11[8] ={0};
   // float __attribute__((aligned(32))) temp2[8] ={0};
   
       //printf("%d,%d\n",i,j);
   for (i = bg;i<seeu;i+=2)
		{
			 
			for (j =0 ;j<n;j+=2)
			{
			    
				sum = 0;
			    sum1=0;
			    sum01=0;
			    sum11=0;
				D =_mm256_setzero_ps();//初始化寄存器
			    D1 =_mm256_setzero_ps();
			    D11 =_mm256_setzero_ps();
			    D01 =_mm256_setzero_ps();
			 //   D2 =_mm256_setzero_ps();
				for (int k = 0;k<test1;k+=8)
				
				{   
				   
				    
					A = _mm256_loadu_ps(&a[i][k]);
					A1=_mm256_loadu_ps(&a[i+1][k]);
			//		A2=_mm256_loadu_ps(&a[i+2][k]);
					//  for (int tt=0;tt<N;tt++)
				  //   {
				   //   	printf("A[%d]:%f\n",tt,A[tt]);
				//	  }
				     
					B = _mm256_loadu_ps(&b[j][k]);
					B1 = _mm256_loadu_ps(&b[j+1][k]);
					 /*	  for (int tt=0;tt<N;tt++)
				      {
				      	printf("B[%d]:%f\n",tt,B[tt]);
					  }
				      */
					C = _mm256_mul_ps(A, B);
					C1= _mm256_mul_ps(A1, B);
					C11= _mm256_mul_ps(A1, B1);
					C01= _mm256_mul_ps(A, B1);
				//	C2= _mm256_mul_ps(A2, B);
					/*	  for (int tt=0;tt<8;tt++)
				      {
				      	printf("C[%d]:%f\n",tt,C[tt]);
					  }*/
				      					

					D = _mm256_add_ps(C, D);
					D1=_mm256_add_ps(C1, D1);
					D11=_mm256_add_ps(C11, D11);
					D01=_mm256_add_ps(C01, D01);
				//	D2=_mm256_add_ps(C2, D);

							
				 	 /*    for (int tt=0;tt<3;tt++)
				      {
				      	printf("%d,%d,%d,D[%d]:%f\n",i,j,k,tt,D[tt]);
					  }*/
				  //    printf("\n");
				      
				}
				
				_mm256_storeu_ps(temp, D);
				_mm256_storeu_ps(temp1, D1);
				_mm256_storeu_ps(temp11, D11);
				_mm256_storeu_ps(temp01, D01);
				 
			//	float*test=(float*)&D;
				for (int m = 0;m<8;m++)
				
				{  // printf("temp[%d]: %f   ",m,temp[m]);
					sum += temp[m];
					sum1 += temp1[m];
					sum11 += temp11[m];
					sum01 += temp01[m];
			//	sum += test[m];
				//	printf("sum: %f   \n",sum);
				}
			//     printf("d[%d][%d]:%f \n",i,j,d[i][j]);
			     for (int k=test1;k<n;k++){
			     	sum+=a[i][k]*b[j][k];
			     	sum1+=a[i+1][k]*b[j][k];
			     	sum01+=a[i][k]*b[j+1][k];
			     	sum11+=a[i+1][k]*b[j+1][k];
			     //	 printf("a[%d][%d]:%f \n",i,k,a[i][k]);
			     }
			    e[i][j] = sum;
			    e[i+1][j] = sum1;
			    e[i+1][j+1] = sum11;
			    e[i][j+1] = sum01;
			  //  printf("%d,%d\n",i,j);
			}
		//	printf("d[%d][0]:%f\n",i,c[i][0]);
		}
	/*	
		for (i = seeu-(seeu-bg)%2;i<seeu;i++)
		{
			for (j=0;j<n;j++)
			{
				e[i][j]=e[i][j]+a[i][j]*b[i][j];
			}
			
		}
	*/
}
void AVX1(int n,int bg,int seeu, float **a, float **b, float **d)
{
//	printf("bg:%d,see:%d\n",bg,seeu);
	__m256 A, B, C, D;
	float tmp=0.0;
    int i=0;
    int j=0;
    //int z=0;
    int test=n-n%8;
   // float __attribute__((aligned(32))) temp[8] ={0};//对齐 
   float temp[8] ={0};
     double sum=0; 
	 for (i = bg;i<seeu;i++)
		{
			
			for (j =0 ;j<n;j++)
			{
			    
				sum = 0;
				
				D =_mm256_setzero_ps();//初始化D
			    
				for (int k = 0;k<test;k+=8)
				
				{   
				    
				    
					A = _mm256_loadu_ps(&a[i][k]);
				
					B = _mm256_loadu_ps(&b[j][k]);
					 
				
					C = _mm256_mul_ps(A, B);				
				  	D = _mm256_add_ps(C, D);										 				      
				}
				
				_mm256_storeu_ps(temp, D);
			
				for (int m = 0;m<8;m++)
				
				{  
					d[i][j] += temp[m];
		
				}
			
			     for (int k=test;k<n;k++){
			     	d[i][j]+=a[i][k]*b[j][k];
			     
			     }
			  
			}
		
		}
}

