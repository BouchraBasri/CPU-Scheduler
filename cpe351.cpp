#include <iostream>
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
void swap(struct process*, struct process*);
struct process* sortArrivalTime(struct process*);
struct process* sortBurstTime(struct process*);
struct process* sortpriority(struct process*);

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
