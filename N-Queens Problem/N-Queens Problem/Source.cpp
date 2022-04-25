/*
Team 1
Assignment 2
N-Queen problem set of 8*8
*/
#include <iostream>
#define N 8
using namespace std;
int attempts = 0;
/*
ChessNode struct used to hold the position of a chess board index
*/
struct ChessNode {
	int row;
	int col;
};
/*
Node class used to hold the value of items in the dynamic stack
*/
template<class H>
class Node {
public:
	H item;
	Node* next;
	Node(H);
};
template<class H>
Node<H> ::Node(H val) {
	item = val;
	next = NULL;
}
/*
Dynamic stack implemented using linked list
the stack uses addFirst() and removeFirst() functions from the linked list as push() and pop() functions
*/
template<class H>
class DynamicStack {
	Node<H>* top;
public:
	DynamicStack();
	~DynamicStack();
	void push(H);
	H pop();
	bool isEmpty();
	void display();
	H peak();
};
/*
DynamicStack() constructor used to intialize the top pointer to NULL 
*/
template<class H>
DynamicStack<H>::DynamicStack() {
	top = NULL;
}
/*
~DynamicStack() destructor used to remove all current nodes in the stack
*/
template<class H>
DynamicStack<H>::~DynamicStack() {
	while (top != NULL) {
		H temp = pop();
	}
}
/*
isEmpty() function used to return true if the stack is empty(no nodes in the stack)
*/
template<class H>
bool DynamicStack<H>::isEmpty() {
	return top == NULL;
}
/*
push() function implemented using the functionality of addFirst() in the linkedList
*/
template<class H>
void DynamicStack<H>::push(H val) {
	Node<H>* elem = new Node<H>(val);
	/*
	if the stack is empty we add the new node as the first node in the stack
	if not we push it as the first node 
	*/
	if (isEmpty()) {
		top = elem;
	}
	else {
		elem->next = top;
		top = elem;
	}
}
/*
pop() function implemented using the functionality of removeFirst() in the linkedList
*/
template<class H>
H DynamicStack<H>::pop() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	else {
		H data = top->item;
		if (top->next == NULL) {
			delete(top);
			top = NULL;
		}
		else {
			Node<H>* ptr = top;
			top = top->next;
			delete(ptr);
		}
		return data;
	}
}
/*
peak() fucntion used to return the top node in the stack
*/
template<class H>
H DynamicStack<H>::peak() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	else {
		return top->item;
	}
}
/*
display() function used to display all existing nodes in the stack
*/
template<class H>
void DynamicStack<H>::display() {
	if (isEmpty()) {
		cout << "Stack is Empty\n";
		system("PAUSE");
		exit(1);
	}
	cout << "Stack: ";
	Node<H>* ptr = top;
	while (ptr != NULL) {
		cout << ptr->item << " ";
		ptr = ptr->next;
	}
	cout << endl;
}
/*
isSafe() function used to check if the board index is safe for placing a queen in that position
*/
bool isSafe(char board[N][N], int row, int col) {
	/*
	for loop used to check if the current row is safe
	*/
	for (int i = 0; i < col; i++)
	{
		if (board[row][i] == 'Q')
			return false;
	}
	/*
	for loop used to check if the left upper diagonal is safe
	*/
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 'Q')
			return false;
	}
	/*
	for loop used to check if the left lower diagonal is safe
	*/
	for (int i = row, j = col; i < N && j >= 0; i++, j--) {
		if (board[i][j] == 'Q')
			return false;
	}
	return true;
}
/*
displayBoard() function used to display the chess board
*/
void displayBoard(char board[N][N], int resArr[N]) {
	for (int i = 0; i < N; i++)
	{

		for (int j = 0; j < N; j++)
		{
			/*
			if the current position contains a Q we add it to the result array to later display
			the indices of the valid positions 
			*/
			if (board[i][j] == 'Q') {
				resArr[j] = i + 1;
			}

			cout << board[i][j] << ' ';
		}
		cout << endl;

	}
	cout << endl;
	cout << '[';
	/*
	for loop used to display the indices of the valid positions on the chess board
	*/
	for (int i = 0; i < N; i++)
	{
		cout << "(" << resArr[i] << "," << i + 1 << ")";
		if (i != N - 1)
			cout << ' ';
	}
	cout << ']' << endl;
}
/*
solveNQueens() function used to operate on a 2d array represinting the chess board
returns a boolean value if the N problem could be solved or not
recieves the 2d array, the column it will start from and the number of filled position on the chess board
*/
bool solveNQueens(char board[N][N], int col, int filled = 0) {
	DynamicStack<ChessNode> boardStack;
	int row = 0;
	/*
	if the number of filled positions equal to the N value it would return true
	meaning that all position on the chess board has been filled
	*/
	if (filled == N) {
		return true;
	}
	else {
		for (row = 0; row < N; row++) {
			/*
			(The Recursive Condition)
			if statement used to determine if the current index is safe to place a queen or not
			*/
			if (isSafe(board, row, col)) {
				board[row][col] = 'Q';
				ChessNode filledNode;
				filledNode.row = row;
				filledNode.col = col;
				boardStack.push(filledNode);
				filled++;
				attempts++;
				/*
				(The Recursion Functionality) 
				the function is later continued recursivly to determine if the position we added
				is valid to build upon
				*/
				if (solveNQueens(board, col + 1, filled)) {
					return true;
				}
				/*
				(The Step Back)
				if the recursive sequence fails the function takes a step back removing the filled position
				and tries again with a different row
				*/
				ChessNode removedNode = boardStack.pop();
				int removedRow = removedNode.row;
				int removedCol = removedNode.col;
				board[removedRow][removedCol] = '-';
				filled--;
			}
		}
	}
	return false;
}
/*
solveBoard() function used to tidy up code and be a step for executing the recursive algorithm
*/
void solveBoard() {
	int filled = 0;
	char board[N][N];
	int resArr[N];
	/*
	memset() function used to set all elements of the chess board to '-'
	*/
	memset(board, '-', sizeof(board));
	/*
	if statement used to determine if the problem could be solved or not before displaying the chess board
	*/
	if (solveNQueens(board, 0, filled)) {
		displayBoard(board, resArr);
	}
	else {
		cout << "Board Set Doesn't Have Any Solutions\n";
		return;
	}
}
void main() {

	solveBoard();
	cout << "Num of attempts:" << attempts << endl;
	cout << "Thanks for your time " << endl;
	
}