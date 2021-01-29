/*code 1000 should receive the data pack for the length of
16 bits packet, it there's an error. it will be inserted after
the instruction part and the length will become 20 bits long*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>


/*those recesive packets are same as rec1000:
1004 1006 1007 1008 1009
1010 1011 1012 1013 1014
1015 1016 1017 1021 1022*/
void receive1000(char * buffer)
{
    unsigned int ilength;
    unsigned int ierror;
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));

    if(ilength==16)
    {
        printf("success ! \n");
        return;
    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }
    
}


/*receive1001*/
void receive1001(char * buffer)
{
    unsigned int ilength;
    unsigned int ierror;
    int inform;
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));

    if(ilength==20)
    {
        printf("success ! \n\n");

        /*read the information*/
        memcpy(&inform,&buffer[12],sizeof( int));
        printf("code 1001 return: status %d \n\n",inform);
        return;
    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }

}


/*receive1002*/
void receive1002(char * buffer)
{
    unsigned int ilength;
    unsigned int ierror;
    int iinput;
    int ioutput; 
    int icheck;

    memcpy(&icheck,&buffer[8],sizeof(unsigned int));
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));

    if(ilength==24 && icheck < 5000 )
    {
        printf("success ! \n\n");

        /*read the Number of input channels*/
        memcpy(&iinput,&buffer[12],sizeof( int));
        printf("code 1002 return: Number of input channels %d \n\n",iinput);
        /*read the Number of output channels*/
        memcpy(&ioutput,&buffer[16],sizeof( int));
        printf("code 1002 return: Number of output channels %d \n\n",ioutput);

        return;
    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }

}


/*receive1003*/
void receive1003(char * buffer)
{
    unsigned int ilength;
    unsigned int ierror;
    int check;

    int iserialnum=0;
    int ichantype=0;
    int isentype=0;
    int isensor=0;
    int icoupletype=0;
    float fsensitivity=0;

    memcpy(&check,&buffer[12],sizeof(unsigned int));
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));

    if(ilength==40 && check < 5000 )
    {
        /*anaylze the information from the server.*/
        printf("success ! \n\n");

        memcpy(&iserialnum,&buffer[12],sizeof(int));
        printf("The channel serial number is: %d \n",iserialnum);

        memcpy(&ichantype,&buffer[16],sizeof(int));
        printf("The type of channel is: %d \n",ichantype);

        memcpy(&isentype,&buffer[20],sizeof(int));
        printf("The sensor type is: %d \n",isentype);

        memcpy(&isensor,&buffer[24],sizeof(int));
        printf("The sensor mode is: %d \n",isensor);

        memcpy(&icoupletype,&buffer[28],sizeof(int));
        printf("The Coupling type is: %d \n",icoupletype);

        memcpy(&fsensitivity,&buffer[32],sizeof(float));

        if (isensor==1)
        {
            printf("The acceleration is: %f mv/(m/s^2)\n\n",fsensitivity);
            return;
        }

        else if(isensor==2)
        {
            printf("The velocity is: %f mv/(m/s)\n\n",fsensitivity);
            return;
        }

        else
        {
            printf("The displacement is: %f mv/(m)\n\n",fsensitivity);
            return;
        }
 
    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }

}



/*receive1005*/
void receive1005(char * buffer)
{
    unsigned int ilength;
    unsigned int ierror;
    int check;

    float facceleration;
    float fvelocity;
    float fposdisplacement;
    float fnegdisplacement;
    float flowfreq;
    float fupfreq;

    memcpy(&check,&buffer[12],sizeof(unsigned int));
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));

    if(ilength==40  )
    {
        /*anaylze the information from the server.*/
        printf("success ! \n\n");

        memcpy(&facceleration,&buffer[12],sizeof(float));
        printf("The max acceleration is: %f m/s^2\n",facceleration);

        memcpy(&fvelocity,&buffer[16],sizeof(float));
        printf("The max velocity is: %f m/s\n",fvelocity);

        memcpy(&fposdisplacement,&buffer[20],sizeof(float));
        printf("The max positive displacement is: %f m\n",fposdisplacement);

        memcpy(&fnegdisplacement,&buffer[24],sizeof(float));
        printf("The max negative displacement is: %f m\n",fnegdisplacement);

        memcpy(&flowfreq,&buffer[28],sizeof(float));
        printf("The lower limit frequency is: %f Hz\n",flowfreq);

        memcpy(&fupfreq,&buffer[32],sizeof(float));
        printf("The upper limit frequency is: %f Hz\n",fupfreq);

        return;

    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }

}



/*receive1018*/
void receive1018(char * buffer)
{
    
    int check;
    int istatus=0;
    float flevel=0;
    float ftarget=0;
    float fcontrol=0;
    int itime=0;
    float ffreq=0;
    int control=0;

    int error=0;
    char buf[7];

    int circle=0;
    char duf[32];

    unsigned int len=0;
    memcpy(&len,&buffer[4],sizeof(unsigned int));
    int count = (len-48)/4; 

    /*check if there is an error status*/
    memcpy(&check,&buffer[12],sizeof(unsigned int));

    if( check < 5000 )
    {
        /*anaylze the information from the server.*/
        printf("success ! \n\n");

        memcpy(&istatus,&buffer[12],sizeof(int));
        printf("Current Software Running State: %d \n",istatus);

        memcpy(&flevel,&buffer[16],sizeof(float));
        printf("Current control level : %f percent\n",flevel);

        memcpy(&ftarget,&buffer[20],sizeof(float));
        printf("Current target value : %f \n",ftarget);

        memcpy(&fcontrol,&buffer[24],sizeof(float));
        printf("Current control value : %f \n",fcontrol);

        memcpy(&itime,&buffer[28],sizeof(int));
        printf("time left : %d \n",itime);

        memcpy(&ffreq,&buffer[32],sizeof(float));
        printf("frequency : %d \n",ffreq);

        for ( int i = 1; i < count+1; i++)
        {
            memcpy(&control,&buffer[32+i*4],sizeof(float));
            printf("control value of channel %d : %f \n",i,control);
        }

        memcpy(&error,&buffer[36+count*4],sizeof(int));
        /*print out binary result*/
        char a[32];
        int i=0;

        while (error>0)
        {
            a[i]=error%2;
            i=i+1;
            error=error/2;
        }
        
        printf("Abnormal information of platform : \n");

        if (error==0)
        {
           printf("0\n");
        }
        
        else
        {
                for ( i-- ; i >= 0; i--)
            {
                printf("%d",a[i]);
            }
        }
        
        /*print out another set of binary result*/
        memcpy(&circle,&buffer[40+count*4],sizeof(int));
        char b[32];
        int j=0;

        while (circle>0)
        {
            b[j]=circle%2;
            j=j+1;
            circle=circle/2;
        }
        
        printf("Open-loop channel : \n");
        
        if (circle==0)
        {
           printf("0\n");
        }
        
        else
        {
                for ( j-- ;j >= 0; j--)
            {
                printf("%d",b[j]);
            }
        }
        return;
    }



    else
    {
         memcpy(&error,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",error);
         return;
    }

}


/*receive1019*/
void receive1019(char * buffer, int inputlen)
{
    unsigned int ilength;
    unsigned int ierror;
    int check;

    char signal[inputlen];
    int type ;
    int dimension;
    char yunit[80];
    unsigned int xlen=0;
    unsigned int ylen=0;
    float xval=0;
    float yval=0;


    memcpy(&check,&buffer[12],sizeof(unsigned int));
    memcpy(&ilength,&buffer[4],sizeof(unsigned int));
  

    if( ilength!=20 )
    {
        /*first copy the signal sent to the server*/
        memcpy(signal,&buffer[12],inputlen * sizeof(char));
        printf("signal name : %s\n",signal);

        memcpy(&type,&buffer[12+inputlen],sizeof(int));
        printf("the type of the signal : %d\n",type);

        memcpy(&dimension,&buffer[16+inputlen],sizeof(int));
        printf("signal dimension : %d\n",dimension);

        memcpy(yunit,&buffer[20+inputlen],10*sizeof(char));
        printf("unit of signal on Y-axis : %s\n",yunit);   

        memcpy(&xlen,&buffer[30+inputlen],sizeof(unsigned int));
        printf("length of data on X-axis : %u\n",xlen);  

        for (int i = 1; i < xlen+1; i++)
        {
            memcpy(&xval,&buffer[30+inputlen+i*4],sizeof(float));
            printf("%d value on X-axis  : %f \n",i,xval);
        }

        unsigned ylen=xlen*dimension;
        printf("length of data on Y-axis : %u\n",ylen); 
        for (int i = 1; i < ylen+1; i++)
        {
            memcpy(&yval,&buffer[30+inputlen+xlen*4+i*4],sizeof(float));
            printf("%d value on Y-axis  : %f \n",i,yval);
        }
        

        return;

    }

    else
    {
         memcpy(&ierror,&buffer[12],sizeof(unsigned int));
         printf("ERROR CODE: %u \n",ierror);
         return;
    }

}


/*end*/