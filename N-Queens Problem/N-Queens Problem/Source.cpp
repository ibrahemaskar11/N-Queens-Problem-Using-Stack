#include <iostream>
#define N 8
using namespace std;
int attempts = 0;
struct ChessNode {
	int row;
	int col;
};
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
template<class H>
DynamicStack<H>::DynamicStack() {
	top = NULL;
}
template<class H>
DynamicStack<H>::~DynamicStack() {
	while (top != NULL) {
		H temp = pop();
	}
}
template<class H>
bool DynamicStack<H>::isEmpty() {
	return top == NULL;
}
template<class H>
void DynamicStack<H>::push(H val) {
	Node<H>* elem = new Node<H>(val);
	if (isEmpty()) {
		top = elem;
	}
	else {
		elem->next = top;
		top = elem;
	}
}
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
bool isSafe(char board[N][N], int row, int col) {
	for (int i = 0; i < col; i++)
	{
		if (board[row][i] == 'Q')
			return false;
	}
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 'Q')
			return false;
	}
	for (int i = row, j = col; i < N && j >= 0; i++, j--) {
		if (board[i][j] == 'Q')
			return false;
	}
	return true;
}
void displayBoard(char board[N][N], int resArr[N]) {
	for (int i = 0; i < N; i++)
	{

		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == 'Q') {
				resArr[j] = i + 1;
			}

			cout << board[i][j] << ' ';
		}
		cout << endl;

	}
	cout << endl;
	cout << '[';
	for (int i = 0; i < N; i++)
	{
		cout << "(" << resArr[i] << "," << i + 1 << ")";
		if (i != N - 1)
			cout << ' ';
	}
	cout << ']' << endl;
}
bool solveNQueens(char board[N][N], int col, int filled = 0) {
	DynamicStack<ChessNode> boardStack;
	int row = 0;

	if (filled == N) {
		return true;
	}
	else {
		for (row = 0; row < N; row++) {
			if (isSafe(board, row, col)) {
				board[row][col] = 'Q';
				ChessNode filledNode;
				filledNode.row = row;
				filledNode.col = col;
				boardStack.push(filledNode);
				filled++;
				attempts++;

				if (solveNQueens(board, col + 1, filled)) {
					attempts;
					return true;
				}
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
void solveBoard() {
	int filled = 0;
	char board[N][N];
	int resArr[N];
	memset(board, '-', sizeof(board));
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
	cout << "Thanks for your time" << endl;
	
}