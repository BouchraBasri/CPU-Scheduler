#include <iostream>
using namespace std;
 
 struct process{
    double burstTime;
    double arrivalTime;
    double priority;
    struct process* next;
};

int firstMenu(string , string );
int secondMenu();
struct process* createnode (double, double, double);
struct process* insertProcess(struct process*, double, double, double);
void FCFS(struct process*);

int main()
{

}

int firstMenu(string schMode, string preMode ) {
    int firstChoice;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) Scheduling Method (" << schMode << ")" << endl;
    cout << "2) Preemptive Mode (" << preMode << ")" << endl;
    cout << "3) Show Result" << endl;
    cout << "4) End Program" << endl;
    cout << "Option > ";
    cin >> firstChoice;
    return firstChoice;
}

int secondMenu(){
    int secondChoice;
    cout << "CPU Scheduler Simulator MODE" << endl;
    cout << "1) None " << endl;
    cout << "2) First Come First Serve Scheduler " << endl;
    cout << "3) Shortest-Job-First Scheduler" << endl;
    cout << "4) Priority Scheduler" << endl;
    cout << "5) Round Robin Scheduling" << endl;
    cout << "Option >";
    cin >> secondChoice;
    return secondChoice;
}

struct process* createnode (double bTime, double aTime, double pTime)
{
    struct process* newnode;
    newnode = (struct process *) malloc(sizeof(process));
    newnode->burstTime = bTime;
    newnode->arrivalTime = aTime;
    newnode->priority = pTime;
    newnode->next = NULL;
    return newnode;
}

struct process* insertProcess(struct process* processList, double bTime, double aTime, double pTime)
{
    struct process* newProcess = createnode(bTime, aTime, pTime);
    struct process* currentProcess;
    if(processList == NULL)
    {
        processList = newProcess;
        return processList;
    }
    currentProcess = processList;
    while(currentProcess->next != NULL)
        currentProcess = currentProcess->next;
    currentProcess->next = newProcess;
    return processList;
}

void FCFS(struct process* processList)
{
    int waitingTime = 0;
    double avgWaitingTime = 0;
    int numOfProcess = 0;
    while(processList != NULL)
    {
        waitingTime += processList->burstTime;
        processList = processList->next;
        numOfProcess++ ;
    }
    if(numOfProcess != 0)
    {
        avgWaitingTime = waitingTime / numOfProcess;
    }
    else
        avgWaitingTime = 0;
}
