#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

#define MAXTAM 50

typedef struct{
char nome[50];
char telefone[50];
char email[50];
} Pessoa;

typedef struct{
Pessoa dados;
char dataVenc[20];
char ativo;
} Socio;

typedef struct{
Pessoa dados;
char empresa[50];
} Fornecedor;

typedef struct{
int id;
char nomeMarca[50];
} Marca;

typedef struct{
int id;
char nomeCat[50];
} Categoria;

typedef struct{
int id;
char nomeProd[50];
int estoque;
float preco;
Marca m;
Categoria c;
} Produto;

typedef struct{
int cod;
int idSocio;
char data[20];
float total;
int status;
} Pedido;

typedef struct{
int cod;
int idProduto;
int quant;
float subtotal;
} ItemPedido;

int Menu(){
int opcao;

printf("\n***CORTE FINO***");
printf("\n1-Gerenciar Pessoas");
printf("\n2-Gerenciar Produtos");
printf("\n3-Gerenciar Marcas");
printf("\n4-Gerenciar Categorias");
printf("\n5-Pedidos");
printf("\n6-Relatorios");
printf("\n0-Exit");

printf("\nQual opcao deseja: ");
scanf("%d",&opcao);

return opcao;
}

void Cadastro_socio() {
	FILE *arq;
	Socio s;
	int pos; 
	arq = fopen("cortefino.bin","ab+");
	if(arq == NULL){
		printf("\nErro no arquivo");
	}else{
		
		do{
			system("cls");
			printf("\nNome: ");fflush(stdin);
			gets(s.dados.nome);
			pos = busca(arq,s.dados.nome);
			if(pos== -1){
				printf("\nTelefone: ");fflush(stdin);
				gets(s.dados.telefone);
				printf("\nEmail: ");fflush(stdin);
				gets(s.dados.email);
				printf("\nData de Vencimento da assinatura: ");fflush(stdin);
				gets(s.dataVenc);
				printf("\nAtivo(S/N): ");fflush(stdin);
				scanf(" %c",&s.ativo);
			}else {
				fseek(arq,pos,0);
				fread(&s,sizeof(Socio),1,arq);
				printf("\n %s ja esta cadastrad(a)o na agenda",s.dados.nome);
				system("pause");
			}
			system("cls");
			printf("\nDeseja continuar S/N? ");
		
		}while(toupper(getch())=='S');
		fclose(arq);
	}
}

void Cadastro_fornecedor() {
	FILE *arq;
	Fornecedor f;
	int pos; 
	arq = fopen("cortefino.bin","ab+");
	if(arq == NULL){
		printf("\nErro no arquivo");
	}else{
		do{
			system("cls");
			printf("\nNome: ");fflush(stdin);
			gets(f.dados.nome);
			pos=busca(arq,f.dados.nome);
			if(pos==-1){
				printf("\nTelefone: "); fflush(stdin);
				gets(f.dados.telefone);
				printf("\nEmail: "); fflush(stdin);
				gets(f.dados.email);
				printf("\nNome da Empresa: ") ;fflush(stdin);
				gets(f.empresa);
			}else{
				fseek(arq,pos,0);
				fread(&f, sizeof(Fornecedor), 1, arq);
				printf("\n %s ja esta cadastrad(a)o na agenda",f.dados.nome);
				system("pause");
			}
			system("cls");
			printf("\nDeseja continuar S/N? ");
		}while(toupper(getche())=='S');
		fclose(arq);
	}
}

void Cadastro_produto() {
	FILE *arq;
	Produto p;
	Fornecedor f; 
	int pos; 
	arq = fopen("cortefino.bin","ab+");
	if(arq == NULL){
		printf("\nErro no arquivo");
	}else{
		
		do {
			system("cls");
			printf("\nNome: ");fflush(stdin);
			gets(p.nomeProd);
			pos = busca(arq, f.dados.nome);
			if(pos==-1){
				printf("\nCodigo: ");
				scanf("%d",&p.id);
				printf("\nQuantidade no Estoque: ");
				scanf("%d",&p.estoque);
				printf("\nPreco: ");
				scanf("%f",&p.preco);
			}else{
				fseek(arq,pos,0);
				fread(&p,sizeof(Produto),1,arq);
				printf("\n %s ja esta cadastrad(a)o na agenda",p.nomeProd);
				system("pause");
			}
			system("cls");
			printf("\nDeseja continuar S/N? ");
		} while(toupper(getche())=='S');
		fclose(arq);
	
	}
}

void Cadastro_marcas() {
	FILE *arq;
	Marca m;
	char nomeBusca[50];
	int pos; 
	arq = fopen("cortefino.bin","ab+");
	if(arq == NULL){
		printf("\nErro no arquivo");
	}else{
		
		do{
			system("cls");
			printf("\nNome: ");fflush(stdin);
			gets(nomeBusca);
			pos = busca(arq,nomeBusca);
			if(pos== -1){
				printf("\nCodigo: ");
				scanf("%d",&m.id);
			}else {
				fseek(arq,pos,0);
				fread(&m, sizeof(Marca), 1, arq);
				printf("\n %s ja esta cadastrad(a)o na agenda", m.nomeMarca);
				system("pause");
			}
			system("cls");
			printf("\nDeseja continuar 'S'|| 'N' ? \n");
		} while(toupper(getche())=='S');
		fclose(arq);
	
	}
}

// ==> Busca
int buscaMarca(FILE *arq, char nomeBusca[]) {
	Marca m; 
	rewind(arq); 
	fread(&m, sizeof(Marca), 1, arq);
	while(!feof(arq) && strcmp(buscaMarca, m.nomeMarca)!= 0) {
		fread(&m, sizeof(Marca), 1, arq);
	}
	if(!feof(arq)) {
		return (ftell(arq) - sizeof(Marca));
	} else {
		return -1;
	}
}


int buscaFornecedor(FILE *arq, char nomeFornecedor[]) {
	Fornecedor F;
	rewind(arq); 
	fread(&F, sizeof(Fornecedor), 1, arq);
		while(!feof(arq) && strcmp(buscaFornecedor, F.dados.nome)!= 0) {
			fread(&F, sizeof(Fornecedor), 1, arq);
		}
		if(!feof(arq)) {
			return (ftell(arq) - sizeof(Marca));
		} else {
			return -1;
		}
}

int buscaSocio(FILE *arq, char nomeSocio[]) {
	Socio S;
	rewind(arq); 
	fread(&S, sizeof(Socio), 1, arq);
		while(!feof(arq) && strcmp(nomeSocio, S.dados.nome)!= 0) {
			fread(&S, sizeof(Socio), 1, arq);
		}
		if(!feof(arq)) {
			return (ftell(arq) - sizeof(Socio));
		} else {
			return -1;
		}
}

int buscaProduto(FILE *arq, char nomeProduto[]) {
	Produto P;
	rewind(arq); 
	fread(&S, sizeof(Produto), 1, arq);
		while(!feof(arq) && strcmp(nomeProduto, S.dados.nome)!= 0) {
			fread(&S, sizeof(Produto), 1, arq);
		}
		if(!feof(arq)) {
			return (ftell(arq) - sizeof(Produto));
		} else {
			return -1;
		}
}

int buscaPedido(FILE *arq, int cod) {
	Pedido P;
	rewind(arq); 
	fread(&P, sizeof(Pedido), 1, arq);
		while(!feof(arq) && cod == P.cod) {
			fread(&P, sizeof(Pedido), 1, arq);
		}
		if(!feof(arq)) {
			return (ftell(arq) - sizeof(Pedido));
		} else {
			return -1;
		}
}

int buscaCategoria(FILE *arq, char nomeCategoria[]) {
	Categoria C;
	rewind(arq); 
	fread(&C, sizeof(Categoria), 1, arq);
		while(!feof(arq) && strcmp(nomeCategoria, C.nomeCat)!= 0) {
			fread(&C, sizeof(Categoria), 1, arq);
		}
		if(!feof(arq)) {
			return (ftell(arq) - sizeof(Categoria));
		} else {
			return -1;
		}
}


int main(){

int opcao;
do{
	opcao = Menu();
	switch(opcao){
		case 1:{
			int submenu;
			
			printf("\n1-Gerenciar Socio");
			printf("\n2-Fornecedores");
			printf("\n0-Voltar");
			printf("\nOpcao:");
			scanf("%d",&submenu);
			
			switch(submenu){
				case 1:{
					int opSocio;
					do{
						printf("\n=== GERENCIAR SOCIO ===\n");
						printf("\n1-Cadastrar Socio");
						printf("\n2-Listar Socio");
						printf("\n3-Buscar Socio");
						printf("\n4-Editar Socio");
						printf("\n5-Excluir");
						printf("\n6-Assinar Socio");
						printf("\n7-Renovar Assinatura");
						printf("\n8-Verificar vencimentos");
						printf("\n0-Voltar");
						printf("\nOpcao: ");
						scanf("%d",&opSocio);
						
						switch(opSocio){
							case 1:{
								//cadastroSocio();
								break;
							}
							case 2:{
								//ListarSocio();
								break;
							}
							case 3:{
								//BuscaSocio();
								break;
							}
							case 4:{
								//Editar();
								break;
							}
							case 5:{
								//Excluir();
								break;
							}
							case 6:{
								//AssinarSocio();
								break;
							}
							case 7:{
								//RenovaAss();
								break;
							}
							case 8:{
								//VerificaVenc();
								break;
							}
							default:{
								printf("\nOpcao Invalida, digite novamente");
								break;
							}
						}
					}while(opSocio != 0);
					break;
				}
				case 2:{
					int opFornecedor;
					do{
						printf("\n=== GERENCIAR FORNECEDOR ===\n");
						printf("\n1-Cadastrar Fornecedor");
						printf("\n2-Listar Fornecedores");
						printf("\n3-Buscar Fornecedores");
						printf("\n4-Editar Fornecedor");
						printf("\n5-Excluir Fornecedor");
						printf("\n0-Voltar");
						printf("\nOpcao: ");
						scanf("%d",&opFornecedor);
						
						switch(opFornecedor){
							case 1:{
								//cadastroFornecedor();
								break;
							}
							case 2:{
								//ListarFornecedor();
								break;
							}
							case 3:{
								//Buscar();
								break;
							}
							case 4:{
								//Editar();
								break;
							}
							case 5:{
								//Excluir();
								break;
							}
						}	
					}while(opFornecedor!=0);
					break;
				}
				default:{
					printf("\nOpcao invalida,digite novamente");
			
					break;
				}
			}
			
			break;
		}
		case 2:{
			int opProd;
			do{
				printf("\n=== GERENCIAR PRODUTOS ===\n");
				printf("1-Cadastrar produto\n");
				printf("2-Listar produtos\n");
				printf("3-Buscar produto\n");
				printf("4-Editar produto\n");
				printf("5-Excluir produto\n");
				printf("6-Atualizar estoque\n");
				printf("7-Produtos por categoria\n");
				printf("8-Produtos por marca\n");
				printf("0-Voltar\n");
				scanf("%d",&opProd);
			
					switch(opProd){
						case 1:{
							//cadastroProduto();
							break;
						}
						case 2:{
							// ListarProduto();
							break;
						}
						case 3:{
							//BuscaProduto();
							break;
						}
						case 4:{
							// Editar();
							break;
						}
						case 5:{
							// Excluir();
							break;
						}
						case 6:{
							// AtualizarEstoque();
							break;
						}
						case 7:{
							// ProdutosCategoria();
							break;
						}
						case 8:{
							// ProdutosMarca();
							break;
						}
						default:{
							printf("\nOpcao Invalida, digite novamente");
							break;
						}
					}
			
			}while(opProd != 0);
								
			break;
		}
		case 3: {
			int opMarca;
				printf("\n=== GERENCIAR MARCAS ===\n");
				printf("\n1-Cadastrar marca\n");
				printf("\n2-Listar marcas\n");
				printf("\n3-Buscar marca\n");
				printf("\n4-Editar marca\n");
				printf("\n5-Excluir marca\n");
				printf("\n0-Voltar\n");
				scanf("%d",&opMarca);
				
				switch(opMarca){
					case 1:{
						
						break;
					}
					case 2:{
						
						break;
					}
					case 3:{
						
						break;
					}
					case 4:{
						
						break;
					}
					case 5:{
						
						break;
					}
					default:{
						printf("\nOpcao Invalida, digite novamente");
						break;
					}
				}
			break;
		}
		case 4:{
			int opCat; 
			printf("\n=== GERENCIAR CATEGORIAS ===\n");
			printf("\n1-Cadastrar categoria\n");
			printf("\n2-Listar categorias\n");
			printf("\n3-Buscar categoria\n");
			printf("\n4-Editar categoria\n");
			printf("\n5-Excluir categoria\n");
			printf("\n0-Voltar\n");
			scanf("%d",&opCat);
			
			switch(opCat){
				case 1:{
					
					break;
				}
				case 2:{
					
					break;
				}
				case 3:{
					
					break;
				}
				case 4:{
					
					break;
				}
				case 5:{
					
					break;
				}
				default:{
					printf("\nOpcao Invalida, digite novamente");
					break;
				}
			}
				break;
		}
		case 5: {
			int opPed;
			printf("\n=== PEDIDOS ===\n");
			printf("\n1-Efetuar pedido\n");
			printf("\n2-Listar pedidos\n");
			printf("\n3-Buscar pedido\n");
			printf("\n4-Adicionar produtos ao pedido\n");
			printf("\n5-Definir entrega\n");
			printf("\n6-Retirar pedido\n");
			printf("\n7-Atualizar status do pedido\n");
			printf("\n8-Cancelar pedido\n");
			printf("\n0-Voltar\n");
			scanf("%d",&opPed);
			
			switch(opPed){
				case 1:{
					
					break;
				}
				case 2:{
					
					break;
				}
				case 3:{
					
					break;
				}
				case 4:{
					
					break;
				}
				case 5:{
					
					break;
				}
				case 6:{
					
					break;
				}
				case 7:{
					
					break;
				}
				case 8:{
					
					break;
				}
				default:{
					printf("\nOpcao Invalida, digite novamente");
					break;
				}
			}
			
			break;
		}
		case 6: {
			int opRel;
			printf("\n=== RELATORIOS ===\n");
			printf("\n1-Socios com assinatura vencendo\n");
			printf("\n2-Produtos mais vendidos\n");
			printf("\n3-Pedidos realizados por periodo\n");
			printf("\n4-Produtos com estoque baixo\n");
			printf("\n5-Produtos por categoria\n");
			printf("\n6-Produtos por marca\n");
			printf("\n7-Historico de pedidos por socio\n");
			printf("\n8-Faturamento mensal\n");
			printf("\n0-Voltar\n");
			scanf("%d",&opRel);
			
			switch(opRel){
				case 1:{
					
					break;
				}
				case 2:{
					
					break;
				}
				case 3:{
					
					break;
				}
				case 4:{
					
					break;
				}
				case 5:{
					
					break;
				}
				case 6:{
					
					break;
				}
				case 7:{
					
					break;
				}
				case 8:{
					
					break;
				}
				default:{
					printf("\nOpcao Invalida, digite novamente");
					break;
				}
				
			}
			
			break;
		}
	
		default:{
			printf("\nOpcao invalida,digite novamente");
			
			break;
		}
	}
}while(opcao!=0);
return 0; 
}
