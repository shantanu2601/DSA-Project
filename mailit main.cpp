#include<iostream>
#include<iomanip>
#include <ctime>
#include<vector>
#include <limits>
#include "classes.cpp"
#include "logincheck.cpp"
#include "useroptions.cpp"
#include "deleteoptions.cpp"
#include "starrfunctions.cpp"
using namespace std;


//actions that user can perform while logged in
void mailingclone::useractions(user *n)
{ //ptr contains the current(logged in) user information
	int i;
	do
	{
		cout << "\n************* HELLO @"<< n->username<< "! WELCOME TO MAILIT! *************";
		cout << "\n0. Logout of your account";
		cout << "\n1. Check inbox messages";
		cout << "\n2. Send a message";
		cout << "\n3. View sent messages";
		cout << "\n4. Search messages sent to an user";
		cout << "\n5. Search messages received from an user";
		cout << "\n6. View deleted messages";
		cout << "\n7. View starred messages in Inbox";
		cout << "\n8. View starred messages in Sentbox";
		i = input("\nEnter your choice: ");
		cout << "\n------------------------------------------\n";

		switch (i)
		{
			case 0:
				n->loggedin = false;
				cout << "\nSuccessfully logged out.";
				return;

			case 1:
				n->useroptions("INBOX", &n->head1);
				break;

			case 2:
				sendmsgfunc(n);
				break;

			case 3:
				n->useroptions("SENT", &n->head2);
				break;

			case 4:
				n->msgsearch("SENT TO ", &n->head2);
				break;

			case 5:
				n->msgsearch("RECEIVED FROM ", &n->head1);
				break;

			case 6:
				n->deloptions();
				break;

			case 7:
				n->strmsg("INBOX ", &n->head1); //sends the head of the received msgs sll for current user
				break;

			case 8:
				n->strmsg("SENTBOX ", &n->head2); ////sends the head of the sent msgs sll for current user
				break;

			default:
				cout << "\nInvalid choice";
		}

	} while (i != 0);
}

//takes input to send msg, updates receiver's inbox & returns pointer to sent msg
msg* mailingclone::sendmessage()
{
	msg *messg = new msg(); // new node of msg linked list
	user *msgptr; 				//pointer To whom user is sending msg
	bool userexist = false;		// stays false till user enters a correct username to which msg is sent
	do
	{
		cout << "Enter username of user to message : ";
		cin >> messg->userto;
		getchar(); //'\n'

		//updating receiver's received msg sll
		for (msgptr = first; msgptr != NULL; msgptr = msgptr->next) //search for username in user dll
		{
			if (msgptr->username == messg->userto)
			{
				cout << "\nEnter message you want to send to @" <<messg->userto<< " :\n";
				getline(cin, messg->text); //took input msg and stored at m->text

				messg->read = false;
				time_t now = time(0); 		// current date/time based on current system
				messg->dattime = ctime(&now);		// convert now to string form
				userexist = true;			// made true since username is now found
				cout << "\nMessage sent successfully to @" << messg->userto;

				//insert new msg at beginning of ptrT's received msg sll
				messg->link = msgptr->head1;
				msgptr->head1 = messg;
				return messg;
			}
		}

		if (msgptr == NULL) //!un_exist
			cout << "\nEntered username doesn't exist.\n";

	} while (userexist == false);
	return messg;
}

//calls msg_sent() & updates user's sent msg sll
void mailingclone::sendmsgfunc(user *ptr)
{
	msg *ms = sendmessage(); 		//pointer to sent msg
	ms->userfrom = ptr->username;

	//updating sender's (logged-in user's) sent msg sll
	msg *m = new msg();			//create new msg to update user's sent msgs sll
	m->sent = true;
	m->read = false;
	m->userto = ms->userto;
	m->userfrom = ms->userfrom;
	m->dattime = ms->dattime;
	m->text = ms->text;

	//insert sent msg at beginning of sent sll
	m->link = ptr->head2;
	ptr->head2 = m;
}
int main()
{
	int ch;
	mailingclone A;
	do
	{
		cout << "\n----------------------------------------";
		cout << "\n******** WELCOME TO MAILIT! **********";
		cout << "\n0. Exit application";
		cout << "\n1. Create a new mailit account";
		cout << "\n2. Login to your existing mailit account";
		cout << "\n3. Delete an existing account";
		cout << "\n4. Change Password";
		ch = input("\nEnter your choice: ");
		cout << "\n----------------------------------------";

		switch (ch)
		{
			case 0:
				cout << "\n********* PROGRAM ENDED **********";
				break;

			case 1:
				A.newaccount();
				break;

			case 2:
				A.acclogin();
				break;

			case 3:
				A.delacc();
				break;

			case 4:
				A.pswchange();
				break;
			default:
				cout << "\nInvalid choice";
		}

	} while (ch != 0);
	return 0;
}
