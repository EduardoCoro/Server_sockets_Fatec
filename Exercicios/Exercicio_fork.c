#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i=0;

	if(fork())
	   if(fork()){
 		for(i=0; i<2; i++)
		   wait(NULL);
		printf("Processo A \n");
 	   }
	   else{
 		printf("Processo C \n");
           }
	else
	  if(fork())
	    if(fork())
             if(fork()){
		for(i=0; i<3; i++)
		    wait(NULL);
		printf("Processo B\n");
	       }
	     else
	 	  printf("Processo F\n");
	    else
		printf("Processo E \n");
	  else
	      printf("Processo D\n");	
	return 0;
}
