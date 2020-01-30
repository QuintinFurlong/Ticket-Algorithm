#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>

using namespace std;

const int n = 4;
int newTicket;
int currentOrder;
int activeOrders[n];
int numThreads;
mutex coutMutex;

ostringstream data;

void func() 
{
	int i = numThreads++;

	coutMutex.lock();
	cout << "Thread number " << i << "." << endl;
	coutMutex.unlock();

	this_thread::sleep_for(chrono::seconds(1));

	while (true)
	{
		activeOrders[i] = newTicket;
		newTicket++;
		
		coutMutex.lock();
		cout << "thread number " << i << ".\torder number : " << activeOrders[i] << endl;
		cout << endl;
		coutMutex.unlock();

		this_thread::sleep_for(chrono::seconds(1));

		while (activeOrders[i] != currentOrder)
		{
			continue;
		}

		coutMutex.lock();
		cout << "thread number " << i << "\tnow being served order number : " << activeOrders[i] << endl;
		coutMutex.unlock();

		currentOrder++;;

		coutMutex.lock();
		cout << "next order is " << currentOrder << endl;
		coutMutex.unlock();
	}
}


int main()
{
	srand(time(NULL));

	numThreads = 0;
	newTicket = 1;
	currentOrder = 1;
	for (int i = 0; i < n; i++)
	{
		activeOrders[i] = 0;
	}

	thread t1 = thread(func);
	thread t2 = thread(func);
	thread t3 = thread(func);
	thread t4 = thread(func);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}