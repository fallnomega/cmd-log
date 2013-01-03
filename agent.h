
#ifndef AGENT_H 
#define AGENT_H

class agent
{
  private:

    char name[40];
    char uuid[7];
    int ext;
    char center[12];
    char department[10];
    char position[10];
    char om[20];
    int ttv;
    agent *next;

  public:
    static int menu();
    static char getYesNo();
    static void header();
    agent* addAgent();
    agent* agent::insert( agent* head); //insertion
    agent* restoreList();//restore from courses.dat
    void agent::saveList();
    void coutList();
    agent* getText();
    void clearList();//clear list
    agent* agent::mergeLists(agent*);
    int agent::compare (const agent* a, const agent* b);
    void agent::toLower(char str[]);
    agent* deleteNode(agent* h, agent& t); // header 
    agent* agent::sortAgent();
    agent* agent::compareDescr(agent* h);
    char agent::compareDCmp( const agent* src);
    int agent::myStricmp(const char* dst, const char* src);
    agent* agent::newEntry();
    void testCout();
};
class logagent
{
  private:
    char timeStamp[30];
    char name[40];
    char uuid[7];
    int ext;
    char center[12];
    char department[10];
    char position[10];
    char om[20];
    int ttv;
    char notes[500];
    logagent *next;

  public:
     void logagent::LsaveList();
     logagent* logagent::LdeleteNode(logagent* h, logagent& t);
     void logagent::LcoutList();
     logagent* logagent::logNewEntry();
     logagent* logagent::LrestoreList();
     logagent* logagent::push_back(logagent* t, logagent* h);
     void logagent::LclearList();//clear list 
     
     //test
     void AtestCout();
};
#endif