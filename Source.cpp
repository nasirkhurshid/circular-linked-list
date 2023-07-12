#include <iostream>
using namespace std;

template <typename T>				//structre for linked list implementation
struct node {
	T data;
	node<T>* next;
};

template <typename T>
class list {						//list class defination
	node<T>* ptr, * it;				//ptr as head pointer, it as iterator, n and count as no. of elements
	int n, count;
public:
	list() {					//constructor 
		ptr = NULL;
		it = NULL;
		n = 0;
	}
	list(const list<T>& li) {		//copy constructor
		operator = (li);			//calling = operator for copying data
	}
	void operator = (const list<T>& li) {		// = operator overloading
		if (!empty()) {							//if list is not empty then making it empty
			makeempty();
		}
		node<T>* temp;							//taking a temporary pointer for copying datat
		temp = li.ptr->next;					//pointing temp to first node
		it = NULL; 
		for (int i = 0; i < li.n; i++) {		//copying data into new list
			insert(temp->data);					//using for loop
			temp = temp->next;
		}
	}
	~list() {									//destructor
		makeempty();
	}
	void insert(const T& val) {					//function for inserting data into list
		node<T>* temp;				//pointer of node type
		temp = new node<T>;			//allocating new memory
		temp->data = val;			//storing value in data type
		if (ptr == NULL) {			//if queue is empty
			temp->next = temp;		//then pointing temp to itself
			ptr = temp;				//and assigning temp to ptr
		}
		else {
			temp->next = ptr->next;		//else storing first node to new node
			ptr->next = temp;			//new node to previous node
			ptr = temp;					//and new node to ptr
		}
		n++;
	}
	bool find(const T& val) {			//function for finding data
		node<T>* temp;
		temp = ptr;						//pointing temp to ptr
		while (temp != NULL) {			//and checking each elements data using while loop
			if (temp->data == val) {	//if found 
				return true;			//returning true
			}
			temp = temp->next;			//else moving temp forward
			if (temp == ptr) {			//breaking loop when last node reached
				break;
			}
		}
		return false;
	}
	bool update(const T& oldval, const T& newval) {			//function for updating data
		if (erase(oldval)) {						//if old data found and erased
			insert(newval);							//then inserting new data
			return true;							//and return true
		}
		else {										//else returning false
			return false;
		}
	}
	bool erase(const T& val) {					//function for erasing data
		node<T>* temp, * del;
		temp = ptr;								//pointing temp to ptr
		if (ptr->data == val) {					//checking data at ptr, if equal to the data to be removed
			while (temp != NULL) {				//then using while loop to access the previous memory
				temp = temp->next;
				if (temp->next == ptr) {		//and when accessed , breaking the loop
					break;
				}
			}
			del = ptr;							//deleting the ptr node after storing it in del
			temp->next = del->next;				//and moving ptr to previous node
			ptr = temp;
			delete del;
			n--;
			return true;
		}
		else {										//if data in ptr is not required data
			while (temp->next != ptr) {				//then checking from first node
				if (temp->next->data == val) {		//and if found
					del = temp->next;				//then connecting previous node to next node
					temp->next = del->next;			//and deleting current node (containing required data)
					delete del;
					n--;
					return true;
				}
				temp = temp->next;
			}
		}
		return false;
	}
	bool full() {						//function for checking whether list is full or not
		node<T>* temp;					//checking by creating a new memory
		temp = new node<T>;				//if new memory is not created 
		if (temp == NULL) {				//then returning
			return true;				//true
		}
		else {							//else deleting new memory
			delete temp;				//and returning
			return false;				//false
		}
	}
	bool empty() {						//function for checking whether the list is empty or not
		return ptr == NULL;				//if ptr == NULL then list is empty
	}
	void makeempty() {					//function for making list empty
		node<T>* temp, *del;			//using temporary pointers
		temp = ptr;						//to delete the
		while (!empty()) {				//nodes one by one
			while (temp != NULL) {		//until the list is
				temp = temp->next;		//empty
				if (temp->next == ptr) {
					break;
				}
			}
			if (temp == temp->next) {			//condition for deleting last node
				del = temp;
				ptr = NULL;
			}
			else {
				del = ptr;
				temp->next = del->next;
				ptr = temp;
			}
			delete del;
		}
		n = 0;
		it = NULL;
	}
	void reset() {				//iterator function to reset list
		count = 0;				
		it = ptr;
	}
	bool is_last() {				//iterator function for checking last element
		return count == n;			//count variable being used in iterator function to get rid of non-terminating loop
	}
	T get_next() {					//iterator function for getting next element in list
		it = it->next;				//moving iterator and
		count++;					//count to next node
		return it->data;
	}
	int length() {					//length of list
		return n;
	}
	void display() {				//display data in list
		reset();									//displaying data
		while (!is_last()) {						//using iterators
			cout << get_next() << "\t";
		}
		cout << endl;
	}
};

/////////	 CLIENT CODE	//////////

int main()
{
	list<int> u;
	u.insert(5); u.insert(1); u.insert(2); u.insert(4);			//inserting 4 integers in list
	u.display();												//displaying list
	if (u.find(2)) {											//if 2 is found
		cout << "Found!\n";
		if (u.update(2, 6)) {									//then updating 2 by 6
			u.display();
			cout << "Updated!\n";
		}
		else {
			cout << "Could not update!\n";
		}
		if (u.erase(6)) {										//and then deleting 6 from list
			u.display();
			cout << "Erased!\n";
		}
		else {
			cout << "Could not erase!\n";
		}
	}
	else {
		cout << "Could not find!\n";
	}

	list<int> u2;
	u2 = u;										//copying data of u to u2 using assignment operator
	cout << "New List: ";
	u2.display();

	return 0;
}