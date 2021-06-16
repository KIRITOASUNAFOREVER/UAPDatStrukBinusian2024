#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node
{
	char phoneName[30];
	char phoneDescription[100];
	char phoneType[10];
	int phonePrice;
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

struct Node* newNode(char phoneName[], char phoneDescription[], char phoneType[], int phonePrice)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(node->phoneName,phoneName);
	strcpy(node->phoneDescription,phoneDescription);
	strcpy(node->phoneType,phoneType);
	node->phonePrice = phonePrice;
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

struct Node* insert(struct Node* node, char phoneName[], char phoneDescription[], char phoneType[], int phonePrice)
{
	if (node == NULL){
		return(newNode(phoneName,phoneDescription,phoneType,phonePrice));
	}

	if (strcmp(phoneName, node->phoneName) < 0){
		node->kiri = insert(node->kiri, phoneName,phoneDescription,phoneType,phonePrice);
	}else if (strcmp(phoneName, node->phoneName) > 0){
		node->kanan = insert(node->kanan, phoneName,phoneDescription,phoneType,phonePrice);
	}else
		return node;

	node->height = 1 + max(height(node->kiri),height(node->kanan));

	int balance = getBalance(node);

	if (balance > 1 && strcmp(phoneName, node->kiri->phoneName) < 0){
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(phoneName, node->kanan->phoneName) > 0){
		return leftRotate(node);
	}

	if (balance > 1 && strcmp(phoneName, node->kiri->phoneName) > 0)
	{
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(phoneName, node->kanan->phoneName) < 0)
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

struct Node* deleteNode(struct Node* root, char phoneName[], char phoneDescription[], char phoneType[], int phonePrice)
{
    if (root == NULL){
        return root;
	}
  
    if (strcmp(phoneName, root->phoneName) < 0){
    	root->kiri = deleteNode(root->kiri, phoneName,phoneDescription,phoneType,phonePrice);
	}else if(strcmp(phoneName, root->phoneName) > 0){
        root->kanan = deleteNode(root->kanan, phoneName,phoneDescription,phoneType,phonePrice);
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
            strcpy(root->phoneName, temp->phoneName);
            strcpy(root->phoneDescription,temp->phoneDescription);
            strcpy(root->phoneType,temp->phoneType);
            root->phonePrice = temp->phonePrice;
            root->kanan = deleteNode(root->kanan, temp->phoneName,temp->phoneDescription,temp->phoneType,temp->phonePrice);
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
		printf("| %-25s | %-26s | %-16s | %-16d |\n",root->phoneName,root->phoneDescription,root->phoneType,root->phonePrice);
		printf("*==============================================================================================*\n");
		viewPreOrder(root->kiri);
		viewPreOrder(root->kanan);
	}
}

void viewInOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewInOrder(root->kiri);
		printf("| %-25s | %-26s | %-16s | %-16d |\n",root->phoneName,root->phoneDescription,root->phoneType,root->phonePrice);
		printf("*==============================================================================================*\n");
		viewInOrder(root->kanan);
	}
}

void viewPostOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewPostOrder(root->kiri);
		viewPostOrder(root->kanan);
		printf("| %-25s | %-26s | %-16s | %-16d |\n",root->phoneName,root->phoneDescription,root->phoneType,root->phonePrice);
		printf("*==============================================================================================*\n");
	}
}

int checkData(struct Node *root){
	if(root == NULL){
		return 0;
	}else{
		return 1;
	}
}

int countWords(char phoneName[]){
	int count = 0;
	int panjang = strlen(phoneName);
	for(int i=0;i<panjang;i++){
		if(i==panjang-1){
			continue;
		}
		else{
			if(phoneName[i]==32 && phoneName[i+1]>32){
				count++;
   			}
  		}
 	}
 	return count;
}

int cekKapital(char phoneDescription[]){
	if(isupper(phoneDescription[0])){
		return 1;
	}else{
		return 0;
	}
}

struct Node *searchInsert(Node **node, char phoneName[]){
	char phoneDescription[100];
	char namaHandphone[30];
	char phoneType[10];
	int phonePrice;
	int hasilCekPhoneDescription;
	int wordCount;
		
	if((*node)!=NULL){
		if(strcmp(phoneName,(*node)->phoneName) < 0){
			searchInsert(&(*node)->kiri,phoneName);
		}else if(strcmp(phoneName,(*node)->phoneName) > 0){
			searchInsert(&(*node)->kanan,phoneName);
		}else{
			do{
				printf("Input Phone's Name [7 - 25 characters | min. 2 words | must be unique]: ");
				scanf(" %[^\n]s", &namaHandphone); fflush(stdin);
				wordCount = countWords(namaHandphone);
			}while(strlen(namaHandphone) < 7 || strlen(namaHandphone) > 25 || wordCount <= 1);
			
			searchInsert(&root,namaHandphone);
		}
	}else{
		do{
			printf("Input Phone's Description [first character must be capitalized]: ");
			scanf("%[^\n]s",&phoneDescription); fflush(stdin);
			hasilCekPhoneDescription = cekKapital(phoneDescription);
		}while(hasilCekPhoneDescription==0);
		
		do{
			printf("Input Phone's Type [Premium | Rare | Common]: ");
			scanf("%[^\n]s",&phoneType); fflush(stdin);
		}while(strcmp(phoneType,"Premium")!=0 && strcmp(phoneType,"Rare")!=0 && strcmp(phoneType,"Common")!=0);
		
		do{
			printf("Input Phone's Price [1.000.000 - 10.000.000]: ");
			scanf("%d",&phonePrice); fflush(stdin);
		}while(phonePrice < 1000000 || phonePrice > 10000000);
		
		root = insert(root, phoneName, phoneDescription, phoneType, phonePrice);
		printf("Successfully inserted a new phone!\n");
		system("PAUSE");
		return 0;
	}
}

struct Node *searchDelete(Node **node, char phoneName[]){
	char namaHandphone[30];
	char areYouSure[5];
	if((*node)!=NULL){
		if(strcmp(phoneName,(*node)->phoneName) < 0){
			searchDelete(&(*node)->kiri,phoneName);
		}else if(strcmp(phoneName,(*node)->phoneName) > 0){
			searchDelete(&(*node)->kanan,phoneName);
		}else{
			printf("Are you sure [Yes | No] (case-insensitive): ");
			scanf("%s",&areYouSure); fflush(stdin);
			strupr(areYouSure);
			if(strcmp(areYouSure,"YES")==0){
				root = deleteNode(root , (*node)->phoneName, (*node)->phoneDescription, (*node)->phoneType, (*node)->phonePrice);
				printf("Successfully removed the phone!\n");
				system("PAUSE");
			}else if(strcmp(areYouSure,"NO")){
				return 0;
			}
		}
	}else{
		printf("Phone does not exist!\n");
		printf("Input Phone's Name to be Removed: ");
		scanf(" %[^\n]s", &namaHandphone); fflush(stdin);
		searchDelete(&root,namaHandphone);
		return 0;
	}
}

void deleteAll(Node **node)
{
	while(root != NULL)
	{
		root = deleteNode(root , (*node)->phoneName, (*node)->phoneDescription, (*node)->phoneType, (*node)->phonePrice);
	}
}

int main()
{
	int id = 1, loop = 1, choice;
	
	while(loop == 1){
		system("cls");
		printf("*=======================================*\n");
		printf("|       DeluXe Smartphone Shop          |\n");
		printf("*=======================================*\n");
		printf("1. Insert New Phone\n");
		printf("2. View All Phones\n");
		printf("3. Remove Phone\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf(" %d", &choice); fflush(stdin);
		if(choice==1){
			system("cls");
			char phoneName[100];
			int wordCount = 0;
			do{
				printf("Input Phone's Name [7 - 25 characters | min. 2 words | must be unique]: ");
				scanf(" %[^\n]s", &phoneName); fflush(stdin);
				wordCount = countWords(phoneName) + 1;
			}while(strlen(phoneName) < 7 || strlen(phoneName) > 25 || wordCount < 2);
			searchInsert(&root,phoneName);
		}else if(choice==2){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				system("cls");
				printf("No phone available! please come back later...\n\n");
				system("PAUSE");
			}else{
				printf("%d\n",&jumlahData);
				int pilihan;
				system("cls");
				printf("Choose View Order\n");
				printf("=================\n");
				printf("1. Pre Order\n");
				printf("2. In Order\n");
				printf("3. Post Order\n");
				printf("Input [1 - 3] >> ");
				scanf("%d",&pilihan); fflush(stdin);
				if(pilihan==1){
					system("cls");
					printf("*==============================================================================================*\n");
					printf("| %-25s | %-26s | %-16s | %-16s |\n","Phone's Name","Phone's Description","Phone's Type","Phone's Price");
					printf("*==============================================================================================*\n");	
					viewPreOrder(root);
					system("PAUSE");
				}else if(pilihan==2){
					system("cls");
					printf("*==============================================================================================*\n");
					printf("| %-25s | %-26s | %-16s | %-16s |\n","Phone's Name","Phone's Description","Phone's Type","Phone's Price");
					printf("*==============================================================================================*\n");	
					viewInOrder(root);
					system("PAUSE");
				}else if(pilihan==3){
					system("cls");
					printf("*==============================================================================================*\n");
					printf("| %-25s | %-26s | %-16s | %-16s |\n","Phone's Name","Phone's Description","Phone's Type","Phone's Price");
					printf("*==============================================================================================*\n");	
					viewPostOrder(root);
					system("PAUSE");
				}
			}
		}else if(choice==3){
			system("cls");
			char phoneName[100];
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				system("cls");
				printf("No phone available! please come back later...\n\n");
				system("PAUSE");
			}else{
				system("cls");
				printf("*==============================================================================================*\n");
				printf("| %-25s | %-26s | %-16s | %-16s |\n","Phone's Name","Phone's Description","Phone's Type","Phone's Price");
				printf("*==============================================================================================*\n");	
				viewInOrder(root);
				printf("Input Phone's Name to be Removed: ");
				scanf(" %[^\n]s", &phoneName); fflush(stdin);
				searchDelete(&root,phoneName);
			}
		}else if(choice==4){
			deleteAll(&root);
			loop = 0;
			system("exit");
		}
	}	
	return 0;
}
