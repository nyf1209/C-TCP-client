/*tcp.c is the main function of the program, the function is to build up
a connection to the server and communicate with the remote server by using 
packet with different sizes*/

/*the file send.c use the input from the local user to build up 
the buffer and send the server.*/
/*the file receive.c can receive the buffer from the client analyze the
data in the packet*/
#include <pthread.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include "send.c"
#include "receive.c"


typedef struct 
{
   int  signal; 
   int  sockfd;
   int  sendlen;
   char * buffpointer; 

}writebuff;

typedef struct 
{
   int  input19; 
   int  sockfd; 

}readbuff;

/*port number of server and the size of buffer*/
/*the port number of the server is fixed*/
#define PORT 5555
#define MAX 30000 



/*print out the error when it happens*/
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

/*send thread*/
void *sended(void *threadid)
{
    writebuff * senddata = (writebuff*) threadid;
    int i;
    
    
    while (1)
    {
        
       /*sending buffer*/
        if (senddata->signal==1)
        {
        /*sending buffer*/
            i = write(senddata->sockfd,senddata->buffpointer,senddata->sendlen);
            senddata->signal=0;
            if(i<0)
            {
                DieWithError("writing error to socket\n");
                free(senddata->buffpointer);
                break;
            }

            /*free the dynamic memory after the buffer sent to the server*/
            free(senddata->buffpointer);
            
        }
        sleep(1);
    }
}



void *receded(void *threadid)
{
    readbuff * recedata = (readbuff*) threadid;
    int sockfd=0;
    sockfd=recedata->sockfd;

    while (1)
    {
    
       
        int receivelength=0;
        int i =0;
         /*create a temporary local string to read the length of the packet*/
        char recvbuf[MAX];
        int temporary[MAX];
        bzero(temporary,MAX);

         
        i = read(sockfd,temporary,MAX);
        
        if (i<0)
        {
            printf("connection closed\n");
            exit(1);
        }
        
        receivelength=temporary[1];    
        printf("packet length is %d \n",receivelength);
        
       
        char* finalbuffer=NULL;
        finalbuffer=(char*)malloc(receivelength*sizeof(char));
        bzero(finalbuffer,receivelength);

        memcpy(&finalbuffer[0],&temporary,i*sizeof(char));
        
        int k=0;
        /*use read function for more than once becasue that the packet received from
        server is so long that the packet will be seperated into parts*/
       
        for (int j = i; j < receivelength; j=j+k)
                {
                    bzero(recvbuf,MAX);
                    k = read(sockfd,recvbuf,MAX);
                    if(k<0)
                    {
                        DieWithError("reading error from socket\n");
                        break;
                    }

                    memcpy(&finalbuffer[j],&recvbuf,k*sizeof(char));     
             
                }
        
                int input19= recedata->input19;
                /*analyzing the data back from the server and 
                print out the result of the experiment*/
                printf("packet received\n\n");
                receive(finalbuffer,input19); 
                free(finalbuffer);
                
          
       
        
    }
    sleep(0.5);
        

}



int main(){
    int num;

    
/*initialize and scan the IP address */
    char  IPaddr[100]="\0";
    printf("please enter the server address:\n");
    scanf("%s",IPaddr);



/*create the socket*/
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0)
    {
        DieWithError("socket failed\n");
    }
    else{
        printf("socket success\n");
    }

    

/*create and initialize the server address */
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
/*check the avaliablity of address*/
    if (inet_pton(AF_INET, IPaddr, &server_addr.sin_addr) <= 0)
    {
        fprintf(stderr,"adddress error\n");
        exit(1);
    }
   
/*try to connect to the server*/
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        DieWithError("connect failed");
    }
    fprintf(stdout, "connect successfully\n");

    writebuff senddata;
    pthread_t sendthread,recethread;
    
    senddata.sockfd=sockfd;
    senddata.buffpointer=NULL;
    senddata.sendlen=0;
    senddata.signal=0;

    readbuff  recedata;
    recedata.sockfd=sockfd;
    recedata.input19=0;
    
    int rc;

    wait(&rc);
    
    rc=pthread_create(&sendthread,NULL,sended,(void *)&senddata);
    
    if (rc)
    { 

    printf("ERROR; return code from pthread_create() is %d\n", rc); 
    exit(-1); 
    
    }
              
            
    rc=pthread_create(&recethread,NULL,receded,(void *)&recedata);

    if (rc)
    {

    printf("ERROR; return code from pthread_create() is %d\n", rc); 
    exit(-1); 

    }
/*processing the data*/
/*exptype record the type of the experiment*/
/*input19 record the length of order in a special instruction in send1019.c*/
    int i;     
    int exptype=0;
    int input19=0;


    /*recesi determine which type of instruction should be received*/
    /*sendlen record the length of the packet sent to the server*/
    int receivesignal;
    int sendlen;
    int new;
           
    while(1){    

        /*prepare the sending buffer*/
        char * sendbuf=NULL;
        sendbuf = sending(exptype);      
        
        /*get the packet length*/
        memcpy(&sendlen,&sendbuf[4],sizeof(unsigned int));
        printf("send length is %d\n",sendlen);
        
        /*get the instruction code*/
        memcpy(&receivesignal,&sendbuf[8],sizeof(unsigned int));
        printf("code %d is sending...\n\n", receivesignal);

        /*check if the experiment is a new one or alrady existing in local*/
        memcpy(&new,&sendbuf[12],sizeof(int));

        if (receivesignal==1000 && new == 1)
        {
            memcpy(&exptype,&sendbuf[16],sizeof( int));
        }

        if (receivesignal==1019)
        {
            input19=sendlen-16;
            recedata.input19=input19;
        }
        
        senddata.buffpointer=sendbuf;
        senddata.sendlen=sendlen;
        senddata.signal=1;
        
    }
    
    /*closed the connection*/
    close(sockfd);
    printf("connection stop\n");
    exit(0);
    /*end */
}


