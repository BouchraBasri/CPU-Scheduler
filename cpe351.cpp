#include <iostream>
#include <fstream>
using namespace std;
 
struct process
{
    int ID;
    double burstTime;
    double arrivalTime;
    double priority;
    double waitingTime;
    struct process* next;
};

double wTime = 0;
double avgWaitingTime = 0;
int count = 0;
int quantum = 2;

int firstMenu(int);
int secondMenu();
struct process* createProcess(int, double, double, double);
struct process* insertProcess(struct process*,struct process*);
struct process* sortArrivalTime(struct process*);
struct process* sortbyID(struct process*);
void FCFSOutput(struct process*);
void RoundRobin(struct process*);
void showresult(int);

int main(int argc, char *argv[])
{
    FILE *input = fopen(input, "r");
    FILE *output = fopen(output, "w");
    struct process* p=NULL;
    int menu=firstMenu();
    switch (menu)
    {
        case 1:
            int scheduling_menu=secondMenu();
            switch (scheduling_menu)
            {
                case 1:           
                    break;
                case 2:
                    FCFSOutput(p);
                    break;
                case 3:
                    break;
                case 4:
                    break;    
                default:
                    break;
            }
    }
}

int firstMenu(int secondChoice) //The function displays the menu options and waits for user input.
{
    int firstChoice;
    string schMode, preMode;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) Scheduling Method (" << schMode << ")" << endl;
    cout << "2) Preemptive Mode (" << preMode << ")" << endl;
    cout << "3) Show Result" << endl;
    cout << "4) End Program" << endl;
    cout << "Option > ";
    cin >> firstChoice;

    switch(secondChoice)
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

struct process* createProcess (int processID, double bTime, double aTime, double pTime, double waitingT)
{
    struct process* processList; //processList pointer to the head of the linked list.
    processList = (struct process *) malloc(sizeof(process));
    processList->processID = processID;
    processList->burstTime = bTime;
    processList->arrivalTime = aTime;
    processList->priority = pTime;
    processList->waitingTime = waitingT;
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

struct process* sortArrivalTime(struct process * processList) //This function sorts list based on arrival time of the processes.
{
    struct process * newProcess = NULL;
    double tempbT, tempaT, temppT, tempwT;
    int tempID;
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
                    tempID = processList->ID;
                    tempbT = processList->burstTime;
                    tempaT = processList->arrivalTime;
                    temppT = processList->priority;
                    tempwT = processList->waitingTime;
                    processList->ID = newProcess->ID;
                    processList->burstTime = newProcess->burstTime;
                    processList->arrivalTime = newProcess->arrivalTime;
                    processList->priority = newProcess->priority;
                    processList->waitingTime = newProcess->waitingTime;
                    newProcess->ID = tempID;
                    newProcess->burstTime = tempbT;
                    newProcess->arrivalTime = tempaT;
                    newProcess->priority = temppT;
                    newProcess->waitingTime = tempwT;
                }
                newProcess = newProcess->next;
            }
            processList = processList->next;
        }
    }
    return processList;
}

struct process* sortbyID(struct process* processList)
{
    struct process * newProcess = NULL;
    double tempbT, tempaT, temppT;
    int tempID;
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
                if(processList->ID > newProcess->ID)
                {
                    tempID = processList->ID;
                    tempbT = processList->burstTime;
                    tempaT = processList->arrivalTime;
                    temppT = processList->priority;
                    processList->ID = newProcess->ID;
                    processList->burstTime = newProcess->burstTime;
                    processList->arrivalTime = newProcess->arrivalTime;
                    processList->priority = newProcess->priority;
                    newProcess->ID = tempID;
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
    processList = sortArrivalTime(processList);
    while(processList != NULL)
    {
        processList->waitingTime = wTime;
        cTime += processList->burstTime;
        turn_around_time = cTime - processList->arrivalTime;
        wTime += turn_around_time - processList->burstTime;
        processList = processList->next;
        count++;
    }
    if(count != 0)
    {
        avgWaitingTime = waitingTime / count;
    }
    else
    {
        avgWaitingTime = 0;
    }
    processList = sortbyID(processList);
    while(processList != NULL)
    {
        cout << "P" << processList->ID << ": " << processList->waitingTime << " ms" << endl;
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
}

void RoundRobin(struct process* processList) 
{
    double executionTime = 0; // Variable to keep track of the total execution time.
    cout << "Scheduling Method: Round Robin" << endl;
    cout << "Process Waiting Time:" << endl;
    processList = sortArrivalTime(processList);
    while (processList != NULL)
    {
        processList->waitingTime = wTime;
        if (processList->burstTime >= quantum)
        {
            executionTime = quantum; // Execute for the quantum time if the burst time is greater than or equal to the quantum.
        }
        else
        {
            executionTime = processList->burstTime; // Execute for the remaining burst time if it's less than the quantum.
        }
        processList->burstTime -= executionTime; // Update the burst time of the current process.
        waitingTime += executionTime;
        if(processList->burstTime > 0)
        {
            processList = processList->next; // Move to the next process if there's more burst time remaining.
        }
        else
        {
            processList = processList->next; // Move to the next process if the current process is completed.
        }
        count++;
    }
    if(count != 0)
    {
        avgWaitingTime = waitingTime / count; // Calculate average waiting time if there are processes.
    }
    else
    {
        avgWaitingTime = 0; // Set average to 0 if there are no process.
    }
    processList = sortbyID(processList); 
    while (processList != NULL)
    {
        cout << "P" << processList->ID << ": " << processList->waitingTime << " ms" << endl;
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
}

void showresult(string schMode, struct process* processList)
{
    cout << "Scheduling Method: " << schMode << endl;
    cout << "Process Waiting Times:" << endl;
    while(processList != NULL)
    {
        cout << "P" << processList->ID << ": " << processList->waitingTime << " ms" << endl;
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
} 
