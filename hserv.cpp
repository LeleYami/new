#include "TFile.h"
#include "TServerSocket.h"
#include "TSocket.h"
#include "TMessage.h"
#include "TMonitor.h"
#include "Sclass.h"
#include "TROOT.h"

void hserv() 
{
   	time_t nowTime1;
	time(&nowTime1);
  	printf("At now time is: %s\n",ctime(&nowTime1));

   	gROOT->ProcessLine(".L libSclass.so");
   	TServerSocket *ss = new TServerSocket(51400, kTRUE);

   	// Accept a connection and return a full-duplex communication socket.
   	TSocket *s[50];
	int i=0;
 	for(i;i<=1;i++)
		s[i] = ss->Accept();
   	//TSocket *s1 = ss->Accept();

   	//tell the clients to start
	for(i=0;i<=1;i++){
   		char str[10];
   		sprintf(str,"%d",i);
   		s[i]->Send(str);
	}
  	//Close the server socket
  	ss->Close();

   	TMonitor *mon=new TMonitor;
   	for(i=0;i<=0;i++)
   		mon->Add(s[i]);
   	//mon->Add(s1);
   
   	while (1) {
       		TMessage *mess;
       		TSocket *s;
 
       		s = mon->Select();
   
       		s->Recv(mess);
       
       		if(mess->What() == kMESS_STRING){
         		 char str[64];
         		 mess->ReadString(str,64);
          		 printf("%s\n", str);
			 if(strcmp(str,"end")==0)
				mon->Remove(s);
			 if (mon->GetActive() == 0) {
           		 	printf("No more active clients... stopping\n");
            			break;
         		 }
	        }else if (mess->What() == kMESS_OBJECT){
          		Sclass* m= (Sclass*)mess->ReadObject(mess->GetClass());
          		m->Print();
       		}

       		delete mess;
	}


       	// Close the socket.
	for(i=0;i<=0;i++)
       		s[i]->Close();
       	time_t nowTime2;
       	time(&nowTime2);
       	printf("At now time is: %s\n",ctime(&nowTime2));
}
int main(int argc, char **argv){
	hserv();
}
