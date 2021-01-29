#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

/*introduction: code0 create or enter an experiment, it's
the first step of tcp.c*/

/*choose the type of the experiment , there are total seven
different functions, if the user's input is out of range ,it 
allows user to reenter the type of experiment*/
 int setuptype0(){

    int type;
    printf("please choose a type of test.\n");
    scanf("%d",&type);
    
         if (type==1)
        {
            printf("sinusoidal test.\n");
            return 1;
        }

        else if(type==2)
        {
            printf("randomized test.\n");
            return 2;
        }

         else if(type==3)
        {
            printf("impact test.\n");
            return 3;
        }

         else if(type==4)
        {
            printf("road Spectrum test.\n");
            return 4;
        }

         else if(type==5)
        {
            printf("sinusoidal plus randomized trail.\n");
            return 5;
        }

        else if(type==6)
        {
            printf("randomized plus randomized trial.\n");
            return 6;
        }

        else if(type==7)
        {
            printf("sinusoidal plus randomized plus randomized trial.\n");
            return 7;
        }

        else if(type==8)
        {
            printf("transient impact test.\n");
            return 8;
        }

        else if(type==9)
        {
            printf("shock response spectrum test.\n");
            return 9;
        }

        else if(type==10)
        {
            printf("resonance search test.\n");
            return 10;
        }

        else if(type==11)
        {
            printf(" blade test .\n");
            return 11;
        }

        else
        {
        printf("invalid input, please retry.\n");
        setuptype0();  
        
        }       
    }


/*1 means: enter the test but don't display the software
  2 means: enter the test and display the software*/
int setupdisplay0(){

    int display;
    printf("do you want to display the interfere of the software?\n");
    scanf("%d",&display);

    if (display==1)
    {
        printf("software is displayed.\n");
        return 1 ;
    }

    else if(display==2)
    {
        printf("software is hidden.\n");
        return 2 ;
    }

    else
    {
      printf("invalid input, please retry.\n");
      setupdisplay0();    
    }
    
}

/*instruction1000 main function*/
char * code0()
{
    /*choose to build new experiment or enter a existing on
    1 means build new , 2 means enter an existing one*/
    int ibuild;

    printf("create or enter a file ? 1=build new ,2=enter\n");
    scanf("%d",&ibuild);

    /*case 1 : create a new experiment*/
    if (ibuild == 1)
    {
        printf("building code 1000 packet...\n");
        printf("building up a new experiment...\n");
        /*constants: length, head , instruction , newexp*/
        unsigned int head = 305419896;
        unsigned int length = 38;
        unsigned int instr = 1000;
        int newexp = 1;

        /*serial number of equipment is fixed*/
        char serial[10] = "AA18321046";


        /*create a pointer which will be returned to send.c*/
        char * buff=NULL;
        buff=(char*)malloc(sizeof(char)*length);

        /*build up the buffer*/
        memcpy(&buff[0],&head,sizeof(unsigned int));
        memcpy(&buff[4],&length,sizeof(unsigned int));
        memcpy(&buff[8],&instr,sizeof(unsigned int));
        memcpy(&buff[12],&newexp,sizeof( int));

        /*let the use choose the type of the experiment*/
        /*1 means sinusoidal test 
        2 means randomized test
        3 means impact test
        4 means road Spectrum test
        5 means a sinusoidal plus randomized trail
        6 means a randomized plus randomized trial
        7 means a sinusoidal plus randomized plus randomized trial
        8 means transient impact test
        9 means shock response spectrum test 
        10 means resonance search test
        11 means the blade test*/    
        int type;
        type = setuptype0();
        memcpy(&buff[16],&type,sizeof(int));

        /*add serial number to the packet*/
        memcpy(&buff[20],serial,10*sizeof(char));

        /*display = 1 : display the interfere of the software
        display = 2 : hide the interfere of the software*/
        int display;
        display = setupdisplay0();
        memcpy(&buff[30],&display,sizeof(int));

        /*a special way to calculate the final check code*/
        unsigned int check = 0;
        for(int i=0; i<length-4;i++)
        {
            check=check+(unsigned int)buff[i];
        }


        /*add the last part CHECK to the data pack*/
        memcpy(&buff[34],&check,sizeof(unsigned int));
        
        return buff;
    }
  
    /*case 2 : enter a saved experiment in the local*/
    else if (ibuild == 2)
    {

        printf("building code 1000 packet...\n");
        printf("enter an experiment...\n");
        /*constants: head , instruction , newexp*/
        unsigned int head = 305419896;
        unsigned int length = 24;
        unsigned int instr = 1000;
        int newexp = 2;

        /*get the address of the file and check if the file exists*/
        char input[1000];
        printf("please enter the address of the file : \n");
        scanf("%s",input);
        length=length+strlen(input);

        /*create a pointer which will be returned to send.c*/
        char * buff=NULL;
        buff=(char*)malloc(sizeof(char)*length);

        /*build up the buffer*/
        memcpy(&buff[0],&head,sizeof(unsigned int));
        memcpy(&buff[4],&length,sizeof(unsigned int));
        memcpy(&buff[8],&instr,sizeof(unsigned int)); 
        memcpy(&buff[12],&newexp,sizeof( int));
        memcpy(&buff[16],input,strlen(input)*sizeof(char));

        int display;
        display = setupdisplay0();
        memcpy(&buff[16+strlen(input)],&display,sizeof(int));

        /*a special way to calculate the final check code*/
        unsigned int check = 0;
        for(int i=0; i<length-4;i++)
        {
            check=check+(unsigned int)buff[i];
        }

        /*add the last part CHECK to the data pack*/
        memcpy(&buff[20+strlen(input)],&check,sizeof(unsigned int));
        
        return buff;
    }

    /*other case: reenter the choice*/
    else
    {
        printf("invalid input");
        code0();
    }
}
    


/*introduction: code1 get the status of the software*/
/*instruction1001 main function*/
char* code1()
{

    printf("building code 1001 packet...\n");
    printf("requesting for the status of software\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1001;

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));
    
    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code2.c gets the number of channels of the software*/
/*choose the type of the channel*/
int setserialnumber2()
{
    int type;
    printf("please enter the Channel serial Number.\n");
    scanf("%d",&type);
    if (type > 0)
    {
        printf("channel %d selected.\n",type);
        return type;
    }
    else
    {
        printf("invalid channel number! \n");
        setserialnumber2();
    }
}

/*instruction1002 main function*/
char *code2()
{
    /*channnel is the serial number of the channel in the software*/
    int channel;

    printf("building code 1002 packet...\n");
    printf("requesting for the number of the channel...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 20;
    unsigned int instr = 1002;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);
    
    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    channel=setserialnumber2();
    memcpy(&buff[12],&channel,sizeof( int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }

    /*add the last part CHECK to the data pack*/
    memcpy(&buff[16],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code3 gets the parameter of specific channel of the software*/
/*select the channel*/
int setserialnumber3()
{

    int type;
    printf("please enter the Channel Number.\n");
    scanf("%d",&type);

    if (type>0 && type<10)
    {
          return type; 
    }

    else
    {
        printf("invalid input\n");
        setserialnumber3();
    }

}

/*instruction1003 main function*/
char *code3()
{
    /*channnel is the serial number of the channel in the software*/
    int channel;

    printf("building code 1003 packet...\n");
    printf("requesting for channel parameter...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 20;
    unsigned int instr = 1003;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);
    
    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    channel=setserialnumber3();
    memcpy(&buff[12],&channel,sizeof( int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[16],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code4 set up the data in the channel selected*/
/*set the channel number*/
int setserialnum4()
{
    int num;
    printf("please enter the channel serial number\n");
    scanf("%d",&num);

    if (num>0 && num <10)
    {
        return num;
    }
    else
    {
        printf("invalid input\n");
        setserialnum4();
    }
}

/*set up the type of channel*/
int setchanneltype4()
{
    int chatype;
    printf("please enter type of channel: control, monitor or ban\n");
    scanf("%d",&chatype);

    if (chatype>0 && chatype<4)
    {
        return chatype;
    }
    else
    {
        printf("invalid input\n");
        setchanneltype4();
    }   
}

/*set up the type of sensor*/
int setsensortype4()
{
    int sentype;
    printf("please enter type of sensor: voltage, charge or IEPE(ICP)\n");
    scanf("%d",&sentype);

    if (sentype>0 && sentype<4)
    {
        return sentype;
    }
    else
    {
        printf("invalid input\n");
        setsensortype4();
    }
}

/*set up the mode of the sensor*/
int setsensormode4(){
    int move;
    printf("please enter the mode of sensor: acceleration, velocity or displacement\n");
    scanf("%d",&move);

    if (move>0 && move<4)
    {
        return move;
    }
    else
    {
        printf("invalid input\n");
        setsensormode4();
    }
}

/*set up the coupling type*/
int setcouplingtype4()
{
    int elec;
    printf("please enter the Coupling type: alternating or direct\n");
    scanf("%d",&elec);

    if (elec>0 && elec<3)
    {
        return elec;
    }
    else
    {
        printf("invalid input\n");
        setcouplingtype4();
    }
    
}

/*set up the sensitivity*/
int setupsensitivity4()
{
    float value;
    printf("please set up the sensitivity\n");
    scanf("%f",&value);

    if (value<0)
    {
        printf("invalid input\n");
        setupsensitivity4();
    }
    else
    {
        return value;
    }
    
}

/* instruction1004 main function*/
char *code4()
{

    /*iserialnum : the serial number of the channel
      ichantype : the type of the channel
      isentype : the type of the sensor
      icontype : the mode of the sensor
      icouple : the the coupling type of the experiment
      fsen: the sensitivity of the experiment*/
    int iserialnum=0;
    int ichantype=0;
    int isentype=0;
    int isenmode=0;
    int icouple=0;
    float fsen=0;

    printf("building code 1004 packet...\n");
    printf("setting the channel parameter...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 40;
    unsigned int instr = 1004;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iserialnum=setserialnum4();
    memcpy(&buff[12],&iserialnum,sizeof(int));

    ichantype=setchanneltype4();
    memcpy(&buff[16],&ichantype,sizeof(int));

    isentype=setsensortype4();
    memcpy(&buff[20],&isentype,sizeof(int));

    isenmode=setsensormode4();
    memcpy(&buff[24],&isenmode,sizeof(int));

    icouple=setcouplingtype4();
    memcpy(&buff[28],&icouple,sizeof(int));

    fsen=setupsensitivity4();
    memcpy(&buff[32],&fsen,sizeof(float));

     /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[36],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code5 get the parameter of vibration table*/
/*instruction1005 main function*/
char *code5()
{

    printf("building code 1005 packet...\n");
    printf("requesting for vibration table parameter...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1005;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code6 set up the parameter of the vibration table*/
/*set up the max acceleration of the vibration table*/
float setmaxacceleration6()
{
    float acc;
    printf("set up the max acceleration (m/s^2)\n");
    scanf("%f",&acc);
    return acc;
}

/*set up the max velocity of the vibration table*/
float setmaxvelocity6()
{
    float acc;
    printf("set up the max velocity (m/s)\n");
    scanf("%f",&acc);
    return acc;
}

/*set up the max positive displacement of the vibration table*/
float setposdisplacement6()
{
    float acc;
    printf("set up the max positive displacement (m)\n");
    scanf("%f",&acc);
    return acc;
}

/*set up the max negative displacement of the vibration table*/
float setnegdisplacement6()
{
    float acc;
    printf("set up the max negative displacement (m)\n");
    scanf("%f",&acc);
    return acc;
}

/*set up the lower limit frequency of the vibration table*/
float setlowerlimit6()
{
    float acc;
    printf("set up the lower limit frequency (Hz)\n");
    scanf("%f",&acc);
    return acc;
}

/*set up the upper limit frequency of the vibration table*/
float setupperlimit6()
{
    float acc;
    printf("set up the upper limit frequency (Hz)\n");
    scanf("%f",&acc);
    return acc;
}

/*instruction1006 main function*/
char *code6()
{

    float fmaxacc=0;
    float fmaxvel=0;
    float fmaxpos=0;
    float fmaxneg=0;
    float fmaxlow=0;
    float fmaxup=0;


    printf("building code 1006 packet...\n");
    printf("setting the vibration table parameter...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 40;
    unsigned int instr = 1006;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    fmaxacc=setmaxacceleration6();
    memcpy(&buff[12],&fmaxacc,sizeof(float));

    fmaxvel=setmaxvelocity6();
    memcpy(&buff[16],&fmaxvel,sizeof(float));

    fmaxpos=setposdisplacement6();
    memcpy(&buff[20],&fmaxpos,sizeof(float));

    fmaxneg=setnegdisplacement6();
    memcpy(&buff[24],&fmaxneg,sizeof(float));

    fmaxlow=setlowerlimit6();
    memcpy(&buff[28],&fmaxlow,sizeof(float));

    fmaxup=setupperlimit6();
    memcpy(&buff[32],&fmaxup,sizeof(float));

    
     /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[36],&check,sizeof(unsigned int));
    
    return buff;

}



/*introduction: code7 gets the number of channels of the software*/
/*set the control type*/
int setcontroltype7()
{
    int a;
    printf("control type : acceleration , velocity or displacement\n");
    scanf("%d",&a);

    if (a>0&&a<4)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setcontroltype7();
    }
}

/*set the residence value*/
float setresifrequency7()
{
    float a;
    printf("set the residence value : \n");
    scanf("%f",&a);
    return a;
}

/*set the residence peak */
float setresipeak7()
{
    float a;
    printf("set the residence peak : \n");
    scanf("%f",&a);
    return a;
}

/*set the residence time*/
float setresitime7()
{
    float a;
    printf("set the residence time : \n");
    scanf("%f",&a);
    return a;
}

/*instruction1007 main function*/
char *code7()
{
   
    int icontype=0;
    float ffreq=0;
    float fpeak=0;
    float ftime=0;

    printf("building code 1007 packet...\n");
    printf("setting quick Residence...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 32;
    unsigned int instr = 1007;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    icontype=setcontroltype7();
    memcpy(&buff[12],&icontype,sizeof(int));

    ffreq=setresifrequency7();
    memcpy(&buff[16],&ffreq,sizeof(float));

    fpeak=setresipeak7();
    memcpy(&buff[20],&fpeak,sizeof(float));

    ftime=setresitime7();
    memcpy(&buff[24],&ftime,sizeof(float));


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[28],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1008 can set quick sweep frequency*/
/*set the control type*/
int setcontroltype8()
{
    int a;
    printf("control type : acceleration , velocity or displacement\n");
    scanf("%d",&a);

    if (a>0&&a<4)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setcontroltype8();
    }
}

/*set the initial sweep frequency*/
float setstartfrequency8()
{
    float a;
    printf("set the initial sweep frequency(Hz) : \n");
    scanf("%f",&a);
    return a;
}

/*set the end sweep frequency*/
float setendfrequency8()
{
    float a;
    printf("set the end sweep frequency(Hz) : \n");
    scanf("%f",&a);
    return a;
}

/*set the sweep frequency peak*/
float setfrequencypeak8()
{
    float a;
    printf("set the sweep frequency peak : \n");
    scanf("%f",&a);
    return a;
}

/*set the sweep frquency velocity*/
float setvelocity8()
{
    float a;
    printf("set the sweep frequency velocity (Oct/Min) : \n");
    scanf("%f",&a);
    return a;
}

/*set the number of sweep frequency*/
float countnumber8()
{
    float a;
    printf("set the number of sweep frequency peak : \n");
    scanf("%d",&a);
    return a;
}


/*instruction1008 main function*/
char *code8()
{
   
    int icontype=0;
    float fstafreq=0;
    float fendfreq=0;
    float fpeak=0;
    float fvelocity=0;
    int icount=0;


    printf("building code 1008 packet...\n");
    printf("setting quick sweep frequency...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 40;
    unsigned int instr = 1008;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    icontype=setcontroltype8();
    memcpy(&buff[12],&icontype,sizeof(int));

    fstafreq=setstartfrequency8();
    memcpy(&buff[16],&fstafreq,sizeof(float));

    fendfreq=setendfrequency8();
    memcpy(&buff[20],&fendfreq,sizeof(float));

    fpeak=setfrequencypeak8();
    memcpy(&buff[24],&fpeak,sizeof(float));

    fvelocity=setvelocity8();
    memcpy(&buff[28],&fvelocity,sizeof(float));

    icount=countnumber8();
    memcpy(&buff[32],&icount,sizeof(int));


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[36],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1009 can Setting target spectrum*/
/*set the control type*/
int setcontroltype9()
{
    int a;
    printf("control type : acceleration , velocity or displacement\n");
    scanf("%d",&a);

    if (a>0&&a<4)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setcontroltype9();
    }
}

/*Starting Frequency of Target Spectrum*/
float setstartfrequency9()
{
    float a;
    printf("set the Starting Frequency of Target Spectrum : \n");
    scanf("%f",&a);
    return a;
}

/*Total number of segments of target spectrum*/
int setsegment9()
{
    int a;
    printf("set the segments : \n");
    scanf("%d",&a);
    return a;
}

/*set the end frequency of current segment*/
float setendfrequency9()
{
    float a;
    printf("set the end frequency of current segment : \n");
    scanf("%f",&a);
    return a;
}

/*set the type of current frequency type*/
int setfrequencytype9()
{
    int a;
    printf("control type : acceleration , velocity or displacement\n");
    scanf("%d",&a);

    if (a>0&&a<4)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setfrequencytype9();
    }
}

/*set the peak of current segment*/
float setuppeak9()
{
    float a;
    printf("set the peak of current segment : \n");
    scanf("%f",&a);
    return a;
}

/*instruction1009 main function*/
char *code9()
{
   
    int icontype=0;
    float fstafreq=0;
    int isegment=0;
    
    float fendfreq=0;
    int ifreqtype=0;
    float fpeak=0;


    printf("building code 1009 packet...\n");
    printf("Setting target spectrum ...\n");
    /*constants:  head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 28;
    unsigned int instr = 1009;

    isegment=setsegment9();
    /*calculate the total length of the packet*/
    length=length+12*isegment;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    icontype=setcontroltype9();
    memcpy(&buff[12],&icontype,sizeof(int));

    fstafreq=setstartfrequency9();
    memcpy(&buff[16],&fstafreq,sizeof(float));

    
    memcpy(&buff[20],&isegment,sizeof(int));

    printf("segment is %d\n\n",isegment);
    int num = 24;
    for (int i = 1; i < isegment+1; i++)
    {   
        printf("set %d segment:\n",i);

        fendfreq = setendfrequency9();
        memcpy(&buff[num],&fstafreq,sizeof(float));

        ifreqtype = setfrequencytype9();
        memcpy(&buff[num+4],&ifreqtype,sizeof(int));

        fpeak = setuppeak9();
        memcpy(&buff[num+8],&fpeak,sizeof(float));

        num=num+12;
    }


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }

    /*add the last part CHECK to the data pack*/
    memcpy(&buff[length-4],&check,sizeof(unsigned int));
    
    return buff;
}



/*code 1010 can Adding resident events*/
/*choose the way of addition*/
int addevent10()
{
    int a;
    printf("choose the way of addition events : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        addevent10();
    }
}

/*set the Frequency of residence*/
float setresifrequency10()
{
    float a;
    printf("set the Frequency of residence(Hz) : \n");
    scanf("%f",&a);
    return a;
}

/*set the level of residence*/
float setresidencelevel10()
{
    float a;
    printf("set the level of residence(percent) : \n");
    scanf("%f",&a);
    return a;
}

/*set the time of residence*/
float setresidencetime10()
{
    float a;
    printf("set the Time of residence(s) : \n");
    scanf("%f",&a);
    return a;
}

/*instruction1010 main function*/
char *code10()
{

    int iadd;
    float ffreq;
    float flevel;
    float ftime;

    printf("building code 1010 packet...\n");
    printf("Adding resident events...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 32;
    unsigned int instr = 1010;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iadd=addevent10();
    memcpy(&buff[12],&iadd,sizeof(int));

    ffreq=setresifrequency10();
    memcpy(&buff[16],&ffreq,sizeof(float));

    flevel=setresidencelevel10();
    memcpy(&buff[20],&flevel,sizeof(float));

    ftime=setresidencetime10();
    memcpy(&buff[24],&ftime,sizeof(float));


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[28],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1011 can add quick sweep frequency event*/
/*choose the way of addition*/
int addevent11()
{
    int a;
    printf("choose the way of addition events : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        addevent11();
    }
}

/*set the initial sweep frequency*/
float setstartfrequency11()
{
    float a;
    printf("set the initial sweep frequency(Hz) : \n");
    scanf("%f",&a);
    return a;
}

/*set the end sweep frequency*/
float setendfrequency11()
{
    float a;
    printf("set the end sweep frequency(Hz) : \n");
    scanf("%f",&a);
    return a;
}

/*set the sweep frequency magnitude*/
float setfrequencylevel11()
{
    float a;
    printf("set the sweep frequency level(percent) : \n");
    scanf("%f",&a);
    return a;
}

/*set the sweep frequency velocity*/
float setvelocity11()
{
    float a;
    printf("set the sweep frequency velocity (Oct/Min) : \n");
    scanf("%f",&a);
    return a;
}

/*set the number of sweep frequency*/
int setsweepnum11()
{
    int a;
    printf("set the number of sweep frequency : \n");
    scanf("%d",&a);
    return a;
}

/*instruction1011 main function*/
char *code11()
{
   
    int iadd;
    float fstafreq;
    float fendfreq;
    float flevel;
    float fvelocity;
    int icount;

    printf("building code 1011 packet...\n");
    printf("adding quick sweep frequency event...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 40;
    unsigned int instr = 1011;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iadd=addevent11();
    memcpy(&buff[12],&iadd,sizeof(int));

    fstafreq=setstartfrequency11();
    memcpy(&buff[16],&fstafreq,sizeof(float));

    fendfreq=setendfrequency11();
    memcpy(&buff[20],&fendfreq,sizeof(float));

    flevel=setfrequencylevel11();
    memcpy(&buff[24],&flevel,sizeof(float));

    fvelocity=setvelocity11();
    memcpy(&buff[28],&fvelocity,sizeof(float));

    icount=setsweepnum11();
    memcpy(&buff[32],&icount,sizeof(int));


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[36],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1012 can add pause event to sweep frequency*/
/*main function*/
char* code12()
{

    printf("building code 1012 packet...\n");
    printf("adding pause event to sweep frequency...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1012;

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));
    
    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;
}



/*code 1013 can Setting target spectrum*/
/*set the control type*/
int setcontroltype13()
{
    int a;
    printf("control type : acceleration , velocity or displacement\n");
    scanf("%d",&a);

    if (a>0&&a<4)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setcontroltype13();
    }
}

/*Total number of segments of target spectrum*/
int setupsegment13()
{
    int a;
    printf("set the segments : \n");
    scanf("%d",&a);
    return a;
}


/*current Frequency of Target Spectrum*/
float setcurrentfrequency13()
{
    float a;
    printf("set the current frequency of Target Spectrum : \n");
    scanf("%f",&a);
    return a;
}


/*set the peak of current segment*/
float setcurrentpeak13()
{
    float a;
    printf("set the peak of current segment : \n");
    scanf("%f",&a);
    return a;
}

/*instruction1013 main function*/
char *code13()
{
   
    int icontype=0;
    int isegment=0;
    float ffrequency=0;
    float fpeak=0;


    printf("building code 1013 packet...\n");
    printf("Setting target spectrum(random expriment) ...\n");
    /*constants:  head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 24;
    unsigned int instr = 1013;

    isegment=setupsegment13();
    icontype=setcontroltype13();

    /*calculate the total length of the packet*/
    length=length+8*isegment;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
   
    memcpy(&buff[12],&icontype,sizeof(int));

    memcpy(&buff[16],&isegment,sizeof(int));

    printf("segment is %d\n\n",isegment);
    int num = 20;
    for (int i = 1; i < isegment+1; i++)
    {   
        printf("set %d segment:\n",i);

        ffrequency = setcurrentfrequency13();
        memcpy(&buff[num],&ffrequency,sizeof(float));

        fpeak = setcurrentpeak13();
        memcpy(&buff[num+4],&fpeak,sizeof(float));

        num=num+8;
    }


    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }

    /*add the last part CHECK to the data pack*/
    memcpy(&buff[length-4],&check,sizeof(unsigned int));
    
    return buff;
}



/*code 1014 can add quick sweep frequency event in random experiment*/
/*choose the way of addition*/
int addevent14()
{
    int a;
    printf("choose the way of addition events : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        addevent14();
    }
}


/*set the sweep frequency level*/
float setfrequencylevel14()
{
    float a;
    printf("set the sweep frequency level(percent) : \n");
    scanf("%f",&a);
    return a;
}

/*set the sweep frequency time*/
float setsweeptime14()
{
    float a;
    printf("set the sweep frequency time(s) : \n");
    scanf("%f",&a);
    return a;
}

/*instruction1014 main function*/
char *code14()
{
   
    int iadd;
    float flevel;
    float ftime;

    printf("building code 1014 packet...\n");
    printf("adding level event...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 28;
    unsigned int instr = 1014;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iadd=addevent14();
    memcpy(&buff[12],&iadd,sizeof(int));

    flevel=setfrequencylevel14();
    memcpy(&buff[16],&flevel,sizeof(float));

    ftime=setsweeptime14();
    memcpy(&buff[20],&ftime,sizeof(float));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[24],&check,sizeof(unsigned int));
    
    return buff;

}


/*code 1015 can add set target spectrum in impact test*/
/*choose the Pulse Waveform of Global Target Spectrum*/
int setpulsetype15()
{
    int a;
    printf("choose the Pulse Waveform of Global Target Spectrum : \n");
    scanf("%d",&a);

    if (a>0&&a<7)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setpulsetype15();
    }
}


/*set the pulse amplitude*/
float setpulselevel15()
{
    float a;
    printf("set the pulse amplitude(m/s^2) : \n");
    scanf("%f",&a);
    return a;
}

/*set the pulse width*/
float setpulsewidth15()
{
    float a;
    printf("set the pulse width(s) : \n");
    scanf("%f",&a);
    return a;
}

/*Left slope pulse width in Trapezoidal wave */
float setleftwidth15(int type)
{
    if (type == 4)
    {
        float a;
        printf("set the Left slope pulse width(s) : \n");
        scanf("%f",&a);
        return a;
    }
    else
    {
        return 0;
    }    
}

/*Right slope pulse width in Trapezoidal wave */
float setrightwidth15(int type)
{
    if (type == 4)
    {
        float a;
        printf("set Right slope pulse width width(s) : \n");
        scanf("%f",&a);
        return a;
    }
    else
    {
        return 0;
    }    
}

/*set the displacement type*/
int setdisplacementtype15()
{
    int a;
    printf("choose the displacement type : Bilateral displacement or Unilateral displacement\n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setdisplacementtype15();
    }
}

/*set the compensation type*/
int setcompensatetype15(int type)
{
    if (type==1)
    {
        printf("front and rear compensation is selected.\n");
        return 3;
    }
    
    else
    {
        int a;
        printf("choose the compensation type : \n");
        scanf("%d",&a);

        if (a>0&&a<4)
        {
            return a;
        }
        else
        {
            printf("invalid input\n");
           setcompensatetype15(type);
        }
    }  
    
}

/*choose type of compensation pulse*/
int setcompensatepulse15()
{
    int a;
    printf("choose the compensation pulse type : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setcompensatepulse15();
    }
}

/*set front compensation value*/
float setfrontcompensate15(int type)
{
    if (type == 1 || type == 3)
    {
        float a;
        printf("set the front compensation value(percent) : \n");
        scanf("%f",&a);
        return a;
    }
    else
    {
        return 0;
    }    
}

/*set back compensation value*/
float setbackcompensate15(int type)
{
    if (type == 1 || type == 3)
    {
        float a;
        printf("set the back compensation value(percent) : \n");
        scanf("%f",&a);
        return a;
    }
    else
    {
        return 0;
    }    
}

/*instruction1015 main function*/
char *code15()
{
   
    int iwavetype=0;
    float fpulselevel=0;
    float fpulsewidth=0;
    float fleftwid=0;
    float frightwid=0;

    int idistype=0;
    int icompentype=0;
    int icompenpulse=0;
    float ffrontcompen=0;
    float fbackcompen=0;
    
    printf("building code 1015 packet...\n");
    printf("setting target spectrum(impact test)...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 56;
    unsigned int instr = 1015;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iwavetype=setpulsetype15();
    memcpy(&buff[12],&iwavetype,sizeof(int));

    fpulselevel=setpulselevel15();
    memcpy(&buff[16],&fpulselevel,sizeof(float));

    fpulsewidth=setpulsewidth15();
    memcpy(&buff[20],&fpulsewidth,sizeof(float));

    fleftwid=setleftwidth15(iwavetype);
    memcpy(&buff[24],&fleftwid,sizeof(float));

    frightwid=setrightwidth15(iwavetype);
    memcpy(&buff[28],&frightwid,sizeof(float));

    idistype=setdisplacementtype15();
    memcpy(&buff[32],&idistype,sizeof(int));

    icompentype=setcompensatetype15(idistype);
    memcpy(&buff[36],&icompentype,sizeof(int));

    icompenpulse=setcompensatepulse15();
    memcpy(&buff[40],&icompenpulse,sizeof(int));

    ffrontcompen=setfrontcompensate15(icompentype);
    memcpy(&buff[44],&ffrontcompen,sizeof(int));

    fbackcompen=setbackcompensate15(icompentype);
    memcpy(&buff[48],&fbackcompen,sizeof(int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }

    /*add the last part CHECK to the data pack*/
    memcpy(&buff[52],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1016 can add quick sweep frequency event in pulse test*/
/*choose the way of addition*/
int addevent16()
{
    int a;
    printf("choose the way of addition events : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        addevent16();
    }
}

/*set the number of pulse*/
float setpulselevel16()
{
    float a;
    printf("set the pulse level(percent) : \n");
    scanf("%f",&a);
    return a;
}

/*set the number of pulse*/
int setpulsenumber16()
{
    int a;
    printf("set the number of pulse : \n");
    scanf("%d",&a);
    return a;
}

/*choose the direction of pulse*/
int setpulsedirection16()
{
    int a;
    printf("choose the direction of pulse : \n");
    scanf("%d",&a);

    if (a>0&&a<3)
    {
        return a;
    }
    else
    {
        printf("invalid input\n");
        setpulsedirection16();
    }
}

/*instructioon1016 main function*/
char *code16()
{
   
    int iadd;
    float flevel;
    int ipulsecount;
    int idirection;

    printf("building code 1016 packet...\n");
    printf("adding level event(pulse test)...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 32;
    unsigned int instr = 1016;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    /*build up the rest part of the packet*/
    iadd=addevent16();
    memcpy(&buff[12],&iadd,sizeof(int));

    flevel=setpulselevel16();
    memcpy(&buff[16],&flevel,sizeof(int));

    ipulsecount=setpulsenumber16();
    memcpy(&buff[20],&ipulsecount,sizeof(int));

    idirection=setpulsedirection16();
    memcpy(&buff[24],&idirection,sizeof(int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[28],&check,sizeof(unsigned int));
    
    return buff;

}


/*code1017 function can control the software.*/
int setcontroltype17()
{
    int type;
    printf("please choose the status of the software\n");
    printf("1=start,2=interrupt,3=pause,4=continue,5=next event\n");
    printf("6=magnitude increase,7=magnitude decrease\n");

    scanf("%d",&type);
    if (type > 0 && type < 8)
    {
        return type;
    }
    else
    {
        printf("invalid input! \n");
        setcontroltype17();
    }
    
    

}

/*instruction1017 main function*/
char *code17()
{
    int ichannel;

    printf("building code 1017 packet...\n");
    printf("controlling the software...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 20;
    unsigned int instr = 1017;

    /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);
    
    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));

    ichannel=setcontroltype17();
    memcpy(&buff[12],&ichannel,sizeof( int));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[16],&check,sizeof(unsigned int));
    
    return buff;

}



/*code1018 function can gets the Running status information.*/
/*instruction1018 main function*/
char* code18()
{

    printf("building code 1001 packet...\n");
    printf("requesting for the status of software\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1018;

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));
    
    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;

}



/*code19 can get the running signal*/
/*instruction1019 main function*/
char* code19()
{
    printf("building code 1019 packet...\n");
    printf("acquiring for the experiment signal...\n");
    /*constants: length,instruction*/
    unsigned int head = 305419896;
    unsigned int length=16;
    unsigned int instr = 1019;
    
    char sinput[15];

    printf("please enter the signal : \n");
    scanf("%s",sinput);
    length=length+strlen(sinput);

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int)); 

    memcpy(&buff[12],sinput,strlen(sinput)*sizeof(char));

    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12+strlen(sinput)],&check,sizeof(unsigned int));
    
    return buff;

}



/*code 1021 can exist the current experiment*/
/*instruction1021 main function*/
char* code21()
{

    printf("building code 1021 packet...\n");
    printf("existing the current experiment...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1021;

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));
    
    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;


}



/*code 1022 can exist the software*/
/*instruction1022 main function*/
char* code22()
{

    printf("building code 1021 packet...\n");
    printf("existing the current experiment...\n");
    /*constants: length, head , instruction*/
    unsigned int head = 305419896;
    unsigned int length = 16;
    unsigned int instr = 1022;

     /*create a pointer which will be returned to send.c*/
    char * buff=NULL;
    buff=(char*)malloc(sizeof(char)*length);

    /*build up the buffer*/
    memcpy(&buff[0],&head,sizeof(unsigned int));
    memcpy(&buff[4],&length,sizeof(unsigned int));
    memcpy(&buff[8],&instr,sizeof(unsigned int));
    
    /*a special way to calculate the final check code*/
    unsigned int check = 0;
    for(int i=0; i<length-4;i++)
    {
        check=check+(unsigned int)buff[i];
    }


    /*add the last part CHECK to the data pack*/
    memcpy(&buff[12],&check,sizeof(unsigned int));
    
    return buff;

}

/*end*/