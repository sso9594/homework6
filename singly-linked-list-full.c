/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [Your Name] [Student ID] -----]");
	printf("\t신승용  2019038073");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {	// 노드를 입력하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 입력받은 키 노드로 동적할당
	node->key = key;	// 노드에 입력받은 키값 입력
	node->link = NULL;	// 노드의 연결값 초기화 

	if (h->first == NULL)	// 리스트에 아무것도 없을경우
	{
		h->first = node;	// 바로 리스트에 키값 입력
		return 0;
	}

	listNode* n = h->first;	//	
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {	// 리스트를 전부 검색해본다
		if(n->key >= key) {	// 리스트 안의 원소가 입력받은 키 값보다 크거나 같을경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//그 원소가 첫번째 원소일 경우
				h->first = node;	// 첫번째 원소를 키값으로 바꿈
				node->link = n;	//키값의 노드의 주소를 다음 값과 연결
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;	// 키값이 들어가있는 노드의 주소를 키값보다 크거나 같은 리스트의 원소가 담긴 노드와 연결
				trail->link = node; // 이전 노드의 주소와 키값이 담긴 노드 연결
			}
			return 0;
		}

		trail = n;	// trail의 주소를 다음 노드값으로 바꿔줌
		n = n->link;	//키값이 담긴 노드와 다음 노드의 주소를 연결
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;	//키값이 담긴 노드를 마지막 리스트의 주소와 연결
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {	// 리스트 마지막에 노드 추가

	listNode* node = (listNode*)malloc(sizeof(listNode));	//키값을 담아둘 노드 동적할당
	node->key = key;	//노드에 키값 입력
	node->link = NULL;	//노드의 연결값 초기화

	if (h->first == NULL)	//리스트가 비어있을경우
	{
		h->first = node;	// 리스트 맨앞에 노드 입력
		return 0;
	}

	listNode* n = h->first;	
	while(n->link != NULL) {
		n = n->link;	// n을 끝까지 이동
	}
	n->link = node;	//마지막 노드 뒤에 키값이 담긴 노드값 연결
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 키값을 담을 노드값 동적할당으로 생성
	node->key = key;	// 키값을 노드에 입력

	node->link = h->first;	//노드를 리스트 맨앞으로 연결
	h->first = node;	//노드의 주소를 리스트의 맨앞으로 설정

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {	// 노드를 삭제하는 함수

	if (h->first == NULL)	//리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	//에러 메세지 출력
		return 0;
	}

	listNode* n = h->first;	//n을 리스트 맨앞으로 설정
	listNode* trail = NULL;	//trail 주소값 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { 	//n을 리스트 끝까지 이동
		if(n->key == key) {	//키값이 리스트의 원소와 같을경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//키값이 리스트 맨앞의 원소와 같을경우
				h->first = n->link;	//키값과 같은 값이 있는 노드의 주소를 리스트 맨앞 노드와 연결
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;	// 키값과 같은 값이 있는 노드의 주소와 trail의 주소를 연결
			}
			free(n);	// 키값과 같은 값이 있는 노드 동적할당 해제
			return 0;
		}

		trail = n;// trail한칸 이동
		n = n->link;	//n 노드와 다음 노드의 주소를 연결
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {	// 마지막 노드 삭제하는 함수

	if (h->first == NULL)	//리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 0;
	}

	listNode* n = h->first;	
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { //노드가 하나만 있는 경우
		h->first = NULL;	//첫번째 원소의 연결을 해제하고
		free(n);	//동적할당을 해제시킨다
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {	//마지막 노드까지 이동
		trail = n;	//trail 한칸 이동
		n = n->link;	//n 노드와 다음 노드의 주소를 연결
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;	//trail연결 끊기
	free(n);	//마지막 노드 동적할당 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)	//리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 0;
	}
	listNode* n = h->first;	//비교할 노드 동적할당하여 first와 연결

	h->first = n->link;	//n노드를 첫번째 노드와 연결
	free(n);	//노드 n 동적할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {	//리스트를 역순으로 정렬하는 함수


	if(h->first == NULL) {	//리스트가 비어있을경우
		printf("nothing to invert...\n");	//에러메세지 출력
		return 0;
	}
	listNode *n = h->first;	
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle; //trail을 middle 쪽으로
		middle = n;	//middle을 n쪽으로
		n = n->link;	//n을 다음링크로 이동
		middle->link = trail;
	}

	h->first = middle;	//마지막 원소였던 노드를 fist로 설정

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

