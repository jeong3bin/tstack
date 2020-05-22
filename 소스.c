#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int stack_size, data_size;

typedef struct ListNode {
	struct ListNode *pre; //다음 stack
	int* stack; //배열로 구현된 stack
	int top; //스택의 top
	struct ListNode *next; //이전 stack
}ListNode;

ListNode* head; //첫번째 stack
ListNode* tail; // 마지막 stack

ListNode *create_stack() {
	//stack 생성
	ListNode *new_node= (ListNode *)malloc(sizeof(ListNode));
	//초기화
	new_node->stack = (int *)malloc(sizeof(int)*stack_size);
	new_node->next = NULL;
	new_node->pre = NULL;
	new_node->top = 0;

	return new_node;
}

void is_full() {
	if (tail->top == stack_size) {
		//다음에 올 stack 생성
		ListNode* next_node = create_stack(); 
		tail->next = next_node; // 다음 stack으로 설정
		tail->next->pre = tail; // 현재 stack을 이전 stack으로 설정
		tail = tail->next; // 마지막 stack을 새 stack으로 변경
	}
}
void is_empty() {
	if (tail->top == 0) {
		tail = tail->pre; //이전 stack을 마지막 stack으로 변경
		free(tail->next); // 빈 stack 동적할당 해제 
		tail->next = NULL; // 마지막 stack의 다음 stack은 없음
	}
}
void peek() {
	printf("peek %d\n", tail->stack[tail->top - 1]);
}

void pop() {
	tail->top -= 1;
	printf("pop %d\n", tail->stack[tail->top]);
	tail->stack[tail->top] = NULL;
	is_empty();
}
void push(int data) {

	is_full();

	tail->stack[tail->top] = data;
	tail->top += 1;

}

void showTstack() {

	printf("\n");
	printf("show all data--------\n");
	ListNode *current = head;
	int size = 0;
	while (current != NULL) {
		size = current->top;
		for (int i = 0; i < size; i++) {
			printf("%2d ", current->stack[i]);
		}
		printf("\n");

		current = current->next;
	}
	printf("\n");
	printf("----------------------\n");

}
int main() {

	int input, data;

	printf("stacksize datasize ");
	scanf("%d %d", &stack_size, &data_size);
	head = create_stack();
	tail = head;

	printf("inputsize ");
	scanf("%d", &input);

	printf("inputdata\n");
	for (int i = 0; i < input; i++) {
		scanf("%d", &data);
		push(data);
	}
	peek();
	printf("\n");
	showTstack();
	printf("\n");

	printf("deletesize ");
	scanf("%d", &input);
	printf("deletedata\n");
	for (int i = 0; i < input; i++) {
		pop();
	}
	peek();
	showTstack();
	printf("\n");

	printf("inputsize ");
	scanf("%d", &input);
	printf("inputdata\n");
	for (int i = 0; i < input; i++) {
		scanf("%d", &data);
		push(data);
	}
	peek();
	printf("\n");
	showTstack();

	return 0;
}