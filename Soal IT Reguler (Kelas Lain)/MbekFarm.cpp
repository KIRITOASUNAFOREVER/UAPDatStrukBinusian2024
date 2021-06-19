#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
	int goatID;
	char goatName[105];
	char goatColor[15];
	int goatWeight;
	int goatAge;
	struct Node *kiri;
	struct Node *kanan;
	int height;
}*root = NULL;

int check;
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

struct Node* newNode(int goatID, char goatName[], char goatColor[], int goatWeight, int goatAge)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->goatID = goatID;
	strcpy(node->goatName,goatName);
	strcpy(node->goatColor,goatColor);
	node->goatWeight = goatWeight;
	node->goatAge = goatAge;
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

struct Node* insert(struct Node* node, int goatID, char goatName[], char goatColor[], int goatWeight, int goatAge)
{
	if (node == NULL){
		return(newNode(goatID,goatName,goatColor,goatWeight,goatAge));
	}

	if (goatID < node->goatID){
		node->kiri = insert(node->kiri, goatID,goatName,goatColor,goatWeight,goatAge);
	}else if (goatID > node->goatID){
		node->kanan = insert(node->kanan, goatID,goatName,goatColor,goatWeight,goatAge);
	}else
		return node;

	node->height = 1 + max(height(node->kiri),height(node->kanan));

	int balance = getBalance(node);

	if (balance > 1 && goatID < node->kiri->goatID){
		return rightRotate(node);
	}

	if (balance < -1 && goatID > node->kanan->goatID){
		return leftRotate(node);
	}

	if (balance > 1 && goatID > node->kiri->goatID)
	{
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}

	if (balance < -1 && goatID < node->kanan->goatID)
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

struct Node* deleteNode(struct Node* root, int goatID, char goatName[], char goatColor[], int goatWeight, int goatAge)
{
    if (root == NULL){
        return root;
	}
  
    if (goatID < root->goatID){
    	root->kiri = deleteNode(root->kiri, goatID,goatName,goatColor,goatWeight,goatAge);
	}else if(goatID > root->goatID){
        root->kanan = deleteNode(root->kanan, goatID,goatName,goatColor,goatWeight,goatAge);
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
            root->goatID = temp->goatID;
            strcpy(root->goatName,temp->goatName);
            strcpy(root->goatColor,temp->goatColor);
            root->goatWeight = temp->goatWeight;
            root->goatAge = temp->goatAge;
            root->kanan = deleteNode(root->kanan, temp->goatID,temp->goatName,temp->goatColor,temp->goatWeight,temp->goatAge);
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
		puts("==============================");
		printf("Goat's ID       :  %d\n",root->goatID);
		printf("Goat's Name     :  %s\n",root->goatName);
		printf("Goat's Color    :  %s\n",root->goatColor);
		printf("Goat's Weight   :  %d KG\n",root->goatWeight); 
		printf("Goat's Age      :  %d Months\n",root->goatAge);
		puts("==============================\n\n");
		viewPreOrder(root->kiri);
		viewPreOrder(root->kanan);
	}
}

void viewInOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewInOrder(root->kiri);
		puts("==============================");
		printf("Goat's ID       :  %d\n",root->goatID);
		printf("Goat's Name     :  %s\n",root->goatName);
		printf("Goat's Color    :  %s\n",root->goatColor);
		printf("Goat's Weight   :  %d KG\n",root->goatWeight); 
		printf("Goat's Age      :  %d Months\n",root->goatAge);
		puts("==============================\n\n");
		viewInOrder(root->kanan);
	}
}

void viewPostOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewPostOrder(root->kiri);
		viewPostOrder(root->kanan);
		puts("==============================");
		printf("Goat's ID       :  %d\n",root->goatID);
		printf("Goat's Name     :  %s\n",root->goatName);
		printf("Goat's Color    :  %s\n",root->goatColor);
		printf("Goat's Weight   :  %d KG\n",root->goatWeight); 
		printf("Goat's Age      :  %d Months\n",root->goatAge);
		puts("==============================\n\n");
	}
}

int checkData(struct Node *root){
	if(root == NULL){
		return 0;
	}else{
		return 1;
	}
}

int checkAlphaExist(char idGoat[]){
	int panjang = strlen(idGoat);
	for(int i = 0 ; i < panjang ; i++){
		if(idGoat[i] >='A' && idGoat[i] <= 'Z'){
			return 1;
			break;
		}else if(idGoat[i] >='a' && idGoat[i] <= 'z'){
			return 1;
			break;
		}
	}
	return 0;
}

struct Node *searchInsert(Node **node, int goatID){
	char idGoat[10];
	int hasilCekIdGoat = 0;
	int goatsID = 0;
	if((*node)!=NULL){
		if(goatID < (*node)->goatID){
			searchInsert(&(*node)->kiri,goatID);
		}else if(goatID > (*node)->goatID){
			searchInsert(&(*node)->kanan,goatID);
		}else{
			puts("GOAT ID MUST BE UNIQUE!");
			printf("\n");
			do{
				printf("Insert goat's id [5 digits number] : ");
				scanf("%[^\n]",&idGoat); fflush(stdin);
				if(strlen(idGoat)!=5){
					puts("GOAT ID MUST CONSIST OF 5 DIGITS!");
					printf("\n");
				}
				hasilCekIdGoat = checkAlphaExist(idGoat);
				if(hasilCekIdGoat==1){
					puts("GOAT ID MUST CONSTS OF NUMBERS ONLY!");
					printf("\n");
				}
			}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
			goatsID = atoi(idGoat);
			searchInsert(&root,goatsID);
		}
	}else{
		printf("\n");
		char goatName[105];
		do{
			printf("Insert goat's name [2 chars or more] : ");
			scanf("%[^\n]",&goatName); fflush(stdin);
			if(strlen(goatName) < 2){
				puts("GOAT NAME MUST CONSISTS OF 2 CHARACTERS OR MORE!");
				printf("\n");	
			}
		}while(strlen(goatName) < 2);
		
		printf("\n");
		char goatColor[15];
		char tempGoatColor[15];
		do{
			printf("Insert goat's color [WHITE|BLACK|BROWN] : ");
			scanf("%s",&goatColor); fflush(stdin);
			strcpy(tempGoatColor,goatColor);
			strupr(tempGoatColor);
			if(strcmp(tempGoatColor,"WHITE")!=0 && strcmp(tempGoatColor,"BLACK")!=0 && strcmp(tempGoatColor,"BROWN")!=0){
				puts("GOAT'S COLOR CAN ONLY BE WHITE / BLACK / BROWN");
				printf("\n");	
			}
		}while(strcmp(tempGoatColor,"WHITE")!=0 && strcmp(tempGoatColor,"BLACK")!=0 && strcmp(tempGoatColor,"BROWN")!=0);
		
		printf("\n");
		int goatWeight = 0;
		do{
			printf("Insert goat's weight in KG [2-150] : ");
			scanf("%d",&goatWeight); fflush(stdin);
			if(goatWeight < 2 || goatWeight > 150){
				puts("GOAT'S WEIGHT MUST BE BETWEEN 2 AND 150 (INCLUSIVELY)");
				printf("\n");
			}
		}while(goatWeight < 2 || goatWeight > 150);
		
		printf("\n");
		int goatAge = 0;
		do{
			printf("Insert goat's age in month(s) [0-60] : ");
			scanf("%d",&goatAge); fflush(stdin);
			if(goatAge < 0 || goatAge > 60){
				puts("GOAT'S AGE MUST BE BETWEEN 0 AND 60 (INCLUSIVELY)");
				printf("\n");
			}
		}while(goatAge < 0 || goatAge > 60);
		
		printf("\n");
		char areYouSure[5];
		do{
			printf("ARE YOU SURE YOU WANT TO ADD mama GOAT? [Y|N] > ");
			scanf("%s",&areYouSure); fflush(stdin);
			if(strcmp(areYouSure,"Y")!=0 && strcmp(areYouSure,"N")!=0){
				printf("\n");
			}
		}while(strcmp(areYouSure,"Y")!=0 && strcmp(areYouSure,"N")!=0);
		if(strcmp(areYouSure,"Y")==0){
			root = insert(root, goatID, goatName, goatColor, goatWeight, goatAge);
			printf("SUCCESS ADD\n");
			system("PAUSE");
		}
		return 0;
	}
}

struct Node *searchDelete(Node **node, int goatID){
	char idGoat[10];
	int hasilCekIdGoat = 0;
	char namaKambing[105];
	if((*node)!=NULL){
		if(goatID < (*node)->goatID){
			searchDelete(&(*node)->kiri,goatID);
		}else if(goatID > (*node)->goatID){
			searchDelete(&(*node)->kanan,goatID);
		}else{
			strcpy(namaKambing,(*node)->goatName);
			strupr(namaKambing);
			if(namaKambing[0]=='M' && namaKambing[1]=='Y'){
				puts("YOU CANNOT REMOVE YOUR GOAT!");
				printf("\n");
			}else{
				root = deleteNode(root , (*node)->goatID, (*node)->goatName, (*node)->goatColor, (*node)->goatWeight, (*node)->goatAge);
				puts("SUCCESS REMOVE GOAT!");
			}
			system("PAUSE");
		}
	}else{
		puts("ID IS INVALID!");
		printf("\n");
		do{
			printf("ENTER GOAT ID TO BE REMOVED! > ");
			scanf("%[^\n]",&idGoat); fflush(stdin);
			hasilCekIdGoat = checkAlphaExist(idGoat);
			if(hasilCekIdGoat==1 || strlen(idGoat)!=5){
				puts("ID IS INVALID!");
				printf("\n");
			}
		}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
		int goatsID = 0;
		goatsID = atoi(idGoat);
		searchDelete(&root,goatsID);
		return 0;
	}
}

void deleteAll(Node **node)
{
	while(root != NULL)
	{
		root = deleteNode(root , (*node)->goatID, (*node)->goatName, (*node)->goatColor, (*node)->goatWeight, (*node)->goatAge);
	}
}

int main()
{
	int id = 1, loop = 1, choice;
	root = insert(root, 12345, "mybudi", "brown", 2, 3);
	root = insert(root, 32543, "ab", "black", 2, 0);
	root = insert(root, 65487, "Bleki", "black", 3, 1);
	while(loop == 1){
		system("cls");
		puts("Mbek Farm"); printf("\n");
		printf("1. Insert New Goat\n");
		printf("2. Remove a goat\n");
		printf("3. See all goat\n");
		printf("4. Remove all goat\n");
		printf("5. Exit\n");
		printf(" >> ");
		scanf(" %d", &choice); fflush(stdin);
		if(choice==1){
			char idGoat[10];
			int hasilCekIdGoat = 0;
			printf("\n");
			do{
				printf("Insert goat's id [5 digits number] : ");
				scanf("%[^\n]",&idGoat); fflush(stdin);
				if(strlen(idGoat)!=5){
					puts("GOAT ID MUST CONSIST OF 5 DIGITS!");
					printf("\n");
				}
				hasilCekIdGoat = checkAlphaExist(idGoat);
				if(hasilCekIdGoat==1){
					puts("GOAT ID MUST CONSTS OF NUMBERS ONLY!");
					printf("\n");
				}
			}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
			int goatID = 0;
			goatID = atoi(idGoat);
			searchInsert(&root,goatID);
		}else if(choice==2){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("\nYOU DON'T HAVE ANY GOAT!\n\n");
				system("PAUSE");
			}else{
				int pilihan;
				int goatID = 0;
				do{
					system("cls");
					puts("How do you want to see all goat?");
					puts("1. In order");
					puts("2. Pre order");
					puts("3. Post order");
					printf(" >> ");
					scanf("%d",&pilihan); fflush(stdin);
				}while(pilihan < 1 || pilihan > 3);
				if(pilihan==1){
					printf("\n");
					viewInOrder(root);
					char idGoat[10];
					int hasilCekIdGoat = 0;
					printf("\n");
					do{
						printf("ENTER GOAT ID TO BE REMOVED! > ");
						scanf("%[^\n]",&idGoat); fflush(stdin);
						hasilCekIdGoat = checkAlphaExist(idGoat);
						if(hasilCekIdGoat==1 || strlen(idGoat)!=5){
							puts("ID IS INVALID!");
							printf("\n");
						}
					}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
					int goatID = 0;
					goatID = atoi(idGoat);
					searchDelete(&root,goatID);
				}else if(pilihan==2){
					printf("\n");
					viewPreOrder(root);
					char idGoat[10];
					int hasilCekIdGoat = 0;
					printf("\n");
					do{
						printf("ENTER GOAT ID TO BE REMOVED! > ");
						scanf("%[^\n]",&idGoat); fflush(stdin);
						hasilCekIdGoat = checkAlphaExist(idGoat);
						if(hasilCekIdGoat==1 || strlen(idGoat)!=5){
							puts("ID IS INVALID!");
							printf("\n");
						}
					}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
					int goatID = 0;
					goatID = atoi(idGoat);
					searchDelete(&root,goatID);
				}else if(pilihan==3){
					printf("\n");
					viewPostOrder(root);
					char idGoat[10];
					int hasilCekIdGoat = 0;
					printf("\n");
					do{
						printf("ENTER GOAT ID TO BE REMOVED! > ");
						scanf("%[^\n]",&idGoat); fflush(stdin);
						hasilCekIdGoat = checkAlphaExist(idGoat);
						if(hasilCekIdGoat==1 || strlen(idGoat)!=5){
							puts("ID IS INVALID!");
							printf("\n");
						}
					}while(strlen(idGoat)!=5 || hasilCekIdGoat == 1);
					int goatID = 0;
					goatID = atoi(idGoat);
					searchDelete(&root,goatID);
				}
			}
		}else if(choice==3){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("\nYOU DON'T HAVE ANY GOAT!\n\n");
				system("PAUSE");
			}else{
				int pilihan;
				do{
					system("cls");
					puts("How do you want to see all goat?");
					puts("1. In order");
					puts("2. Pre order");
					puts("3. Post order");
					printf(" >> ");
					scanf("%d",&pilihan); fflush(stdin);
				}while(pilihan < 1 || pilihan > 3);
				if(pilihan==1){
					printf("\n");
					viewInOrder(root);
					system("PAUSE");
				}else if(pilihan==2){
					printf("\n");
					viewPreOrder(root);
					system("PAUSE");
				}else if(pilihan==3){
					printf("\n");
					viewPostOrder(root);
					system("PAUSE");
				}
			}
		}else if(choice==4){
			printf("\n");
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("\nYOU DON'T HAVE ANY GOAT!\n\n");
				system("PAUSE");
			}else{
				char areYouSure[5];
				do{
					printf("ARE YOU SURE YOU WANT TO REMOVE ALL GOAT? [Y|N] > ");
					scanf("%s",&areYouSure); fflush(stdin);
					if(strcmp(areYouSure,"Y")!=0 && strcmp(areYouSure,"N")!=0){
						printf("\n");
					}
				}while(strcmp(areYouSure,"Y")!=0 && strcmp(areYouSure,"N")!=0);
				if(strcmp(areYouSure,"Y")==0){
					deleteAll(&root);
					printf("SUCCESS REMOVE ALL GOAT!\n\n");
					system("PAUSE");
				}
			}
		}else if(choice==5){
			loop = 0;
			system("exit");
		}
	}	
	return 0;
}
