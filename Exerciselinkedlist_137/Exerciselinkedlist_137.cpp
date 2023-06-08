#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;
public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** ramdhani, Node** luthfi);
    bool listEmpty();
    bool delNode(int rollno);
    void hapus();
    void traverse();
};

void CircularLinkedList::addNode() {//write here
    int no;
    string nm;
    cout << "\nEnter the roll number of student";
    cin >> no;
    cout << "\nEnter the name of the student: ";
    cin >> nm;
    Node* newnode = new Node(); /*step a.1 mengalokasikan memory untuk node baru*/
    newnode->name = nm; /*step a.2 memasukan nilai ke data field pada nodebaru*/
    newnode->rollNumber = no; /*step a.2 memasukan nilai ke data field pada nodebaru */
    /*memasukan data pada awal list*/
    if (LAST == NULL || no >= LAST->rollNumber) {
        if (LAST != NULL && no == LAST->rollNumber) {
            cout << "\nDuplicate number not allowed" << endl;
            return;
        }
        /*Bug?*/newnode->next = LAST; /*step a.3 menunjuk next newnode menunjuk dirinya sendiri*/
        if (LAST != NULL) {
            LAST->next = newnode; /*a.4 menunjuk LAST.next ke node baru*/
            LAST = newnode; /*c.5 menjadikan newnode menjadi LAST yang baru*/
            return;
        }
    }
    /*Between two nodes in the list*/
    Node* luthfi = LAST; //step b.1 menunjuk current ke last?
    Node* ramdhani = NULL; //step b.2 menunjuk previous ke nilai null
    if (luthfi->next != NULL && luthfi->next->rollNumber > no) { //b.3 repeat
        ramdhani = luthfi; //b.4 previous menjadi current
        luthfi = luthfi->next; //b.5 current point to the next node
    }
    if (luthfi->next != NULL && no == luthfi->next->rollNumber) {
        cout << "\nDuplicate number not allowed" << endl;
        return;
    }
    newnode->next = luthfi->next; //Bug?
}

bool CircularLinkedList::search(int rollno, Node** ramdhani, Node** luthfi) {
    *ramdhani = LAST->next;
    *luthfi = LAST->next;
    while (*luthfi != LAST) {
        if (rollno == (*luthfi)->rollNumber) {
            return true;
        }
        *ramdhani = *luthfi;
        *luthfi = (*luthfi)->next;
    }
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}
bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}
bool CircularLinkedList::delNode(int rollno) {//write here
    if (rollno == LAST->rollNumber) {
        return true;
    }
    Node* ramdhani, * luthfi;
    if (search(rollno, &ramdhani, &luthfi) == false) {
        return false;
    }
    if (luthfi->next != NULL) {
        luthfi->next = ramdhani;
    }
    if (ramdhani != NULL) {
        ramdhani->next = luthfi->next;
    }
    delete luthfi; //step 4
    return true;
}
void CircularLinkedList::hapus() {
    if (listEmpty()) {
        cout << "\nlist is empty" << endl;
    }
    cout << "\nEnter the roll number of the student whose record is to be delete";
    int rollNo;
    cin >> rollNo;
    cout << endl;
    if (CircularLinkedList::delNode(rollNo) == false)
        cout << "Record not found" << endl;
    else
        cout << "Record with roll number" << rollNo << " deleted" << endl;
}
void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* luthfiNode = LAST->next;
        while (luthfiNode != LAST) {
            cout << luthfiNode->rollNumber << "  " << luthfiNode->name << endl;
        }
        cout << LAST->rollNumber << "  " << LAST->name << endl;
    }
}
int main() {
	CircularLinkedList obj;
	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the record from the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your Choise (1-4): ";
			char ch;
			cin >> ch;

			switch (ch) {
			case'1':
				obj.addNode();
				break;
			case'2':
				obj.hapus();
				break;
			case'3':
				obj.traverse();
				break;
			case'4':
				return 0;
			default:
				cout << "\nInvalid Option" << endl;
				break;
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
    return 0;
}
