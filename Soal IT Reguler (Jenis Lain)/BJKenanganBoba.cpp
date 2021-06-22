#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
	char bobaName[105];
	int bobaPrice;
	char bobaTopping[15];
	int bobaQuantity;
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

struct Node* newNode(char bobaName[], int bobaPrice, char bobaTopping[], int bobaQuantity)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(node->bobaName,bobaName);
	node->bobaPrice = bobaPrice;
	strcpy(node->bobaTopping,bobaTopping);
	node->bobaQuantity = bobaQuantity;
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

struct Node* insert(struct Node* node, char bobaName[], int bobaPrice, char bobaTopping[], int bobaQuantity)
{
	if (node == NULL){
		return(newNode(bobaName,bobaPrice,bobaTopping,bobaQuantity));
	}

	if (strcmp(bobaName, node->bobaName) < 0){
		node->kiri = insert(node->kiri, bobaName,bobaPrice,bobaTopping,bobaQuantity);
	}else if (strcmp(bobaName, node->bobaName) > 0){
		node->kanan = insert(node->kanan, bobaName,bobaPrice,bobaTopping,bobaQuantity);
	}else
		return node;

	node->height = 1 + max(height(node->kiri),height(node->kanan));

	int balance = getBalance(node);

	if (balance > 1 && strcmp(bobaName, node->kiri->bobaName) < 0){
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(bobaName, node->kanan->bobaName) > 0){
		return leftRotate(node);
	}

	if (balance > 1 && strcmp(bobaName, node->kiri->bobaName) > 0)
	{
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(bobaName, node->kanan->bobaName) < 0)
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

struct Node* deleteNode(struct Node* root, char bobaName[], int bobaPrice, char bobaTopping[], int bobaQuantity)
{
    if (root == NULL){
        return root;
	}
  
    if (strcmp(bobaName, root->bobaName) < 0){
    	root->kiri = deleteNode(root->kiri, bobaName,bobaPrice,bobaTopping,bobaQuantity);
	}else if(strcmp(bobaName, root->bobaName) > 0){
        root->kanan = deleteNode(root->kanan, bobaName,bobaPrice,bobaTopping,bobaQuantity);
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
            strcpy(root->bobaName,temp->bobaName);
            root->bobaPrice = temp->bobaPrice;
            strcpy(root->bobaTopping,temp->bobaTopping);
            root->bobaQuantity = temp->bobaQuantity;
            root->kanan = deleteNode(root->kanan, temp->bobaName,temp->bobaPrice,temp->bobaTopping,temp->bobaQuantity);
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
		printf("| %-25s | %-13d | %-15s | %-13d |\n",root->bobaName,root->bobaPrice,root->bobaTopping,root->bobaQuantity);
		viewPreOrder(root->kiri);
		viewPreOrder(root->kanan);
	}
}

void viewInOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewInOrder(root->kiri);
		printf("| %-25s | %-13d | %-15s | %-13d |\n",root->bobaName,root->bobaPrice,root->bobaTopping,root->bobaQuantity);
		viewInOrder(root->kanan);
	}
}

void viewPostOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewPostOrder(root->kiri);
		viewPostOrder(root->kanan);
		printf("| %-25s | %-13d | %-15s | %-13d |\n",root->bobaName,root->bobaPrice,root->bobaTopping,root->bobaQuantity);
	}
}

int checkData(struct Node *root){
	if(root == NULL){
		return 0;
	}else{
		return 1;
	}
}

struct Node *searchDelete(Node **node, char bobaName[]){
	char Username[30];
	char areYouSure[5];
	if((*node)!=NULL){
		if(strcmp(bobaName,(*node)->bobaName) < 0){
			searchDelete(&(*node)->kiri,bobaName);
		}else if(strcmp(bobaName,(*node)->bobaName) > 0){
			searchDelete(&(*node)->kanan,bobaName);
		}else{
			do{
				printf("Are you sure want to delete? ['Yes' or 'No'] (case insensitive): ");
				scanf("%s",&areYouSure); fflush(stdin);
				strupr(areYouSure);
			}while(strcmp(areYouSure,"YES")!=0 && strcmp(areYouSure,"NO")!=0);
			if(strcmp(areYouSure,"YES")==0){
				root = deleteNode(root , (*node)->bobaName, (*node)->bobaPrice, (*node)->bobaTopping, (*node)->bobaQuantity);
				printf("Item deleted!\n\n");
				system("PAUSE");
			}
		}
	}else{
		return 0;
	}
}

void deleteAll(Node **node)
{
	while(root != NULL)
	{
		root = deleteNode(root , (*node)->bobaName, (*node)->bobaPrice, (*node)->bobaTopping, (*node)->bobaQuantity);
	}
}

int checkExistString(char bobaName[]){
		if(strstr(bobaName,"Boba")){
			return 1;
		}
	return 0;
}

int FirstPlace(char bobaName[]){
	if((bobaName[0]=='B' || bobaName[0]=='b') && bobaName[1]=='o' && bobaName[2]=='b' && bobaName[3]=='a'){
		return 0;
	}
	return 1;
}

void logoAwal(){
	puts("__________      ____.  ____  __. __________      ___.");
	puts("\\______   \\    |    | |    |/ _| \\______   \\ ____\\_ |__ _____");
	puts(" |    |  _/    |    | |      <    |    |  _//  _ \\| __ \\\\__  \\");
	puts(" |    |   \\/\\__|    | |    |  \\   |    |   (  <_> ) \\_\\ \\/ __ \\_");
	puts(" |______  /\\________| |____|__ \\  |______  /\\____/|___  (____  /");
	puts("        \\/                    \\/         \\/           \\/     \\/");
	printf("\n\n\n\n\n");
}

void spasi(){
	for(int i = 0; i < 30; i++){
		printf("\n");
	}
}

int main()
{
	int id = 1, loop = 1, choice;
	while(loop == 1){
		system("cls");
		spasi();
		logoAwal();
		puts("Bluejack Kenangan Boba!");
		printf("1. View Drink\n");
		printf("2. Insert Drink\n");
		printf("3. Delete Drink\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf(" %d", &choice); fflush(stdin);
		if(choice==1){
			system("cls");
			spasi();
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("There is no boba here!\n\n");
				system("PAUSE");
			}else{
				char chooseView[5];
				do{
					printf("Choose Order [Pre | In | Post]: ");
					scanf("%[^\n]",&chooseView); fflush(stdin);
				}while(strcmp(chooseView,"Pre")!=0 && strcmp(chooseView,"In")!=0 && strcmp(chooseView,"Post")!=0);
				
				if(strcmp(chooseView,"Pre")==0){
					puts("===============================================================================");
					printf("| %-25s | %-13s | %-15s | %-13s |\n","Name","Price","Topping","Quantity");
					puts("===============================================================================");
					viewPreOrder(root);
					puts("===============================================================================");
					system("PAUSE");
				}else if(strcmp(chooseView,"In")==0){
					puts("===============================================================================");
					printf("| %-25s | %-13s | %-15s | %-13s |\n","Name","Price","Topping","Quantity");
					puts("===============================================================================");
					viewInOrder(root);
					puts("===============================================================================");
					system("PAUSE");
				}else if(strcmp(chooseView,"Post")==0){
					puts("===============================================================================");
					printf("| %-25s | %-13s | %-15s | %-13s |\n","Name","Price","Topping","Quantity");
					puts("===============================================================================");
					viewPostOrder(root);
					puts("===============================================================================");
					system("PAUSE");
				}	
			}
		}else if(choice==2){
			system("cls");
			spasi();
			char bobaName[105];
			int hasilCekBobaName = 0;
			int hasilCekKata = 0;
			do{
				printf("Input Drink Name [end with 'Boba'] : ");
				scanf("%[^\n]",&bobaName); fflush(stdin);
				hasilCekBobaName = checkExistString(bobaName);
				hasilCekKata = FirstPlace(bobaName);
			}while(hasilCekBobaName==0 || hasilCekKata==0);
			
			int bobaPrice = 0;
			do{
				printf("Input Drink Price [20000...50000] : ");
				scanf("%d",&bobaPrice); fflush(stdin);
			}while(bobaPrice < 20000 || bobaPrice > 50000);
			
			char bobaTopping[15];
			do{
				printf("Input Drink Topping ['Gold Boba' or 'Regular Boba'] (case sensitive): ");
				scanf("%[^\n]",&bobaTopping); fflush(stdin);
			}while(strcmp(bobaTopping,"Gold Boba")!=0 && strcmp(bobaTopping,"Regular Boba")!=0);
			
			int bobaQuantity = 0;
			do{
				printf("Input Drink Quantity [1...50] : ");
				scanf("%d",&bobaQuantity); fflush(stdin);
			}while(bobaQuantity < 1 || bobaQuantity > 50);	
			
			char finalDecision[5];
			do{
				puts("======================================================");
				printf("Drink Name               : %s\n",bobaName);
				printf("Drink Price              : %d\n",bobaPrice);
				printf("Drink Topping            : %s\n",bobaTopping);
				printf("Drink Quantity           : %d\n",bobaQuantity);
				puts("======================================================");
				printf("Are You sure want to insert? ['Yes' or 'No'] (case insensitive): ");
				scanf("%s",&finalDecision); fflush(stdin);
				strupr(finalDecision);
			}while(strcmp(finalDecision,"YES")!=0 && strcmp(finalDecision,"NO")!=0);
			if(strcmp(finalDecision,"YES")==0){
				root = insert(root, bobaName, bobaPrice, bobaTopping, bobaQuantity);
				printf("Item inserted !\n\n");
				system("PAUSE");
			}else if(strcmp(finalDecision,"NO")==0){
				printf("Item not inserted !\n\n");
				system("PAUSE");
			}
		}else if(choice==3){
			int jumlahData = checkData(root);
			system("cls");
			spasi();
			if(jumlahData < 1){
				printf("There is no boba here!\n\n");
				system("PAUSE");
			}else{
				char bobaName[105];
				char tempBoba[105];
				puts("===============================================================================");
				printf("| %-25s | %-13s | %-15s | %-13s |\n","Name","Price","Topping","Quantity");
				puts("===============================================================================");
				viewInOrder(root);
				puts("===============================================================================");
				printf("Input product name['cancel' to exit]: ");
				scanf("%[^\n]",&bobaName); fflush(stdin);
				strcpy(tempBoba,bobaName);
				strupr(tempBoba);
				if(strcmp(tempBoba,"CANCEL")!=0){
					searchDelete(&root,bobaName);
				}
			}
		}else if(choice==4){
			deleteAll(&root);
			loop = 0;
			system("exit");
		}	
	}
	return 0;
}
