#include<bits/stdc++.h>
using namespace std;

//SRTF ALgorithm

class Process{
public:
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    bool isready; //true if it's present in ready_queue

    Process(int i,int j,int k){
        pid=i;
        at=j;
        bt=k;
        ct=-1;
        tat=-1;
        wt=-1;
        rt=k;
        isready=false;
    }


};

//custom comparator function for priority_queue 
class Compare{
public:
    bool operator()(Process* p1,Process* p2){
         if(p1->rt>p2->rt)return true;
        if(p1->rt==p2->rt){
           if(p1->at>p2->at)return true;
            if(p1->at==p2->at){
            if(p1->pid>p2->pid)return true;
     }
    }
    return false;
    }
};

bool cmp_at(Process* p1,Process* p2){
   if(p1->at>p2->at)return false;
   if(p1->at==p2->at){
     if(p1->pid>p2->pid)return false;
   }
   return true; 
}

void generateParams(vector<Process*>&process){
    for(int i=0;i<process.size();i++){
        process[i]->tat=process[i]->ct-process[i]->at;
        process[i]->wt=process[i]->tat-process[i]->bt;
    }

}


void srtf(vector<Process*>&process){
   sort(process.begin(),process.end(),cmp_at);
   priority_queue<Process*,vector<Process*>,Compare>ready;

   int timer=process[0]->at;
   int k=0;
   while(k<process.size()){
       if(process[k]->at==timer){
         ready.push(process[k]);
         process[k]->isready=true;
         k++;
       }else break;
   }
   
   
   
  
   while(!ready.empty()){
       auto execution=ready.top();
       ready.pop();
       int temp=timer;
       timer++;
       execution->rt--;
       execution->isready=false;
       if(execution->rt==0){
        execution->ct=timer;
       }

       //temproary gant chart with time
      // cout<<execution->pid<<"->["<<temp<<","<<execution->ct<<"]"<<endl;

      cout<<execution->pid<<" | ";

       for(int l=0;l<process.size();l++){
         if(process[l]->isready)continue;
         if(process[l]->at<=timer){
            if(process[l]->rt>0){
                ready.push(process[l]);
                process[l]->isready=true;
            }
         }else break;
       }

   }

   cout<<endl<<endl;

   generateParams(process);

   int schedule=0;
   int tt=0;
   int wt=0;
   for(auto i:process){
      schedule=max(schedule,i->ct);
      tt+=i->tat;
      wt+=i->wt;
   }
   

    
    cout<<"Pid"<<" "<<"A.T"<<" "<<"B.T"<<" "<<"C.T"<<" "<<"T.A.T"<<" "<<"W.T"<<endl;
   for(auto i:process){
    cout<<i->pid<<"  | "<<i->at<<" | "<<i->bt<<" | "<<i->ct<<" | "<<i->tat<<"   | "<<i->wt<<endl;
   }
   cout<<endl;
   cout<<"AVERAGE T.A.T -> "<<(float)tt/process.size()<<endl;
   cout<<"AVERAGE W.T -> "<<(float)wt/process.size()<<endl;
   cout<<"Scheduling Length -> "<<schedule<<endl;
}
 
int main(){
    int n;
    cin>>n;
    vector<Process*>process;
    for(int i=0;i<n;i++){
        int pid,at,bt;
        cin>>pid>>at>>bt;
        Process*p1=new Process(pid,at,bt);
        process.push_back(p1);
    }

    srtf(process);
    
    return 0;
}