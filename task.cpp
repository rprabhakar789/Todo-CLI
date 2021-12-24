#include <iostream>
#include<bits/stdc++.h>
using namespace std;


void printHelp()
{
  /*
  Usage :-
  $ ./task add 2 hello world    # Add a new item with priority 2 and text "hello world" to the list
  $ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order
  $ ./task del INDEX            # Delete the incomplete item with the given index
  $ ./task done INDEX           # Mark the incomplete item with the given index as complete
  $ ./task help                 # Show usage
  $ ./task report               # Statistics
*/
  cout<<"Usage :-"<<endl
  <<"$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list"<<endl
  <<"$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order"<<endl
  <<"$ ./task del INDEX            # Delete the incomplete item with the given index"<<endl
  <<"$ ./task done INDEX           # Mark the incomplete item with the given index as complete"<<endl
  <<"$ ./task help                 # Show usage"<<endl
  <<"$ ./task report               # Statistics"<<endl;
}

vector<pair<int, string>>getItems(){
  string myText;

  // Read from the text file
  ifstream file("task.txt");

  // Use a while loop together with the getline() function to read the file line by line
    int priority;
    string task;
    vector<pair<int, string>>items;

    while (file >> priority >> task)
    {
        items.push_back({priority,task});
      //  cout<<cnt++<<". "<<task<<" ["<<priority<<"]"<<endl;
    }


  // Close the file
  file.close();
  return items;
}
void showList(){
  // Create a text string, which is used to output the text file
  //cout<<"Showing list...\n";
  int cnt = 1;
  vector<pair<int, string>>items = getItems();
  if(items.size()==0)
  {
    cout<<"There are no pending tasks!";
    return;
  }
  for(int i=0;i<(int)items.size();i++)
  {
    cout<<cnt++<<". "<<items[i].second<<" ["<<items[i].first<<"]"<<endl;
  }

}

void addItem(char* p, char* task)
{
  //cout<<"adding item\n";
  auto n = stoi(p, nullptr, 10);
  //cout<<*(task)<<endl;
  string s = string(task);
  pair<int,string>item = {n,s};
  vector<pair<int, string>>items = getItems();
  items.push_back(item);
  sort(items.begin(),items.end());

  ofstream fout("task.txt");
  for(int i=0;i<(int)items.size();i++)
  {
    fout<<items[i].first<<" "<<items[i].second<<endl;
  }
  cout<<"Added task:\""<<s<<"\" with priority "<<n<<endl;

}

void deleteItem(char* ind)
{
  auto n = stoi(ind, nullptr, 10);
  vector<pair<int, string>>items = getItems();
  if(n>(int)items.size())
  {
    cout<<"Error: item with index "<<n<<" does not exist. Nothing deleted.";
    return;
  }
  ofstream fout("task.txt");
  for(int i=0;i<(int)items.size();i++)
  {
    if(i!=n-1)
    fout<<items[i].first<<" "<<items[i].second<<endl;
  }
  cout<<"Deleted item with index "<<n<<endl;

}

void markDone(char* ind)
{
  auto n = stoi(ind, nullptr, 10);
  vector<pair<int, string>>items = getItems();
  if(n>items.size())
  {
    cout<<"Error: no incomplete item with index "<<n<<" exists.";
    return;
  }
  ofstream fout("task.txt");
  ofstream done("completed.txt");
  for(int i=0;i<(int)items.size();i++)
  {
    if(i!=n-1)
    fout<<items[i].first<<" "<<items[i].second<<endl;
    else{
      done<<items[i].second<<"\n";
    }
  }
  cout<<"Marked item as done.";

}
vector<string>getDoneItems()
{
  ifstream fin("completed.txt");
  string word;
  vector<string>done;
  while(fin>>word)
  {
    done.push_back(word);
  }
  return done;
}
void getReport(){
    vector<pair<int, string>>items = getItems();
    cout<<"Pending : "<<items.size()<<endl;
    int cnt = 1;
    for(int i=0;i<(int)items.size();i++)
    {
      cout<<(i+1)<<". "<<items[i].second<<" ["<<items[i].first<<"]\n";
    }
    cout<<endl;
    vector<string>completed = getDoneItems();
    cout<<"Completed : "<<completed.size()<<endl;
    for(int i=0;i<completed.size();i++)
    {
      cout<<i+1<<". "<<completed[i]<<endl;
    }

}
int main(int argc, char* argv[])
{
    string cmd = *(argv+1);
    if(argc==1)
    {
      printHelp();
    }
    if(strcmp(*(argv+1), "help")==0)
    {
      printHelp();
    }
    else if(strcmp(*(argv+1), "ls")==0)
    {
      showList();
    }
    else if(strcmp(*(argv+1), "del")==0)
    {
      deleteItem(*(argv+2));
    }
    else if(strcmp(*(argv+1), "add")==0)
    {
      if(argc<4)
      {
        cout<<"Error: Missing tasks string. Nothing added!";
        return 0;
      }
      addItem(*(argv+2),*(argv+3));
    }
    else if(strcmp(*(argv+1), "done")==0)
    {
      markDone(*(argv+2));
    }
    else if(strcmp(*(argv+1), "report")==0)
    {
      getReport();
    }

    // for(int i=1;i<argc;i++)
    // {
    //   cout<<*(argv+i)<<" ";
    // }
    return 0;
}
