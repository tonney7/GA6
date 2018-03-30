#include <iostream>
#include <string>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
using namespace std;


//this is the structure inside each queue
struct Queue{
    string NameFirst;
    string NameLast;
    string Message;
    int daysLeft;
    int daySent;
    Queue*next;
};




//this is the class queue
class QUEUE{
private:
    Queue *Head;
public:
    QUEUE(){
        Head = nullptr;
    }
    void pop(){
        Queue * temp = Head;
        Head = temp ->next;
        temp->NameFirst = nullptr;
        temp->NameLast = nullptr;
        temp->Message = nullptr;
        temp->daysLeft = NULL;
        temp->daySent =NULL;
        temp->next = nullptr;
        delete temp;
    }
    void push(string first, string last, string message, int daysleft, int daySent){
        Queue * temp = Head;
        if (temp == nullptr){
            Queue * temp = new Queue;
            temp->NameFirst = first;
            temp->NameLast = last;
            temp->Message = message;
            temp->daysLeft = daysleft;
            temp->daySent = daySent;
            temp->next = nullptr;
            Head = temp;
        }
        else{
            while (temp->next != nullptr) {// get to position
                temp = temp->next;
            }
            temp->next = new Queue;
            temp = temp->next;
            temp->NameFirst = first;
            temp->NameLast = last;
            temp->Message = message;
            temp->daysLeft = daysleft;
            temp->daySent = daySent;
            temp->next = nullptr;
        }
    }
    void print(){
        Queue * temp = Head;
        if (temp == nullptr){}
        else{
            cout<<temp->NameFirst<<" "<<temp->NameLast<<","<<endl;
            cout<<temp->Message<<endl;
            cout<<"sent on day: "<<temp->daySent<<endl;
            cout<<endl;
            while (temp->next != nullptr) {// get to position
                temp = temp->next;
                cout<<temp->NameFirst<<" "<<temp->NameLast<<","<<endl;
                cout<<temp->Message<<endl;
                cout<<"sent on day: "<<temp->daySent<<endl;
                cout<<"day(s) left on server: "<<temp->daysLeft<<endl;
                cout<<endl;
            }
            
            
        }
    }
    void DayDecrease(){ //to decrease the number of days allowed on queue
        Queue * temp = Head;
        if (temp == nullptr){}
        else{
            temp->daysLeft -=1;
            while (temp->next != nullptr) {// get to position
                temp = temp->next;
                temp->daysLeft -=1;
            }
        }
    }
    
    
    int getDayleft(Queue * cu){ // get the amount of days left allowed on the "server"
        return cu->daysLeft;
    }
    
    
    
    
    void endofdayPop(){ //get rid of add the queue with 0 days left
        Queue * temp = Head;
        if (temp == nullptr){}
        else{
            if(getDayleft(temp) == 0 && temp->next == nullptr){
                Head = nullptr;
            }
            while (getDayleft(temp) == 0 &&temp->next != nullptr) {// get to position
                temp = temp->next;
            }
            Head = temp;
        }
    }
};





int main() {
    srand(time(0));  // Initialize random number generator.
    //r = (rand() % 10) + 1;
    
    QUEUE request;
    QUEUE Replies;
    QUEUE Errors;
    QUEUE PlainInfo;
    
    string ListFirstName[20]= {
        "AARON","BOB","BRUCE","COLUMBUS","JULIAN",
        "MICHAEL","REX","STEPHEN","ZACK","TONY",
        "MARY","DOROTHY","JENNIFER","BETTY","HELEN",
        "KATHERINE","DEBBIE","CHRISTINE","ANITA","ELLEN"
    };
    string ListLastName[15]= {
        "SMITH","GARCIA","MARTINEZ","JACKSON","GONZALEZ",
        "NGUYEN","PARKER","REED","BELL","COOPER",
        "HENDERSON","SIMMONS","HAMILTON","STEVENS","WOODS"
    };
    string ListMessages[20]{
        "Hi, I just wanted to say Hi",
        "Just wanted to comment",
        "I would like to ask for a refund",
        "can i replace this item?",
        "how do i comment?",
        "","","","","",
        "","","","","",
        "","","","",""
        //insert 15 other messages
    };
    string ErrorMessages[10]{
        "","","","","",
        "","","","",""
        //insert 10 other error messages
    };
    int RequestCounter = 0;
    int replyCounter = 0;
    int errorCounter = 0;
    int PlainInfoCounter = 0;
    int choice;
    bool autoMove = false;
    bool Move = false;
    
    //overall
    int RequestOverall = 0;
    int replyOverall = 0;
    int errorOverall = 0;
    int PlainInfoOverall = 0;
    
    
    
    
    
    
    
    
    //start of the main for loop
    for(int i = 1; i <= 31;i++){
        
        //add onto queue "throughout" the day
        //for Request
        RequestCounter = (rand() % 25) + 1;
        RequestOverall+= RequestCounter;
        for(int j = 0;j < RequestCounter;j++){
            request.push(ListFirstName[(rand() % 20)], ListLastName[(rand() % 15)], ListMessages[(rand() % 20)], 4, i);
        }
        //for reply
        replyCounter = (rand() % 25) + 1;
        replyOverall += replyCounter;
        for(int j = 0;j < replyCounter;j++){
            Replies.push(ListFirstName[(rand() % 20)], ListLastName[(rand() % 15)], ListMessages[(rand() % 20)], 0, i);
            Replies.endofdayPop();
        }
        //for error
        errorCounter = (rand() % 5) + 1;
        errorOverall += errorCounter;
        for(int j = 0;j < errorCounter;j++){
            Errors.push(ListFirstName[(rand() % 20)], ListLastName[(rand() % 15)] , ErrorMessages[(rand() % 20)], 1, i);
        }
        //for info
        PlainInfoCounter = (rand() % 25) + 1;
        PlainInfoOverall += PlainInfoCounter;
        for(int j = 0;j < PlainInfoCounter;j++){
            PlainInfo.push(ListFirstName[(rand() % 20)], ListLastName[(rand() % 15)], ListMessages[(rand() % 20)], 100, i);
        }
        
        
        
        //end of day
        
        cout<<"This marks the end of day: "<<i<<endl;
        cout<<"This is the information at the end of the day"<<endl;
        cout<<"there were a total of "<<RequestCounter<<" new requests"<<endl;
        cout<<"there were a total of "<<replyCounter<<" new Replies"<<endl;
        cout<<"there were a total of "<<errorCounter<<" new Error"<<endl;
        cout<<"there were a total of "<<PlainInfoCounter<<" new Plain Info"<<endl<<endl;
        
        //while not in automove, or have not pressed moved
        while ( !autoMove && !Move) {
            cout<<"if you want to see any information, press the appropriate number"<<endl;
            cout<<"[1]: see all request"<<endl;
            cout<<"[2]: see all replies (should be none left in queuesince deleted directly after, as instructed to)"<<endl;
            cout<<"[3]: see all Error "<<endl;
            cout<<"[4]: see all plain info "<<endl;
            cout<<"[5]: Move onto next day"<<endl;
            cout<<"[6]: auto Move through the rest of the month, although you can't access any of the information"<<endl;
            cin>>choice;
            if (choice == 6){
                autoMove = true;
            }
            else if (choice == 5){
                cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<endl;
                Move = true;
            }
            else if (choice == 4){
                PlainInfo.print();
            }
            else if (choice == 3){
                Errors.print();
            }
            else if (choice == 2){
                Replies.print();
            }
            else if (choice == 1){
                request.print();
            }
        }
        
        //reset
        Move = false;
        request.DayDecrease();
        Errors.DayDecrease();
        //no day decrease for plain info bc that doesn't change
        
        //delete those messages when days == 0;
        request.endofdayPop();
        Errors.endofdayPop();
        
        
        
    }
    cout<<"\n\n\n\n\n\n"<<endl;
    cout<<"After the month with this, the total amount is: "<<endl;
    cout<<RequestOverall<<" requests, "<< replyOverall<<" replies, "<<errorOverall<<" error messages, and "<<PlainInfoOverall<<" plain info, "<<endl;
    
    
    return 0;
}
