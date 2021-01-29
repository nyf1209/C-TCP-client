/*revceive.c is supposed to receive a data pack from the server
It check the correctness and the integrity of the data pack
Then, it shows the result from the server*/

#include<malloc.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
/*the receive.c file include different type of received packet, because
different data packet have different return form, there are
total 21 receive functions */
#include "receinstruction.c"  



/* example of the receive.c packet */
/*warning: if there's error, another four bits will be
inserted in the data pack after the LONG*/
///////////////////////////////////////////////////////
// value            //name    //     function      ////
///////////////////////////////////////////////////////
// 0x87654321      //HEAD   // head of the data pack//
//////////////////////////////////////////////////////
// 16             //LONG    // length of data pack //
/////////////////////////////////////////////////////
// 1000            //INSTR  // enter the experiment//
////////////////////////////////////////////////////
//75            //CHECK // check the data pack   //
////////////////////////////////////////////////////


/*the function head() check the first 4 bits of the datapack
if the first four bits is not 0x87654321, it returns 0
it it is, then the function returns 1.*/
int head(char * addre){

/*check the first four bit*/
unsigned int  check ;
memcpy(&check,&addre[0],sizeof(unsigned int));

//printf("head is %d",check);

/*check code is 0x87654321, which is 2271560481 in decimal*/
    if(check==2271560481){
        return 1;
    }
    else
    {
        return 0;
    }
}


/*the main function will check each part of the data pack,
it all of them are correct, it return 1 , if any part of
them is incorrect, it returns 0.*/
int receive(char * buffaddr,unsigned int trigger19 ){

    unsigned int type;

    /*check the head error .*/
     if(head(buffaddr)== 0 ){
         printf("packet corruption, HEAD ERROR\n");
         return 0;
     }  
     

    /*if everything is correct, analyze the packet returned from the server.*/
    memcpy(&type,&buffaddr[8],sizeof(unsigned int));
    printf("analyzing instruction code : %u ...\n",type);


    /*if every part of the packet is correct, check the instruction 
    which cater to the different receive functions, there are
    total 21 functions which ranges from 1000 to 1022 but 1020
    is not included*/
    if (type == 1000)
    {
        receive1000(buffaddr);
    }

    else if (type == 1001)
    {
        receive1001(buffaddr);
    }
    
    else if(type == 1002)
    {
        receive1002(buffaddr);
    }

    else if(type == 1003)
    {
        receive1003(buffaddr);
    }

    else if(type == 1004)
    {
        receive1000(buffaddr);
    }

    else if(type == 1005)
    {
        receive1005(buffaddr);
    }

    else if(type == 1006)
    {
        receive1000(buffaddr);
    }

    else if(type == 1007)
    {
        receive1000(buffaddr);
    }

     else if(type == 1008)
    {
        receive1000(buffaddr);
    }

    else if(type == 1009)
    {
        receive1000(buffaddr);
    }

    else if(type == 1010)
    {
        receive1000(buffaddr);
    }

    else if(type == 1011)
    {
        receive1000(buffaddr);
    }

    else if(type == 1012)
    {
        receive1000(buffaddr);
    }

    else if(type == 1013)
    {
        receive1000(buffaddr);
    }

    else if(type == 1014)
    {
        receive1000(buffaddr);
    }

    else if(type == 1015)
    {
        receive1000(buffaddr);
    }

    else if(type == 1016)
    {
        receive1000(buffaddr);
    }

    else if (type == 1017)
    {
        receive1000(buffaddr);
    }

    else if (type == 1018)
    {
        receive1018(buffaddr);
    }
    /*special case*/
    else if (type == 1019)
    {
        receive1019(buffaddr,trigger19);
    }

    else if (type == 1021)
    {
        receive1000(buffaddr);
    }

    else if (type == 1022)
    {
        receive1000(buffaddr);
    }
    
    /*the instruction is none of those 21 instructions
    print the error.*/
    else
    {
        printf("unknown instruction\n");
    }

return 1; 
}
    
