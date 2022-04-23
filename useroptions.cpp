#include "classes.cpp"

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
