#include <iostream>
#include <string>
using namespace std;

struct process
{
    int ID;
    double burstTime;
    double arrivalTime;
    double priority;
    struct process* next;
};

struct process* createProcess(int, double, double, double);
struct process* insertProcess(struct process*, int, double, double, double);
int MainMenu(string, string);
int SchedulingMenu();
void swap(struct process*, struct process*);
struct process* sortArrivalTime(struct process*);
struct process* sortBurstTime(struct process*);
struct process* sortpriority(struct process*);
void FCFS(struct process*);
void SJF_NP(struct process*);

int main()
{
    

    return 0;
}

struct process* createProcess(int processID, double bTime, double aTime, double pTime)
{
    struct process* processHeader = (struct process *)malloc(sizeof(process));
    processHeader->ID = processID;
    processHeader->burstTime = bTime;
    processHeader->arrivalTime = aTime;
    processHeader->priority = pTime;
    processHeader->next = NULL;
    return processHeader;
}

struct process* insertProcess(struct process* processHeader, int process_id, double process_burst, double process_arrival, double process_priority)
{
    struct process* newProcess = createProcess(process_id, process_burst, process_arrival, process_priority);
    struct process* currentProcess;
    if (processHeader == NULL)
    {
        return newProcess;
    }
    currentProcess = processHeader;
    while (currentProcess->next != NULL)
        currentProcess = currentProcess->next;
    currentProcess->next = newProcess;
    return processHeader;
}

int MainMenu(string schedulingMethod, string preemptiveMode)
{
    int Choice;
    cout << "CPU Scheduler Simulator" << endl;
    cout << "1) Scheduling Method ("<< schedulingMethod <<")" << endl;
    cout << "2) Preemptive Mode ("<< preemptiveMode <<")" << endl;
    cout << "3) Show Result" << endl;
    cout << "4) End Program" << endl;
    cout << "Option > ";
    cin >> Choice;
    return Choice;
}

int SchedulingMenu() //The function displays the menu options and waits for user to choose scheduler simulator.
{
    int schedulingMethod;
    cout << "CPU Scheduler Simulator MODE" << endl;
    cout << "1) None " << endl;
    cout << "2) First Come First Serve Scheduler " << endl;
    cout << "3) Shortest-Job-First Scheduler" << endl;
    cout << "4) Priority Scheduler" << endl;
    cout << "5) Round Robin Scheduling" << endl;
    cout << "Option > ";
    cin >> schedulingMethod;
    return schedulingMethod;
}

void swap(struct process* processHeader, struct process* nextProcess)
{
    int tempID;
    double tempburst, temparrival, temppriority;

    tempID = processHeader->ID;
    tempburst = processHeader->burstTime;
    temparrival = processHeader->arrivalTime;
    temppriority = processHeader->priority;

    processHeader->ID = nextProcess->ID;
    processHeader->burstTime = nextProcess->burstTime;
    processHeader->arrivalTime = nextProcess->arrivalTime;
    processHeader->priority = nextProcess->priority;

    nextProcess->ID = tempID;
    nextProcess->burstTime = tempburst;
    nextProcess->arrivalTime = temparrival;
    nextProcess->priority = temppriority;
}

struct process* sortArrivalTime(struct process* processHeader)
{
    bool swapped;
    struct process* temp;

    do
    {
        swapped = false;
        temp = processHeader;

        while(temp->next != NULL)
        {
            if(temp->arrivalTime > temp->next->arrivalTime)
            {
                swap(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    }while(swapped);
    return processHeader;
}

struct process* sortBurstTime(struct process* processHeader)
{
    bool swapped;
    struct process* temp;

    do
    {
        swapped = false;
        temp = processHeader;

        while(temp->next != NULL)
        {
            if(temp->burstTime > temp->next->burstTime)
            {
                swap(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    }while(swapped);
    return processHeader;
}

struct process* sortpriority(struct process* processHeader)
{
    bool swapped;
    struct process* temp;

    do
    {
        swapped = false;
        temp = processHeader;

        while(temp->next != NULL)
        {
            if(temp->priority > temp->next->priority)
            {
                swap(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    }while(swapped);
    return processHeader;
}

void FCFS(struct process* processHeader)
{
    double completionTime = 0; 
    double turn_around_time = 0;
    cout << "Scheduling Method: First Come First Served" << endl;
    cout << "Process Waiting Time:" << endl;
    processHeader = sortArrivalTime(processHeader);
    while(processHeader != NULL)
    {
        completionTime += processHeader->burstTime; // Adding the burst time of each process that has finished. 
        turn_around_time = completionTime - processHeader->arrivalTime; 
        wTime = turn_around_time - processHeader->burstTime;
        cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
        avgWaitingTime += wTime;
        processHeader = processHeader->next;
        count++; // This variable calculate the number of processes in the list.
    }
    if(count != 0)
    {
        avgWaitingTime = avgWaitingTime / count;
    }
    else
    {
        avgWaitingTime = 0; // List is empty.
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
}

void SJF_NP(struct process* processHeader)
{
    int completionTime = 0;
    int Turn_around_time = 0;
    cout << "Scheduling Method: Shortest Job First - Non Preemptive" << endl;
    cout << "Process Waiting Time:" << endl;
    processHeader = sortArrivalTime(processHeader);
    while(processHeader != NULL)
    {
        completionTime += processHeader->burstTime; 
        turn_around_time = completionTime - processHeader->arrivalTime; 
        wTime = turn_around_time - processHeader->burstTime;
        cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
        avgWaitingTime += wTime;
        processHeader = processHeader->next;
        count++;
        break;
    }
    processHeader = sortBurstTime(processHeader);
    while(processHeader != NULL)
    {
        if(processHeader->next != NULL)
        {
            completionTime += processHeader->burstTime;
            turn_around_time = completionTime - processHeader->arrivalTime;
            wTime = turn_around_time - processheader->burstTime;
            cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;                avgWaitingTime += wTime;
            avgWaitingTime += wTime;
        }
        else if(processHeader->next == NULL)
        {
            completionTime += processHeader->burstTime;
            turn_around_time = completionTime - processHeader->arrivalTime;
            wTime = turn_around_time - processHeader->burstTime;
            cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
            avgWaitingTime += wTime;
        }
        processHeader = processHeader->next;
        count++;
    }
    if(count != 0)
    {
        avgWaitingTime = avgWaitingTime / count;
    }
    else
    {
        avgWaitingTime = 0; // List is empty.
    }
    cout << " Average Waiting Time: " << avgWaitingTime << " ms" << endl;
} 
