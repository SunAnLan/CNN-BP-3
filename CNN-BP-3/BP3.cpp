#include "iostream"
#include "cmath"
#include "time.h"


using namespace std;

//整型转换32维Array
int * TransForm(int input){
	int InputTrans[32];
	int n =input;
	int temp=0;
	for(int i=31;i>=0;i--){
	  InputTrans[i] =n%2;
	  temp =n/2;
	  n =temp;
  }
	return InputTrans;
}




class BPNN{
public :BPNN(int i);
		double* BP(int  input,int *expt,double *inputweights,double*outputweights,double learningrate);
		double getDist();
private:double dist;

};

BPNN::BPNN(int i){

}

double* BPNN::BP(int input,int *expt,double *inputweights,double *outputweights,double learningrate){
  int *InputTrans;
  double hide[15]={0};
  int c=0,d=0,e=0,f=0,g=0;
  double output[4]={0};
  dist =0;
  
  //转换成32位向量表示数字

  InputTrans =TransForm(input);
  
  
  //开始forward
  for(int i=0;i<32;i++){
	  if(c<480){
	  for(int j=c,p=0;j<c+15;j++,p++)
		  hide[p] +=InputTrans[i]*inputweights[j];
      c+=15;
	  }
  }
   for(int i=0;i<15;i++){
    double temp =0;
	temp =hide[i];
	hide[i]=1/(1+exp(-temp));
  }
  for(int i =0;i<15;i++){
	  if(d<60){
	    for(int j=0,p=0;j<d+4;j++,p++)
			output[p] += hide[i]*outputweights[j];
		  
	  }
  }
  for(int i=0;i<4;i++){
    double temp =0;
	temp =output[i];
	output[i]=1/(1+exp(-temp));
  }
  //求解误差值
  for(int i =0;i<4;i++){
	  dist += pow(output[i]-expt[i],2)/2;
  }

  //反向修改权值

  //1.修改outputweights
  while(f<4){
	  for(int i=f,p=0;i<60;i +=4,p++){
		  outputweights[i] -= hide[p]*learningrate*output[f]*(1-output[f])*(output[f]-expt[f]);  
		 // cout<<outputweights[i]<<"  ";
	  }
	//  cout<<endl;
	  f++;
  }

  //2.修改inputweights
	  for(int i=0,p=0,q=0;i<420;i++,p++){
		  for(int j=0;j<4;j++){
			  inputweights[i] -= hide[p]*(1-hide[p])*InputTrans[q]*output[j]*(1-output[j])*outputweights[j];
		  }
		  if(p>=14)
		  {p=0;
		   q++;
		  }

	 // cout<<endl;
	  g++;
  }

  return output;
}

double BPNN::getDist(){
     return dist;
}

int main(){
   BPNN bp(1);
   double dist;
   double *output;
   double inputweights[480];
   for(int i=0;i<480;i++){
	   srand((unsigned)time(0));
	   inputweights[i] =(double)rand()/RAND_MAX;
   }
   double outputweights[60];
   for(int i=0;i<60;i++){
       srand((unsigned)time(0));
	   outputweights[i] =(double)rand()/RAND_MAX;
   }
   int expt[4];
   for(int j=0;j<2000;j++){
   for(int input =1;input<1000;input++){
	      if(input%2==0){
		      expt[0]=1;expt[1]=0;expt[2]=0;expt[3]=0;
	      }
	      else{
	          expt[0]=0;expt[1]=1;expt[2]=0;expt[3]=0;
	      }
		  output =bp.BP(input,expt,inputweights,outputweights,0.001);
		 // cout<<output[0]<<"  "<<output[1]<<"  "<<output[2]<<"  "<<output[3]<<endl;
		  dist =bp.getDist();
		  if(dist<0.1){
		    break;
		  }
     }
   }
   output =bp.BP(27,expt,inputweights,outputweights,0.001);
   for(int i=0;i<4;i++){
	   cout<<output[i]<<endl;
   }

   return 0;
}