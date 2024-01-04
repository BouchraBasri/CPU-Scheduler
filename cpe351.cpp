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

int firstMenu(int, string, string );
int secondMenu();
struct process* createProcess(double, double, double);
struct process* insertProcess(struct process*,struct process*);
struct process* sortArrivalTime(struct process*);
void FCFSOutput(struct process*);
void RoundRobin(struct process*);

int main(int argc, char *argv[])
{
    
}

int firstMenu(int secondMenu,string schMode, string preMode){ //The function displays the menu options and waits for user input.
    int firstChoice;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) Scheduling Method (" << schMode << ")" << endl;
    cout << "2) Preemptive Mode (" << preMode << ")" << endl;
    cout << "3) Show Result" << endl;
    cout << "4) End Program" << endl;
    cout << "Option > ";
    cin >> firstChoice;

    switch(secondMenu)
    {
        case 2:
            schMode = "FCFS";
            break;
        case 3:
            schMode = "SJF";
            break;
        case 4:
            schMode = "Priotity";
            break;
        case 5:
            schMode = "Round Robin";
            break;
        default:
            break;
    }
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
    struct process* processList;
    processList = (struct process *) malloc(sizeof(process));
    processList->burstTime = bTime;
    processList->arrivalTime = aTime;
    processList->priority = pTime;
    processList->next = NULL;
    return processList;
}

struct process* insertProcess(struct process* processList, struct process* currentProcess)
{
    if(processList == NULL)
    {
        processList = processList;
        return processList;
    }
    currentProcess = processList;
    while(currentProcess->next != NULL)
        currentProcess = currentProcess->next;
    currentProcess->next = processList;
    return processList;
}

struct node * sortArrivalTime(struct process * processList)
{
    struct process * newProcess = NULL;
    double tempbT, tempaT, temppT;
    if(list_is_empty(processList))
    {
        return processList;
    }
    else
    {
        while(processList != NULL)
        {
            while(newProcess != NULL)
            {
                if(processList->arrivalTime > newProcess->arrivalTime)
                {
                    tempbT = processList->burstTime;
                    tempaT = processList->arrivalTime;
                    temppT = processList->priority;
                    processList->burstTime = newProcess->burstTime;
                    processList->arrivalTime = newProcess->arrivalTime;
                    processList->priority = newProcess->priority;
                    newProcess->burstTime = tempbT;
                    newProcess->arrivalTime = tempaT;
                    newProcess->priority = temppT;
                }
                newProcess = newProcess->next;
            }
            processList = processList->next;
        }
    }
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
    double executionTime = 0;
    cout << "Scheduling Method: Round Robin" << endl;
    cout << "Process Waiting Time:" << endl;
    while (processList != NULL)
    {
        cout << "P" << processID << ": " << waitingTime << " ms" << endl;
        processID++;
        if (processList->burstTime >= quantum)
        {
            executionTime += quantum;
        }
        else
        {
            executionTime += processList->burstTime;
        }
        processList->burstTime -= executionTime;
        if(processList->burstTime > 0)
        {
            processList = processList->next;
        }
        else
        {
            processList = processList->next;
        }
    }
}
