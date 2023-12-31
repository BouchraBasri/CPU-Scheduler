#include <iostream>
using namespace std;
 
 struct process{
    double burstTime;
    double arrivalTime;
    double priority;
    struct process* next;
};

int processID = 1;
double waitingTime = 0;
double avgWaitingTime = 0;
int quantum = 2;

int firstMenu(string , string );
int secondMenu();
struct process* createProcess(double, double, double);
struct process* insertProcess(struct process*, double, double, double);
void FCFSOutput(struct process*);
void RoundRobin(struct process*);

int main()
{

}

int firstMenu(string schMode, string preMode){ //The function displays the menu options and waits for user input.
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

int secondMenu() //The function displays the menu options and waits for user to choose scheduler simulator.
{
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

struct process* createProcess (double bTime, double aTime, double pTime)
{
    struct process* newProcess;
    newProcess = (struct process *) malloc(sizeof(process));
    newProcess->burstTime = bTime;
    newProcess->arrivalTime = aTime;
    newProcess->priority = pTime;
    newProcess->next = NULL;
    return newProcess;
}

struct process* insertProcess(struct process* processList, struct process* newProcess)
{
    struct process* currentProcess
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

void FCFSOutput(struct process* processList)
{
    double cTime = 0;
    double turn_around_time = 0;
    cout << "Scheduling Method: First Come First Served" << endl;
    cout << "Process Waiting Time:" << endl;
    while(processList != NULL)
    {
        cout << "P" << processID << ": " << waitingTime << " ms" << endl;
        processID++;
        cTime = cTime + processList->burstTime;
        turn_around_time = cTime - processList->arrivalTime;
        waitingTime = turn_around_time - processList->burstTime;
        processList = processList->next
    }
    processID = processID - 1;
    if(processID != 0)
    {
        avgWaitingTime = waitingTime / processID;
    }
    else
    {
        avgWaitingTime = 0;
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
}

void RoundRobin(struct process* processList) 
{
    while (processList != NULL)
    {
        if(processList->burstTime >= quantum)
        {
        waitingTime = waitingTime + quantum;
        processList->burstTime = processList->burstTime - quantum;
        }
        else
        {
        waitingTime = waitingTime + processList->burstTime;
        processList->burstTime = 0;
        }
        processList = processList->next;
    }
}
