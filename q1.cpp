/*Priority Scheduling is a method of scheduling processes that are based on priority. In
this algorithm, the scheduler selects the tasks to work as per the priority. The processes
with higher priority should be carried out first, whereas jobs with equal priorities are
carried out on an FCFS basis. Sometimes it is important to run a task with a higher priority
before another lower priority task, even if the lower priority task is still running. The lower
priority task holds for some time and resumes when the higher priority task finishes its
execution.
Consider n processes, P1, P2 .. Pn. Write a program to find out the average waiting time
(WT), the turn-around time(TAT), and the completion order of the processes using the
Priority preemptive ​ scheduling algorithm ( in case of conflict, the process with smaller
process id​ will execute first).
The number of processes and for each process, the arrival_time, priority, and burst_time
are to be considered as input.*/

//Copyright@Souhardya
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mk make_pair
#define f first
#define se second
#define ll long long int
#define ld long double
#define MOD 1000000007

//Rounding upto 2 places
ld round(ld var) 
{ 
    ld value = (int)(var * 100 + .5); 
    return (ld)value / 100; 
} 


//Structure of each process.
struct Interval{
    int process;
    int arrival;
    int priority;
    int burst_time;
    int waiting_time;
    int turn_around;
    int complete;
    int target;
};


//Initial Sorting function of vectors based on arrival time
bool compare(Interval i1,Interval i2)
{   
       if(i1.arrival!=i2.arrival)
        return i1.arrival<i2.arrival;
       else if(i1.priority!=i2.priority)
        return i1.priority>i2.priority;
       else
        return i1.process<i2.process;
}


//Custom sorting priority queue based on priority>arrival_time>process.
struct Compareprio {
    bool operator()(Interval const &p1, Interval const &p2)
    {
        // return "true" if "p1" is ordered 
        // before "p2", for example:
      if(p1.priority!=p2.priority)
          return p1.priority < p2.priority;
      else if(p1.arrival!=p2.arrival)
          return p1.arrival>p2.arrival;
      else
          return p1.process>p2.process;

    }
};


//Driver code
int main() 
{    
    ll n;
    //Total Number of process
    cin>>n;
    //Input vector
    vector<Interval>v(n);

    //Answer vector
    vector<Interval>ans;

    //Taking Input
    for(int i=0;i<n;i++)
    {    
      int a,b,c;
      cin>>a>>b>>c;
      v[i].arrival=a;   v[i].priority=b;   v[i].burst_time=c;
      v[i].process=i+1;     v[i].target=c; 
    }
    //Sorting input vector
    sort(v.begin(),v.end(),compare);
    // cout<<"Arrival Time "<<endl;
    // for(int i=0;i<n;i++)
    // {
    //   cout<<v[i].arrival<<" "<<v[i].priority<<" "<<v[i].burst_time;
    
    // cout<<endl;
    // }
    priority_queue<Interval,vector<Interval>,Compareprio> q;
    int t=0;   int k=0;   int cp=0;   // t->time,k->parameter,cp->total array visited
    int vis[n]={0};
    while(ans.size()!=n)
    {    
           int j=k;
           if(cp<n)
          { 
           for(int j=k;j<n;j++)
           {    

                if((v[j].arrival==t)&&(vis[j]==0)){
                     
                    cp++;   vis[j]=1;
                     q.push(v[j]);
                     
                }
                else if(v[j].arrival>t){
                  k=j;
                  break;
                }
                
           }
         }
           if(q.size())
           {
                Interval temp=q.top();
                q.pop();
                temp.burst_time=temp.burst_time-1;
                 t++;
                if(temp.burst_time==0)
                {     
                      temp.turn_around=t-temp.arrival;
                      temp.waiting_time=temp.turn_around-temp.target;
                      ans.pb(temp);
                }
                else{
                    q.push(temp);
                }

           }
          else
           t++;
    }
    int avrg_wait=0,avrg_turn=0;
    for(int i=0;i<n;i++)
    {
        // cout<<"For Process: "<<ans[i].process<<endl;
        // cout<<"Waiting Time: "<<ans[i].waiting_time;
        // cout<<"Turn-around Time: "<<ans[i].turn_around<<endl;
        avrg_wait+=ans[i].waiting_time;
        avrg_turn+=ans[i].turn_around;
    }
    cout<<"The average waiting time(WT) is: "<<(ld)avrg_wait/n<<" seconds"<<endl;
    cout<<"The average Turn-around time(TAT) is: "<<(ld)avrg_turn/n<<" seconds"<<endl;
    cout<<"Completion order of the processes:"<<endl;
     for(int i=0;i<n;i++)
       cout<<"P"<<ans[i].process<<" ";
     cout<<endl;




  return 0;
              
}
      

 
