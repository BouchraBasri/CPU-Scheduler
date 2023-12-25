#include <iostream>
using namespace std;
 
 struct node{
    double burstTime;
    double arrivalTime;
    double priority;
    struct node *next;
};

int firstMenu(string , string );
int secondMenu();
struct node * createNode (double, double, double);
struct node * insertFront(struct node *, double, double, double);
struct node * insertBack(struct node *, double, double, double);
void insertAfter (struct node *, double, double, double);
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

struct node * createNode (double bTime, double aTime, double pTime)
{
    struct node * temp;
    temp = (struct node *) malloc(sizeof(node));
    temp->burstTime = bTime;
    temp->arrivalTime = aTime;
    temp->priority = pTime;
    temp->next = NULL;
    return temp;
}

struct node * insertFront(struct node *, double bTime, double aTime, double pTime)
{
    struct node * temp = createNode(bTime, aTime, pTime);
    temp->next = header;
    header = temp;
    return header;
}

struct node * insertBack(struct node *, double bTime, double aTime, double pTime)
{
    struct node * temp = createNode(bTime, aTime, pTime);
    struct node * headertemp;
    if(header == NULL)
    {
        header = temp;
        return header;
    }
    headertemp = header;
    while(headertemp->next != NULL)
        headertemp = headertemp->next;
    headertemp->next = temp;
    return header;
}

void insertAfter (struct node *afterNode, double bTime, double aTime, double pTime)
{
    struct node * temp = createNode(bTime, aTime, pTime);
    temp->next = afterNode->next;
    afterNode->next = temp;
}
