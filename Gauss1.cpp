#include "Func.h"


int Gauss(double* Matrix, double* X, double eps, double NormInf, int n){


        double mach_eps = 1.0;
	double Norm;
	double ForNorm;
	double* MultInd;
        while (1.0 + mach_eps/ 2.0 > 1.0)
        {
                mach_eps /= 2.0;
        }
        //int IntSwap;
        mach_eps=mach_eps*1000;
	int sh=1;
	
	//почти диагональный
	while(sh<n-1){
		ForNorm=0;
		Norm=0;
		for(int i=sh; i<n; i++){
			X[i]=Matrix[i*n+sh-1];
			ForNorm+=X[i]*X[i];
		}        
		ForNorm=sqrt(ForNorm);
		for(int i=sh; i<n; i++){
			if(i==sh){
                		X[i]=X[i]-ForNorm;
                		Norm+=X[i]*X[i];
			}else{
				Norm+=X[i]*X[i];
			}
		
	        }
		Norm=sqrt(Norm);
		if(Norm>mach_eps){
			for(int i=sh; i<n; i++){
                		X[i]=X[i]/Norm;
	        	}
	
	
			for(int j=sh-1; j<n; j++){
				ForNorm=0;
				for(int i=sh; i<n; i++){
        	        		ForNorm+=Matrix[j+i*n]*X[i];
	                	}
				for(int i=sh; i<n; i++){
					Matrix[j+i*n]-=2*ForNorm*X[i];
				}
			}
		
		//return 0;

                	for(int i=sh-1; i<n; i++){
                        	ForNorm=0;
				MultInd=Matrix+i*n;
                        	for(int j=sh; j<n; j++){
                               		ForNorm+=MultInd[j]*X[j];
                        	}
                        	for(int j=sh; j<n; j++){
                                	MultInd[j]-=2*ForNorm*X[j];
                        	}
                	}

		}
	sh++;
	}
	
	//почти диагональный
	double a=-1*fabs(1/NormInf+4), b=-1*a*2,c=0;
	double li=Matrix[0], li1, ui=Matrix[1]/li, ui1, lyi;
	int s;

	
	
	for(int k=1; k<n+1; k++){
		a=-1*fabs(1/NormInf);
		b=-1*a*2;
        	li=Matrix[0]; 
		ui=Matrix[1]/li;
		while(fabs(b-a)>eps*NormInf){
			c=(b+a)/2+eps*NormInf/10;
	        	//if(k==2){printf("c %f ", c);}	
			li=Matrix[0]-c;
			ui=Matrix[1]/li;
		
			if(li<mach_eps){s=1;}else{s=0;}

			for(int i=1; i<n; i++){
				lyi=Matrix[i*n+i-1];
				li1=Matrix[i*n+i]-c-lyi*ui;
				if(i!=n-1){
					ui1=Matrix[i+1+i*n]/li1;
				}
				if(li1/fabs(li1)<mach_eps){s++;} 
				//if(k==2){printf("i %d s %d ", i, s);
				//printf("ui %f, lyi %f, li1 %f, b %f, a %f \n", ui, lyi, li1, b, a);}
				ui=ui1;
                		li=li1;
			}
	 	

			if(k>s){a=c;}else{b=c;}
			

		}
		//printf("\n \n \n");
		X[k-1]=b/NormInf;
		//printf("%f \n", b/NormInf);
		
	}

	//printf("%f \n", b);
	
        return 0;
}


