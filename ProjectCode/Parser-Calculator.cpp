#include<bits/stdc++.h>
#include<iostream>
#include<utility>
#include<stack>
#include<queue>
#include<climits>
#include<cstring>
#include<cmath>


using namespace std;

#define length 500

typedef pair<char, int> pii;
typedef pair<char, int> qii;
typedef pair<char, int> rii;


stack<int>evaluationStack;      //To evaluate the postfix expression
queue<pii>QUEUE;                //To keep inputed expression with value of variables

pii postfixStrim[length];       //Queue: To keep postfix expression
rii operatorSTK[length];        //Stack: Operator stack
qii read[length];               //Array of checking duplicate

int Ans;
int value = 0;
int number;
int result;
int sCount;
int qCount;


void STACK_FUNCTION();
int OPERATION_FUNCTION(char Operator, int OP1, int OP2);
void QUEUE_FUNCTION(string A, int l);
void infixToPostfix();
void queuePrintFunction();
void postfixStrimPrintFunction();
void postfixStrimPrintFunctionTest();
void operatorSTKPrintFunction();
void inputExpression();


void STACK_FUNCTION(){
}
void expressionEvaluationStack(){
    int I1, I2;
    Ans = 0;
    if(qCount == 1){
        Ans = postfixStrim[qCount-1].second;
        evaluationStack.push(Ans);
    }
    else{
        for(int i=0; i<qCount; i++){
            if(postfixStrim[i].first == '$'){
                evaluationStack.push(postfixStrim[i].second);
            }
            else{
                I2 = evaluationStack.top();
                evaluationStack.pop();
                I1 = evaluationStack.top();
                evaluationStack.pop();
                Ans = OPERATION_FUNCTION(postfixStrim[i].first, I1, I2);
                evaluationStack.push(Ans);
            }
        }
    }
}
int OPERATION_FUNCTION(char Operator, int OP1, int OP2){
    int Total =0;
    if(Operator == '+'){
        Total = OP1+OP2;
    }
    else if(Operator == '-'){
        Total = OP1-OP2;
    }
    else if(Operator == '*'){
        Total = OP1*OP2;
    }
    else if(Operator == '/'){
        Total = OP1/OP2;
    }
    else if(Operator == '^'){
        //Total = OP1^OP2;
        Total = 1;
        for(int i=0; i<OP2; i++){
            Total *= OP1;
        }
    }
    return Total;
}
void QUEUE_FUNCTION(string A, int l){
    int i = 0;
    int j = -1;
    while(i < l){
        if(A[i]=='('){
            QUEUE.push(pii ('(', -1));
            i++;
        }
        else if(A[i]>='0' && A[i]<='9'){
            int number = 0;
            while(A[i]>='0' && A[i]<='9'){
                number *= 10;
                number += A[i]-'0';
                i++;
            }
            QUEUE.push(pii ('$', number));
        }
        else if(A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/' || A[i] == '^' || A[i] == '%'){
            if(A[i] == '+' || A[i] == '-'){
                QUEUE.push(pii (A[i], 1));
                i++;
            }
            else if(A[i] == '*'){
                QUEUE.push(pii (A[i], 2));
                i++;
            }
            else if(A[i] == '/'){
                QUEUE.push(pii (A[i], 3));
                i++;
            }
            else{                           //for '^' and '%' operator
                QUEUE.push(pii (A[i], 0));
                i++;
            }
        }
        else if((A[i]>='A'&&A[i]<='Z') || (A[i]>='a'&&A[i]<='z')){
            bool indicator = false;
            for(int k=j; k>=0; k--){
                if(A[i] == read[k].first){
                    indicator = true;
                    QUEUE.push(pii (A[i], read[k].second));
                    i++;
                }
            }
            if(!indicator){
                cout << A[i] << " =? " ;
                cin >> value;
                cout << '\n';
                j++;
                read[j].first = A[i];
                read[j].second = value;
                QUEUE.push(pii (A[i], value));
                i++;
            }
        }
        else{
            QUEUE.push(pii (')', -1));
            i++;
        }
    }
}
void infixToPostfix(){
    sCount = 0;
    qCount = 0;
    while (!QUEUE.empty()){
        if(QUEUE.front().first == '('){
            operatorSTK[sCount].first = '(';
            operatorSTK[sCount].second = -1;
            sCount++;
            QUEUE.pop();
        }
        else if(QUEUE.front().first == '+' || QUEUE.front().first == '-'){
            if(sCount == 0 || operatorSTK[sCount-1].first == '('){
                operatorSTK[sCount].first = QUEUE.front().first;
                operatorSTK[sCount].second = QUEUE.front().second;
                sCount++;
                QUEUE.pop();
            }
            else if(operatorSTK[sCount-1].first == '*' || operatorSTK[sCount-1].first == '/'){
                postfixStrim[qCount].first = operatorSTK[sCount-1].first;
                postfixStrim[qCount].second = operatorSTK[sCount-1].second;
                qCount++;
                sCount--;
            }
            else if(operatorSTK[sCount-1].first == '+' || operatorSTK[sCount-1].first == '-'){
                postfixStrim[qCount].first = operatorSTK[sCount-1].first;
                postfixStrim[qCount].second = operatorSTK[sCount-1].second;
                qCount++;
                sCount--;
            }
        }
        else if(QUEUE.front().first == '*'){
            if(sCount == 0 || operatorSTK[sCount-1].first == '('){
                operatorSTK[sCount].first = QUEUE.front().first;
                operatorSTK[sCount].second = QUEUE.front().second;
                sCount++;
                QUEUE.pop();
            }
            else if(operatorSTK[sCount-1].first == '*' || operatorSTK[sCount-1].first == '/'){
                postfixStrim[qCount].first = operatorSTK[sCount].first;
                postfixStrim[qCount].second = operatorSTK[sCount].second;
                qCount ++;
                sCount--;
            }
            else {
                operatorSTK[sCount].first = QUEUE.front().first;
                operatorSTK[sCount].second = QUEUE.front().second;
                sCount++;
                QUEUE.pop();
            }
        }
        else if(QUEUE.front().first == '/'){
            if(operatorSTK[sCount-1].first == '/'){
                postfixStrim[qCount].first = operatorSTK[sCount].first;
                postfixStrim[qCount].second = operatorSTK[sCount].second;
                qCount ++;
                sCount--;
            }
            else{
                operatorSTK[sCount].first = QUEUE.front().first;
                operatorSTK[sCount].second = QUEUE.front().second;
                sCount++;
                QUEUE.pop();
            }
        }
        else if(QUEUE.front().first == '^'){
            int power;
            int P1 = postfixStrim[qCount-1].second;
            qCount --;
            QUEUE.pop();
            int P2 = QUEUE.front().second;
            QUEUE.pop();
            int powerResult = OPERATION_FUNCTION('^', P1, P2);
            postfixStrim[qCount].first = '$';
            postfixStrim[qCount].second = powerResult;
            qCount++;
        }
        else if(QUEUE.front().first == '%'){
            int Modulus;
            int P1 = postfixStrim[qCount-1].second;
            qCount --;
            QUEUE.pop();
            int P2 = QUEUE.front().second;
            QUEUE.pop();
            int modulusResult = P1%P2;
            postfixStrim[qCount].first = '$';
            postfixStrim[qCount].second = modulusResult;
            qCount++;
        }
        else if(QUEUE.front().first == ')'){
            while(operatorSTK[sCount-1].first != '('){
                postfixStrim[qCount].first = operatorSTK[sCount-1].first;
                postfixStrim[qCount].second = operatorSTK[sCount-1].second;
                sCount--;
                qCount ++;
            }
            sCount--;
            QUEUE.pop();
        }
        else if(QUEUE.front().first >= 'A' && QUEUE.front().first <= 'Z' ||
                QUEUE.front().first >= 'a' && QUEUE.front().first <= 'z'){
            postfixStrim[qCount].first = '$';
            postfixStrim[qCount].second = QUEUE.front().second;
            QUEUE.pop();
            qCount ++;
        }
        else{
            postfixStrim[qCount].first = '$';
            postfixStrim[qCount].second = QUEUE.front().second;
            QUEUE.pop();
            qCount ++;
        }
    }
    if(QUEUE.empty()){
        while(sCount-1 >= 0){
            postfixStrim[qCount].first = operatorSTK[sCount-1].first;
            postfixStrim[qCount].second = operatorSTK[sCount-1].second;
            sCount--;
            qCount ++;
        }
    }
}
void operatorSTKPrintFunction(){
    cout << "Operator Stack is:" << endl;
    for(int j=0; j<sCount; j++){
        cout << operatorSTK[j].first << "  ";
    }
    cout<<endl;
    cout<<endl;
}
void queuePrintFunction(){
    cout << " Queue is";
    cout << '\n';
    while (!QUEUE.empty()){
        cout << ' ' <<"F: "<< QUEUE.front().first<<" , S: "<<QUEUE.front().second;
        QUEUE.pop();
        cout<<endl;
    }
    cout << '\n';
    cout << '\n';
    cout << '\n';
}
void postfixStrimPrintFunctionTest(){
    for(int i=0; i<qCount; i++){
        cout << ' ' <<"FPS: "<< postfixStrim[i].first<<" , SPS: "<<postfixStrim[i].second;
        cout << '\n';
    }
    cout << '\n';
    cout << '\n';
}
void postfixStrimPrintFunction(){
    cout << "prefixStrim is: ";
    cout << endl;
    for(int i=0; i<qCount; i++){
        if(postfixStrim[i].first == '+' || postfixStrim[i].first == '-' || postfixStrim[i].first == '*'
           || postfixStrim[i].first == '/'){
            cout << postfixStrim[i].first << " ";
           }
        else if(postfixStrim[i].first == '$'){
            cout << postfixStrim[i].second << " ";
        }
    }
    cout << '\n';
    cout << '\n';
}
void inputExpression(){
}
int main(){
    cout << " Your option: "<<endl<<"     a. Arithmetic expression."
                            <<endl<<"     b. Algebraic expression."
                            <<endl<<"     c. Scientific expression."
                            <<endl;

    cout << '\n'; cout << '\n'; cout << '\n';
    string A;
    cout << "Enter the Expression: ";
    cin >> A;
    int l = A.size();
    A[l] = '\0';
    QUEUE_FUNCTION(A, l);
    //queuePrintFunction();
    infixToPostfix();
    expressionEvaluationStack();
    cout << endl;
    cout << "Result: " << Ans;
    cout << endl;
    cout << endl;
    while(1){
        cout << "Enter the Expression: ";
        cin >> A;
        if(A == "n"){
            break;
        }
        int Position = A.find("Ans");
        if(A[0] == '+' || A[0] == '-' || A[0] == '*' || A[0] == '/' || A[0] == '^' || A[0] == '%'){
            int l = A.size();
            A[l] = '\0';
            QUEUE_FUNCTION(A, l);
            infixToPostfix();
            expressionEvaluationStack();
            cout << endl;
            cout << "Result: " << Ans;
            cout << endl;
            cout << endl;
        }
        else if(Position > -1){
            string Convert;
            string findPosition ("Ans");
            stringstream ss;
            ss << Ans;
            Convert = ss.str();
            //str.replace(str.find(str2),str2.length(),"preposition");
            A.replace(A.find(findPosition), 3, Convert);
            int l = A.size();
            A[l] = '\0';
            evaluationStack.pop();

            QUEUE_FUNCTION(A, l);
            infixToPostfix();
            expressionEvaluationStack();
            cout << endl;
            cout << "Result: " << Ans;
            cout << endl;
            cout << endl;
        }
        else{
            int l = A.size();
            A[l] = '\0';
            evaluationStack.pop();
            QUEUE_FUNCTION(A, l);
            //queuePrintFunction();
            infixToPostfix();
            expressionEvaluationStack();
            cout << endl;
            cout << "Result: " << Ans;
            cout << endl;
            cout << endl;
        }
    }
    return 0;
}
/*
a+(b*c)
a+(b+c-d+G+k*c*d-345*g+(b-c)*c-d/5)-55-39*a+v
a+(b+c-d+G+k*c*d-3*g+(b-c)*c-d/5)-5-3*a+v
((((a+(((((((b+c)-d)+G)+((k*c)*d))-(3*g))+((b-c)*c))-(d/5)))-5)-(3*a))+v)

*/



