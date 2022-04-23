// we have 2 single linked list(declared in msg class): one for storing user's sent messages, and one for user's received messages
// we have 1 doubly linked list: for storing the list of users
#include<iostream>
#include<iomanip>
#include <ctime>
#include<vector>
#include <limits>

using namespace std;

//to deal with bad input
int input(string prompt)
{
	int inp;
	cout << prompt;
	cin >> inp;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nInput is invalid.Please try again. \n" << prompt;
		cin >> inp;
	}
	return inp;
}

//node for sent & received msg SLLs
class msg
{
	public:
		bool msgstar;			//true if msg is starred
		bool sent;			//true if msg has been sent to whom the user wishes to
		bool read;			//true if msg has been read by the logged-in user
		string dattime; 			//date & time when msg was sent/received
		string userto;			//username of user to whom msg is sent
		string userfrom;		        //username of user from whom msg is sent
		string text;		        //the actual message
		msg *link;

		msg()
		{
			msgstar = false;
			sent = false;
			read = true;
			userto = "";
			userfrom = "";
			text = "";
			link = NULL;
		}
};

//node for user DLL
class user
{
	public:
		bool loggedin;
		string username;
		string password;
		msg *head2; 			//Singly Linked List for sent messages. so for each user we have a (single)linked list of sent messages
		msg *head1; 			//Singly linked List for reciever messages. so for each user we also have a (single)linked list of received messages
		vector<msg*> trash;		//vector of deleted msg
		user *next;
		user *prev;
		//friend class messager;
		user()
		{
			loggedin = false;
			username = "";
			password = "";
			head2 = NULL;
			head1 = NULL;
			next = NULL;
			prev = NULL;
		}

		void displaymsg(string title, msg *head);				//to display list of sent/inbox msg
		void useroptions(string title, msg **head);				//actions user can perform with displayed list of msg
		void msgread(msg *head);					        //to read a certain msg
		void msgdel(msg **head);						//to delete a certain msg
		void starunstarr(msg *m);						//to mark an msg as important (star) or unstar
		void vec_msgread(vector<msg*> results);				//to read msg from search results
		void vec_msgdel(vector<msg*> results, msg **head); 	                //to delete msg from search results
		void vec_starUnstar(vector<msg*> results); 				//to star/unstar msg from search results
		void msgsearch(string title, msg **head);				//to search msg sent to/ received from a user
		void strmsg(string title, msg **head);				//displays list of starred msg
		void deloptions();							//actions to perform on deleted msg
		void permdelete();							//to delete a msg from trash (permanently)
		void trashread();							//to read a msg in trash

};

//To display received/sent messages
void user::displaymsg(string title, msg *head)
{
	string A[] = { "unread", "read" };
	string B[] = { "unstarred", "starred" };
	cout <<"\n******************************* " <<title<< " *******************************";

	if (head == NULL)
		cout << "\nNo messages to display yet!\n";

	else
	{
		int i = 1;
		cout << "\n-------------------------------------------------------------------------------------------------"; //creates a table displaying sent messages
		cout << "\n" << setw(5) << "No." << setw(15) << "From" << setw(15)
				<< "To" << setw(15) << "Message" << setw(14) << "When"
				<< setw(10) << "Status" << setw(14) << "Starred";
		cout << "\n-------------------------------------------------------------------------------------------------"; //setw is a function used to setwidth, for example setw(15)

		msg *m = head;
		while (m != NULL)
		{
			cout << "\n" << setw(5) << i << setw(15) << m->userfrom << setw(15)
					<< m->userto << setw(15) << m->text.substr(0, 8) << "..."
					<< setw(14) << m->dattime.substr(4, 6) << setw(10) << A[m->read]
					<< setw(14) << B[m->msgstar];
			cout << "\n-------------------------------------------------------------------------------------------------"; //performs all the functionalities such as m->star etc for each particular sent message.
			m = m->link;
			i++; 
		}
	}
}

//Is only displayed if there are received/sent messages in the table.
void user::useroptions(string title, msg **head)
{
	int ch;
	do
	{
		displaymsg(title, *head); //different functionalities for the received/sent messages in the table.
		if (*head == NULL)
			return;
		cout << "\n********* " << title << " OPTIONS **********";
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
				msgread(*head);
				break;

			case 2:
				msgdel(head);
				break;

			case 3:
				starunstarr(*head);
				break;
		}
	} while (ch != 0);
}

//To read a particular message
void user::msgread(msg *head)
{
	int no;
	no = input("\nEnter message no. to read: ");
	if (no < 1)
	{
		cout << "\nInvalid message no.";
		return;
	}
	msg *ptr = head;
	for (int i = 1; i < no; i++)
	{
		ptr = ptr->link;
		if (ptr == NULL)
		{
			cout << "\nInvalid message no.";
			return;
		}
	}
	cout << "\n..................................................................";
	cout << "\n************** MESSAGE " << no << " **************";
	cout << "\nFrom : " << ptr->userfrom;
	cout << "\nTo : " << ptr->userto;
	cout << "\nWhen : " << ptr->dattime;
	cout << "\nMessage : \n" << ptr->text;
	cout << "\n...................................................................\n";
	ptr->read = true;
}

//To delete a particular valid message and add it to trash.
void user::msgdel(msg **head)
{
	if (*head == NULL)
	{
		cout << "No messages found.\n";
		return;
	}

	int no = input("\nEnter message no. to delete: ");

	if (no < 1)
	{
		cout << "\nInvalid message no.";
		return;
	}

	msg *ptr = *head;
	msg *prev = *head;
	if (no == 1) //if message to be deleted is the first message
	{
		*head = (*head)->link; 
		cout << "Message deleted successfully!!\n";
		trash.push_back(ptr);
		return;
	}

	for (int i = 1; i < no; i++)
	{
		prev = ptr;
		ptr = ptr->link;
		if (ptr == NULL)
		{
			cout << "Invalid message no.\n";
			return;
		}
	}
	prev->link = ptr->link;      //points the previous message to the current messages next message.
	trash.push_back(ptr);        //deletes the message where pointer currently lies.
	cout << "Message deleted successfully!!\n";
}

//To star or unstar a message,i.e to mark a message as important, or remove that mark. 
void user::starunstarr(msg *head)
{
	int no = input("\nEnter message no. to star/unstar: ");

	if (no < 1)
	{
		cout << "\nInvalid message no.";
		return;
	}
	msg *ptr = head;
	for (int i = 1; i < no; i++)
	{
		ptr = ptr->link;
		if (ptr == NULL)
		{
			cout << "\nInvalid message no.";
			return;
		}
	}
	if (ptr->msgstar == false)
	{
		ptr->msgstar = true;
		cout << "Message no. " << no << " has been starred.\n";
	}
	else
	{
		ptr->msgstar = false;
		cout << "Message no. " << no << " has been unstarred.\n";
	}
}

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
			if (title == "SENT TO ")   //if we want to check sent messages to a user
				cmp = m->userto;
			else (title == "RECIEVED FROM") //"RECEIVED FROM "
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

//actions to perform on deleted msg
void user::deloptions()
{
	int ch;
	do
	{
		string A[] = { "unread", "read" };
		string B[] = { "unstarred", "starred" };
		if (this->trash.size() == 0)
		{
			cout << "Trash empty\n";
			return;
		}
		cout<< "\n******************************* TRASH *******************************";
		cout<< "\n-------------------------------------------------------------------------------------------------";
		cout << "\n" << setw(5) << "No." << setw(15) << "From" << setw(15) << "To"
				<< setw(15) << "Message" << setw(14) << "When" << setw(10)
				<< "Status" << setw(14) << "Starred";
		cout<< "\n-------------------------------------------------------------------------------------------------";

		for (unsigned int i = 0; i < this->trash.size(); i++)
		{
			msg *m = this->trash[i]; //gets the address of the i'th deleted message for the current user
			cout << "\n" << setw(5) << i+1 << setw(15) << m->userfrom << setw(15)
								<< m->userto << setw(15) << m->text.substr(0, 8) << "..."
								<< setw(14) << m->dattime.substr(4, 6) << setw(10) << A[m->read]<< setw(14) << B[m->msgstar];
			cout << "\n-------------------------------------------------------------------------------------------------";
		}

		cout << "\n********* TRASH OPTIONS **********";
		cout << "\n0. Exit";
		cout << "\n1. Delete a message permanently";
		cout << "\n2. View a message";
		ch = input("\nEnter your choice: ");
		cout << "\n---------------------------------------------";

		switch (ch)
		{
			case 0:
				break;

			case 1:
				permdelete();
				break;

			case 2:
				trashread();
				break;
		}
	} while (ch != 0);
}

//to delete a msg from trash (permanently)
void user::permdelete()
{
	unsigned int no = unsigned(input("\nEnter message no. to delete: "));
	if (no > trash.size() || no < 1)
	{
		cout << "Invalid message no.\n";
		return;
	}

	msg *m = trash[no - 1]; //we get the address of message to be deleted permanently
	trash.erase(trash.begin() + no - 1); //we delete the reference from the trash vector
	cout << "Message permanently deleted\n";
	delete m; //we delete the reference and free the memory
}

//to read a msg in trash
void user::trashread()
{
	unsigned int no = unsigned(input("\nEnter message no. to read: "));

	if (no < 1 || no > trash.size())
	{
		cout << "\nInvalid message no.";
		return;
	}

	cout << "\n..................................................................";
	cout << "\n************** MESSAGE " << no << " **************";
	cout << "\nFrom : " << trash[no - 1]->userfrom;
	cout << "\nTo : " << trash[no - 1]->userto;
	cout << "\nWhen : " << trash[no - 1]->dattime;
	cout << "\nMessage : \n" << trash[no - 1]->text;
	cout << "\n...................................................................\n";
	trash[no - 1]->read = true;
}

class mailingclone
{
		user *first;		        //start pointer of user DLL
		user *end;			//pointer to last node of user DLL
	public:
		mailingclone()
		{
			first = NULL;
			end = NULL;
		}

		bool noaccount();			//returns true if no user has created account yet
		user* inputacc();				//takes input required while creating a new account
		void acclogin();  				//to login to an existing account
		void delacc(); 				//to delete your account
		void pswchange();			//to change current password
		void useractions(user *n); 		//actions that user can perform while logged in
		void newaccount(); 				//creates new user account & adds it to user DLL(sign-up)
		msg* sendmessage(); 				//takes input to send msg, updates receiver's inbox & returns pointer to sent msg
		void sendmsgfunc(user *n); 		//calls msg_sent() & updates user's sent msg sll
};

//returns true if no user has created account yet
bool mailingclone::noaccount()
{
	if (first == NULL)
		return true;
	else
		return false;
}

//takes input required while creating a new account
user* mailingclone::inputacc()
{
	bool un_exist = false;
	user *m = new user(); //new user node
	user *n;
	do
	{
		n = first;
		cout << "\nEnter username to create : ";
		cin >> m->username;
		while (n != NULL)
		{
			if (n->username == m->username)
			{
				cout << "\nEntered username already exists.";
				un_exist = true;
				break;
			}
			n = n->next;
		}
		if (n == NULL)
			un_exist = false;
	} while (un_exist); // repeat till username isn't unique
	cout << "\nCreate password: ";
	cin >> m->password;
	return m;
}

//creates new user account & adds it to user dll(sign-up)
void mailingclone::newaccount()
{
	user *m = inputacc(); //accepts new username and password
	if (noaccount()) //checks if user linked list is empty
	{
		first = m;
		end = m;
	}
	else
	{
		end->next = m;
		m->prev = end;
		end = m;
	}
	cout << "\nYour account has been created successfully!";
}

//to login to an existing account
void mailingclone::acclogin()
{
	string usrnm, pass;
	cout << "\nEnter username: ";
	cin >> usrnm;
	for (user *n = first; n != NULL; n = n->next) //search for username in the user linked list
	{
		if (n->username == usrnm)
		{
			cout << "\nEnter password: ";
			cin >> pass;
			if (n->password == pass)
			{ // n is the node of the found user
				n->loggedin = true; //if username and password is correct then log in
				cout << "\nSuccessfully logged in.";
				useractions(n); //displays the next set of instructions the user can perform
				return;
			}
			else
			{
				cout << "\nIncorrect password. Try again.";
				return;
			}
		}
	}
	cout << "\nUsername not found.";
}

//to delete your account //removes n from user dll
void mailingclone::delacc()
{
	char ch;
	string usrnm, pass;

	cout << "\nEnter username: ";
	cin >> usrnm;

	if (noaccount())
		cout << "\nCurrently no user accounts exist.";

	for (user *exst = first; exst != NULL; exst = exst->next)
	{
		if (exst->username == usrnm)
		{
			cout << "\nEnter the password: ";
			cin >> pass;

			if (exst->password == pass)
			{
				do
				{
					cout << "Are you sure you want to delete your account?(Y/N): ";
					cin >> ch;
					if (ch == 'N') return;
					else if (ch == 'Y') break;
					else cout << "\nInvalid choice. Try again.";
				} while (ch != 'Y' || ch != 'N');

				//if start node
				if (exst == first)
					first = exst->next;

				//if curr is not last node
				if (exst->next != NULL)
					(exst->next)->prev = exst->prev;

				//if curr is not 1st node
				if (exst->prev != NULL)
					(exst->prev)->next = exst->next;

				delete exst;
				cout << "\nYour account has been deleted successfully!";
				return;
			}
			else
			{
				cout << "\nIncorrect password....please try again.";
				return;
			}
		}
	}
	cout << "\nUsername not found.";
}

//to change current password
void mailingclone::pswchange()
{
	string usrnm, pass, pass1;
	cout << "\nEnter username: ";
	cin >> usrnm;

	for (user *n = first; n != NULL; n = n->next)
	{
		if (n->username == usrnm)
		{
			do
			{
				cout << "\nEnter previous password: ";
				cin >> pass;
				if (n->password == pass)
				{
					cout << "\nEnter new password : ";
					cin >> pass1;
					n->password = pass1;

					cout << "\nYour password has been changed successfully!";
					return;
				}
				else
					cout << "\nIncorrect previous password.\n";
			} while (true);
		}
	}
	cout << "\nUsername not found.";
}

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
