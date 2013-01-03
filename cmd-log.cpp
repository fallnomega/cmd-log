#include <iostream>
#include<fstream>
#include <ctime>
#include "agent.h"

using namespace std;

int main()
{
  cout << "Command Log Application\n";
  
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  cout << "Current local time and date: " << asctime (timeinfo) ;


  agent* head = 0;
  agent* loghead = 0;
  logagent* cmdlog = 0;

  head=head->restoreList();
  cmdlog=cmdlog->LrestoreList();
  while(true)
  {
    int choice = agent::menu();
    if(choice==1) 
    {
      while(true)
      {
        head=head->addAgent();
        agent::header();  
        head->coutList();
        cout << "\n\nContinue to add more Agents to the list[y/n]?\n>";
        char aanswer= agent::getYesNo();
        if(aanswer=='n') break;
      }
    }
    if(choice==2) 
    {

      agent temp;
      temp = *head;
      head=head->deleteNode(head, temp);
    }
    if(choice==3)
    {
      agent::header();  
      head->coutList();
    }
    if(choice==4)
    {
      head=head->sortAgent();
    }
    if(choice ==5)
    {
      break;
    }

    if(choice==6)
    {
      loghead=head->agent::newEntry();
      cmdlog=cmdlog->logagent::logNewEntry();
      cmdlog->logagent::LsaveList();
    }
    if(choice==7)
    {
      logagent temp;
      temp = *cmdlog;
      cmdlog=cmdlog->LdeleteNode(cmdlog, temp);
    }
    if(choice==8)
    {
      cmdlog->LcoutList();
    }
    if(choice==666) 
    {
      agent *temphead = 0;   
      temphead=temphead->getText();
      head=head->mergeLists(temphead);
    }
    cout << endl << endl;
  }
  head->saveList();
  head->clearList();
  cmdlog->logagent::LsaveList();
  cmdlog->LclearList();

  cout << "\n\nHave a nice day" << endl ;

  ifstream fin;
  char timeStamp[30];
  fin.open("timestamp.txt");

  fin.get(timeStamp,30);
  
  cout << "time stamp = " << timeStamp << endl;
  fin.close();


  cout << endl;
}