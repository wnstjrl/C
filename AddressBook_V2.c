/*C��� ����ü�迭, ������, ���� ������� �̿��� �ּҷ� ���α׷�*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LANG 30 //�Է¹޴� ������ ���� ���
#define MAX_NUM 5 //�ּҷ� ũ�� �����

typedef enum {
	Insert = 1, Delete, Search, PrintAll, SaveExit
}FuncList;

typedef struct {
	char name[MAX_LANG];
	char number[MAX_LANG];
	char gender[MAX_LANG];
	char age[MAX_LANG];
}User;

//�Լ� �����.
int saveFile(User* ptr, int* num); //File���·� hardDisk�� �����ϰڴ�.
int openFile(User* ptr, int* num); //����� ������ �ε��ϰڴ�.
void insertUser(User* ptr, int* num); // User �߰�. ����
int deleteUser(User* ptr, int* num); // User ����
int seachUser(User* ptr, int* num); // Ư�� ������ ������ ��ȸ
void printAll(User* ptr, int* num); // ��� ������ ����Ʈ�� ��������.

int main(void) {

	int input;
	User user[MAX_NUM]; // ����� ������ ������ ����ü �迭 ����
	int person = 0;

	openFile(user, &person); //����� �����͸� �ҷ����� �Լ�.

	//�޴�����
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

	//���Ͽ� ����� �����͸� �о�� ����ü �迭�� ����.
	while (true) {
		fscanf(fp, "%s %s %s %s", ptr[*num].name, ptr[*num].number, ptr[*num].gender , ptr[*num].age);
		if (feof(fp) != 0) break;
		(*num)++; //���� �����ͷ� �̵�.
	}
	/* fclose �Լ��� ����� ������ �߻��ϸ�
	0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ� �ȳ� �� ���α׷��� ����*/

	state = fclose(fp);
	if (state != 0) {
		printf("File Close Error!\n");
		return 1;
	}

	return 0;
}

//�����͸� ���Ͽ� �����ϴ� �Լ�
int saveFile(User* ptr, int* num) {

	if (*num > 0) { //����� 1���̶� ���� ��.
		int i, state;
		FILE* fp = fopen("UserInfo.txt", "wt");

		if (fp == NULL) {
			printf("File Open Error!\n");
			return 1;
		}

		//����ü �迭�� ����� �����͸� ���Ͽ� ����
		//�ٹٲ����� �����Ͽ� ����.
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
	else { //����� ���� ��
		printf("\n Exit \n");
		return 0;
	}

}

//���������� ����ü�� ����
void insertUser(User* ptr, int* num) {

	//���������� ���� ���� ���� ���. insert ����
	if (*num < MAX_NUM) {
		printf("Input Name : ");
		scanf("%s", ptr[*num].name);
		printf("Input Tel Number : ");
		scanf("%s", ptr[*num].number);
		printf("Input Gender : ");
		scanf("%s", ptr[*num].gender);
		printf("Input Age : ");
		scanf("%s", ptr[*num].age);

		(*num)++; //�ּҷϿ� ��ϵ� ���� ��� 1�� ����.
	}
	else { //���� ������ ���� �� ���.
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

				if (i != MAX_NUM - 1) { //������ �����Ͱ� ���� ��ġ�� �����Ͱ� �ƴ϶��.
					for (j = i; j < MAX_NUM; j++) {
						strcpy(ptr[j].name, ptr[j + 1].name);
						strcpy(ptr[j].number, ptr[j + 1].number);
						strcpy(ptr[j].gender, ptr[j + 1].gender);
						strcpy(ptr[j].age, ptr[j + 1].age);
					}

					//�迭 ��°�� call by ref ���ִ� �Ͱ� ���� ȿ��.
					*ptr[MAX_NUM - 1].name = NULL;
					*ptr[MAX_NUM - 1].number = NULL;
					*ptr[MAX_NUM - 1].gender = NULL;
					*ptr[MAX_NUM - 1].age = NULL;
				}
				else { //������ �����Ͱ� ����ü�迭 ��������° �����Ϳ��� ���.
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
