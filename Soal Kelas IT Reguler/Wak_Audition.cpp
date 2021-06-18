#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Winner
{
    char winName[25];
    char winGender[15];
    int winAge;
    char winSong[105];
    int winScore;
};
Winner win[3];
Winner temp;
Winner swap;

struct Node
{
	char contestName[25];
	char contestGender[15];
	char contestSong[105];
	int contestAge;
	struct Node *kiri;
	struct Node *kanan;
	int height;
}*root = NULL;

int check;
int pmn;
int aman;
int max(int a, int b);
int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

struct Node* newNode(char contestName[], char contestGender[], char contestSong[], int contestAge)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(node->contestName,contestName);
	strcpy(node->contestGender,contestGender);
	strcpy(node->contestSong,contestSong);
	node->contestAge = contestAge;
	node->kiri = NULL;
	node->kanan = NULL;
	node->height = 1;
	return(node);
}

struct Node *rightRotate(struct Node *y)
{
	struct Node *x = y->kiri;
	struct Node *T2 = x->kanan;

	x->kanan = y;
	y->kiri = T2;

	y->height = max(height(y->kiri), height(y->kanan))+1;
	x->height = max(height(x->kiri), height(x->kanan))+1;

	return x;
}

struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->kanan;
	struct Node *T2 = y->kiri;

	y->kiri = x;
	x->kanan = T2;

	x->height = max(height(x->kiri), height(x->kanan))+1;
	y->height = max(height(y->kiri), height(y->kanan))+1;

	return y;
}

int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->kiri) - height(N->kanan);
}

struct Node* insert(struct Node* node, char contestName[], char contestGender[], char contestSong[], int contestAge)
{
	if (node == NULL){
		return(newNode(contestName,contestGender,contestSong,contestAge));
	}

	if (strcmp(contestName, node->contestName) < 0){
		node->kiri = insert(node->kiri, contestName,contestGender,contestSong,contestAge);
	}else if (strcmp(contestName, node->contestName) > 0){
		node->kanan = insert(node->kanan, contestName,contestGender,contestSong,contestAge);
	}else
		return node;

	node->height = 1 + max(height(node->kiri),height(node->kanan));

	int balance = getBalance(node);

	if (balance > 1 && strcmp(contestName, node->kiri->contestName) < 0){
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(contestName, node->kanan->contestName) > 0){
		return leftRotate(node);
	}

	if (balance > 1 && strcmp(contestName, node->kiri->contestName) > 0)
	{
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(contestName, node->kanan->contestName) < 0)
	{
		node->kanan = rightRotate(node->kanan);
		return leftRotate(node);
	}

	return node;
}

struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
    while (current->kiri != NULL)
        current = current->kiri;
  
    return current;
}

struct Node* deleteNode(struct Node* root, char contestName[], char contestGender[], char contestSong[], int contestAge)
{
    if (root == NULL){
        return root;
	}
  
    if (strcmp(contestName, root->contestName) < 0){
    	root->kiri = deleteNode(root->kiri, contestName,contestGender,contestSong,contestAge);
	}else if(strcmp(contestName, root->contestName) > 0){
        root->kanan = deleteNode(root->kanan, contestName,contestGender,contestSong,contestAge);
	}else
    {
    	if( (root->kiri == NULL) || (root->kanan == NULL) )
        {
            struct Node *temp = root->kiri ? root->kiri : root->kanan;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            	*root = *temp;
            free(temp);
        	check = 1;
		}
        else
        {
            struct Node* temp = minValueNode(root->kanan);
            strcpy(root->contestName,temp->contestName);
            strcpy(root->contestGender,temp->contestGender);
            strcpy(root->contestSong,temp->contestSong);
            root->contestAge = temp->contestAge;
            root->kanan = deleteNode(root->kanan, temp->contestName,temp->contestGender,temp->contestSong,temp->contestAge);
        }
    }
  
    if (root == NULL){
		return root;
	}
      
    root->height = 1 + max(height(root->kiri), height(root->kanan));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->kiri) >= 0){
        return rightRotate(root);
	}
  
    if (balance > 1 && getBalance(root->kiri) < 0)
    {
        root->kiri =  leftRotate(root->kiri);
        return rightRotate(root);
    }
  
    if (balance < -1 && getBalance(root->kanan) <= 0){
        return leftRotate(root);
	}
  
    if (balance < -1 && getBalance(root->kanan) > 0)
    {
        root->kanan = rightRotate(root->kanan);
        return leftRotate(root);
    }
  
    return root;
}

void viewPreOrder(struct Node *root)
{
	if(root != NULL)
	{
		printf("| %-21s | %-7s | %-4d | %-21s |\n",root->contestName,root->contestGender,root->contestAge,root->contestSong);
		viewPreOrder(root->kiri);
		viewPreOrder(root->kanan);
	}
}

void viewInOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewInOrder(root->kiri);
		printf("| %-21s | %-7s | %-4d | %-21s |\n",root->contestName,root->contestGender,root->contestAge,root->contestSong);
		viewInOrder(root->kanan);
	}
}

void viewPostOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewPostOrder(root->kiri);
		viewPostOrder(root->kanan);
		printf("| %-21s | %-7s | %-4d | %-21s |\n",root->contestName,root->contestGender,root->contestAge,root->contestSong);
	}
}

int checkData(struct Node *root){
	if(root == NULL){
		return 0;
	}else{
		return 1;
	}
}

int cekKapital(char contestName[]){
	if(isupper(contestName[0])){
		return 1;
	}else{
		return 0;
	}
}

int countWords(char contestName[]){
	int count = 0;
	int panjang = strlen(contestName);
	for(int i=0;i<panjang;i++){
		if(i==panjang-1){
			continue;
		}
		else{
			if(contestName[i]==32 && contestName[i+1]>32){
				count++;
   			}
  		}
 	}
 	return count;
}

int checkNumberExist(char contestName[]){
	int panjang = strlen(contestName);
	for(int i = 0 ; i < panjang ; i++){
		if(contestName[i] >='0' && contestName[i] <= '9'){
			return 0;
			break;
		}
	}
	return 1;
}

struct Node *searchDelete(Node **node, char contestName[]){
	int contestScore = 0;
	struct Winner* masuk = (struct Winner*)malloc(sizeof(struct Winner));
	if((*node)!=NULL){
		if(strcmp(contestName,(*node)->contestName) < 0){
			searchDelete(&(*node)->kiri,contestName);
		}else if(strcmp(contestName,(*node)->contestName) > 0){
			searchDelete(&(*node)->kanan,contestName);
		}else{
			do{
				printf("Input Score [1-100]: ");
				scanf("%d",&contestScore); fflush(stdin);
			}while(contestScore < 0 || contestScore > 100);
			aman = 1;
            if (pmn == 0)
            {
                strcpy(win[0].winName, (*node)->contestName);
                strcpy(win[0].winGender, (*node)->contestGender);
                win[0].winAge = (*node)->contestAge;
                strcpy(win[0].winSong, (*node)->contestSong);
                win[0].winScore = contestScore;
            }
            else if (pmn == 1)
            {
                strcpy(win[1].winName, (*node)->contestName);
                strcpy(win[1].winGender, (*node)->contestGender);
                win[1].winAge = (*node)->contestAge;
                strcpy(win[1].winSong, (*node)->contestSong);
                win[1].winScore = contestScore;
            }
            else if (pmn == 2)
            {
                strcpy(win[2].winName, (*node)->contestName);
                strcpy(win[2].winGender, (*node)->contestGender);
                win[2].winAge = (*node)->contestAge;
                strcpy(win[2].winSong, (*node)->contestSong);
                win[2].winScore = contestScore;
            }
            else if (pmn >= 3)
            {
                strcpy(temp.winName, (*node)->contestName);
                strcpy(temp.winGender, (*node)->contestGender);
                temp.winAge = (*node)->contestAge;
                strcpy(temp.winSong, (*node)->contestSong);
                temp.winScore = contestScore;
                for (int i = 0; i < 3; i++)
                {
                    if (win[i].winScore <= temp.winScore)
                    {
                        swap = win[i];
                        win[i] = temp;
                        temp = swap;
                        break;
                    }
                }
            }
            if (pmn == 2)
            {
                if (win[0].winScore <= win[1].winScore)
                {
                    swap = win[0];
                    win[0] = win[1];
                    win[1] = swap;
                }
            }
            if (pmn >= 3)
            {
                if (win[1].winScore <= win[2].winScore)
                {
                    swap = win[1];
                    win[1] = win[2];
                    win[2] = swap;
                }
                if (win[0].winScore <= win[1].winScore)
                {
                    swap = win[0];
                    win[0] = win[1];
                    win[1] = swap;
                }
                if (win[0].winScore <= win[2].winScore)
                {
                    swap = win[0];
                    win[0] = win[2];
                    win[2] = swap;
                }
            }
            pmn++;
			root = deleteNode(root , (*node)->contestName, (*node)->contestGender, (*node)->contestSong, (*node)->contestAge);
			system("PAUSE");
		}
	}else{
		printf("Contestant Not Found\n");
		system("PAUSE");
		return 0;
	}
}

void deleteAll(Node **node)
{
	while(root != NULL)
	{
		root = deleteNode(root , (*node)->contestName, (*node)->contestGender, (*node)->contestSong, (*node)->contestAge);
	}
}

void spasi(){
	for(int i = 0; i < 27 ; i++){
		printf("\n");
	}
}

int main()
{
	int id = 1, loop = 1, choice;
	while(loop == 1){
		system("cls");
		spasi();
		puts("Wak_Audition");
		printf("1. View Contestant\n");
		printf("2. Register Contestant\n");
		printf("3. Call Contestant\n");
		printf("4. End Audition\n");
		printf(">> ");
		scanf(" %d", &choice); fflush(stdin);
		if(choice==1){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("There is no contestant\n\n");
				system("PAUSE");
			}else{
				char chooseView[5];
				do{
					printf("Choose order [Pre | In | Post]: ");
					scanf("%[^\n]",&chooseView); fflush(stdin);
				}while(strcmp(chooseView,"Pre")!=0 && strcmp(chooseView,"In")!=0 && strcmp(chooseView,"Post")!=0);
				
				if(strcmp(chooseView,"Pre")==0){
					printf("| %-21s | %-7s | %-4s | %-21s |\n","Name","Gender","Age","Song");
					viewPreOrder(root);
					system("PAUSE");
				}else if(strcmp(chooseView,"In")==0){
					printf("| %-21s | %-7s | %-4s | %-21s |\n","Name","Gender","Age","Song");
					viewInOrder(root);
					system("PAUSE");
				}else if(strcmp(chooseView,"Post")==0){
					printf("| %-21s | %-7s | %-4s | %-21s |\n","Name","Gender","Age","Song");
					viewPostOrder(root);
					system("PAUSE");
				}	
			}
		}else if(choice==2){
			char contestName[25];
			int hasilCekContestName = 0;
			int wordCount = 0;
			int hasilCekNumber = 0;
			int hasilCekAkhir = 0;
			do{
				printf("Input Contestant Name: ");
				scanf("%[^\n]",&contestName); fflush(stdin);
				hasilCekContestName = cekKapital(contestName);
				wordCount = countWords(contestName) + 1;
				hasilCekNumber = checkNumberExist(contestName);
				hasilCekAkhir = hasilCekContestName + hasilCekNumber;
			}while(strlen(contestName) < 6 || strlen(contestName) > 20 || wordCount < 2 || hasilCekAkhir!=2);
			
			char contestGender[15];
			do{
				printf("Input Gender [male | female]: ");
				scanf("%[^\n]",&contestGender); fflush(stdin);
			}while(strcmp(contestGender,"male")!=0 && strcmp(contestGender,"female")!=0);
			
			char contestSong[15];
			printf("Input Song: ");
			scanf("%[^\n]",&contestSong); fflush(stdin);
			
			int contestAge;
			do{
				printf("Input Age [6 - 59]: ");
				scanf("%d",&contestAge); fflush(stdin);
			}while(contestAge < 6 || contestAge > 59);
			
			root = insert(root, contestName, contestGender, contestSong, contestAge);
			printf("Insert Success\n");
			system("PAUSE");
		}else if(choice==3){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("There is no data\n\n");
				system("PAUSE");
			}else{
				char contestName[25];
				printf("| %-21s | %-7s | %-4s | %-21s |\n","Name","Gender","Age","Song");
				viewInOrder(root);		
				printf("Input Contestant Name: ");
				scanf("%[^\n]",&contestName); fflush(stdin);
				searchDelete(&root,contestName);
			}
		}else if(choice==4){
			if (aman == 1)
            {
                printf("| Rank | Name                      | Gender | Age | Score | Song\n");
                if (pmn >= 1)
                {
                    if (strcmp(win[0].winGender, "male") == 0)
                    {
                        printf("| %-4d | Mr. %-21s | %-6s | %-3d | %-5d | %s\n", 1, win[0].winName, win[0].winGender, win[0].winAge, win[0].winScore, win[0].winSong);
                    }
                    else
                    {
                        printf("| %-4d | Mrs. %-20s | %-6s | %-3d | %-5d | %s\n", 1, win[0].winName, win[0].winGender, win[0].winAge, win[0].winScore, win[0].winSong);
                    }
                }
                if (pmn >= 2)
                {
                    if (strcmp(win[1].winGender, "male") == 0)
                    {
                        printf("| %-4d | Mr. %-21s | %-6s | %-3d | %-5d | %s\n", 2, win[1].winName, win[1].winGender, win[1].winAge, win[1].winScore, win[1].winSong);
                    }
                    else
                    {
                        printf("| %-4d | Mrs. %-20s | %-6s | %-3d | %-5d | %s\n", 2, win[1].winName, win[1].winGender, win[1].winAge, win[1].winScore, win[1].winSong);
                    }
                }
                if (pmn >= 3)
                {
                    if (strcmp(win[2].winGender, "male") == 0)
                    {
                        printf("| %-4d | Mr. %-21s | %-6s | %-3d | %-5d | %s\n", 3, win[2].winName, win[2].winGender, win[2].winAge, win[2].winScore, win[2].winSong);
                    }
                    else
                    {
                        printf("| %-4d | Mrs. %-20s | %-6s | %-3d | %-5d | %s\n", 3, win[2].winName, win[2].winGender, win[2].winAge, win[2].winScore, win[2].winSong);
                    }
                }
            }
            else
            {
                printf("There is no winner");
            }
			deleteAll(&root);
			loop = 0;
			system("exit");
		}	
	}
	return 0;
}
