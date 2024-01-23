#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<cmath>

using namespace std;

struct Process {
	int id = 0, priority = 0, arrivaltime = 0, bursttime = 0, memorysize = 0, turnaroundtime = 0, waitingtime = 0;
	string state, iointerrupt;
};
void createprocess(Process& process)
{
	cout << "Enter ID: "; cin >> process.id;
	cout << "Enter Priority: "; cin >> process.priority;
	cout << "Enter Arrival Time: "; cin >> process.arrivaltime;
	cout << "Enter Burst Time: "; cin >> process.bursttime;
	cout << "Enter Memory Size: "; cin >> process.memorysize;
	cout << "Is this process need an I/O resources? (yes,no) "; cin >> process.iointerrupt;
	
	cout << "\n************** Process Successfully Created!! ****************" << endl;
	if (process.iointerrupt == "yes")
	{
		process.state = "Block";
	}
	else
	{
		process.state = "Ready";
	}
}
void editprocess(Process& process)
{
	int idd;
	cout << "Enter the ID of the process to edit: ";
	cin >> idd;
	if (process.id == idd)
	{
		cout << "Enter Priority: "; cin >> process.priority;
		cout << "Enter Arrival Time: "; cin >> process.arrivaltime;
		cout << "Enter Burst Time: "; cin >> process.bursttime;
		cout << "Enter Memory Size: "; cin >> process.memorysize;
		cout << "Is this process still need an I/O resources? (yes,no) "; cin >> process.iointerrupt;
		if (process.iointerrupt == "yes")
		{
			process.state = "Block";
		}
		else
		{
			process.state = "Running";
		}
		cout << "\n************** Successfully Saved!! ****************" << endl;
	}
	else
	{
		cout << "\n************** No such input found!! Invalid ID!! ****************" << endl;
	}
}

//////////////////////////////////////////////////////////////////////// FCFS
void calculateTimes(vector<Process>& processes)
{
	int currentTime = 0;
	float totalTurnaroundTime = 0, totalWaitingTime = 0;

	cout << "\nGantt Chart:\n";
	for (const Process& process : processes) {
		cout << "P" << process.id << " ";
	}
	cout << endl;

	for (int i = 0; i < processes.size(); i++) {
		Process& currentProcess = processes[i];
		currentProcess.waitingtime = currentTime - currentProcess.arrivaltime;
		if (currentProcess.waitingtime < 0) {
			currentProcess.waitingtime = 0;
		}      //current process AT - total BT
		currentTime = max(currentTime, currentProcess.arrivaltime);
		currentTime += currentProcess.bursttime;
		currentProcess.turnaroundtime = currentTime - currentProcess.arrivaltime;
		    // TAT= BT-AT
		totalTurnaroundTime += currentProcess.turnaroundtime;
		totalWaitingTime += currentProcess.waitingtime;
		currentProcess.state = "Completed";
	}

	float avgTurnaroundTime = totalTurnaroundTime / processes.size();
	float avgWaitingTime = totalWaitingTime / processes.size();

	cout << "\nProcess Details:\n";
	cout << "ID\tPriority\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";
	for (const Process& process : processes) {
		cout << process.id << "\t" << process.priority << "\t\t" << process.arrivaltime
			<< "\t\t" << process.bursttime << "\t\t" << process.turnaroundtime
			<< "\t\t" << process.waitingtime << endl;
	}
	cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTurnaroundTime << endl;
	cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWaitingTime << endl;
}
void fcfs(vector<Process>& processes)
{
	sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
		return p1.arrivaltime < p2.arrivaltime;
		});

	calculateTimes(processes);
}


////////////////////////////////////////////////////////////  SJF
bool compareBybursttime(const Process& p1, const Process& p2)
{
	return p1.bursttime < p2.bursttime;
}
void sjf(vector<Process>& processes) {
	//int n = processes.size();
	int currentTime = 0;
	float totalwaitingtime = 0, totalturnaroundtime = 0;

	sort(processes.begin(), processes.end(), compareBybursttime);

	cout << "\nGantt Chart:\n";
	for (const Process& process : processes) {
		cout << "P" << process.id << " ";
	}
	cout << endl;

	for (int i = 0; i < processes.size(); i++) {
		Process& currentProcess = processes[i];
		currentProcess.waitingtime = currentTime;
		currentTime += currentProcess.bursttime;
		currentProcess.turnaroundtime = currentTime;

		totalwaitingtime += currentProcess.waitingtime;
		totalturnaroundtime += currentProcess.turnaroundtime;
	}

	float avgwaitingtime = totalwaitingtime / processes.size();
	float avgturnaroundtime = totalturnaroundtime / processes.size();

	cout << "\nProcess Details:\n";
	cout << "ID\tPriority\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";
	for (const Process& process : processes) 
	{
		cout << process.id << "\t" << process.priority << "\t\t" << process.arrivaltime
			<< "\t\t" << process.bursttime << "\t\t" << process.turnaroundtime
			<< "\t\t" << process.waitingtime << endl;
	}

	cout << "\nAverage Waiting Time: " << avgwaitingtime << endl;
	cout << "Average Turnaround Time: " << avgturnaroundtime << endl;
}

//////////////////////////////////////////////////////////////////////// State
void displayprocessstates(const vector<Process>& processes) 
{
	cout << "\nProcess States:\n";
	for (const Process& process : processes)
	{
		cout << "ID: " << process.id << "  State: " << process.state << endl;
	}
}
void mainmenu();
void processmanagement()
{
	vector<Process> processes;
	Process process;
	int choice=0;
	do
	{
		cout << "\n1. Create Process" << endl;
		cout << "2. Edit Process" << endl;
		cout << "3. FCFS Scheduling" << endl;
		cout << "4. SJF Scheduling" << endl;
		cout << "5. Process State" << endl;
		cout << "6. Back to Main Menu" << endl;
		cout << "\nChoose Option: "; cin >> choice;
		switch (choice)
		{
		case 1:
			createprocess(process);
			processes.push_back(process);
			break;
		case 2:
			editprocess(process);
			break;
		case 3:
			fcfs(processes);
			break;
		case 4:
			sjf(processes);
			break;
		case 5:
			displayprocessstates(processes);
			break;
		case 6:
			mainmenu();
			break;
		case 7:
			cout << "\n************** Exiting the Program!! ****************" << endl;
		default:
			cout << "Invalid!! Wrong Input!!" << endl;
		}
	} while (choice != 7);
}


void memorymanagement()
{
	int id = 0, at = 0, bt = 0, ms = 0, framesize = 4;
	double numpage = 0;
	cout << "Enter id: "; cin >> id;
	cout << "Enter arrival time: "; cin >> at;
	cout << "Enter burst time: "; cin >> bt;
	cout << "Enter memory size: "; cin >> ms;
	numpage = ms / framesize;
	cout << "Number of Pages: " << ceil(numpage) << endl;
}
	

void iomanagement()
{
	cout << "It is defined during creating a process" << endl;
}
void otheroperations()
{
	cout << "GoodBye!!" << endl;

}



void mainmenu()
{
	int option = 0;
	vector<Process> processes;
	do
	{
		cout << "\n\n******************************* Main Menu ******************************\n\n" << endl;
		cout << " 1. Process Management" << endl;
		cout << " 2. Memory Management" << endl;
		cout << " 3. I/O Management" << endl;
		cout << " 4. Other Operations" << endl;
		cout << "Enter option : ";
		cin >> option;
		if (option <= 0  || option >= char(97))
		{
			cout << "Invalid input!!" << endl;
		}
		else
		{
			switch (option)
			{
			case 1:
			{
				processmanagement();
				break;
			}
			case 2:
			{
				memorymanagement();
				break;
			}
			case 3:
			{
				iomanagement();
				break;
			}
			case 4:
			{
				otheroperations();
				break;
			}
			case 5:
				cout << "Exit" << endl;
			}
		}
		} while (option != 5);
	
}

int main()
{
	mainmenu();
	system("pause");
	return 0;
}