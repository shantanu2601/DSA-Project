#include<iostream>
#include<iomanip>
#include <ctime>
#include<vector>
#include <limits>
#include "classes.cpp"
using namespace std;
//to read msg from search results or from starred msg list
void user::vec_msgread(vector<msg*> results)
{
	unsigned int no = unsigned(input("\nEnter message no. to read: "));

	if (no < 1 || no > results.size())
	{
		cout << "\nInvalid message no.";
		return;
	}

	msg *ptr = results.at(no - 1); // stores the address of the node of message to be read
	cout << "\n..................................................................";
	cout << "\n************** MESSAGE " << no << " **************";
	cout << "\nFrom : " << ptr->userfrom;
	cout << "\nTo : " << ptr->userto;
	cout << "\nWhen : " << ptr->dattime;
	cout << "\nMessage : \n" << ptr->text;
	cout << "\n...................................................................\n";
	ptr->read = true;
}

//to delete msg from search results or from starred msg list
void user::vec_msgdel(vector<msg*> results, msg **head)
{
	unsigned int no = unsigned(input("\nEnter message no. to delete: "));

	if (no < 1 || no > results.size())
	{
		cout << "\nInvalid message no.";
		return;
	}

	msg *ptr = *head;
	msg *prev = *head;

	if (results.at(no - 1) == *head) //if msg to be deleted is the first message in the msg sll
	{
		*head = (*head)->link;
		cout << "\nMessage deleted successfully!";
		trash.push_back(ptr); //put the reference of deleted message in the trash vector
		results.erase(results.begin() + no - 1); // erase the deleted message from search results list
		return;
	}
	for (ptr = *head; ptr != results.at(no - 1);)
	{
		prev = ptr;
		ptr = ptr->link;
		if (ptr == NULL)
		{
			cout << "Invalid message no.\n";
			return;
		}
	}
	//message found, now we delete it and store its reference in trash vector
	prev->link = ptr->link;
	ptr = results.at(no - 1);
	trash.push_back(ptr);
	results.erase(results.begin() + no - 1);
	cout << "Message deleted successfully!!\n";
}

//to star/unstar msg from search results
void user::vec_starUnstar(vector<msg*> results)
{
	unsigned int no = unsigned(input("\nEnter message no. to star/unstar: "));

	if (no < 1 || no > results.size())
	{
		cout << "\nInvalid message no.";
		return;
	}

	msg *ptr = results.at(no - 1);
	if (ptr->msgstar) // if message is starred, then unstar it
	{
		ptr->msgstar = false;
		cout << "Message no. " << no << " has been unstarred.\n";
	}
	else //if message is unstarred, then star it
	{
		ptr->msgstar = true;
		cout << "Message no. " << no << " has been starred.\n";
	}
}

//to search msg sent to/ received from a user
void user::msgsearch(string title, msg **head)
{
	string un;
	cout << "\nEnter the username: ";
	cin >> un;

	bool found = false;
	msg *m = *head;
	if (*head == NULL) //no messages have ever been seen from your account to any user
	{
		cout << "\nNo messages to display yet!";
		return;
	}

	string cmp;

	string A[] =  { "unread", "read" };
	string B[] =  { "unstarred", "starred" };

	int ch, i;
	do
	{
		i = 0;
		found = false;

		vector<msg*> results;
		for (m = *head; m != NULL; m = m->link)
		{
			if (title == "SENT TO ")//if we want to check sent messages to a user
				cmp = m->userto;
			else //"RECEIVED FROM "
				cmp = m->userfrom;

			if (cmp == un) //message found
			{
				if (!found)
				{
					cout<<"\n**************************** MESSAGES " <<title<< un << " ****************************";
					cout<< "\n-------------------------------------------------------------------------------------------------";
					cout<< "\n" << setw(5) << "No." << setw(15) << "From"
							<< setw(15) << "To" << setw(15) << "Message"
							<< setw(14) << "When" << setw(10) << "Status"
							<< setw(14) << "Starred";
					cout<< "\n-------------------------------------------------------------------------------------------------";

				}
				i++;
				found = true;
				results.push_back(m); //append the reference of found(searched) message to results vector

				cout << "\n" << setw(5) << i << setw(15) << m->userfrom << setw(15)
						<< m->userto << setw(15) << m->text.substr(0, 8) << "..."
						<< setw(14) << m->dattime.substr(4, 6) << setw(10)
						<< A[m->read] << setw(14) << B[m->msgstar];
				cout << "\n-------------------------------------------------------------------------------------------------";
			}
		}

		if (m == NULL && !found) //no messages sent/received to/from user
		{
			cout << "\nNo messages found!\n";
			return;
		}

		cout << "\n********* MESSAGE OPTIONS **********";
		cout << "\n0. Exit";
		cout << "\n1. Read a message";
		cout << "\n2. Delete a message";
		cout << "\n3. Star/Unstar a message";
		ch = input("\nEnter your choice: ");
		cout << "\n---------------------------------------------";

		switch (ch)
		{
			case 0:
				break;

			case 1:
				vec_msgread(results);
				break;

			case 2:
				vec_msgdel(results, head);
				break;

			case 3:
				vec_starUnstar(results);
				break;
		}
	} while (ch != 0);
}

//displays list of starred msg
void user::strmsg(string title, msg **head)
{

	string R[] = { "unread", "read" };
	string S[] = { "unstarred", "starred" };

	msg *m = *head; //pointer to the first node of sent/received msg sll for current user
	if (head == NULL)
	{
		cout << "\nNo messages to display yet!"; // no sent/received messages
		return;
	}

	int ch, i;
	bool found;
	vector<msg*> results;
	do
	{
		i = 0;
		found = false;
		vector<msg*> results;

		for (m = *head; m != NULL; m = m->link)
		{

			if (m->msgstar == true)
			{

				if (!found)
				{
					cout << "\n**************************** STARRED MESSAGES IN "<< title << " ****************************";
					cout << "\n-------------------------------------------------------------------------------------------------";
					cout << "\n" << setw(5) << "No." << setw(15) << "From"
							<< setw(15) << "To" << setw(15) << "Message"
							<< setw(14) << "When" << setw(10) << "Status"
							<< setw(14) << "Starred";
					cout << "\n-------------------------------------------------------------------------------------------------";
				}
				i++;
				found = true;
				results.push_back(m); // adds the address of found(starred) msg to results vector

				cout << "\n" << setw(5) << i << setw(15) << m->userfrom << setw(15)
						<< m->userto << setw(15) << m->text.substr(0, 8) << "..."
						<< setw(14) << m->dattime.substr(4, 6) << setw(10)
						<< R[m->read] << setw(14) << S[m->msgstar];
				cout << "\n-------------------------------------------------------------------------------------------------";
			}
		}

		if (m == NULL && !found) //no starred message present
		{
			cout << "\nNo messages found!\n";
			return;
		}

		cout << "\n********* MESSAGE OPTIONS **********";
		cout << "\n0. Exit";
		cout << "\n1. Read a message";
		cout << "\n2. Delete a message";
		cout << "\n3. Star/Unstar a message";
		ch = input("\nEnter your choice: ");
		cout << "\n---------------------------------------------";

		switch (ch)
		{
			case 0:
				break;

			case 1:
				vec_msgread(results); //to read a starred message
				break;

			case 2:
				vec_msgdel(results, head); // to delete a starred message
				break;

			case 3:
				vec_starUnstar(results); // to unstar a starred message
				break;
		}
	} while (ch != 0);

}
