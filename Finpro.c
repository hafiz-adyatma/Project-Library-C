#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct perpus
{
	int tree;
	char buku[500];
	struct perpus *left, *right; 
}*root=NULL;
 

struct perpus *createNode(int tree,const char*buku)
{
	struct perpus *newNode = (struct perpus*)malloc(sizeof(struct perpus));
	strcpy(newNode->buku,buku);
	newNode->tree= tree;
	newNode->left = newNode->right = NULL;
	return newNode;
}

void display(){
	printf("\n\nSISTEM MANAJEMEN PERPUSTAKAAN");
	printf("\n\n*****************************");
	printf("\n\n");
	printf("\n\n 1. Lihat daftar buku");
	printf("\n\n 2. Tambah buku");
	printf("\n\n 3. Perbarui buku");
	printf("\n\n 4. Hapus buku");
	printf("\n\n 5. Urutkan buku");
	printf("\n\n 6. Keluar program");
	printf("\n\n");
}
struct perpus *InsertNode(struct perpus *root, int tree,const char*buku,int level)
{
	char position[500];
	
	if(level<4) 
	{
		if(!root)
		{ 
		  	printf("\n\n Sukses menambahkan buku");
		    return createNode(tree,buku);
		} 
		else
		{
			while(level<4) 
			{
				printf("\n\n Tambahkan data dari sisi 'kiri' atau 'kanan' %s ? : ",root->buku);
				getchar();
				scanf("%[^\n]s",position);
				if(strcmpi(position,"kiri")==0) 
				{
					root->left = InsertNode(root->left,tree,buku,level+1);
				}
				else if(strcmpi(position,"kanan")==0) 
				{
					root->right = InsertNode(root->right,tree,buku,level+1);
				}
				break;
				printf("\n\n --- Sukses menambahkan buku ---");
			}
		}
	}
	else if(level==4) 
	{
		printf("\n\n --- Maksimal tinggi tree adalah 4 ---");
	}
}

void print(struct perpus *root) //preorder print
{
  	if(root!=NULL)
  	{
	    printf("%s ([%d]) \n",root->buku,root->tree);
	    print(root->left);
	    print(root->right);
  	}
}
struct perpus *search(struct perpus *root,int tree)
{
	if(root!=NULL)
	{
		if(root->tree==tree)
		{
			return root;
		}
		else
		{
			struct perpus *temp;
			temp=search(root->left,tree);
			if(temp==NULL)
			{
				temp=search(root->right,tree);
			}
			return temp;
		}
	}
	else
	{
		return 0;
	}
}
void update(struct perpus *root, const char *new_book){
 	if(root!=NULL){
 	strcpy(root->buku,new_book);
 	}
}
	
void PreOrder(struct perpus *root)
{
  	if(root)
  	{
	    printf(" [%d] ", root->tree);
	    PreOrder(root->left);
	    PreOrder(root->right);
  	}
}

void InOrder(struct perpus *root)
{
  	if(root)
	{
	    InOrder(root->left);
	    printf(" [%d] ", root->tree);
	    InOrder(root->right);
  	}
}

void PostOrder(struct perpus *root)
{
	if(root)
  	{
	    PostOrder(root->left);
	    PostOrder(root->right);
	    printf(" [%d] ", root->tree);
  	}
}


void copy(struct perpus *from,struct perpus *to)
{
	to->tree=from->tree;
	strcmp(to->buku,from->buku)==0;
}

struct perpus *InOrderSucessor(struct perpus *root)
{ 
	struct perpus *curr=root->right; 
  	while(curr&&curr->left)
  	{ 
    	curr=curr->left; 
  	}
  	return curr;
}

struct perpus *Deleteall(struct perpus *root)
{
	if(root!=NULL)
	{
    	Deleteall(root->left);
    	Deleteall(root->right);
    	free(root);
  	}
  	return 0;
}

void DeleteNode(struct perpus **temp, int tree)
{
	if((*temp)!=NULL&&tree==(*temp)->tree)
	{
   		Deleteall(*temp);
		(*temp)=NULL;
	}
	else if((*temp)!=NULL)
	{
		DeleteNode(&(*temp)->left, tree);
  		DeleteNode(&(*temp)->right, tree);
	} 
}


int main()
{
	int input;
	int tree, new_tree;
	int level=0;
	char buku[500];
	char position[500];
	
	while(1)
	{
		printf("");
		display();
		printf("\n\n >> Masukkan Pilihan : ");
		scanf("%d",&input);
			
		if(input==1) 
		{
			if(root==NULL) 
			{
				printf("\n\n --- Tidak ada buku pada tree ---");	
			}
			else 
			{
				printf("\n\n");
				printf("\n\n --- Daftar buku ---");
				printf("\n\n");
				print(root);
				printf("\n\n");
			}
		}
		
		else if(input==2) //add menu
		{
			while(1)
			{
				printf("\n\n \nMasukkan nama buku [3..50] : ");
				getchar();
				scanf("%[^\n]s",buku);
				getchar();
				if(strlen(buku)<3||strlen(buku)>50) //if the perpus's buku isn't valid
				{
					printf("\n\n --- Penamaan buku tidak valid ---");	
				}	
				else //if the perpus's buku is valid
				{
					while(1)
					{
						printf("\n\n \nMasukkan kode buku [0..100] : ");
						scanf("%d",&tree);
						if(tree<0||tree>100) //if the perpus's tree isn't valid
						{
							printf("\n\n --- Pengkodean buku tidak valid ---");	
						}
						else if(search(root,tree)==NULL) //if the perpus's tree is valid
						{
							root=InsertNode(root,tree,buku,level);
							break;
						}
						else if(search(root,tree)!=NULL) //if there's same perpus's tree
						{
							printf("\n\n --- Kode buku tidak boleh sama ---");
						}
					}
				break;			
				}
			}
		}
		else if(input==3){
			
			if(root==NULL){
   			printf("--- Tidak ada data pada tree ---");
   			getchar();
  			printf("Press enter to continue...");
  			getchar();
   			system("cls");
  			}
  		else{
   		while(1){
   		printf("\n\n \nMasukkan kode buku [0..100] : ");
		scanf("%d",&new_tree);
   		printf("");
   			if(new_tree<10 || new_tree>99){
   		printf("-- Kode buku tidak ditemukan ---\n");
      	}
   			else if(search(root,new_tree)==NULL){
   		printf("Buku tidak  ditemukan\n");
   		getchar();
   		printf("Press enter to continue...\n");
   		getchar();
   		system("cls");      
   		}		 
   			else if(search(root,new_tree)!=NULL){
    	printf("\nKode buku   : S%d\n",root->tree);
    	printf("Nama Buku : %s\n",root->buku);
    	while(1){
    	getchar();
    	printf("");
    	printf("Masukkan nama buku: ");
    	scanf("%[^\n]",buku);
    	printf("");  
    		if(strlen(buku)<0 ||strlen(buku)>20){
     	printf("-- Buku tidak ditemukan ---\n");
    	}
     		else{
       struct perpus *var=search(root,new_tree);
       update(var,buku);
       printf("--Data berhasil diperbarui--");
       getchar();
       printf("Press enter to continue...");
       getchar();
       system("cls");
       break; 
     }
     break; 
    }
    
    break; 
   } 
  break;
   }
}

 }
			
		
		else if(input==4) 
		{
			while(1)
			{
				printf("\n\n Masukkan kode buku yang ingin dihapus [0..100] : ");
				scanf("%d",&tree);	
				struct perpus *temp=search(root,tree);	
				if(temp==NULL) 
				{
	        		printf("\n\n --- Buku tidak ditemukan ---");
	    		} 
				else 
				{
					DeleteNode(&root,tree);
					printf("\n\n --- Buku berhasil dihapus ---");
					break;
				}
			}
		}
		
		else if(input==5) 
		{
			if(root==NULL) 
			{
				printf("\n\n ---Tidak ada buku pada tree---");
			}
			else 
			{
				printf("\n\n \nInOrder : ");
				InOrder(root);
				printf("\n\n");
				printf("\n\n \nPreOrder : ");
				PreOrder(root);
				printf("\n\n");
				printf("\n\n \nPostOrder : ");
				PostOrder(root);
				printf("\n\n");
			}
		}
		
		else if(input==6)
		{
			root=Deleteall(root); 
			print(root);
			printf("\n\n");
			printf("\n\n ---Semua data berhasil dihapus---");
			printf("\n\n");
			printf("\n\n --- Terimakasih ---");
			exit(0);
			break;
		}
		else if(input<1 || input>6){
			printf("\n\nPerintah tidak valid");
		}
	}
	return 0;
}

