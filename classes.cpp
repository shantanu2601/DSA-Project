#include<iostream>
#include<iomanip>
#include <ctime>
#include<vector>
#include <limits>


using namespace std;

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

