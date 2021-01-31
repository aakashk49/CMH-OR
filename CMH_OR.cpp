#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>

using namespace std;

#define Assert(X,Y)	if(!(X)){cout<<Y;while(1);}

class Node{
	int PID;
	int num; //cardinality of Dependent Set
	bool wait;
	int engP; //Process which sent the engaging Query
public:
	Node()
	{
		PID = -1;
		num = 0;
		wait = false;
		engP = -1;
	}
	void setPID(int p){ PID = p; }
	void incNum(){ num++; }
	void decNum(){ num--; }
	int getNum(){ return num; }
	void setWait(bool b){ wait = b; }
	bool isWait(){ return wait; }
	void setEngagingProcess(int e){ engP = e; }
	int getEngP(){ return engP; }
};

class Msg{
	char msgT;
	int initiator;
	int Src;
	int Dst;
public:
	Msg(char msgType, int initiator, int Source, int Destination)
	{
		this->msgT = msgType;
		this->initiator = initiator;
		this->Src = Source;
		this->Dst = Destination;
	}
	char getMsgType(){ return msgT; }
	int getSrc(){ return Src; }
	int getDst(){ return Dst; }
};


queue<Msg> MsgQ;
vector<int>* DS; //Dependent Sets of Processes
vector<Node> P;  //Array of Processes

bool DetectDeadlock(int S)
{
	// initiator sends query msg to all processes in its dependent Set
	for (int i = 0; i < DS[S].size(); ++i)
	{
		Msg msgE('q', S, S, DS[S][i]);
		MsgQ.push(msgE);
		P[S].incNum();	//inc num for initiator
	}
	P[S].setWait(true); //set wait as true

	while (!MsgQ.empty()) //Run untill all msg are exhausted
	{
		Msg topMsg = MsgQ.front();
		int curP = topMsg.getDst();
		int msgSrc = topMsg.getSrc();
		MsgQ.pop();
		if (topMsg.getMsgType() == 'q') //if Query Msg Received
		{
			if (P[curP].isWait() == false)
			{
				//engaging Query
				//send query to all Pm in its dependent set DSk;
				for (int i = 0; i < DS[curP].size(); ++i)
				{
					Msg msgE('q', S, curP, DS[curP][i]);
					MsgQ.push(msgE);
					P[curP].incNum();
				}
				P[curP].setWait(true); //set wait as true
				Assert(P[curP].getEngP() == -1, "Already Engaged");
				P[curP].setEngagingProcess(msgSrc); //set the Process which sent Engaging Query
			}
			else
			{
				//non engaging Query
				//send a reply back
				Msg msgE('r', S, curP, msgSrc);
				MsgQ.push(msgE);
			}
		}
		else if (topMsg.getMsgType() == 'r') //if reply Msg Received
		{
			if (P[curP].isWait())
			{
				Assert(P[curP].getNum()>0,"Check Reply Msg");
				P[curP].decNum();
				if (P[curP].getNum() == 0)
				{
					if (curP == S)
						return true; //DeadLock Detected
					else
					{
						//send reply to Process which sent the Engaging Query
						Msg msgE('r', S, curP, P[curP].getEngP());
						MsgQ.push(msgE);
					}
				}
			}
		}
		else
		{
			Assert(false, "Wrong Msg Type");
		}
	}

	return false; //No Deadlock Detected
}


int main()
{
	cout << "=====Chandy-Misra-Haas Algorithm for OR Model=====" << endl;
	int n; //no of processes
	cout << "Input no of Processes: ";
	cin >> n;
	DS = new vector<int>[n+1]();
	P.resize(n + 1);
	for (int i = 0; i <= n; ++i)P[i].setPID(i);

	int m; 
	cout << "Input no of Edges in WFG: ";
	cin >> m;
	int t = m;
	while (t--)
	{
		int u, v;
		cout << "input Src,Dst: ";
		cin >> u >> v;
		Assert(u <= n&&v <= n, "Invalide Process Numbers");
		DS[u].push_back(v);
	}
	int S;
	cout << "Input initiator Node: ";
	cin >> S;
	Assert(S <= n, "Source Process shlould be less than number of Processes");
	bool bDeadLock = DetectDeadlock(S);
	if (bDeadLock)
		cout << "DeadLock Detected";
	else
		cout << "No DeadLock Detected";
	cout << endl;
	getc(stdin);
	getc(stdin);
	//system("pause");
}