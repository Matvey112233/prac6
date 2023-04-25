#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node* createNode(int data) {

	Node* newNode = new Node;
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void printList(Node* head) {
	cout << "List: " << endl;
	Node* current = head;
	while (current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

Node* createList() {
	cout << "Enter numbers of elements: ";
	auto start_time = chrono::high_resolution_clock::now();
	int n;
	Node* head = NULL;
	Node* tail = NULL;
	cin >> n;
	cout << endl;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		int value = rand() % 100;
		Node* newNode = createNode(value);
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	cout << endl;
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
	return head;
}

Node* createListFromInput() {
	auto start_time = chrono::high_resolution_clock::now();
	Node* head = NULL;
	Node* tail = NULL;
	int n = 0;
	cout << "Enter the elements of the list: " << endl;
	string line;
	getline(cin, line);
	stringstream ss(line);
	int value;
	while (ss >> value) {
		n++;
		Node* newNode = createNode(value);
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
	cout << "Entered " << n << " elements." << endl;
	return head;
}

void insertNode(Node** headRef, int index, int value) {
	auto start_time = chrono::high_resolution_clock::now();
	Node* newNode = createNode(value);
	if (*headRef == NULL) {
		*headRef = newNode;
		return;
	}
	if (index == 0) {
		newNode->next = *headRef;
		(*headRef)->prev = newNode;
		*headRef = newNode;
		return;
	}
	Node* current = *headRef;
	int i = 0;
	while (i < index && current != NULL) {
		current = current->next;
		i++;
	}
	if (current == NULL) {
		Node* tail = *headRef;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = newNode;
		newNode->prev = tail;
		return;
	}
	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;
	current->prev = newNode;
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
}

void deleteByIndex(Node** head, int index) {
	auto start_time = chrono::high_resolution_clock::now();
	if (*head == NULL) {
		return;
	}
	Node* current = *head;
	if (index == 0) {
		*head = current->next;
		if (*head != NULL) {
			(*head)->prev = NULL;
		}
		delete current;
		return;
	}
	for (int i = 0; current != NULL && i < index - 1; i++) {
		current = current->next;
	}
	if (current == NULL || current->next == NULL) {
		return;
	}
	Node* next = current->next->next;
	delete current->next;
	current->next = next;
	if (next != NULL) {
		next->prev = current;
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
}

void deleteByValue(Node** head, int data) {
	auto start_time = chrono::high_resolution_clock::now();
	if (*head == NULL) {
		return;
	}
	Node* current = *head;
	if (current->data == data) {
		*head = current->next;
		if (*head != NULL) {
			(*head)->prev = NULL;
		}
		delete current;
		return;
	}
	while (current != NULL && current->data != data) {
		current = current->next;
	}
	if (current == NULL) {
		return;
	}
	Node* prev = current->prev;
	Node* next = current->next;
	delete current;
	if (prev != NULL) {
		prev->next = next;
	}
	if (next != NULL) {
		next->prev = prev;
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
}

void swapNodes(Node** head, int data1, int data2) {
	if (data1 == data2) {
		return;
	}
	Node* current = *head;
	Node* node1 = NULL;
	Node* node2 = NULL;
	while (current != NULL) {
		if (current->data == data1) {
			node1 = current;
		}
		else if (current->data == data2) {
			node2 = current;
		}
		current = current->next;
	}
	if (node1 == NULL || node2 == NULL) {
		return;
	}
	if (node1->prev != NULL) {
		node1->prev->next = node2;
	}
	else {
		*head = node2;
	}
	if (node2->prev != NULL) {
		node2->prev->next = node1;
	}
	else {
		*head = node1;
	}
	Node* temp = node1->prev;
	node1->prev = node2->prev;
	node2->prev = temp;
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;
}

void swapNodesByIndex(Node** head, int index1, int index2) {
	if (index1 == index2) {
		return;
	}
	Node* current = *head;
	Node* node1 = NULL;
	Node* node2 = NULL;
	int i = 0;
	while (current != NULL) {
		if (i == index1) {
			node1 = current;
		}
		else if (i == index2) {
			node2 = current;
		}
		current = current->next;
		i++;
	}
	if (node1 == NULL || node2 == NULL) {
		return;
	}
	if (node1->prev != NULL) {
		node1->prev->next = node2;
	}
	else {
		*head = node2;
	}
	if (node2->prev != NULL) {
		node2->prev->next = node1;
	}
	else {
		*head = node1;
	}
	Node* temp = node1->prev;
	node1->prev = node2->prev;
	node2->prev = temp;
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;
}

Node* findNodeByIndex(Node* head, int index) {
	auto start_time = chrono::high_resolution_clock::now();
	Node* current = head;
	int i = 0;
	while (current != NULL) {
		if (i == index) {
			auto end_time = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
			cout << "Elepsed time: " << duration << " ns" << endl;
			return current;
		}
		current = current->next;
		i++;
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
	return NULL;
}

int findNodeIndexByValue(Node* head, int value) {
	auto start_time = chrono::high_resolution_clock::now();
	Node* current = head;
	int index = 0;
	while (current != NULL) {
		if (current->data == value) {
			auto end_time = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
			cout << "Elepsed time: " << duration << " ns" << endl;
			return index;
		}
		current = current->next;
		index++;
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
	cout << "Elepsed time: " << duration << " ns" << endl;
	return -1; 
}

int main() {
	Node* head = NULL;
	Node* list = NULL;
	Node* foundNode = nullptr;
	Node* currentNode = head;
	while (true) {
		int task;
		cout << "Choose an operation:" << endl;
		cout << "1. Create a list " << endl;
		cout << "2. Insert of element " << endl;
		cout << "3. Delete of element " << endl;
		cout << "4. Exchange of element " << endl;
		cout << "5. Receiving of element " << endl;
		cout << "0. Exit " << endl;
		cin >> task;
		cin.ignore();
		switch (task) {
		case 1:
			while (true) {
				int task1;
				cout << "Choose a method: " << endl;
				cout << "1. Random " << endl;
				cout << "2. By you " << endl;
				cout << "0. Back to main menu" << endl;
				cin >> task1;
				cin.ignore();
				switch (task1) {
				case 1:
					list = createList();
					printList(list);
					break;
				case 2:
					list = createListFromInput();
					printList(list);
					break;
				case 0:
					break;
				default:
					break;
				}
				if (task1 == 0) {
					break;
				}
			}
			break;
		case 2:
			int index, value;
			cout << "Enter index to insert: ";
			cin >> index;
			cout << "Enter value to insert: ";
			cin >> value;
			insertNode(&list, index, value);
			printList(list);
			break;
		case 3:
			while (true) {
				int task2;
				cout << "Choose a method: " << endl;
				cout << "1. By index " << endl;
				cout << "2. By value " << endl;
				cout << "0. Back to main menu" << endl;
				cin >> task2;
				cin.ignore();
				switch (task2) {
				case 1:
					int index;
					cout << "Enter the index of the element to be deleted: ";
					cin >> index;
					deleteByIndex(&list, index);
					printList(list);
					break;
				case 2:
					int value;
					cout << "Enter the value of the element to be deleted: ";
					cin >> value;
					deleteByValue(&list, value);
					printList(list);
					break;
				case 0:
					break;
				default:
					break;
				}
				if (task2 == 0) {
					break;
				}
			}
			break;
		case 4:
			while (true) {
				int task3;
				cout << "Choose a method: " << endl;
				cout << "1. By value " << endl;
				cout << "2. By index " << endl;
				cout << "0. Back to main menu" << endl;
				cin >> task3;
				cin.ignore();
				switch (task3) {
				case 1:
					int data1, data2;
					cout << "Enter the values of the nodes to be swapped: ";
					cin >> data1 >> data2;
					swapNodes(&list, data1, data2);
					printList(list);
					break;
				case 2:
					int index1, index2;
					cout << "Enter index of the nodes to be swapped: ";
					cin >> index1 >> index2;
					swapNodesByIndex(&list, index1, index2);
					printList(list);
					break;
				case 0:
					break;
				default:
					break;
				}
				if (task3 == 0) {
					break;
				}
			}
			break;
		case 5:
			int task5;
			cout << "Choose a method: " << endl;
			cout << "1. Find element by index" << endl;
			cout << "2. Find element by value" << endl;
			cout << "0. Back to main menu" << endl;
			cin >> task5;
			cin.ignore();
			if (task5 == 1) {
				int index;
				cout << "Enter the index of the element: ";
				cin >> index;
				foundNode = findNodeByIndex(list, index);
				if (foundNode != NULL) {
					cout << "Found node: " << foundNode->data << endl;
				}
			}
			else if (task5 == 2) {
				int value;
				cout << "Enter the value of the element: ";
				cin >> value;
				int index = findNodeIndexByValue(list, value);
				if (index != -1) {
					cout << "Node found at index: " << index << endl;
				}
			}
			else {
				break;
			}
			break;
		case 0:
			return 0;
		default:
			break;
		}
	}
	return 0;
}