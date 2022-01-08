/*  Final Project Data Structure

	By :
	1. I Putu Krisna Dharma Saputra - 2301924353
	2. Felix Filipi					- 2301877590
	
	Program Ini dibuat menggunakan prinsip Binary Search Tree
	
*/	

/*****************
 *    Library    *
 *****************/
#include<stdio.h> //printf, scanf, FILE, fopen, fclose, fcloseall, fflush(stdin)
#include<stdlib.h> //system("cls")
#include<string.h> //strcpy(), strcmp()
#include <conio.h> //getch()
#include <windows.h> //keybd_event()

/********************
 * Deklarasi Struct *
 ********************/
typedef struct node tree;
struct node{
	char code[15];
	int salary;
	tree* left;
	tree* right;
	
};
tree* root;

/********************
 * Deklarasi Fungsi *
 ********************/
tree *newnode(char *code,int salary);
int code_convert(char *code);
tree* search(tree* root, char *code);
int search_avail(tree* node,char *code);
tree *insert(tree *node, char *code,int salary);
tree *update(tree *node);
tree *inordersucc(tree *node);
tree *findParent(tree *node,char *code);
tree *del_exec(tree *node);
int code_check(char *code);
void add();
void del(tree *node);
void preorder(tree *root);
void inorder(tree *root);
void postorder(tree *root);
void show();
int menu();
void keluar();

/*******************************************************************
 *    Fungsi Agar Saat Aplikasi di Buka Dalam Keadaan Fullscreen   *
 *******************************************************************/
void fullscreen()
{  keybd_event(VK_MENU,
               0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
}

/********************
 *    Fungsi Main   *
 ********************/
void main(){
	int choice;
	
	fullscreen();
	
	do{
		system("cls");
		choice = menu();
		switch(choice){
			case 1 : add();break;
			case 2 : update(root);break;
			case 3 : del(root);break;
			case 4 : show();break;
			case 5 : keluar();break;
		}
	}while(choice != 5);
	
}

/*************************
 *    Fungsi Main Menu   *
 *************************/
int menu(){
	fflush(stdin);
	int choice;
		printf("\t\t ______                   ______  _________   __           ___________     __________         ____________________         _________");
	printf("\n\t\t \\     \\                 /     / |   ______| |  |         |   ________|   |  ______  |       /                    \\       |   ______|");
	printf("\n\t\t  \\     \\       $_$     /     /  |  |__      |  |         |  |            | |      | |      /      _        _      \\      |  |__   ");	
	printf("\n\t\t   \\     \\     /  \\    /     /   |     |__   |  |         |  |            | |      | |     /      / \\\      / \\      \\     |     |__");
	printf("\n\t\t    \\     \\   |	   |  /     /    |      __|  |  |         |  |            | |      | |    /      /   \\\    /   \\      \\    |      __|");
	printf("\n\t\t     \\     \\__|	   |_/     /     |   __|     |  |         |  |            | |      | |   /      /  $  \\\__/  $  \\      \\   |   __|  ");
	printf("\n\t\t      \\                   /      |  |______  |  |_______  |  |________    | |______| |  /      /                \\      \\  |  |______ ");
	printf("\n\t\t       \\_________________/       |_________| |__________| |___________|   |__________| /______/                  \\______\\ |_________| ");
	printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\t\t\t\t\t\t\t       | |      BINUS LECTURER'S SALARY DATABASE    | |\n");
	printf("\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\n MAIN MENU");
	printf("\n____________________________________________________________________________________________________________________________________________________________________________");

	printf("\n\n  1. Add New Data");
	printf("\n  2. Update Lecturer's Salary");
	printf("\n  3. Delete Data");	
	printf("\n  4. View Database");
	printf("\n  5. Exit");
	printf("\n\n Choice >> ");
	scanf("\n%d",&choice);
	return choice;
}

//Fungsi untuk Membuat Newnode
tree *newnode(char *code,int salary){
	tree *temp = (tree*)malloc(sizeof(tree));
	strcpy(temp->code,code);
	temp->salary = salary;
	temp->left = NULL;
	temp->right = NULL;
};

//Fungsi untuk Menconvert code dari tipe data string ke tipe data integer
int code_convert(char *code){
	char src[15];
	int key;
	strcpy(src,code);
	memmove(&src[0],&src[1],strlen(src) - 0);
	key = atoi(src);
	return key;	
}

//Searching Pada Binary Search Tree
tree* search(tree* root, char *code) {
  	if(root == NULL){
		return root;  
	}
	int key = code_convert(code);
	int keynode = code_convert(root->code);
    if (keynode == key) 
       return root; 
       
    if (keynode < key){
       return search(root->right, code); 
   	}else{
    	return search(root->left, code);
	}
};

int search_avail(tree* node,char *code){
	if(node == NULL){
		return 0;
	}
	int key = code_convert(code);
	int keynode = code_convert(node->code);
	if(keynode == key){
		return -1;
	}
	int src1 = search_avail(node->left,code);
		if(src1) return -1;
	int src2 = search_avail(node->right,code);
		if(src2) return -1;		
}

/***********************************
 *    Fungsi Input Pada Menu ke 1  *
 ***********************************/
void add(){
	char code[15];
	int salary,check,key,confirm;
	
	do{
		system("cls");
			printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\t\t\t\t\t\t\t       | |      BINUS LECTURER'S SALARY DATABASE    | |\n");
			printf("\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\n MENU 1");
			printf("\n____________________________________________________________________________________________________________________________________________________________________________");

		printf("\n\n\t Input Lecturer Code D[1-9][0-9][0-9][0-9] : ");
		fflush(stdin);
		gets(code);
		check = code_check(code);
		confirm = search_avail(root,code);
		if(check != 0 || strlen(code) > 5){
			printf("\n\n\t Code invalid! (check format above!)\n");
			getch();
		}
		if(confirm != 0){
			printf("\n\n\t Lecturer's Code Alredy Exists! \n");
			getch();
		}
	}while(check != 0 || strlen(code) > 5 || confirm != 0);
	
	printf("\n\t Input Lecturer's Salary  :Rp ");
	fflush(stdin);
	scanf("\n%d",&salary);
		
	
	if(root == NULL){
		root = insert(root,code,salary);
	}else{
		insert(root,code,salary);
	}
	getch();
}

/***********************************************
 *    Fungsi Insert Pada Binary Search Tree    *
 ***********************************************/
tree *insert(tree *node, char *code,int salary){
	int key,keynode;
	
	if(node == NULL){
		node = newnode(code,salary);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n -------------------------------------------------------------------------- Add New Data Success --------------------------------------------------------------------------");
		return node;
	}
	
	key = code_convert(code);
	keynode = code_convert(node->code);
	if(key < keynode){
		node->left = insert(node->left,code,salary);
	}else if(key > keynode){
		node->right = insert(node->right,code,salary);
	}
}
/*****************************************
 *    Fungsi Menu ke 2 Update Databse    *
 *****************************************/
tree *update(tree *node){
	char code[15];
	int salary,check,found;
	system("cls");
	do{
			system("cls");
			printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\t\t\t\t\t\t\t       | |      BINUS LECTURER'S SALARY DATABASE    | |\n");
			printf("\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\n MENU 2");
			printf("\n____________________________________________________________________________________________________________________________________________________________________________");

		printf("\n\n\t Input Lecturer Code D[1-9][0-9][0-9][0-9] : ");
		fflush(stdin);
		gets(code);
		check = code_check(code);
		if(check != 0){
			printf("\n\n\t Code invalid! (check format above!)\n");
			getch();
		}
		if(root == NULL){
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ------------------------------------------------------------------- There's no Data Found -------------------------------------------------------------------");
			getch();
			return;
		}
	}while(check != 0);
	node = search(node,code);
	if(node == NULL){
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ------------------------------------------------------------------- Lecturer's code not found -------------------------------------------------------------------");

		getch();
		return node;
	}
	printf("\n\n\t\t Lecturer's Code : %s",node->code);
	printf("\n\n\t\t Lecturer's Salary : Rp %d,00",node->salary);
	getch();
	
	printf("\n\n\n\t Input new Lecturer's Salary : ");
	fflush(stdin);
	scanf("\n%d",&salary);
	
	node->salary = salary;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n --------------------------------------------------------------------------- Update Data Success --------------------------------------------------------------------------");

	getch();
	return node;
} 

/************************************
 *    Fungsi Untuk Mencari Parent   *
 ************************************/
tree *findParent(tree *node,char *code){
	if(node == NULL){
		return NULL;
	}
	if(node->left == NULL && node->right == NULL){
		return NULL;
	}
	if((node->left != NULL && strcmp(node->left->code,code) == 0) || node->right != NULL && strcmp(node->right->code,code) == 0){
		return node;
	}
	int key = code_convert(code);
	int keynode = code_convert(node->code);
	if(keynode > key){
		return findParent(node->left,code);
	}
	if(keynode < key){
		return findParent(node->right,code);
	}
}

/************************************
 *    Fungsi Untuk Mengcheck Code   *
 ************************************/
int code_check(char *code){
	if(code[0] != 'D')return 1;
	if(code[1] < '1' || code[1] > '9')return 1;
	if(code[2] < '0' || code[2] > '9')return 1;
	if(code[3] < '0' || code[3] > '9')return 1;
	if(code[4] < '0' || code[4] > '9')return 1;
	return 0;
}

/***************************************************************************************************************
 *    Fungsi untuk Mencari Successor inorder (digunakan pada saat Akan Mendelete parent yang memiliki 2 child  *
 ***************************************************************************************************************/
tree *inordersucc(tree *node){
	struct node *curr = node;
	while(curr && curr->left != NULL){
		curr = curr->left;
	}
	return curr;
}

/***********************************************
 *    Fungsi Delete Pada Binary Search Tree    *
 ***********************************************/
tree *del_exec(tree *node){
	//Kondisi Apabila Parent Tidak Mempunyai child
	if(node->left == NULL && node->right == NULL){
		tree *parent = findParent(root,node->code);
		if(parent->left == node){
			parent->left = NULL;
		}else if(parent->right == node){
			parent->right = NULL;
		}
		node = NULL;
		return node;
	}else if(node->left == NULL){ //Kondisi Apabila Apabila Parent tidak mempunyai left child
        tree *temp = node->right;
		strcpy(node->code,temp->code);
		node->salary = temp->salary;
		free(temp);
		temp = NULL;
		node->right = temp;
		return temp;
	}else if (node->right == NULL){ //Kondisi Apabila Apabila Parent tidak mempunyai Right child
        tree *temp = node->left;
		strcpy(node->code,temp->code);
		node->salary = temp->salary;
		free(temp);
		temp = NULL;
		node->left = temp;
		return temp; 
    }else{ //Kondisi Apabila Apabila Parent mempunyai 2 child 
	    tree* temp = inordersucc(node->right);
	    strcpy(node->code,temp->code);
		node->salary = temp->salary; 
	  	node->right = del_exec(node->right);
	}
	return node; 
}

/*********************************************
 *    Fungsi Display Delete Pada Menu ke 3   *
 *********************************************/
void del(tree *node){
	if(root == NULL){
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n------------------------------------------------------------ There's no data in the tree -------------------------------------------------------------------");
		getch();
		return;
	}else{
		char code[15];
		int check;
		
		do{
			system("cls");
			printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\t\t\t\t\t\t\t       | |      BINUS LECTURER'S SALARY DATABASE    | |\n");
			printf("\t\t\t\t\t\t\t       ________________________________________________\n");
			printf("\n\n MENU 3");
			printf("\n____________________________________________________________________________________________________________________________________________________________________________");
			printf("\n\n\t Input Lecturer's Code D[1-9][0-9][0-9][0-9] : ");
			fflush(stdin);
			gets(code);
			check = code_check(code);
			if(check != 0){
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ------------------------------------------------------------------------------ Code Invalid ------------------------------------------------------------------------------");
				getch();
			}
			if(root == NULL){
				
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ---------------------------------------------------------------------------- There's no Data -----------------------------------------------------------------------------");
				getch();
				return;
			}
		}while(check != 0);
		node = search(root,code);
		if(node == NULL){
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ----------------------------------------------------------------------------- Code not Found -----------------------------------------------------------------------------");
			getch();
			return;
		}
		if(node == root && root->left == NULL && root->right == NULL){
			root = NULL;
		}else{
			node = del_exec(node);
		}
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n ------------------------------------------------------------------------------ Delete Success ----------------------------------------------------------------------------");
		getch();
	}
}

/********************
 * Fungsi Preorder  *
 ********************/
 
 // Urutan Preorder = parent -> left child -> Right Child
void preorder(tree *root){
	if(root != NULL){
		printf(" \t\t| %-6s  | Rp %5d,00     \t\t\t|\n",root->code,root->salary); 
		preorder(root->left); 
		preorder(root->right); 
	}
}

/********************
 * Fungsi  Inorder  *
 ********************/
 
 // Urutan Inorder =  left child -> parent -> Right Child

void inorder(tree *root){
	if(root != NULL){
		inorder(root->left);
		printf(" \t\t| %-6s  | Rp %5d,00     \t\t\t|\n",root->code,root->salary);
		inorder(root->right);
	}
}

/********************
 * Fungsi Postorder *
 ********************/
 
 // Urutan Postorder =  left child -> Right Child -> parent
void postorder(tree *root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf(" \t\t|  %-6s | Rp %5d,00      \t\t\t| \n",root->code,root->salary);
	}
}

/***********************************************
 * Fungsi Display Menu ke 4 (Show Data Orders) *
 ***********************************************/
void show(){
	
	char choose[10],back;
	if(root == NULL){
		printf("\n\n\n\n\n -------------------------------------------------------------------------- There's no Data Found ---------------------------------------------------------------------------");
		getch();
	}else{
		do{
			system("cls");
			fflush(stdin);
			printf("\n\n MENU 4");
			printf("\n____________________________________________________________________________________________________________________________________________________________________________");
			printf("\n\n\t Show by [preorder/inorder/postorder] = ");
			gets(choose);
			printf("\n____________________________________________________________________________________________________________________________________________________________________________");		
			if(strcmp(choose,"preorder") == 0) {
				printf("\n\n\n\t\t\t\t\t\t\t ________________________________________________\n");
				printf("\n\t\t\t\t\t\t\t | |               PreOrder                   | |\n");
				printf("\t\t\t\t\t\t\t ________________________________________________\n\n\n");
				printf(" \n\n\t\t+-----------------------------------------------+\n");
				printf(" \t\t| Code    | Salary           \t\t\t|\n");
				printf(" \t\t+-----------------------------------------------+\n");
				
				preorder(root);
				
				printf(" \t\t+-----------------------------------------------+\n");
				getch();			
			}
			else if(strcmp(choose,"inorder") == 0){
				printf("\n\n\n\t\t\t\t\t\t\t ________________________________________________\n");
				printf("\n\t\t\t\t\t\t\t | |                InOrder                   | |\n");
				printf("\t\t\t\t\t\t\t ________________________________________________\n\n\n");
				printf(" \n\n\t\t+-----------------------------------------------+\n");
				printf(" \t\t| Code    | Salary           \t\t\t|\n");
				printf(" \t\t+-----------------------------------------------+\n");
				
				inorder(root);
				
				printf(" \t\t+-----------------------------------------------+\n");
				getch();		
			}
			else if(strcmp(choose,"postorder") == 0){
				printf("\n\n\n\t\t\t\t\t\t\t ________________________________________________\n");
				printf("\n\t\t\t\t\t\t\t | |              PostOrder                   | |\n");
				printf("\t\t\t\t\t\t\t ________________________________________________\n\n\n");
				printf(" \n\n\t\t+-----------------------------------------------+\n");
				printf(" \t\t| Code    | Salary           \t\t\t|\n");
				printf(" \t\t+-----------------------------------------------+\n");
				
				postorder(root);
				
				printf(" \t\t+-----------------------------------------------+\n");
				getch();					
			}
			else {
				printf("\n\t\t\t\t __   __  _______     _________  __   __  _______  _______");
				printf("\n\t\t\t\t | \\  | | | ___  |   |____ ____|| |__| | | |__| | | _____|");
				printf("\n\t\t\t\t |  \\ | | | |  | |       | |    |____  | | _____| | |__");
				printf("\n\t\t\t\t | |\\\\| | | |__| |       | |        _| | | |      | __|");
				printf("\n\t\t\t\t |_| \\\\_| |______|       |_|       |___| |_|      |_____|");
				printf("\n\n____________________________________________________________________________________________________________________________________________________________________________");
				getch();
			}
			
			reinput :
			printf("\n\n\t Do you want to back to main menu (Y/N) ? : ");
			fflush(stdin);
			scanf("%c",&back);
				
				if(back == 'y' || back == 'Y'){
					printf("\n\n\t Back to main menu !");
					getch();
					return;
				}
				else if(back == 'n' || back == 'N'){
					printf("\n\n\t Stay in this menu !");
					getch();
				}
				else{
					printf("\n\n ------------------------------------------------------------------- Choose the right answer ! -------------------------------------------------------------------");
					getch();
					goto reinput;
				}
		
		
		}while(strcmp(choose,"preorder") == 0 || strcmp(choose,"inorder") ==0 || strcmp(choose,"postorder") ==0 || back == 'n' || back == 'N');
    
    }
	
}


void keluar (){
	system("cls");
	system(" color f0");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
	printf("\t\t\t\t\t     _________ 	    ___     ___	      ____	  __	 ______    ___   ____  ___________      	\n");
	printf("\t\t\t\t\t    |___   ___|    |   |   |   |     /	  \\	 |  |   /      |  |   | /   /  |  ________|      \n");
	printf("\t\t\t\t\t	| |	   |   |___|   |    /  /\\  \\	 |  |  /   /|  |  |   |/   /   | |________\n");
	printf("\t\t\t\t\t	| |	   |   	       |   /  /__\\  \\	 |  | /	  / |  |  |	   <   |_________ |\n");
	printf("\t\t\t\t\t	| |	   |   	___    |  /  ______  \\   |  |/   /  |  |  |   |\\   \\    ________| |\n");
	printf("\t\t\t\t\t	|_|	   |___|   |___| /__/	   \\__\\  |______/   |__|  |___| \\___\\  |__________| \n\n\n\n");
	getch();
	exit(0);
}


