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
