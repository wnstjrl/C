/*C언어 구조체배열, 포인터, 파일 입출력을 이용한 주소록 프로그램*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LANG 30 //입력받는 정보의 길이 상수
#define MAX_NUM 5 //주소록 크기 상수값

typedef enum {
	Insert = 1, Delete, Search, PrintAll, SaveExit
}FuncList;

typedef struct {
	char name[MAX_LANG];
	char number[MAX_LANG];
	char gender[MAX_LANG];
	char age[MAX_LANG];
}User;

//함수 선언부.
int saveFile(User* ptr, int* num); //File형태로 hardDisk에 저장하겠다.
int openFile(User* ptr, int* num); //저장된 파일을 로드하겠다.
void insertUser(User* ptr, int* num); // User 추가. 삽입
int deleteUser(User* ptr, int* num); // User 삭제
int seachUser(User* ptr, int* num); // 특정 유저의 정보를 조회
void printAll(User* ptr, int* num); // 모든 유저의 리스트를 출력해줘라.

int main(void) {

	int input;
	User user[MAX_NUM]; // 사용자 정보를 저장할 구조체 배열 변수
	int person = 0;

	openFile(user, &person); //저장된 데이터를 불러오는 함수.

	//메뉴선택
	while (true) {
		printf("***** Menu ***** \n");
		printf("1. Insert \n");
		printf("2. Delete \n");
		printf("3. Search \n");
		printf("4. Print All \n");
		printf("5. Save and Exit \n");

		printf("Choose the Function : ");
		scanf("%d", &input);

		switch (input) {
		case Insert:
			printf("\n[INSERT] \n");
			insertUser(user, &person);
			break;
		case Delete:
			printf("\n[DELETE] \n");
			deleteUser(user, &person);
			break;
		case Search:
			printf("\n[SEARCH] \n");
			seachUser(user, &person);
			break;
		case PrintAll:
			printf("\n[PRINT ALL] \n");
			printAll(user, &person);
			break;
		case SaveExit:
			saveFile(user, &person);
			return 0;
		default:
			printf("\nError! Retry! \n\n");
			break;
		}
		
	}
	return 0;
}

int openFile(User* ptr, int* num) {
	int state;
	char temp;

	FILE* fp = fopen("UserInfo.txt", "rt");

	if (fp == NULL) {
		printf("\nFile Open Error!\n\n");
		return 0; 
	}

	//파일에 저장된 데이터를 읽어와 구조체 배열에 저장.
	while (true) {
		fscanf(fp, "%s %s %s %s", ptr[*num].name, ptr[*num].number, ptr[*num].gender , ptr[*num].age);
		if (feof(fp) != 0) break;
		(*num)++; //다음 데이터로 이동.
	}
	/* fclose 함수는 종료시 오류가 발생하면
	0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면 안내 후 프로그램을 종료*/

	state = fclose(fp);
	if (state != 0) {
		printf("File Close Error!\n");
		return 1;
	}

	return 0;
}

//데이터를 파일에 저장하는 함수
int saveFile(User* ptr, int* num) {

	if (*num > 0) { //사람이 1명이라도 있을 때.
		int i, state;
		FILE* fp = fopen("UserInfo.txt", "wt");

		if (fp == NULL) {
			printf("File Open Error!\n");
			return 1;
		}

		//구조체 배열에 저장된 데이터를 파일에 저장
		//줄바꿈으로 구분하여 저장.
		for (i = 0; i < *num; i++) {
			fprintf(fp, "%s %s %s %s", ptr[i].name, ptr[i].number, ptr[i].gender , ptr[i].age);
			fputc('\n', fp);
		}

		state = fclose(fp);
		if (state != 0) {
			printf("File Close Error!\n");
			return 1;
		}

		printf("\n Data Save \n");
		return 0;
	}
	else { //사람이 없을 때
		printf("\n Exit \n");
		return 0;
	}

}

//유저정보를 구조체에 삽입
void insertUser(User* ptr, int* num) {

	//유저정보가 가득 차지 않은 경우. insert 가능
	if (*num < MAX_NUM) {
		printf("Input Name : ");
		scanf("%s", ptr[*num].name);
		printf("Input Tel Number : ");
		scanf("%s", ptr[*num].number);
		printf("Input Gender : ");
		scanf("%s", ptr[*num].gender);
		printf("Input Age : ");
		scanf("%s", ptr[*num].age);

		(*num)++; //주소록에 등록된 유저 명수 1명 증가.
	}
	else { //유저 정보가 가득 찬 경우.
		printf(" Data Full \n\n");
	}

}

int deleteUser(User* ptr, int* num) {
	char name[30];
	int i, j;

	if (*num > 0) {
		printf("Input Name : ");
		scanf("%s", name);

		for (i = 0; i < MAX_NUM; i++) {
			if (strcmp(name, ptr[i].name) == 0) {
				(*num)--;
				printf("Data Deleted \n\n");

				if (i != MAX_NUM - 1) { //삭제된 데이터가 끝에 위치한 데이터가 아니라면.
					for (j = i; j < MAX_NUM; j++) {
						strcpy(ptr[j].name, ptr[j + 1].name);
						strcpy(ptr[j].number, ptr[j + 1].number);
						strcpy(ptr[j].gender, ptr[j + 1].gender);
						strcpy(ptr[j].age, ptr[j + 1].age);
					}

					//배열 통째로 call by ref 해주는 것과 같은 효과.
					*ptr[MAX_NUM - 1].name = NULL;
					*ptr[MAX_NUM - 1].number = NULL;
					*ptr[MAX_NUM - 1].gender = NULL;
					*ptr[MAX_NUM - 1].age = NULL;
				}
				else { //삭제된 데이터가 구조체배열 마지막번째 데이터였을 경우.
					*ptr[MAX_NUM - 1].name = NULL;
					*ptr[MAX_NUM - 1].number = NULL;
					*ptr[MAX_NUM - 1].gender = NULL;
					*ptr[MAX_NUM - 1].age = NULL;
				}
				return 0;
			}
		}

		printf("Not Found \n\n");
		return 0;
	}
	else {
		printf(" No Data \n\n");
		return 0;
	}
}

int seachUser(User* ptr, int* num) {
	char name[30];
	int i;

	if (*num > 0) {
		printf("Input Name: ");
		scanf("%s", name);

		for (i = 0; i < MAX_NUM; i++) {

			if (!strcmp(name, ptr[i].name)) {
				printf("Name : %s", ptr[i].name);
				printf(" Tel : %s", ptr[i].number);
				printf(" Gender : %s", ptr[i].gender);
				printf(" Age : %s\n", ptr[i].age);

				printf("Data Found \n\n");
				return 0;
			}
		}
		printf("Not Found \n\n");
		return 0;
	}
	else {
		printf(" No Data \n\n");
		return 0;
	}
}

void printAll(User* ptr, int* num) {
	int i = 0;

	if (*num > 0) {
		for (i = 0; i < *num; i++) {
			printf("Name : %s", ptr[i].name);
			printf(" Tel : %s", ptr[i].number);
			printf(" Gender : %s", ptr[i].gender);
			printf(" Age : %s\n", ptr[i].age);
		}
		printf("Data Print \n\n");
	}
	else {
		printf(" No Data \n\n");
	}

}
