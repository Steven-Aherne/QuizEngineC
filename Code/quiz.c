#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
struct Question//Dynamic structure for storing questions
{
	char* question;
	char* answer;
	struct Question* next;
};
typedef struct Question Question;
void addQuestion(Question** tail, char* question, char* answer) {  // adding questions dynamically

	Question* q1 = (Question*)malloc(sizeof(Question));
	q1->question = (char*)malloc(strlen(question));
	strcpy(q1->question, question);
	q1->answer = (char*)malloc(strlen(answer));
	strcpy(q1->answer, answer);
	q1->next = NULL;
	(*tail)->next = q1;
	*tail = q1;
}
void addTohead(Question **head, char* question, char* answer) { //initializing head
	Question* q1 = (Question*)malloc(sizeof(Question));
	q1->question = (char*)malloc(strlen(question));
	strcpy(q1->question, question);
	q1->answer = (char*)malloc(strlen(answer));
	strcpy(q1->answer, answer);
	q1->next = NULL;
	*head = q1;
}
int caseInsensitiveComp(char* s1, char* s2) { //method for case insensitive comparison
	if (strlen(s1) != strlen(s2))
		return 0;
	for (unsigned i = 0; i < strlen(s1); i++) {
		if (tolower(s1[i]) != tolower(s2[i]))
			return 0;
	}
	return 1;
}
int isInArray(int arr[], int num, int i) { //utility function for difficuly5Clue 
	while (i >= 0) {
		if (arr[i] == num)
			return 1;
		i--;
	}
	return 0;
}
void difficulty2Clue(int ansSize) { // prints clue for difficulty levle two
	for (int i = 0; i < ansSize; i++)
		printf("- ");
	printf("\n");
}
void difficulty3Clue(int ansSize, char* ans) { // prints clue for difficulty levle three
	for (int i = 0; i < ansSize; i++)
	{
		if (i == 0 || i == ansSize - 1)
			printf("%c ", ans[i]);
		else
			printf("- ");
	}
	printf("\n");
}
void difficulty4Clue(int ansSize, char* ans) { // prints clue for difficulty levle four
	int c1 = rand() % ansSize, c2 = rand() % ansSize;
	while (c1 == c2)
		c2 = rand() % ansSize;
	for (int i = 0; i < ansSize; i++)
	{
		if (i == c1 || i == c2)
			printf("%c ", ans[i]);
		else
			printf("- ");
	}
	printf("\n");
}
void difficulty5Clue(int ansSize, char* ans) { // prints clue for difficulty levle five
	int *arr = (int*)malloc(ansSize * sizeof(int));
	for (int i = 0; i < ansSize; i++)  //generating array of random numbers
	{
		arr[i] = rand() % ansSize;
		while (isInArray(arr, arr[i], i - 1))
			arr[i] = rand() % ansSize;
	}
	for (int i = 0; i < ansSize; i++)
	{
		printf("%c ", ans[arr[i]]);
	}
	printf("\n");
	free(arr);
}

void main(int argc, char** argv) {
	if (argc != 3)
		printf("Invalid number of command line arguments passed!!\n");
	else
	{
		int difficulty = atoi(argv[2]);
		if (difficulty <= 0 || difficulty > 6)
			printf("Invalid second command line argument passed!!\n");
		else
		{
			FILE *file = fopen(argv[1], "r");
			if (file != NULL)  //if file found
			{
				srand(time(NULL));
				Question *head = NULL;
				Question *tail = NULL;
				char question[120];
				char *answer;
				int count = 0;
				if (fgets(question, 120, file) != NULL) // reading from file
				{
					char *quest = strtok(question, "?");
					answer = strtok(NULL, "?");
					answer[strlen(answer) - 1] = '\0';
					addTohead(&head, quest, &answer[1]);
					tail = head;
					while (fgets(question, 120, file) != NULL)// reading until end of file and dynamically adding to data Structure
					{
						quest = strtok(question, "?"); // separating question and answer
						answer = strtok(NULL, "?");
						answer[strlen(answer) - 1] = '\0';
						addQuestion(&tail, quest, &answer[1]);
						count++;
					}
					count++;
				}
				Question* currentQ = head;
				int index = 1;
				printf("There are %d Questions in the Quiz!!\n", count);
				char ans[30];
				int right = 0;
				switch (difficulty)
				{
				case 1:  //difficulty level 1
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n?\n", index, currentQ->question);
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						index++;
						currentQ = currentQ->next;
					}

					break;
				}
				case 2: //difficulty level 2
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n", index, currentQ->question);
						int ansSize = strlen(currentQ->answer);
						difficulty2Clue(ansSize);
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						currentQ = currentQ->next;
						index++;
					}

					break;
				}
				case 3: //difficulty level 3
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n", index, currentQ->question);
						int ansSize = strlen(currentQ->answer);
						difficulty3Clue(ansSize, currentQ->answer);
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						currentQ = currentQ->next;
						index++;
					}
					break;
				}
				case 4: //difficulty level 4
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n", index, currentQ->question);
						int ansSize = strlen(currentQ->answer);
						difficulty4Clue(ansSize, currentQ->answer);
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						currentQ = currentQ->next;
						index++;
					}
					break;
				}
				case 5: //difficulty level 5
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n", index, currentQ->question);
						int ansSize = strlen(currentQ->answer);
						difficulty5Clue(ansSize, currentQ->answer);
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						index++;
						currentQ = currentQ->next;
					}

					break;
				}
				case 6: //difficulty level 6
				{
					while (currentQ != NULL)
					{
						printf("%d. %s?\n", index, currentQ->question);
						int ansSize = strlen(currentQ->answer);
						int diffLevel = rand() % 5 + 1;
						switch (diffLevel)  //selecting random difficulty level
						{
						case 1:
							printf("?\n");
							break;
						case 2:
							difficulty2Clue(ansSize);
							break;
						case 3:
							difficulty3Clue(ansSize, currentQ->answer);
							break;
						case 4:
							difficulty4Clue(ansSize, currentQ->answer);
							break;
						case 5:
							difficulty5Clue(ansSize, currentQ->answer);
							break;
						}
						fgets(ans, 30, stdin);
						ans[strlen(ans) - 1] = '\0';
						if (caseInsensitiveComp(ans, currentQ->answer))
							right++;
						printf("Score: %d/%d\n", right, index);
						index++;
						currentQ = currentQ->next;
					}

					break;
				}
				}
				FILE* outFile = fopen("C:\\Users\\Steven\\OneDrive\\Course Work\\Year 2\\Semester 2\\C Programming\\Assignment02\\Code\\quiz_history.txt", "a");
				if (outFile != NULL) {  //writing to file if file found
					fprintf(outFile, "Test File:%s\tScore: %d/%d\tDifficulty: %d\n", argv[1], right, index, difficulty);
					printf("Score written to quiz_history.txt\n");
				}
				else { //creating file if not found and writing to it
					outFile = fopen("C:\\Users\\Steven\\OneDrive\\Course Work\\Year 2\\Semester 2\\C Programming\\Assignment02\\Code\\quiz_history.txt", "w");
					fprintf(outFile, "Test File:%s\tScore: %d/%d\tDifficulty: %d\n", argv[1], right, index, difficulty);
					printf("Score written to quiz_history.txt\n");
				}
			}
			else
				printf("%s does not exist!!\n", argv[1]);
		}
	}
}