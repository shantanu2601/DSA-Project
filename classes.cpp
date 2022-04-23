#include<iostream>
#include<iomanip>
#include <ctime>
#include<vector>
#include <limits>


using namespace std;

class messager
{
		user *start;		//start pointer of user DLL
		user *last;			//pointer to last node of user DLL
	public:
		messager()
		{
			start = NULL;
			last = NULL;
		}

		bool is_empty();			//returns true if no user has created account yet
		user* accept();				//takes input required while creating a new account
		void create(); 				//creates new user account & adds it to user DLL(sign-up)
		void login();  				//to login to an existing account
		void remove(); 				//to delete your account
		void change_pw();			//to change current password
		void activity(user *ptr); 		//actions that user can perform while logged in
		msg* msg_sent(); 				//takes input to send msg, updates receiver's inbox & returns pointer to sent msg
		void send_msg(user *ptr); 		//calls msg_sent() & updates user's sent msg sll
};

class msg
{
	public:
		bool star;			//true if msg is starred
		bool sent;			//true if msg has been sent to whom the user wishes to
		bool read;			//true if msg has been read by the logged-in user
		string dt; 			//date & time when msg was sent/received
		string to;			//username of user to whom msg is sent
		string from;		        //username of user from whom msg is sent
		string text;		        //the actual message
		msg *link;

		msg()
		{
			star = false;
			sent = false;
			read = true;
			to = "";
			from = "";
			text = "";
			link = NULL;
		}
};

class user
{
	public:
		bool logged_in;
		string username;
		string password;
		msg *headS; 			//sent msg SLL head. so for each user we have a (single)linked list of sent messages
		msg *headR; 			//received msg SLL head. so for each user we also have a (single)linked list of received messages
		vector<msg*> trash;		//vector of deleted msg
		user *next;
		user *prev;
		//friend class messager;
		user()
		{
			logged_in = false;
			username = "";
			password = "";
			headS = NULL;
			headR = NULL;
			next = NULL;
			prev = NULL;
		}

		void display_msgs(string title, msg *head);				//to display list of sent/inbox msg
		void msg_options(string title, msg **head);				//actions user can perform with displayed list of msg
		void read_msg(msg *head);					        //to read a certain msg
		void del_msg(msg **head);						//to delete a certain msg
		void starUnstar_msg(msg *m);						//to mark an msg as important (star) or unstar
		void vec_read_msg(vector<msg*> results);				//to read msg from search results
		void vec_del_msg(vector<msg*> results, msg **head); 	                //to delete msg from search results
		void vec_starUnstar(vector<msg*> results); 				//to star/unstar msg from search results
		void search_msg(string title, msg **head);				//to search msg sent to/ received from a user
		void starred_msg(string title, msg **head);				//displays list of starred msg
		void trash_options();							//actions to perform on deleted msg
		void del_permanently();							//to delete a msg from trash (permanently)
		void read_trashMsg();							//to read a msg in trash

};



