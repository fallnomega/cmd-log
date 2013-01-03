#include <iostream>
#include<fstream>
#include <ctime>
#include <iomanip>
#include "agent.h"


using namespace std;
/////////////
//functions//
/////////////
//MAIN MENU
int agent::menu()
{
  int choice;
  cout << "Menu\n----\n\n";
  cout << "[1] add agent to agent list\n[2] delete agent from agent list\n[3] list current agents\n"
    << "[4] sort agent list\n[5] quit application\n[6] add entry to command log\n"
    << "[7] delete command log entry\n[8] list command log entries\n>>";
  cin >> choice;
  cin.ignore(1000,10);
  return choice;
}
//YAY or NAY
char agent::getYesNo()
{
   char yesNo;
   cin >> yesNo;
   cin.ignore(1000,10);
   return yesNo;
}
//HEADER FOR LISTING AGENTS
void agent::header()
{
  cout << "\n\n//////////////////\n//Agent Listing//\n//////////////////\n\n-----------------------------------------------\n"
    << "     Name" << setw(15) <<"      UUID\n" << setw(10) 
    << "-----------------------------------------------\n";
}
//ADD AGENT TO THE LIST
agent* agent::addAgent()
{
  agent* head = this;
  agent* newAgent = new agent;
  cout << "To add new entry, type the name and uuid in the following format:\n"
    << "Last Name, First Name: ";
  cin.get(newAgent->name, 40);
  cout << "\nUUID: ";
  cin>> newAgent->uuid;
  cin.ignore(1000,10);
  newAgent->next=head;
  head=newAgent;
  return head;
}
//INSERT AGENT INTO LIST
agent* agent::insert( agent* head) //insertion
{
  agent* p, *prev;
  agent* t = this;
  for (p=head, prev=0; p; prev=p, p=p->next);
  t->next = p; // p is zero
  if (prev) // pointer to last node
    prev->next = t;
  else // empty list, new node is 1st node
    head = t;
  return head;
}
//RESTORE LIST FROM cmdLog.dat
agent* agent::restoreList()
{

    fstream fin;
    fin.open("agent.dat",ios::binary|ios::in);
    if(!fin) return this;
    
    int nCount;
    fin.read((char*)&nCount, sizeof(int));
    agent* newHead = this;
    for(int i = 0; i<nCount;i++)
    {
      agent* newAgent = new agent;
      fin.read((char*) newAgent,sizeof(agent));
      newAgent->next=newHead;
      newHead = newAgent->insert(newHead);
      
    }

    fin.close();

    return newHead;
    
}//restore from agent.dat 1
//SAVE TO agent.dat
void agent::saveList()
{
  agent* head = this;
  int nCount = 0;
  for(agent* p=head;p;p=p->next) nCount++;

  ofstream fout;
  fout.open("agent.dat",ios::out|ios::binary);
    
  //process list to file   
  fout.write((char*)&nCount, sizeof(int));
  for(agent* p=head;p;p=p->next)
  {
    fout.write((char*)p, sizeof(agent));
  }
  fout.close();
}
//PRINT LISTING
void agent::coutList()
{
  agent* head=this;
    int nList = 1;
  for(agent* p=head;p;p=p->next)
  {
    if(nList<10) cout << "00";
    if((nList<100)&&(nList>=10)) cout << "0";
    cout << nList << ".) "; 
      cout << setw(25)<<left << p->uuid  << "\n      "<< 
      p->name << " " << p->ext << " " << p->center << " "<< p->department << " "<< p->position << " "<< p->om << " "<< p->ttv << endl;
    nList++;
  }
}
//PULLS NAMES FROM NAMES.TXT USING 
//HIDDEN OPTION 6
agent* agent::getText()
{
  agent* textNames=this;
  ifstream fin;
  fin.open("names.txt");
  if(!fin.good())
  {
    cout <<  "I/O error! No file to read from";
    return textNames;
  }
  else
  {
    while(fin.good())
    {
      agent* aTextNames = new agent;
      fin.get(aTextNames->name, 40);
      fin.ignore(1000,10);
      fin.get(aTextNames->uuid, 7);
      fin.ignore(1000,10);
      fin >> aTextNames->ext;
      fin.ignore(1000,10);
      fin.get(aTextNames->center, 12);
      fin.ignore(1000,10);
      fin.get(aTextNames->department, 10);
      fin.ignore(1000,10);
      fin.get(aTextNames->position, 10);
      fin.ignore(1000,10);
      fin.get(aTextNames->om, 20);
      fin.ignore(1000,10);
      fin >> aTextNames->ttv;
      fin.ignore(1000,10);
      aTextNames->next = textNames;
      textNames = aTextNames->insert(textNames);

    }
  } 
 textNames->coutList();
  return textNames;
}
//DELETE LIST
void agent::clearList()//clear list
{
  cout << "Deleting agent list from memory" << endl;
  agent* head = this;
  int i = 1;
  while(head)
  {
    agent* next = head->next;
    delete head;
    head=next;
    i++;
  }//while
  cout << "Done with deletion of agent list\n" << endl;
}
//MERGE LISTS
agent* agent::mergeLists(agent* temp)
{
  agent* head1 = this; // one list...
  agent* head2 = temp; // ...another list
        agent::header();  
      head2->coutList();
  //... // add nodes to both lists, and sort them
  agent* head3 = 0; // combined list
  agent* tail3 = 0; // for temporary use
  if (!head2) // SPECIAL CASE: 1st list initially empty
    head3 = head1; // finished!
  else if (!head1) // SPECIAL CASE: 2nd list initially empty
    head3 = head2; // finished!
  else while(1) // GENERAL CASE: combine node-by-node
  {
    if (!head1) // 1st list exhausted first
    {
      tail3->next = head2; //...attach rest of 1st list
      break; //...and we're finished
    }
    if (!head2) // 2nd list exhausted first
    {
      tail3->next = head1; //...attach rest of 2nd list
      break; //...and we're finished
    }
    // both lists still have nodes
    agent* t = head1; // assume take from 1st list

    if (compare(head1, head2) < 0) // check this assumption
      head1 = head1->next; // got it right! remove from 1st list
    else // assumed wrong!
    {
      t = head2; // take from 2nd list instead
      head2 = head2->next; // remove from 2nd list
    }
    // insert at end of combined list (queue w/tail method)
    t->next = 0;
    if (tail3)
      tail3->next = t;
    else
      head3 = t;
    tail3 = t;
  }
  return head3;
}
//COMPARE
int agent::compare (const agent* a, const agent* b)
{
  char* pa = (char*)a->name; // required casting
  char* pb = (char*)b->name; // required casting
  char va = tolower(*pa); // the value of a
  char vb = tolower(*pb); // the value of b
  if (va < vb)
    return -1; // or va - vb
  else if (va > vb)
    return 1; // or va - vb
  else
    return 0; // or va - vb
}
//TO LOWER
void agent::toLower(char str[])
{
  for(int i=0;str[i]!=0;i++)
  {
    str[i] = tolower(str[i]);
  }
}
//DELETE FROM LIST
agent* agent::deleteNode(agent* h, agent& t) // header 
{ 
  int nList = 1;
  for(agent* p=h;p;p=p->next)
  {
    cout <<   nList << ".) " << setw(5) << p->uuid <<setw(7) << " "<< p->name
      << endl;
    nList++;
  }//for
  cout << "Which agent would you like to delete?\n>"; 
  int choice;
  cin >> choice;
  cin.ignore(1000,10);
  while(true)
  {
    int nCount=1;
    agent* prev;
    int fCount = 1;
    for(agent* p = h;p;p=p->next) fCount++;
    if((fCount-1)==choice)
    {
      agent* temp = h;
      for(h,prev=0;h;prev=h,h=h->next)
      {
        if(h->next==NULL)
        {
          h=prev;
          h->next = 0;
        }//if
      }//for
      
      return temp;
    }//if
    else if(choice==1)
    {
      agent *temp;
      temp = h;
      h = h->next;
      delete(temp);
      break; 
    }//if
    agent* p;
    for(p=h,prev=0;p;prev=p,p=p->next,nCount++)
    {
      agent* temp = p;
      if(nCount==choice)
      { 
          agent* temp;
          temp = p;
          p=prev;
          p->next=p->next->next;
          delete (temp);
          break; 
      }//if
    }//for
    break;
  }//while   
  return h;
}//delete node
//SORT NAMES
agent* agent::sortAgent()
{
  agent* newHead=0; //a new empty list
  agent* oldHead=this; // the original list
  while(oldHead)
  {
    agent* t = oldHead; // get node from old list
    oldHead= oldHead->next; //remove node from old list       
    newHead=t->compareDescr(newHead);//compare and insert
  }
  return newHead;
}
//COMPARE AND INSERT
agent* agent::compareDescr(agent* h)
{
  agent* p, *prev;
  agent* t =this;
  for (p=h, prev=0; p; prev=p, p=p->next)
    if (t->compareDCmp(p) < 0) // if "t" precedes "p"...
      break; // "t" goes between "prev" and "p"
  t->next = p; // "t" inserted before "p"
  if (prev) // "t" inserted after "prev"
    prev->next = t;
  else // "t" added to front of list
    h = t;
  return h;
}
//COMPARE AND INSERT
char agent::compareDCmp(const agent* src)
{
  //handle ties here
  agent* dst = this;
  agent tempSRC =*src;
  agent tempDST = *this;
  toLower(tempSRC.name);
  toLower(tempDST.name);
 return myStricmp(dst->name,src->name);
}
int agent::myStricmp(const char* dst, const char* src)
{
  int f, l;
  do
  {
    if (((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z')) f -= 'A' - 'a';
    if (((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z')) l -= 'A' - 'a';
  } while (f && (f == l));
  return(f - l);
}
//ADD NEW CMD LOG ENTRY
agent* agent::newEntry()
{
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );


  agent* head = this;
  cout << "UUID of the agent to add to the log: ";
  char uuid [7];
  cin.get(uuid, 7);
  cin.ignore(1000,10);
  agent* p = head;
  while(true)
  {
    if(myStricmp(uuid,p->uuid)==0)
    {
        char name[40];
          strcpy(name,p->name);
        char uuid[7];
          strcpy(uuid,p->uuid);
        int ext;
          ext = p->ext;
        char center[12];
          strcpy(center,p->center);
        char department[10];
          strcpy(department,p->department);
        char position[10];
          strcpy(position,p->position);
        char om[20];
          strcpy(om,p->om);
        int ttv;
          ttv = p->ttv;

        ofstream fout;
        fout.open("tempLog.txt");
        fout << asctime (timeinfo);
        fout << name << endl;
        fout << uuid << endl;
        fout << ext << endl;
        fout << center << endl;
        fout << department << endl;
        fout << position << endl;
        fout << om << endl;
        fout << ttv << endl;
        fout.close();
        return p;
        break;
    } 
    else p=p->next;
  }
  return 0;
}
//CONVERT FROM AGENT NODE TO LOGAGENT NODE
//AND GET NEW ENTRY FOR CMDLOG LIST
logagent* logagent::logNewEntry()
{

  fstream fin, fout;
  fin.open("tempLog.txt");
  
  logagent* cmdlog = this;
  logagent* temp = new logagent;
  fin.get(temp->timeStamp, 30);
  fin.ignore(1000,10);
  fin.get(temp->name,40);
  fin.ignore(1000,10);
  fin.get(temp->uuid, 7);
    fin.ignore(1000,10);
  fin >> temp->ext;
    fin.ignore(1000,10);
  fin.get(temp->center, 12);
    fin.ignore(1000,10);
  fin.get(temp->department, 10);
    fin.ignore(1000,10);
  fin.get(temp->position, 10);
    fin.ignore(1000,10);
  fin.get(temp->om, 20);
    fin.ignore(1000,10);
  fin >>temp->ttv;
    fin.ignore(1000,10);
  cout << "Type out notes > ";
    cin.get(temp->notes, 500);
    cin.ignore(1000,10);
    //getline(cin, temp->notes);
  //temp->next = cmdlog;
  //cmdlog = temp;
  cmdlog=push_back(temp, cmdlog);
  return cmdlog;
}
//SAVE TO CMDLOG.DAT
void logagent::LsaveList()
{
  cout << "\nSaving to cmdlog.dat\n";
  logagent* head = this;
  int nCount = 0;
  for(logagent* p=head;p;p=p->next) nCount++;

  ofstream fout;
  fout.open("cmdlog.dat",ios::binary|ios::out);

  //process list to file   
  fout.write((char*)&nCount, sizeof(int));
  for(logagent* p=head;p;p=p->next)
  {
    fout.write((char*)p, sizeof(logagent));
  }
  fout.close();
  fout.open("timestamp.txt");
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  fout << asctime (timeinfo) ;
  fout.close();

  cout << "Save completed\n\n" << endl;
}
//RESTORE FROM CMDLOG.DAT
logagent* logagent::LrestoreList()
{

    fstream fin;
    fin.open("cmdlog.dat",ios::binary|ios::in);
    if(!fin) return this;
   
    int nCount;
    fin.read((char*)&nCount, sizeof(int));
    logagent* newHead = this;
    for(int i = 0; i<nCount;i++)
    {
      logagent* newAgent = new logagent;
      fin.read((char*) newAgent,sizeof(logagent));

      newAgent->next=newHead;
      newHead = newAgent;
    }

    fin.close();

    return newHead;
    
}//restore from cmdlog.dat 1
//QUEUE ADD TO THE LIST
logagent* logagent::push_back(logagent* t, logagent* h) // header 
{ 
  logagent* p, *prev; 
  for (p=h, prev=0; p; prev=p, p=p->next); 
  t->next = p; // p is zero 
  if (prev) // pointer to last node 
    prev->next = t; 
  else // empty list -- new node is 1st node 
    h = t; 
  return h; 
}
//CLEAR CMD LOG LIST FROM MEMORY
void logagent::LclearList()//clear list
{
  cout << "Deleting command log from memory" << endl;
  logagent* head = this;
  int i = 1;
  while(head)
  {
    logagent* next = head->next;
    delete head;
    head=next;
    i++;
  }//while
  cout << "DONE WITH DELETE CMD LOG " << endl;
}
//LIST COMMAND LOG ENTRIES
void logagent::LcoutList()
{
  logagent* head = this;
  int nCount = 1;
  for(logagent* p = head;p;p=p->next)
  {
    cout << nCount << " .) " << p->timeStamp <<" Name: " << p->name << " | UUID: "
      << p->uuid << "\nNotes: = " << p->notes << endl;
    nCount++;
  }

}
/////////////////////
//TESTING FUNCTIONS//
/////////////////////

void agent::testCout()
{
//  agent* head = this;
//  
//  char name[40];
//    strcpy(name,head->name);
//  char uuid[7];
//    strcpy(uuid,head->uuid);
//  int ext;
//    ext = head->ext;
//  char center[12];
//    strcpy(center,head->center);
//  char department[10];
//    strcpy(department,head->department);
//  char position[10];
//    strcpy(position,head->position);
//  char om[20];
//    strcpy(om,head->om);
//  int ttv;
//    ttv = head->ttv;
//
//  ofstream fout;
//  fout.open("tempLog.txt");
//  fout << name << endl;
//  fout << uuid << endl;
//  fout << ext << endl;
//  fout << center << endl;
//  fout << department << endl;
//  fout << position << endl;
//  fout << om << endl;
//  fout << ttv << endl;
//  fout << "NOTES GO HERE" << endl;
//  fout.close();
//  
}

void logagent::AtestCout()
{
  logagent* head = this;
  for(logagent* p = head;p;p=p->next)
  {
    cout << "AtestCout NAME for head = " << p->name;
    //cout << "\nAtestCout ext for head = " << p->ext;
    //cout << "\nAtestCout center for head = " << p->center; 
    //cout << "\nAtestCout deparment for head = " << p->department;
    //cout << "\nAtestCout position for head = " << p->position;
    //cout << "\nAtestCout om for head = " << p->om;
    //cout << "\nAtestCout ttv for head = " << p->ttv;
    cout << "\n AtestCout notes for head = " << p->notes;
    cout << endl;
  }
}


//DELETE FROM LIST
logagent* logagent::LdeleteNode(logagent* h, logagent& t) // header 
{ 
  int nList = 1;
  for(logagent* p=h;p;p=p->next)
  {
    cout <<   nList << ".) " << setw(5) << p->uuid <<setw(7) << " "<< p->name
      << endl;
    nList++;
  }//for
  cout << "Which agent would you like to delete?\n>"; 
  int choice;
  cin >> choice;
  cin.ignore(1000,10);
  while(true)
  {
    int nCount=1;
    logagent* prev;
    int fCount = 1;
    for(logagent* p = h;p;p=p->next) fCount++;
    if((fCount-1)==choice)
    {
      logagent* temp = h;
      for(h,prev=0;h;prev=h,h=h->next)
      {
        if(h->next==NULL)
        {
          h=prev;
          h->next = 0;
        }//if
      }//for
      
      return temp;
    }//if
    else if(choice==1)
    {
      logagent *temp;
      temp = h;
      h = h->next;
      delete(temp);
      break; 
    }//if
    logagent* p;
    for(p=h,prev=0;p;prev=p,p=p->next,nCount++)
    {
      logagent* temp = p;
      if(nCount==choice)
      { 
          logagent* temp;
          temp = p;
          p=prev;
          p->next=p->next->next;
          delete (temp);
          break; 
      }//if
    }//for
    break;
  }//while   
  return h;
}//delete node