/******************************************************************************
 * author: akhil
 * job sequencing algorithm for jobs with assosiated deadline and profit.
 *******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm> // for begin() and end().
#include <numeric> // for accumulate.
using namespace std;

struct job{
	char job_id;
	int deadline;
	int profit;
};

// for printing all the jobs.
void print_jobs(vector<job>& job_list)
{
	for(auto itr: job_list)
	{
		cout<<"job.job_id: "<<itr.job_id<<"\t";
		cout<<"job.deadline: "<<itr.deadline<<"\t";
		cout<<"job.profit: "<<itr.profit<<"\t";
		cout<<endl;
	}
}

// for getting the execution order of the jobs.
void get_job_execution_order(vector<job> job_list, int size)
{
	int curr_time=0;
	int selected_index=0;
	int max_profit;
	vector<job> ordered_jobs; // holds the selected jobs in the appropriate order.


	for(int i=0; i<job_list.size(); i++)
	{
		max_profit=0;
		bool progress= false;
		for(int j=0; j<job_list.size(); j++)
		{
			if(job_list[j].deadline>curr_time)
			{
				if(max_profit<job_list[j].profit)
				{
					selected_index=j;
					max_profit=job_list[j].profit;
					progress=true;
				}
			}
		}
		if(progress)
		{
			ordered_jobs.push_back(job_list[selected_index]);
			job_list.erase(begin(job_list)+1);
		}
		else{
			break;
		}
	}

	// end of the outer for loop.
	cout<<"number of selected jobs: "<<ordered_jobs.size()<<endl;
	cout<<"total profit: "<<accumulate(begin(ordered_jobs), end(ordered_jobs), 0, [](int total, job j)->int{return total+=j.profit;});
}


int main(void)
{
	int test_cases, num_of_jobs;
	vector<job> job_list;
	// buffer to store the job_ids.
	job buffer;

	cout<<"test_cases:"<<endl;
	cin>>test_cases;
	for(int i=0; i<test_cases; i++)
	{
		cout<<"num_of_jobs: "<<endl;
		cin>>num_of_jobs;
		// get the job details for the input.
		for(int i=0; i<num_of_jobs; i++)
		{
			cout<<"id:";
			cin>>buffer.job_id;
			cout<<"deadline: ";
			cin>>buffer.deadline;
			cout<<"profit: ";
			cin>>buffer.profit;
			job_list.push_back(buffer);
		}
		cout<<"printing jobs in the test case #"<<test_cases<<endl;
		print_jobs(job_list);
	}

	cout<<"reordering the jobs: "<<endl;
	int size= job_list.size();
	get_job_execution_order(job_list, size);
	return 0;
}