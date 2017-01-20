#include "Sclass.h"
#include "TFile.h"
#include "TSocket.h"
#include "TMessage.h"
#include "stdlib.h"
#include "stdio.h"

void hclient(char *argv,TSocket *sock)
{
   	// Open connection to server

   	//wait till we get the start message
   	char str[32];
   	sock->Recv(str,32);
   	int idx;
	idx=atoi(str);	
	printf("%d\n",idx);
   	if (idx >= 0){
		TMessage mess(kMESS_OBJECT);
   		//open the file and get the object
   		if(strcmp(argv,"test1.root") == 0){
      			TFile f1("test1.root");
      			Sclass* obj1=dynamic_cast<Sclass*>(f1.Get("anObject1"));
      			//create TMessage to save the object
      			mess.Reset();
      			mess.WriteObject(obj1);
      			obj1->Print();

      			// send message
      			sock->Send(mess);
    		}else if(strcmp(argv,"test2.root") == 0){
      			TFile f2("test2.root");
      			Sclass* obj2=dynamic_cast<Sclass*>(f2.Get("anObject2"));
      			//create TMessage to save the object 
      			mess.Reset();
      			mess.WriteObject(obj2);
      			obj2->Print();

      			// send message
      			sock->Send(mess);
   		}else if(strcmp(argv,"test3.root") == 0){
      			TFile f3("test3.root");
      			Sclass* obj3=dynamic_cast<Sclass*>(f3.Get("anObject3"));
      			//create TMessage to save the object 
      			mess.Reset();
      			mess.WriteObject(obj3);
      			obj3->Print();

      // send message
      			sock->Send(mess);
   	}else{
      		return;
      		printf("the input is wrong\n");    
   	}
   }
  // Close the socket
  // sock->Close();
}

int main(int argc, char **argv){
  	TSocket *sock = new TSocket("localhost", 51400);
        for(int i=1;i<argc;i++){
	     //printf("%s=%s\n",*(argv+i),argv[i]);
             hclient(argv[i],sock);
        }
	sock->Send("end");
	sock->Close();
        return 0;
}
