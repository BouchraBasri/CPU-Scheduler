#include <iostream>
#include <string>
#include <sstream>
#define LINE_MAX 1024
using namespace std;

struct process
{
    int ID;
    double burstTime;
    double arrivalTime;
    double priority;
    struct process* next;
};

double wTime = 0;
double avgWaitingTime = 0;

struct process* createProcess(int, double, double, double);
struct process* insertProcess(struct process*, int, double, double, double);
int MainMenu(string, string);
int SchedulingMenu();
int preemptive_mode();
void swap(struct process*, struct process*);
struct process* sortArrivalTime(struct process*);
struct process* sortBurstTime(struct process*);
struct process* sortpriority(struct process*);
void FCFS(struct process*, FILE*);
void SJF_NP(struct process*, FILE*);
void priority_NP(struct process*, FILE*);
int size(struct process*);
void showResult(string, string, struct process*, FILE*);
void readOutputFile(const char*);

int main(int argc,char *argv[])
{
    if(argc!=5){
        cout << "Invalid number of arguments." << endl;
        return 1;
    }

    FILE *input=fopen(argv[2],"r");
    if(input == NULL)
    {
        cout << "Cannot open input.txt ." << endl;
        return 1;
    }

    FILE *output=fopen(argv[4],"w");
    if(output == NULL)
    {
        cout << "Cannot open output.txt ." << endl;
        fclose(input);
        return 1;
    }
    
    struct process* p=NULL;
    char line[LINE_MAX];
    int x = size(p);

    while (fgets(line, LINE_MAX, input) != NULL)
    {
        int i[3];
        char colon;
        istringstream iss(line);
        iss >> i[0] >> colon >> i[1] >> colon >> i[2];
        p = insertProcess(p, x, i[0], i[1], i[2]);
        x++;
    }
    string schMethod, preMode;
    int menu, scheduling_menu, mode;
    do{
        menu = MainMenu(schMethod, preMode);
        switch(menu)
        {
            case 1:
                scheduling_menu = SchedulingMenu();
                switch(scheduling_menu)
                {
                    case 1:
                        schMethod = "None";
                        break;
                    case 2:
                        schMethod = "FCFS";
                        break;
                    case 3:
                        schMethod = "SJF";
                        break;
                    case 4:
                        schMethod = "Priority";
                        break;
                    case 5:
                        schMethod = "Round Robin";
                        break;
                }
                break;
            case 2:
                mode = preemptive_mode();
                switch(mode)
                {
                    case 1:
                        if(schMethod == "Round Robin")
                        {
                            cout << "Round Robin is preemptive." << endl;
                            preMode = "On";
                        }
                        else
                        {
                            preMode = "Off";
                        }
                        break;
                    case 2:
                        if(schMethod == "FCFS")
                        {
                            cout << "First Come First Serve is non preemptive." << endl;
                            preMode = "Off";
                        }
                        else
                        {
                            preMode = "On";
                        }
                        break;
                }
                break;
            case 3:
                showResult(schMethod, preMode, p, output);
                break;
        }
    }while(menu <= 4);

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

int preemptive_mode()
{
    int pMode;
    cout << "preemptive MODE" << endl;
    cout << "1.off" << endl;
    cout << "2.on" << endl;
    cout << "Option > ";
    cin >> pMode;
    return pMode;
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

void FCFS(struct process* processHeader, FILE* output)
{
    double completionTime = 0; 
    double turn_around_time = 0;
    int count = 0;
    double sum = 0;
    cout << "Scheduling Method: First Come First Served" << endl;
    fprintf(output, "Scheduling Method: First Come First Served\n");
    cout << "Process Waiting Time:" << endl;
    fprintf(output, "Process Waiting Time:\n");
    processHeader = sortArrivalTime(processHeader);
    while(processHeader != NULL)
    {
        completionTime += processHeader->burstTime; // Adding the burst time of each process that has finished. 
        turn_around_time = completionTime - processHeader->arrivalTime; 
        wTime = turn_around_time - processHeader->burstTime;
        cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
        fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
        sum += wTime;
        processHeader = processHeader->next;
        count++; // This variable calculate the number of processes in the list.
    }
    if(count != 0)
    {
        avgWaitingTime = sum / count;
    }
    else
    {
        avgWaitingTime = 0; // List is empty.
    }
    cout << "Average Waiting Time: " << avgWaitingTime << " ms" << endl;
    fprintf(output, "Average Waiting Time: %f \n ", avgWaitingTime);
}

void SJF_NP(struct process* processHeader, FILE* output)
{
    int completionTime = 0;
    int turn_around_time = 0;
    double sum = 0;
    double count = 0;
    cout << "Scheduling Method: Shortest Job First - Non Preemptive" << endl;
    fprintf(output, "Scheduling Method: Shortest Job First - Non Preemptive\n");
    cout << "Process Waiting Time:" << endl;
    fprintf(output, "Process Waiting Time:\n");
    processHeader = sortArrivalTime(processHeader);
    while(processHeader != NULL)
    {
        completionTime += processHeader->burstTime; // Adding the burst time of each process that has finished. 
        turn_around_time = completionTime - processHeader->arrivalTime; 
        wTime = turn_around_time - processHeader->burstTime;
        cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
        fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
        sum += wTime;
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
                wTime = turn_around_time - processHeader->burstTime;
                cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
                fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
                sum += wTime;
        }
        else if(processHeader->next == NULL)
        {
                completionTime += processHeader->burstTime;
                turn_around_time = completionTime - processHeader->arrivalTime;
                wTime = turn_around_time - processHeader->burstTime;
                cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
                fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
                sum += wTime;
        }
        processHeader = processHeader->next;
        count++;
    }
    if(count != 0)
    {
        avgWaitingTime = sum / count;
    }
    else
    {
        avgWaitingTime = 0; // List is empty.
    }
    cout <<"Average Waiting Time: " << avgWaitingTime << " ms" << endl;
    fprintf(output, "Average Waiting Time: %f ms \n ", avgWaitingTime);
}

void priority_NP(struct process* processHeader, FILE* output)
{
    int completionTime = 0;
    int turn_around_time = 0;
    int count = 0;
    double sum = 0;
    cout << "Scheduling Method: Priority Scheduling - Non Preemptive" << endl;
    fprintf(output, "Scheduling Method: Priority Scheduling - Non Preemptive\n");
    cout << "Process Waiting Time:" << endl;
    fprintf(output, "Process Waiting Time:\n");
    processHeader = sortArrivalTime(processHeader);
    while(processHeader != NULL)
    {
        completionTime += processHeader->burstTime; // Adding the burst time of each process that has finished. 
        turn_around_time = completionTime - processHeader->arrivalTime; 
        wTime = turn_around_time - processHeader->burstTime;
        cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
        fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
        sum += wTime;
        processHeader = processHeader->next;
        count++;
        break;
    }
    processHeader = sortpriority(processHeader);
    while(processHeader != NULL)
    {
        if(processHeader->next != NULL)
        {
                completionTime += processHeader->burstTime;
                turn_around_time = completionTime - processHeader->arrivalTime;
                wTime = turn_around_time - processHeader->burstTime;
                cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
                fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
                sum += wTime;
        }
        else if(processHeader->next == NULL)
        {
                completionTime += processHeader->burstTime;
                turn_around_time = completionTime - processHeader->arrivalTime;
                wTime = turn_around_time - processHeader->burstTime;
                cout << "P" << processHeader->ID << ": " << wTime << " ms" << endl;
                fprintf(output, "P %d: %f ms\n", processHeader->ID, wTime);
                sum += wTime;
        }
        processHeader = processHeader->next;
        count++;
    }
    if(count != 0)
    {
        avgWaitingTime = sum / count;
    }
    else
    {
        avgWaitingTime = 0; // List is empty.
    }
    cout << "Average Waiting Time: " << avgWaitingTime << " ms" << endl;
    fprintf(output, "Average Waiting Time: %f ms \n", avgWaitingTime);
}

int size(struct process *processHeader)
{
	int x=1;
	while(processHeader!=NULL)
	{
		x++;
		processHeader = processHeader->next;
	}
	return x;	
}

void showResult(string Method, string Mode,struct process* p, FILE* output)
{
    if(Method == "FCFS" && Mode == "off")
    {
        FCFS(p,output);
    }
    else if(Method == "FCFS" && Mode == "On")
    {
        cout << "FCFS is a non preemptive method." << endl;
    }
    else if(Method == "SJF" && Mode == "Off")
    {
        SJF_NP(p,output);
    }
    else if(Method == "SJF" && Mode == "On")
    {
        cout << "This function is not implemented yet." << endl;
    }
    else if(Method == "Priority" && Mode == "Off")
	{
        priority_NP(p,output);
    }
    else if(Method == "Priority" && Mode == "On")
    {
        cout << "This function is not implemented yet." << endl;
    }
    else if(Method == "Round Robin" && Mode == "On")
    {
        cout << "This function is not implemented yet." << endl;
    }
    else if(Method == "Round Robin" && Mode == "Off")
    {
        cout << "FCFS is a non preemptive method."<< endl;
    }
    else if(Method == " " || Mode == " ")
    {
        cout << "Please choose scheduling method and preemptive mode." << endl;
    }
}

void readOutputFile(const char* filename)
{
    FILE* OFile = fopen(filename,"r");
    if (OFile != NULL)
    {
        char line [LINE_MAX];
        while (fgets(line, LINE_MAX, OFile) != NULL)
        {
            cout << line << "\n";
        }
    }
    else
    {
        cout << "Cannot open output.txt" << endl;
    }
} 
