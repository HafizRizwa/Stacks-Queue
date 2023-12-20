#include <iostream>

using namespace std;

struct Node1 {
  int data;
  Node1* next;
};

class LinkedStack {
private:
  Node1* head;

public:
  LinkedStack() : head(nullptr) {}

  ~LinkedStack() {
    while (head) {
      Node1* temp = head;
      head = head->next;
      delete temp;
    }
  }

  bool isEmpty()  { return head == nullptr; }

  bool isFull()  { return false; } // Linked lists can grow dynamically

  void push(int element) {
    Node1* newNode1 = new Node1{element, head};
    head = newNode1;
  }

  int pop() {
    if (isEmpty()) {
      cout << "Stack underflow!" << endl;
      return -1;
    }
    int data = head->data;
    Node1* temp = head;
    head = head->next;
    delete temp;
    return data;
  }

  int peek()  {
    if (isEmpty()) {
      return -1;
    }
    return head->data;
  }

  void display()  {
    if (isEmpty()) {
      cout << "Stack is empty." << endl;
      return;
    }
    cout << "[";
    Node1* curr = head;
    while (curr) {
      cout << curr->data << ", ";
      curr = curr->next;
    }
    cout << "\b\b]" << endl;
  }

  bool balancedParenthesis(const string& exp) {
    LinkedStack brackets;
    for (char c : exp) {
      if (c == '(' || c == '{' || c == '[') {
        brackets.push(c);
      } else if (c == ')' || c == '}' || c == ']') {
        if (brackets.isEmpty() || brackets.peek() != getOpeningBracket(c)) {
          return false;
        }
        brackets.pop();
      }
    }
    return brackets.isEmpty();
  }

  string infixToPostfix(const string& exp) {
    LinkedStack operators;
    string postfix;
    for (char c : exp) {
      if (isalpha(c)) {
        postfix += c;
      } else if (isOperator(c)) {
        while (!operators.isEmpty() && precedence(c) <= precedence(operators.peek())) {
          postfix += operators.pop();
        }
        operators.push(c);
      } else if (c == '(') {
        operators.push(c);
      } else if (c == ')') {
        while (!operators.isEmpty() && operators.peek() != '(') {
          postfix += operators.pop();
        }
        if (!operators.isEmpty()) {
          operators.pop(); // remove '('
        }
      }
    }
    while (!operators.isEmpty()) {
      postfix += operators.pop();
    }
    return postfix;
  }

private:
  char getOpeningBracket(char closingBracket) {
    switch (closingBracket) {
      case ')': return '(';
      case '}': return '{';
      case ']': return '[';
      default: return ' ';
    }
  }

  bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
  }

  int precedence(char op) {
    switch (op) {
      case '^': return 5;
      case '*': return 4;
      case '/': return 4;
      case '+': return 3;
      case '-': return 3;
      default: return 0;
    }
  }
};
class ArrayStack {
private:
    int arr[100];
    int top;

public:
    ArrayStack() : top(-1) {}

    bool isEmpty()  { return top == -1; }

    bool isFull() const { 
	return top == 99; 
	}

    void push(int element) {
        if (!isFull()) {
            arr[++top] = element;
        } else {
            cout << "Stack Overflow!" << endl;
        }
    }

    int pop() {
        if (!isEmpty()) {
            return arr[top--];
        } else {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
    }

    int peek()  {
        if (!isEmpty()) {
            return arr[top];
        } else {
            return -1;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "[";
        for (int i = 0; i <= top; ++i) {
            cout << arr[i] << ", ";
        }
        cout << "\b\b]" << endl;
    }

    bool balancedParenthesis(string exp) {
        ArrayStack brackets;
        for (char c : exp) {
            if (c == '(' || c == '{' || c == '[') {
                brackets.push(c);
            } else if (c == ')' || c == '}' || c == ']') {
                if (brackets.isEmpty() || brackets.peek() != getOpeningBracket(c)) {
                    return false;
                }
                brackets.pop();
            }
        }
        return brackets.isEmpty();
    }

    string infixToPostfix(string exp) {
        ArrayStack operators;
        string postfix;
        for (char c : exp) {
            if (isalpha(c)) {
                postfix += c;
            } else if (isOperator(c)) {
                while (!operators.isEmpty() && precedence(c) <= precedence(operators.peek())) {
                    postfix += operators.pop();
                }
                operators.push(c);
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.isEmpty() && operators.peek() != '(') {
                    postfix += operators.pop();
                }
                if (!operators.isEmpty()) {
                    operators.pop(); // remove '('
                }
            }
        }
        while (!operators.isEmpty()) {
            postfix += operators.pop();
        }
        return postfix;
    }

private:
    char getOpeningBracket(char closingBracket) {
        switch (closingBracket) {
            case ')': return '(';
            case '}': return '{';
            case ']': return '[';
            default: return ' ';
        }
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    int precedence(char op) {
        switch (op) {
            case '^': return 5;
            case '*': return 4;
            case '/': return 4;
            case '+': return 3;
            case '-': return 3;
            default: return 0;
        }
    }
};

struct Node {
  int data;
  Node* next;
};

class LinkedQueue {
private:
  Node* front, *rear;
  int size;

public:
  LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

  bool isEmpty()  { return size == 0; }

  bool isFull()  { return false; } // Linked lists grow dynamically

  void enqueue(int element) {
    Node* newNode = new Node{element, nullptr};
    if (isEmpty()) {
      front = rear = newNode;
    } else {
      rear->next = newNode;
      rear = newNode;
    }
    size++;
  }

  int dequeue() {
    if (isEmpty()) {
      cout << "Queue underflow!" << endl;
      return -1;
    }
    int data = front->data;
    Node* temp = front;
    if (front == rear) {
      front = rear = nullptr;
    } else {
      front = front->next;
    }
    delete temp;
    size--;
    return data;
  }

  int getFront()  {
    if (isEmpty()) {
      return -1;
    }
    return front->data;
  }

  int getRear()  {
    if (isEmpty()) {
      return -1;
    }
    return rear->data;
  }

//  int size()  { 
//  return size; 
//  }

  void display()  {
    if (isEmpty()) {
      cout << "Queue is empty." << endl;
      return;
    }
    cout << "[";
    Node* curr = front;
    do {
      cout << curr->data << ", ";
      curr = curr->next;
    } while (curr != front);
    cout << "\b\b]" << endl;
  }

  void reverseQueue(LinkedStack& stack) {
    while (!isEmpty()) {
      stack.push(dequeue());
    }
    while (!stack.isEmpty()) {
      enqueue(stack.pop());
    }
  }
};

class ArrayQueue {
private:
    int arr[100];
    int front, rear;

public:
    ArrayQueue() : front(0), rear(-1) {}

    bool isEmpty()  { 
	return front > rear; 
	}

    bool isFull()  { 
	return (rear + 1) % 100 == front;
	 }

    void enqueue(int element) {
        if (!isFull()) {
            rear = (rear + 1) % 100;
            arr[rear] = element;
        } else {
            cout << "Queue overflow!" << endl;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            int data = arr[front];
            front = (front + 1) % 100;
            return data;
        } else {
            cout << "Queue underflow!" << endl;
            return -1;
        }
    }

    int getFront()  {
        if (!isEmpty()) {
            return arr[front];
        } else {
            return -1;
        }
    }

    int getRear()  {
        if (!isEmpty()) {
            return arr[rear];
        } else {
            return -1;
        }
    }

    int size()  {
        return (rear - front + 100) % 100;
    }

    void display()  {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "[";
        for (int i = front; i <= rear; ++i) {
            cout << arr[i] << ", ";
        }
        cout << "\b\b]" << endl;
    }

    void reverseQueue(ArrayStack& stack) {
        while (!isEmpty()) {
            stack.push(dequeue());
        }
        while (!stack.isEmpty()) {
            enqueue(stack.pop());
        }
    }
};
int main() {
    int choice;
    int data;
    string expression;

    cout << "Choose Data Structure:\n";
    cout << "1. Array\n";
    cout << "2. Linked List\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {  // Array
        cout << "Choose Operation:\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {  // Array Stack
            ArrayStack arrayStack;
            do {
                cout << "\nArray Stack Operations:\n";
                cout << "1. Push\n";
                cout << "2. Pop\n";
                cout << "3. Peek\n";
                cout << "4. Display\n";
                cout << "5. Balanced Parenthesis\n";
                cout << "6. Infix to Postfix\n";
                cout << "7. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter element to push: ";
                        cin >> data;
                        arrayStack.push(data);
                        break;
                    case 2:
                        arrayStack.pop();
                        break;
                    case 3:
                        cout<<arrayStack.peek();
                        break;
                    case 4:
                        arrayStack.display();
                        break;
                    case 5:
                        cout << "Enter expression to check balanced parenthesis: ";
                        cin >> expression;
                        cout << (arrayStack.balancedParenthesis(expression) ? "Balanced" : "Not Balanced") << endl;
                        break;
                    case 6:
                        cout << "Enter infix expression: ";
                        cin >> expression;
                        cout << "Postfix expression: " << arrayStack.infixToPostfix(expression) << endl;
                        break;
                    case 7:
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } while (choice != 7);
        } else if (choice == 2) {  
            ArrayQueue arrayQueue;
            do {
                cout << "\nArray Queue Operations:\n";
                cout << "1. Enqueue\n";
                cout << "2. Dequeue\n";
                cout << "3. Get Front\n";
                cout << "4. Get Rear\n";
                cout << "5. Display\n";
                cout << "6. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter element to enqueue: ";
                        cin >> data;
                        arrayQueue.enqueue(data);
                        break;
                    case 2:
                        arrayQueue.dequeue();
                        break;
                    case 3:
                        arrayQueue.getFront();
                        break;
                    case 4:
                        arrayQueue.getRear();
                        break;
                    case 5:
                        arrayQueue.display();
                        break;
                    case 6:
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } while (choice != 6);
        } else {
            cout << "Invalid choice. Exiting program.\n";
        }
    } else if (choice == 2) {  // Linked List
        cout << "Choose Operation:\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {  // Linked Stack
            LinkedStack linkedStack;
            do {
                cout << "\nLinked Stack Operations:\n";
                cout << "1. Push\n";
                cout << "2. Pop\n";
                cout << "3. Peek\n";
                cout << "4. Display\n";
                cout << "5. Balanced Parenthesis\n";
                cout << "6. Infix to Postfix\n";
                cout << "7. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter element to push: ";
                        cin >> data;
                        linkedStack.push(data);
                        break;
                    case 2:
                        linkedStack.pop();
                        break;
                    case 3:
                        cout<<linkedStack.peek();
                        break;
                    case 4:
                        linkedStack.display();
                        break;
                    case 5:
                        cout << "Enter expression to check balanced parenthesis: ";
                        cin >> expression;
                        cout << (linkedStack.balancedParenthesis(expression) ? "Balanced" : "Not Balanced") << endl;
                        break;
                    case 6:
                        cout << "Enter infix expression: ";
                        cin >> expression;
                        cout << "Postfix expression: " << linkedStack.infixToPostfix(expression) << endl;
                        break;
                    case 7:
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } while (choice != 7);
        } else if (choice == 2) {  // Linked Queue
            LinkedQueue linkedQueue;
            do {
                cout << "\nLinked Queue Operations:\n";
                cout << "1. Enqueue\n";
                cout << "2. Dequeue\n";
                cout << "3. Get Front\n";
                cout << "4. Get Rear\n";
                cout << "5. Display\n";
                cout << "6. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter element to enqueue: ";
                        cin >> data;
                        linkedQueue.enqueue(data);
                        break;
                    case 2:
                        linkedQueue.dequeue();
                        break;
                    case 3:
                        linkedQueue.getFront();
                        break;
                    case 4:
                        linkedQueue.getRear();
                        break;
                    case 5:
                        linkedQueue.display();
                        break;
                    case 6:
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } while (choice != 6);
        } else {
            cout << "Invalid choice. Exiting program.\n";
        }
    } else {
        cout << "Invalid choice. Exiting program.\n";
    }

    return 0;
}