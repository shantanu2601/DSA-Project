// we have 2 single linked list(declared in msg class): one for storing user's sent messages, and one for user's received messages
// we have 1 doubly linked list: for storing the list of users
#include "classes.cpp"

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
