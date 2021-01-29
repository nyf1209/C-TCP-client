/*send.c is supposed to send a datapack to the server.
It allocate the memory location for the data pack and 
check the correctness of the data pack during the 
tranfer.The table below shows a structure of the data
pack */

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
/*the head file include the 21 different instructions which communicate
with the server and get the data back from the server.*/
#include "sendinstruction.c"


/*example of send.c packet */
///////////////////////////////////////////////////////
// value            //name    //     function      ////
///////////////////////////////////////////////////////
// 0x12345678       //HEAD   // head of the data pack//
//////////////////////////////////////////////////////
// 38              //LONG    // length of data pack //
/////////////////////////////////////////////////////
// 1000            //INSTR  // enter the experiment//
/////////////////////////////////////////////////////
// 1               //inform // show the interface of sample//
/////////////////////////////////////////////////////
// 1              //inform // create sinusoidal test//
//////////////////////////////////////////////////////
//AA16286909      //inform// code of the experiment //
/////////////////////////////////////////////////////
//q             //inform//  prepare to send     //
////////////////////////////////////////////////////
//853            //CHECK // check the data pack   //
////////////////////////////////////////////////////


/*sending function is to collect different data from each user's choice
and integrate into a big buffer*/
char * sending(int type){
unsigned int instruction=0;

/*the function read the instruction first,then call different function
the instruction is from 1000 to 1022 but 1020 is not included*/
    if (type==0)
    {
        printf("please start a new experiment, enter 1000 :\n");
        scanf("%d",&instruction);
    }
   
     else
    {
        
        scanf("%d",&instruction);
    }    

    if (instruction == 1000 )
    {
        return code0();
    }

    else if(instruction == 1001)
    {
        return code1();
    }

    else if(instruction == 1002)
    {
        return code2();
    }

    else if(instruction == 1003)
    {
        return code3();
    }

    else if(instruction == 1004)
    {
        return code4();
    }

    else if(instruction == 1005)
    {
        return code5();
    }

    else if(instruction == 1006)
    {
        return code6();
    }

    else if(instruction == 1007)
    {
        return code7();
    }

    else if(instruction == 1008)
    {
        return code8();
    }

    else if(instruction == 1009)
    {
        return code9();
    }

     else if(instruction == 1010)
    {
        return code10();
    }

     else if(instruction == 1011)
    {
        return code11();
    }

    else if(instruction == 1012)
    {
        return code12();
    }

    else if(instruction == 1013)
    {
        return code13();
    }

    else if(instruction == 1014)
    {
        return code14();
    }

    else if(instruction == 1015)
    {
        return code15();
    }

    else if(instruction == 1016)
    {
        return code16();
    }

    else if(instruction == 1017)
    {
        return code17();
    }

      else if(instruction == 1018)
    {
        return code18();
    }

     else if(instruction == 1019)
    {
        return code19();
    }

    else if(instruction == 1021)
    {
        return code21();
    }

     else if(instruction == 1022)
    {
        return code22();
    }

/*if the input is none of those instruction , let the user reenter
the instruction*/
    else 
    {
      printf("invalid instruction,please retry.\n");
      
      sending(type);
    }

}




  




