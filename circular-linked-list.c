#include<stdio.h>
#include<stdlib.h>

/* 노드 구조체 정의 */
typedef struct Node {
	int key; // key값
	struct Node* llink; // 왼쪽을 가리키는 노드 구조체 포인터
	struct Node* rlink; // 오른쪽 가리키는 노드 구조체 포인터
} listNode;

/* 함수 원형 선언 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("------ [2019036068] [허원일] ------");
	char command;
	int key;
	listNode* headnode=NULL; // headNode를 NULL로 지정

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			// 리스트 초기화
			initialize(&headnode);
			break;
		case 'p': case 'P':
			// 리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I':
			// 원소 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			// 원소 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			// 마지막에 원소 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			// 마지막 원소 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			// 첫번째에 원소 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			// 첫번째 원소 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			// 리스트 역순으로 뒤집기
			invertList(headnode);
			break;
		case 'q': case 'Q':
			// 리스트 메모리 해제 후 프로그램 종료
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* 리스트를 초기화하는 함수 */
int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; // headNode의 다음노드를 자기 자신으로 지정
	(*h)->llink = *h; // headNode의 이전노드를 자기 자신으로 지정
	(*h)->key = -9999; // headNode의 key 초기화

	return 1;
}

/* 리스트에 할당된 메모리를 반납하는 함수 */
int freeList(listNode* h){

	/* 리스트에 노드 하나만 존재하는 경우 */
	if(h->rlink == h)
	{
		free(h); // headNode의 메모리를 해제

		return 1;
	}

	listNode* p = h->rlink; // headNode의 다음노드를 가리키는 임시 노드 구조체 포인터 p

	listNode* prev = NULL; // headNode의 다음노드를 가리키는 임시 노드 구조체 포인터 prev

	/* 포인터 p로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(p != NULL && p != h) {
		prev = p; // prev는 p를 따라감
		p = p->rlink; // p를 다음노드로 이동
		free(prev); // prev가 가리키는 노드에 할당된 메모리 해제
	}
	free(h); // headNode에 할당된 메모리 해제

	return 0;
}


/* 리스트를 출력하는 함수 */
void printList(listNode* h) {
	int i = 0;
	listNode* p; // 임시 노드 구조체 포인터 p

	printf("\n---PRINT\n");

	/* headNode가 NULL인 경우 즉, 빈 리스트인 경우 경고문 출력 후 함수 종료 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // p를 headNode의 다음노드를 가리키게 함 

	/* 포인터 p로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key); // 현재노드의 key를 출력
		p = p->rlink; // p를 p의 다음노드로 이동
		i++;
	}
	printf("  items = %d\n", i); // item 갯수 출력


	/* 링크들의 주소를 출력 */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	// headNode의 노드 주소와 각 링크 주소를 출력

	i = 0;
	p = h->rlink; // p를 headNode의 다음노드로 가리키게 함
	/* 포인터 p로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		// 노드들의 노드 주소와 각 링크 주소를 출력
		p = p->rlink; // p를 p의 다음노드로 이동
		i++;
	}

}

/* 리스트의 마지막에 노드를 추가하는 함수 */
int insertLast(listNode* h, int key) {

	/* headNode가 NULL인 경우 즉, 빈 리스트인 경우 경고문 출력 후 함수 종료 */
	if (h == NULL) return -1;

	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* 리스트에 노드 하나만 존재하는 경우 */
	if (h->rlink == h) 
	{
		h->rlink = node; // headNode의 다음노드를 node로 지정
		h->llink = node; // headNode의 이전노드를 node로 지정
		node->rlink = h; // node의 다음노드를 headNode로 지정
		node->llink = h; // node의 이전노드를 headNode로 지정
	} 
	else {
		h->llink->rlink = node; // headNode의 이전노드의 다음노드를 node로 지정
		node->llink = h->llink; // node의 이전노드를 headNode의 이전노드로 지정
		h->llink = node; // headNode의 이전노드를 node로 지정
		node->rlink = h; // node의 다음노드를 headNode로 지정
	}

	return 1;
}

/* 리스트의 마지막 노드를 삭제하는 함수 */
int deleteLast(listNode* h) {

	/* 빈 리스트인 경우 경고문 출력 후 함수 종료 */
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; 
	// headNode의 이전노드 즉, 마지막 노드를 가리키는 노드 구조체 포인터 nodetoremove

	nodetoremove->llink->rlink = h; // 마지막노드 이전노드의 다음노드를 headNode로 지정
	h->llink = nodetoremove->llink; // headNode의 이전노드를 마지막노드의 이전노드로 지정

	free(nodetoremove); // nodetoremove에 할당된 메모리 해제 (삭제된 노드)

	return 1;
}


/* 리스트 처음에 key값의 노드를 삽입하는 함수 */
int insertFirst(listNode* h, int key) {

	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	node->rlink = h->rlink; // node의 다음노드를 headNode의 다음노드로 지정
	h->rlink->llink = node; // headNode 다음노드의 이전노드를 node로 지정
	node->llink = h; // node의 이전노드를 headNode로 지정
	h->rlink = node; // headNode의 다음노드를 node로 지정

	return 1;
}

/* 리스트의 첫번째 노드를 삭제하는 함수 */
int deleteFirst(listNode* h) {

	/* 빈 리스트인 경우 경고문 출력 후 함수 종료 */
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; 
	// headNode의 다음노드 즉, 첫번째 노드를 가리키는 노드 구조체 포인터 nodetoremove

	nodetoremove->rlink->llink = h; // 첫번째 노드 다음노드의 이전노드를 headNode로 지정
	h->rlink = nodetoremove->rlink; // headNode의 다음노드를 첫번째 노드의 다음노드로 지정

	free(nodetoremove); // nodetoremove에 할당된 메모리 해제 (삭제된 노드)

	return 1;

}


/* 리스트를 역순으로 재배치하는 함수 */
int invertList(listNode* h) {

	/* 빈 리스트인 경우 경고문 출력 후 함수 종료 */
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink; // headNode의 다음노드를 가리키는 노드 구조체 포인터 n
	listNode *trail = h; // headNode를 가리키는 노드 구조체 포인터 trail
	listNode *middle = h; // headNode를 가리키는 노드 구조체 포인터 middle

	h->llink = h->rlink; // headNode의 이전노드를 headNode의 다음노드로 지정

	/* 포인터 n으로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(n != NULL && n != h){
		trail = middle; // trail은 middle을 따라감
		middle = n; // middle을 n을 따라감
		n = n->rlink; // n을 n의 다음노드로 이동
		middle->rlink = trail; // middle의 다음노드를 trail로 지정
		middle->llink = n; // middle의 이전노들를 n으로 지정
	}

	h->rlink = middle; // headNode의 다음노드를 middle로 지정

	return 0;
}



/* 리스트를 탐색하여 입력받은 key보다 크거나 같은 값이 나오는 노드 바로 앞에 삽입하는 함수 */
int insertNode(listNode* h, int key) {

	/* 빈 리스트인 경우 함수 종료 */
	if(h == NULL) return -1;

	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* headNode만 존재하는 경우 */
	if (h->rlink == h)
	{
		insertFirst(h, key); // insertFirst로 리스트의 첫번째에 노드 삽입
		return 1;
	}

	listNode* n = h->rlink; // headNode의 다음노드를 가리키는 노드 구조체 포인터 n

	/* 포인터 n으로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} 
			else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // node의 다음노드를 n으로 지정 
				node->llink = n->llink; // node의 이전노드를 n의 이전노드로 지정
				n->llink->rlink = node; // n의 이전노드의 다음노드를 node로 지정
				n->llink = node; // n의 이전노드를 node로 지정
			}

			return 0;
		}

		n = n->rlink; // n을 다음노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/* 리스트를 탐색하여 해당 key의 노드를 삭제하는 함수 */
int deleteNode(listNode* h, int key) {

	/* 빈 리스트인 경우 */
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; // headNode의 다음노드를 가리키는 노드 구조체 포인터 n

	/* 포인터 n으로 headNode 다음노드부터 headNode 이전까지 방문 */
	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫번째 노드인 경우 */
				deleteFirst(h); // deleteFirst로 첫번째 노드 삭제
			} 
			else if (n->rlink == h) { /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast로 마지막 노드 삭제 
			} 
			else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // n의 이전노드의 다음노드를 n의 다음노드로 지정
				n->rlink->llink = n->llink; // n의 다음노드의 이전노드를 n의 이전노드로 지정
				free(n); // n에 할당된 메모리 해제
			}

			return 0;
		}

		n = n->rlink; // n을 n의 다음노드로 이동
	}

	/* 찾지 못한 경우 */
	printf("cannot find the node for key = %d\n", key);

	return 0;
}


