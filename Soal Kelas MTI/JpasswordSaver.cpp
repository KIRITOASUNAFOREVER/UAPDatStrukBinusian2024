#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
	char username[85];
	char platform[85];
	char password[65];
	char strength[10];
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

struct Node* newNode(char username[], char platform[], char password[], char strength[])
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(node->username,username);
	strcpy(node->platform,platform);
	strcpy(node->password,password);
	strcpy(node->strength,strength);
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

struct Node* insert(struct Node* node, char username[], char platform[], char password[], char strength[])
{
	if (node == NULL){
		return(newNode(username,platform,password,strength));
	}

	if (strcmp(username, node->username) < 0){
		node->kiri = insert(node->kiri, username,platform,password,strength);
	}else if (strcmp(username, node->username) > 0){
		node->kanan = insert(node->kanan, username,platform,password,strength);
	}else
		return node;

	node->height = 1 + max(height(node->kiri),height(node->kanan));

	int balance = getBalance(node);

	if (balance > 1 && strcmp(username, node->kiri->username) < 0){
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(username, node->kanan->username) > 0){
		return leftRotate(node);
	}

	if (balance > 1 && strcmp(username, node->kiri->username) > 0)
	{
		node->kiri = leftRotate(node->kiri);
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(username, node->kanan->username) < 0)
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

struct Node* deleteNode(struct Node* root, char username[], char platform[], char password[], char strength[])
{
    if (root == NULL){
        return root;
	}
  
    if (strcmp(username, root->username) < 0){
    	root->kiri = deleteNode(root->kiri, username,platform,password,strength);
	}else if(strcmp(username, root->username) > 0){
        root->kanan = deleteNode(root->kanan, username,platform,password,strength);
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
            strcpy(root->username, temp->username);
            strcpy(root->platform,temp->platform);
            strcpy(root->password,temp->password);
            strcpy(root->strength,temp->strength);
            root->kanan = deleteNode(root->kanan, temp->username,temp->platform,temp->password,temp->strength);
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
		printf("| %-26s | %-21s | %-7d | %-21s | %-10s |\n",root->username,root->platform,root->height,root->password,root->strength);
		puts(" =================================================================================================== ");
		viewPreOrder(root->kiri);
		viewPreOrder(root->kanan);
	}
}

void viewInOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewInOrder(root->kiri);
		printf("| %-26s | %-21s | %-7d | %-21s | %-10s |\n",root->username,root->platform,root->height,root->password,root->strength);
		puts(" =================================================================================================== ");
		viewInOrder(root->kanan);
	}
}

void viewPostOrder(struct Node *root)
{
	if(root != NULL)
	{
		viewPostOrder(root->kiri);
		viewPostOrder(root->kanan);
		printf("| %-26s | %-21s | %-7d | %-21s | %-10s |\n",root->username,root->platform,root->height,root->password,root->strength);
		puts(" =================================================================================================== ");
	}
}

int checkData(struct Node *root){
	if(root == NULL){
		return 0;
	}else{
		return 1;
	}
}
int checkPassLength(char password[]){
	int panjang = strlen(password);
	if(panjang > 6){
		return 1;
	}else{
		return 0;
	}
}

int checkUppercase(char password[]){
	int panjang = strlen(password);
	for(int i = 0; i < panjang ; i++){
		if(password[i] >= 'A' && password[i] <= 'Z'){
			return 1;
			break;
		}
	}
	return 0;
}

int checkLowercase(char password[]){
	int panjang = strlen(password);
	for(int i = 0; i < panjang ; i++){
		if(password[i] >= 'a' && password[i] <= 'z'){
			return 1;
			break;
		}
	}
	return 0;
}

int checkNumberExist(char password[]){
	int panjang = strlen(password);
	for(int i = 0 ; i < panjang ; i++){
		if(password[i] >='0' && password[i] <= '9'){
			return 1;
			break;
		}
	}
	return 0;
}

struct Node *searchDelete(Node **node, char username[]){
	char Username[30];
	char areYouSure[5];
	if((*node)!=NULL){
		if(strcmp(username,(*node)->username) < 0){
			searchDelete(&(*node)->kiri,username);
		}else if(strcmp(username,(*node)->username) > 0){
			searchDelete(&(*node)->kanan,username);
		}else{
			do{
				printf("Do you want to delete this account(y/n) \n");
				printf("? >> ");
				scanf("%s",&areYouSure); fflush(stdin);
			}while(strcmp(areYouSure,"y")!=0 && strcmp(areYouSure,"n")!=0);
			if(strcmp(areYouSure,"y")==0){
				root = deleteNode(root , (*node)->username, (*node)->platform, (*node)->password, (*node)->strength);
				system("PAUSE");
			}
		}
	}else{
		printf("Username (cancel to exit) >> ");
		scanf("%[^\n]",&Username); fflush(stdin);
		if(strcmp(username,"cancel")==0){
			return 0;
		}else{
			searchDelete(&root,Username);
		}
		
		return 0;
	}
}

void deleteAll(Node **node)
{
	while(root != NULL)
	{
		root = deleteNode(root , (*node)->username, (*node)->platform, (*node)->password, (*node)->strength);
	}
}

void logoAwal(){
	puts("     ____.__________                                                    .___");
	puts("    |    |\\______   \\_____     ______  ________  _  __ ____ _______   __| _/      ___________  ___  __  ____ _______");
	puts("    |    | |     ___/\\__  \\   /  ___/ /  ___/\\ \\/ \\/ //  _ \\\\_  __ \\ / __ |      /  ___/\\__  \\ \\  \\/ /_/ __ \\\\_  __ \\");
	puts("/\\__|    | |    |     / __ \\_ \\___ \\  \\___ \\  \\     /(  <_> )|  | \\// /_/ |      \\___ \\  / __ \\_\\   / \\  ___/ |  | \\/");
	puts("\\________| |____|    (____  / ____  >/____  >  \\/\\_/  \\____/ |__|   \\____ |     /____  >(____  / \\_/   \\___  >|__|");
	puts("                          \\/      \\/      \\/                             \\/          \\/      \\/            \\/");
	puts("Press Enter to Continue...");
	getchar();
}

int main()
{
	int id = 1, loop = 1, choice;
	logoAwal();
	while(loop == 1){
		system("cls");
		puts("JPassword saver");
		printf("1. View Accounts\n");
		printf("2. Insert Account\n");
		printf("3. Delete Account\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf(" %d", &choice); fflush(stdin);
		if(choice==1){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("There is no data\n\n");
				system("PAUSE");
			}else{
				char chooseView[5];
				do{
					printf("Choose Print Order [Pre | In | Post]: ");
					scanf("%[^\n]",&chooseView); fflush(stdin);
				}while(strcmp(chooseView,"Pre")!=0 && strcmp(chooseView,"In")!=0 && strcmp(chooseView,"Post")!=0);
				
				if(strcmp(chooseView,"Pre")==0){
					puts(" =================================================================================================== ");
					printf("| %-26s | %-21s | %-7s | %-21s | %-10s |\n","UserName","Platform","Height","Password","Strength");
					puts(" =================================================================================================== ");
					viewPreOrder(root);
					system("PAUSE");
				}else if(strcmp(chooseView,"In")==0){
					puts(" =================================================================================================== ");
					printf("| %-26s | %-21s | %-7s | %-21s | %-10s |\n","UserName","Platform","Height","Password","Strength");
					puts(" =================================================================================================== ");
					viewInOrder(root);
					system("PAUSE");
				}else if(strcmp(chooseView,"Post")==0){
					puts(" =================================================================================================== ");
					printf("| %-26s | %-21s | %-7s | %-21s | %-10s |\n","UserName","Platform","Height","Password","Strength");
					puts(" =================================================================================================== ");
					viewPostOrder(root);
					system("PAUSE");
				}	
			}
		}else if(choice==2){
			char username[85];
			do{
				printf("Input userName [6-80 characters]: ");
				scanf("%[^\n]",&username); fflush(stdin);
			}while(strlen(username) < 6 || strlen(username) > 80);
			
			char platform[85];
			do{
				printf("Input platform [6-80 characters]: ");
				scanf("%[^\n]",&platform); fflush(stdin);
			}while(strlen(platform) < 6 || strlen(platform) > 80);
			
			char password[65];
			char strength[15];
			char finalDecision[5];
			int cekPanjangPass, cekHurufBesar, cekHurufKecil, cekAdaAngka, totalCekPass;
			do{
				printf("Input Password [<60 characters && must be a valid password]: ");
				scanf("%[^\n]",&password); fflush(stdin);
				cekPanjangPass = checkPassLength(password);
				cekHurufBesar = checkUppercase(password);
				cekHurufKecil = checkLowercase(password);
				cekAdaAngka = checkNumberExist(password);
				totalCekPass = cekPanjangPass + cekHurufBesar + cekHurufKecil + cekAdaAngka;
				if(totalCekPass==2){
					strcpy(strength,"weak");
				}else if(totalCekPass==3){
					strcpy(strength,"medium");
				}else if(totalCekPass==4){
					strcpy(strength,"strong");
				}
			}while(strlen(password) > 60 || totalCekPass < 2);
			do{
				printf("Do you want to insert this login(y/n): \n");
				printf("? >> ");
				scanf("%s",&finalDecision); fflush(stdin);
			}while(strcmp(finalDecision,"y")!=0 && strcmp(finalDecision,"n")!=0);
			if(strcmp(finalDecision,"y")==0){
				root = insert(root, username, platform, password, strength);
			}
		}else if(choice==3){
			int jumlahData = checkData(root);
			if(jumlahData < 1){
				printf("There is no data\n\n");
				system("PAUSE");
			}else{
				char username[85];
				puts(" =================================================================================================== ");
				printf("| %-26s | %-21s | %-7s | %-21s | %-10s |\n","UserName","Platform","Height","Password","Strength");
				puts(" =================================================================================================== ");
				viewInOrder(root);		
				puts("Which account you want to delete ?");
				printf("Username (cancel to exit) >> ");
				scanf("%[^\n]",&username); fflush(stdin);
				if(strcmp(username,"cancel")!=0){
					searchDelete(&root,username);
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
