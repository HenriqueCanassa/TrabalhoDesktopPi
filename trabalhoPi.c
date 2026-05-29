#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct {
    char nome[50];
    char telefone[50];
    char email[50];
} Pessoa;

typedef struct {
    Pessoa dados;
    char dataVenc[20];
    char ativo;
} Socio;

typedef struct {
    Pessoa dados;
    char empresa[50];
} Fornecedor;

typedef struct {
    int  id;
    char nomeMarca[50];
} Marca;

typedef struct {
    int  id;
    char nomeCat[50];
} Categoria;

typedef struct {
    int id;
    char nomeProd[50];
    int estoque;
    float preco;
    Marca m;
    Categoria c;
} Produto;

typedef struct {
    int cod;
    int idProduto;
    int quant;
    float subtotal;
} ItemPedido;

typedef struct {
    int cod;
    int idSocio;
    char data[20];
    float total;
    int status;
    ItemPedido ip;
} Pedido;


int Menu() {
    int opcao;
    printf("\n***CORTE FINO***");
    printf("\n1-Gerenciar Pessoas");
    printf("\n2-Gerenciar Produtos");
    printf("\n3-Pedidos");
    printf("\n4-Relatorios");
    printf("\n5-Exit");
    printf("\nQual opcao deseja: ");
    scanf("%d", &opcao);
    return opcao;
}


int buscaSocio(FILE *arq, char nomeSocio[]) {
    Socio s;
    rewind(arq);
    fread(&s, sizeof(Socio), 1, arq);
    while (!feof(arq) && strcmp(nomeSocio, s.dados.nome) != 0)
        fread(&s, sizeof(Socio), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Socio));
    return -1;
}

int buscaFornecedor(FILE *arq, char nomeFornecedor[]) {
    Fornecedor f;
    rewind(arq);
    fread(&f, sizeof(Fornecedor), 1, arq);
    while (!feof(arq) && strcmp(nomeFornecedor, f.dados.nome) != 0)
        fread(&f, sizeof(Fornecedor), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Fornecedor));
    return -1;
}

int buscaProduto(FILE *arq, char nomeProduto[]) {
    Produto p;
    rewind(arq);
    fread(&p, sizeof(Produto), 1, arq);
    while (!feof(arq) && strcmp(nomeProduto, p.nomeProd) != 0)
        fread(&p, sizeof(Produto), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Produto));
    return -1;
}

int buscaMarca(FILE *arq, char nomeBusca[]) {
    Marca m;
    rewind(arq);
    fread(&m, sizeof(Marca), 1, arq);
    while (!feof(arq) && strcmp(nomeBusca, m.nomeMarca) != 0)
        fread(&m, sizeof(Marca), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Marca));
    return -1;
}

int buscaCategoria(FILE *arq, char nomeCategoria[]) {
    Categoria c;
    rewind(arq);
    fread(&c, sizeof(Categoria), 1, arq);
    while (!feof(arq) && strcmp(nomeCategoria, c.nomeCat) != 0)
        fread(&c, sizeof(Categoria), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Categoria));
    return -1;
}

int buscaPedido(FILE *arq, int cod) {
    Pedido p;
    rewind(arq);
    fread(&p, sizeof(Pedido), 1, arq);
    while (!feof(arq) && cod != p.cod)
        fread(&p, sizeof(Pedido), 1, arq);
    if (!feof(arq)) return (ftell(arq) - sizeof(Pedido));
    return -1;
}


void Cadastro_socio() {
    FILE *arq;
    Socio s;
    int pos;
    arq = fopen("socios.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nNome: "); fflush(stdin);
        gets(s.dados.nome);
        pos = buscaSocio(arq, s.dados.nome);
        if (pos == -1) {
            printf("\nTelefone: "); fflush(stdin);
            gets(s.dados.telefone);
            printf("\nEmail: "); fflush(stdin);
            gets(s.dados.email);
            printf("\nData de Vencimento da assinatura: "); fflush(stdin);
            gets(s.dataVenc);
            printf("\nAtivo(S/N): "); fflush(stdin);
            scanf(" %c", &s.ativo);
            fseek(arq, 0, SEEK_END);
            fwrite(&s, sizeof(Socio), 1, arq);
        } else {
            fseek(arq, pos, 0);
            fread(&s, sizeof(Socio), 1, arq);
            printf("\n%s ja esta cadastrado(a)", s.dados.nome);
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    }while (toupper(getche()) == 'S');
    fclose(arq);
}

void Cadastro_fornecedor() {
    FILE *arq;
    Fornecedor f;
    int pos;
    arq = fopen("fornecedores.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nNome: "); fflush(stdin);
        gets(f.dados.nome);
        pos = buscaFornecedor(arq, f.dados.nome);
        if (pos == -1) {
            printf("\nTelefone: "); fflush(stdin);
            gets(f.dados.telefone);
            printf("\nEmail: "); fflush(stdin);
            gets(f.dados.email);
            printf("\nNome da Empresa: "); fflush(stdin);
            gets(f.empresa);
            fseek(arq, 0, SEEK_END);
            fwrite(&f, sizeof(Fornecedor), 1, arq);
        } else {
            fseek(arq, pos, 0);
            fread(&f, sizeof(Fornecedor), 1, arq);
            printf("\n%s ja esta cadastrado(a)", f.dados.nome);
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    } while (toupper(getche()) == 'S');
    fclose(arq);
}

void Cadastro_produto() {
    FILE *arq;
    Produto p;
    int pos;
    arq = fopen("produtos.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nNome: "); fflush(stdin);
        gets(p.nomeProd);
        pos = buscaProduto(arq, p.nomeProd);
        if (pos == -1) {
            printf("\nCodigo: ");
            scanf("%d", &p.id);
            printf("\nQuantidade no Estoque: ");
            scanf("%d", &p.estoque);
            printf("\nPreco: ");
            scanf("%f", &p.preco);
            printf("\nDigite a marca: ");fflush(stdin);
            gets(p.m.nomeMarca);
            printf("\nDigite a categoria do produto: ");fflush(stdin);
            gets(p.c.nomeCat);
            fwrite(&p, sizeof(Produto), 1, arq);
        } else {
            fseek(arq, pos, 0);
            fread(&p, sizeof(Produto), 1, arq);
            printf("\n%s ja esta cadastrado(a)", p.nomeProd);
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    } while (toupper(getche()) == 'S');
    fclose(arq);
}

void Cadastro_marcas() {
    FILE *arq;
    Marca m;
    int pos;
    arq = fopen("marcas.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nNome da marca: "); fflush(stdin);
        gets(m.nomeMarca);
        pos = buscaMarca(arq, m.nomeMarca);
        if (pos == -1) {
            printf("\nID da marca: ");
            scanf("%d", &m.id);
            fseek(arq, 0, SEEK_END);
            fwrite(&m, sizeof(Marca), 1, arq);
        } else {
            fseek(arq, pos, 0);
            fread(&m, sizeof(Marca), 1, arq);
            printf("\n%s ja esta cadastrada", m.nomeMarca);
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    } while (toupper(getche()) == 'S');
    fclose(arq);
}

void Cadastro_categorias() {
    FILE *arq;
    Categoria c;
    int pos;
    arq = fopen("categorias.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nNome da categoria: "); fflush(stdin);
        gets(c.nomeCat);
        pos = buscaCategoria(arq, c.nomeCat);
        if (pos == -1) {
            printf("\nID da categoria: ");
            scanf("%d", &c.id);
            fseek(arq, 0, SEEK_END);
            fwrite(&c, sizeof(Categoria), 1, arq);
        } else {
            fseek(arq, pos, 0);
            fread(&c, sizeof(Categoria), 1, arq);
            printf("\n%s ja esta cadastrada", c.nomeCat);
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    } while (toupper(getche()) == 'S');
    fclose(arq);
}

void cadastrosPedido() {
    FILE *arq, *arqProd;
    Pedido p;
    Produto prod;
    int pos, posProd;
    arq = fopen("pedidos.bin", "ab+");
    if (arq == NULL) {
        printf("\nErro no arquivo");
        return;
    }
    do {
        system("cls");
        printf("\nQual codigo do pedido: ");
        scanf("%d", &p.cod);
        pos = buscaPedido(arq, p.cod);
        if (pos == -1) {
            printf("\nId do socio: ");
            scanf("%d", &p.idSocio);
            printf("\nId do produto: ");
            scanf("%d", &p.ip.idProduto);

            arqProd = fopen("produtos.bin", "rb");
            if (arqProd != NULL) {
                posProd = -1;
                Produto tmp;
                rewind(arqProd);
                fread(&tmp, sizeof(Produto), 1, arqProd);
                while (!feof(arqProd)) {
                    if (tmp.id == p.ip.idProduto) {
                        posProd = ftell(arqProd) - sizeof(Produto);
                        prod = tmp;
                        break;
                    }
                    fread(&tmp, sizeof(Produto), 1, arqProd);
                }
                fclose(arqProd);
            }

            if (posProd == -1) {
                printf("\nProduto nao cadastrado!");
                system("pause");
            } else {
                printf("\nQuantidade: ");
                scanf("%d", &p.ip.quant);
                p.ip.subtotal = p.ip.quant * prod.preco;
                printf("\nSubtotal calculado: %.2f", p.ip.subtotal);
                printf("\nQual data para entrega (XX/XX/XXXX): "); fflush(stdin);
                gets(p.data);
                printf("\nTotal: ");
                scanf("%f", &p.total);
                printf("\nStatus (1-Pendente 2-Concluido 3-Cancelado): ");
                scanf("%d", &p.status);
                fseek(arq, 0, SEEK_END);
                fwrite(&p, sizeof(Pedido), 1, arq);
                printf("\nPedido cadastrado com sucesso!");
            }
        } else {
            printf("\nPedido com esse codigo ja existe!");
            system("pause");
        }
        system("cls");
        printf("\nDeseja continuar S/N? ");
    } while (toupper(getche()) == 'S');
    fclose(arq);
}


void listarSocios() {
    FILE *arq;
    Socio s;
    int achou = 0;
    arq = fopen("socios.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n             LISTA DE SOCIOS            ");
    printf("\n========================================\n");
    fread(&s, sizeof(Socio), 1, arq);
    while (!feof(arq)) {
        printf("\nNome:      %s", s.dados.nome);
        printf("\nTelefone:  %s", s.dados.telefone);
        printf("\nEmail:     %s", s.dados.email);
        printf("\nVencimento:%s", s.dataVenc);
        printf("\nAtivo:     %c", s.ativo);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&s, sizeof(Socio), 1, arq);
    }
    if (!achou) printf("\nNenhum socio cadastrado.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void listarFornecedores() {
    FILE *arq;
    Fornecedor f;
    int achou = 0;
    arq = fopen("fornecedores.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n          LISTA DE FORNECEDORES         ");
    printf("\n========================================\n");
    fread(&f, sizeof(Fornecedor), 1, arq);
    while (!feof(arq)) {
        printf("\nNome:     %s", f.dados.nome);
        printf("\nTelefone: %s", f.dados.telefone);
        printf("\nEmail:    %s", f.dados.email);
        printf("\nEmpresa:  %s", f.empresa);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&f, sizeof(Fornecedor), 1, arq);
    }
    if (!achou) printf("\nNenhum fornecedor cadastrado.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void listarProdutos() {
    FILE *arq;
    Produto p;
    int achou = 0;
    arq = fopen("produtos.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n           LISTA DE PRODUTOS            ");
    printf("\n========================================\n");
    fread(&p, sizeof(Produto), 1, arq);
    while (!feof(arq)) {
        printf("\nCodigo:    %d", p.id);
        printf("\nNome:      %s", p.nomeProd);
        printf("\nEstoque:   %d", p.estoque);
        printf("\nPreco:     R$ %.2f", p.preco);
        printf("\nMarca:     %s", p.m.nomeMarca);
        printf("\nCategoria: %s", p.c.nomeCat);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&p, sizeof(Produto), 1, arq);
    }
    if (!achou) printf("\nNenhum produto cadastrado.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void listarMarcas() {
    FILE *arq;
    Marca m;
    int achou = 0;
    arq = fopen("marcas.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n            LISTA DE MARCAS             ");
    printf("\n========================================\n");
    fread(&m, sizeof(Marca), 1, arq);
    while (!feof(arq)) {
        printf("\nNome: %s", m.nomeMarca);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&m, sizeof(Marca), 1, arq);
    }
    if (!achou) printf("\nNenhuma marca cadastrada.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void listarCategorias() {
    FILE *arq;
    Categoria c;
    int achou = 0;
    arq = fopen("categorias.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n          LISTA DE CATEGORIAS           ");
    printf("\n========================================\n");
    fread(&c, sizeof(Categoria), 1, arq);
    while (!feof(arq)) {
        printf("\nNome: %s", c.nomeCat);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&c, sizeof(Categoria), 1, arq);
    }
    if (!achou) printf("\nNenhuma categoria cadastrada.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void listarPedidos() {
    FILE *arq;
    Pedido p;
    int achou = 0;
    arq = fopen("pedidos.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n========================================");
    printf("\n           LISTA DE PEDIDOS             ");
    printf("\n========================================\n");
    fread(&p, sizeof(Pedido), 1, arq);
    while (!feof(arq)) {
        printf("\nCodigo:      %d", p.cod);
        printf("\nID Socio:    %d", p.idSocio);
        printf("\nData:        %s", p.data);
        printf("\nStatus:      %d", p.status);
        printf("\nTotal:       R$ %.2f", p.total);
        printf("\n-- Item do Pedido --");
        printf("\nID Produto:  %d", p.ip.idProduto);
        printf("\nQuantidade:  %d", p.ip.quant);
        printf("\nSubtotal:    R$ %.2f", p.ip.subtotal);
        printf("\n----------------------------------------\n");
        achou = 1;
        fread(&p, sizeof(Pedido), 1, arq);
    }
    if (!achou) printf("\nNenhum pedido cadastrado.\n");
    fclose(arq);
    printf("\n========================================");
    system("pause");
    system("cls");
}

void editaSocio() {
    Socio s;
    int pos, op;
    FILE *arq;
    arq = fopen("socios.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR SOCIO PELO NOME ======\n");
    printf("\nNome para editar: "); fflush(stdin);
    gets(s.dados.nome);
    while (strcmp(s.dados.nome, "") != 0) {
        pos = buscaSocio(arq, s.dados.nome);
        if (pos == -1) {
            printf("\nSocio nao cadastrado");
        } else {
            fseek(arq, pos, 0);
            fread(&s, sizeof(Socio), 1, arq);
            printf("\n----------------------------\n");
            printf("\nNome: %s", s.dados.nome);
            printf("\nAtivo: %c", s.ativo);
            printf("\n----------------------------\n");
            printf("\nDeseja alterar \n1 - Nome \n2 - Status\n");
            scanf("%d", &op);
            if (op == 1) {
                printf("\nNovo nome: "); fflush(stdin);
                gets(s.dados.nome);
                fseek(arq, pos, 0);
                fwrite(&s, sizeof(Socio), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
            if (op == 2) {
                printf("\nNovo status (S/N): "); fflush(stdin);
                scanf(" %c", &s.ativo);
                fseek(arq, pos, 0);
                fwrite(&s, sizeof(Socio), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
        }
        system("cls");
        printf("\nNome para editar (ENTER para sair): "); fflush(stdin);
        gets(s.dados.nome);
    }
    fclose(arq);
}

void editaFornecedor() {
    Fornecedor f;
    int pos, op;
    FILE *arq;
    arq = fopen("fornecedores.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR FORNECEDOR PELO NOME ======\n");
    printf("\nNome para editar: "); fflush(stdin);
    gets(f.dados.nome);
    while (strcmp(f.dados.nome, "") != 0) {
        pos = buscaFornecedor(arq, f.dados.nome);
        if (pos == -1) {
            printf("\nFornecedor nao cadastrado");
        } else {
            fseek(arq, pos, 0);
            fread(&f, sizeof(Fornecedor), 1, arq);
            printf("\n----------------------------\n");
            printf("\nNome: %s", f.dados.nome);
            printf("\nEmpresa: %s", f.empresa);
            printf("\n----------------------------\n");
            printf("\nDeseja alterar \n1 - Nome \n2 - Empresa\n");
            scanf("%d", &op);
            if (op == 1) {
                printf("\nNovo nome: "); fflush(stdin);
                gets(f.dados.nome);
                fseek(arq, pos, 0);
                fwrite(&f, sizeof(Fornecedor), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
            if (op == 2) {
                printf("\nNova Empresa: "); fflush(stdin);
                gets(f.empresa);
                fseek(arq, pos, 0);
                fwrite(&f, sizeof(Fornecedor), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
        }
        system("cls");
        printf("\nNome para editar (ENTER para sair): "); fflush(stdin);
        gets(f.dados.nome);
    }
    fclose(arq);
}

void editaProduto() {
    Produto p;
    int pos, op;
    FILE *arq;
    arq = fopen("produtos.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR PRODUTO PELO NOME ======\n");
    printf("\nNome para editar: "); fflush(stdin);
    gets(p.nomeProd);
    while (strcmp(p.nomeProd, "") != 0) {
        pos = buscaProduto(arq, p.nomeProd);
        if (pos == -1) {
            printf("\nProduto nao cadastrado");
        } else {
            fseek(arq, pos, 0);
            fread(&p, sizeof(Produto), 1, arq);
            printf("\n----------------------------\n");
            printf("\nEstoque: %d", p.estoque);
            printf("\nPreco: %.2f", p.preco);
            printf("\n----------------------------\n");
            printf("\nDeseja alterar \n1 - Estoque \n2 - Preco\n");
            scanf("%d", &op);
            if (op == 1) {
                printf("\nNovo Estoque: ");
                scanf("%d", &p.estoque);
                fseek(arq, pos, 0);
                fwrite(&p, sizeof(Produto), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
            if (op == 2) {
                printf("\nNovo preco: ");
                scanf("%f", &p.preco);
                fseek(arq, pos, 0);
                fwrite(&p, sizeof(Produto), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
        }
        system("cls");
        printf("\nNome para editar (ENTER para sair): "); fflush(stdin);
        gets(p.nomeProd);
    }
    fclose(arq);
}

void editaCategoria() {
    Categoria c;
    int pos, op;
    FILE *arq;
    arq = fopen("categorias.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR CATEGORIA PELO NOME ======\n");
    printf("\nNome para editar: "); fflush(stdin);
    gets(c.nomeCat);
    while (strcmp(c.nomeCat, "") != 0) {
        pos = buscaCategoria(arq, c.nomeCat);
        if (pos == -1) {
            printf("\nCategoria nao cadastrada");
        } else {
            fseek(arq, pos, 0);
            fread(&c, sizeof(Categoria), 1, arq);
            printf("\n----------------------------\n");
            printf("\nNome: %s", c.nomeCat);
            printf("\nID: %d", c.id);
            printf("\n----------------------------\n");
            printf("\nDeseja alterar \n1 - Nome \n2 - ID\n");
            scanf("%d", &op);
            if (op == 1) {
                printf("\nNovo nome: "); fflush(stdin);
                gets(c.nomeCat);
                fseek(arq, pos, 0);
                fwrite(&c, sizeof(Categoria), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
            if (op == 2) {
                printf("\nNovo ID: ");
                scanf("%d", &c.id);
                fseek(arq, pos, 0);
                fwrite(&c, sizeof(Categoria), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
        }
        system("cls");
        printf("\nNome para editar (ENTER para sair): "); fflush(stdin);
        gets(c.nomeCat);
    }
    fclose(arq);
}

void editaMarca() {
    Marca m;
    int pos, op;
    FILE *arq;
    arq = fopen("marcas.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR MARCA PELO NOME ======\n");
    printf("\nNome para editar: "); fflush(stdin);
    gets(m.nomeMarca);
    while (strcmp(m.nomeMarca, "") != 0) {
        pos = buscaMarca(arq, m.nomeMarca);
        if (pos == -1) {
            printf("\nMarca nao cadastrada");
        } else {
            fseek(arq, pos, 0);
            fread(&m, sizeof(Marca), 1, arq);
            printf("\n----------------------------\n");
            printf("\nNome: %s", m.nomeMarca);
            printf("\nID: %d", m.id);
            printf("\n----------------------------\n");
            printf("\nDeseja alterar \n1 - Nome \n2 - ID\n");
            scanf("%d", &op);
            if (op == 1) {
                printf("\nNovo nome: "); fflush(stdin);
                gets(m.nomeMarca);
                fseek(arq, pos, 0);
                fwrite(&m, sizeof(Marca), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
            if (op == 2) {
                printf("\nNovo ID: ");
                scanf("%d", &m.id);
                fseek(arq, pos, 0);
                fwrite(&m, sizeof(Marca), 1, arq);
                printf("\nRegistro atualizado!");
                system("pause");
            }
        }
        system("cls");
        printf("\nNome para editar (ENTER para sair): "); fflush(stdin);
        gets(m.nomeMarca);
    }
    fclose(arq);
}

void atualizaStatus_pedido() {
    Pedido p;
    int pos;
    FILE *arq;
    arq = fopen("pedidos.bin", "rb+");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\n====== ALTERAR STATUS DO PEDIDO ======\n");
    printf("\nCodigo para editar: ");
    scanf("%d", &p.cod);
    pos = buscaPedido(arq, p.cod);
    if (pos == -1) {
        printf("\nPedido nao cadastrado");
    } else {
        fseek(arq, pos, 0);
        fread(&p, sizeof(Pedido), 1, arq);
        printf("\n----------------------------\n");
        printf("\nCodigo: %d", p.cod);
        printf("\nStatus atual: %d", p.status);
        printf("\n----------------------------\n");
        printf("\nNovo Status (1-Pendente 2-Concluido 3-Cancelado): ");
        scanf("%d", &p.status);
        fseek(arq, pos, 0);
        fwrite(&p, sizeof(Pedido), 1, arq);
        printf("\nRegistro atualizado!");
        system("pause");
    }
    fclose(arq);
}


void excluiSocio() {
    FILE *arq, *temp;
    Socio s;
    int pos;
    char nome[50];
    arq = fopen("socios.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o nome do socio a excluir: "); fflush(stdin);
    gets(nome);
    pos = buscaSocio(arq, nome);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
    } else {
        fseek(arq, pos, 0);
        fread(&s, sizeof(Socio), 1, arq);
        printf("\n=====================\n");
        printf("\nNome: %s", s.dados.nome);
        printf("\nTelefone: %s", s.dados.telefone);
        printf("\nEmail: %s", s.dados.email);
        printf("\nData de vencimento: %s", s.dataVenc);
        printf("\nAtivo: %c", s.ativo);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&s, sizeof(Socio), 1, arq) == 1) {
                if (strcmp(nome, s.dados.nome) != 0)
                    fwrite(&s, sizeof(Socio), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("socios.bin");
            rename("aux.bin", "socios.bin");
            printf("\nSocio excluido com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}

void excluiFornecedor() {
    FILE *arq, *temp;
    Fornecedor f;
    int pos;
    char nome[50];
    arq = fopen("fornecedores.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o nome do fornecedor a excluir: "); fflush(stdin);
    gets(nome);
    pos = buscaFornecedor(arq, nome);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
    } else {
        fseek(arq, pos, 0);
        fread(&f, sizeof(Fornecedor), 1, arq);
        printf("\n=====================\n");
        printf("\nNome: %s", f.dados.nome);
        printf("\nTelefone: %s", f.dados.telefone);
        printf("\nEmail: %s", f.dados.email);
        printf("\nEmpresa: %s", f.empresa);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&f, sizeof(Fornecedor), 1, arq) == 1) {
                if (strcmp(nome, f.dados.nome) != 0)
                    fwrite(&f, sizeof(Fornecedor), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("fornecedores.bin");
            rename("aux.bin", "fornecedores.bin");
            printf("\nFornecedor excluido com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}

void excluiCategoria() {
    FILE *arq, *temp;
    Categoria c;
    int pos;
    char nome[50];
    arq = fopen("categorias.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o nome da categoria a excluir: "); fflush(stdin);
    gets(nome);
    pos = buscaCategoria(arq, nome);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
    } else {
        fseek(arq, pos, 0);
        fread(&c, sizeof(Categoria), 1, arq);
        printf("\n=====================\n");
        printf("\nNome: %s", c.nomeCat);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&c, sizeof(Categoria), 1, arq) == 1) {
                if (strcmp(nome, c.nomeCat) != 0)
                    fwrite(&c, sizeof(Categoria), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("categorias.bin");
            rename("aux.bin", "categorias.bin");
            printf("\nCategoria excluida com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}

void excluiMarca() {
    FILE *arq, *temp;
    Marca m;
    int pos;
    char nome[50];
    arq = fopen("marcas.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o nome da marca a excluir: "); fflush(stdin);
    gets(nome);
    pos = buscaMarca(arq, nome);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
    } else {
        fseek(arq, pos, 0);
        fread(&m, sizeof(Marca), 1, arq);
        printf("\n=====================\n");
        printf("\nNome: %s", m.nomeMarca);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&m, sizeof(Marca), 1, arq) == 1) {
                if (strcmp(nome, m.nomeMarca) != 0)
                    fwrite(&m, sizeof(Marca), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("marcas.bin");
            rename("aux.bin", "marcas.bin");
            printf("\nMarca excluida com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}

void excluiPedido() {
    FILE *arq, *temp;
    Pedido p;
    int pos, cod;
    arq = fopen("pedidos.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o cod do pedido a excluir: ");
    scanf("%d", &cod);
    pos = buscaPedido(arq, cod);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
        fclose(arq);
    } else {
        fseek(arq, pos, 0);
        fread(&p, sizeof(Pedido), 1, arq);
        printf("\n=====================\n");
        printf("\nCodigo: %d", p.cod);
        printf("\nID do Socio: %d", p.idSocio);
        printf("\nData: %s", p.data);
        printf("\nStatus: %d", p.status);
        printf("\nTotal: %.2f", p.total);
        printf("\nProduto ID: %d", p.ip.idProduto);
        printf("\nQuantidade: %d", p.ip.quant);
        printf("\nSubtotal: %.2f", p.ip.subtotal);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&p, sizeof(Pedido), 1, arq) == 1) {
                if (p.cod != cod)
                    fwrite(&p, sizeof(Pedido), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("pedidos.bin");
            rename("aux.bin", "pedidos.bin");
            printf("\nPedido excluido com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}

void excluiProduto() {
    FILE *arq, *temp;
    Produto p;
    int pos;
    char nome[50];
    arq = fopen("produtos.bin", "rb");
    if (arq == NULL) { printf("\nErro no arquivo"); return; }
    system("cls");
    printf("\nInforme o nome do produto a excluir: "); fflush(stdin);
    gets(nome);
    pos = buscaProduto(arq, nome);
    if (pos == -1) {
        printf("\nRegistro nao encontrado");
    } else {
        fseek(arq, pos, 0);
        fread(&p, sizeof(Produto), 1, arq);
        printf("\n=====================\n");
        printf("\nCodigo:    %d", p.id);
        printf("\nNome:      %s", p.nomeProd);
        printf("\nEstoque:   %d", p.estoque);
        printf("\nPreco:     R$ %.2f", p.preco);
        printf("\nMarca:     %s", p.m.nomeMarca);
        printf("\nCategoria: %s", p.c.nomeCat);
        printf("\nDeseja Excluir: (S/N) ");
        if (toupper(getche()) == 'S') {
            temp = fopen("aux.bin", "wb");
            rewind(arq);
            while (fread(&p, sizeof(Produto), 1, arq) == 1) {
                if (strcmp(nome, p.nomeProd) != 0)
                    fwrite(&p, sizeof(Produto), 1, temp);
            }
            fclose(temp);
            fclose(arq);
            remove("produtos.bin");
            rename("aux.bin", "produtos.bin");
            printf("\nProduto excluido com sucesso!");
        } else {
            fclose(arq);
        }
    }
    getchar();
    system("cls");
}


void relatorioSociosVencendo() {
    FILE *arq;
    Socio s;
    int achou = 0;
    time_t agora = time(NULL);
    time_t limite = agora + (30 * 24 * 60 * 60);

    arq = fopen("socios.bin", "rb");
    if (arq == NULL) { printf("\nErro ao abrir socios.bin"); return; }

    system("cls");
    printf("\n========================================");
    printf("\n   SOCIOS COM ASSINATURA VENCENDO       ");
    printf("\n========================================\n");

    fread(&s, sizeof(Socio), 1, arq);
    while (!feof(arq)) {
        if (s.ativo == 'S' || s.ativo == 's') {
            struct tm t = {0};
            sscanf(s.dataVenc, "%d/%d/%d", &t.tm_mday, &t.tm_mon, &t.tm_year);
            t.tm_mon  -= 1;
            t.tm_year -= 1900;
            time_t venc = mktime(&t);
            if (venc >= agora && venc <= limite) {
                printf("\nNome:      %s", s.dados.nome);
                printf("\nTelefone:  %s", s.dados.telefone);
                printf("\nEmail:     %s", s.dados.email);
                printf("\nVencimento:%s", s.dataVenc);
                printf("\n----------------------------------------\n");
                achou = 1;
            }
        }
        fread(&s, sizeof(Socio), 1, arq);
    }

    if (!achou) printf("\nNenhum socio com vencimento nos proximos 30 dias.\n");
    fclose(arq);
    printf("\n========================================");
    getchar(); getchar();
    system("cls");
}

void relatorioProdutosMaisVendidos() {
    FILE *arqPed, *arqPro;
    Pedido ped;
    Produto pro;
    int ids[100], qtds[100], total = 0;
    int i, j, a, b, tmp, exibe;

    arqPro = fopen("produtos.bin", "rb");
    if (arqPro == NULL) { printf("\nErro ao abrir produtos.bin"); return; }

    fread(&pro, sizeof(Produto), 1, arqPro);
    while (!feof(arqPro)) {
        ids[total]  = pro.id;
        qtds[total] = 0;
        total++;
        fread(&pro, sizeof(Produto), 1, arqPro);
    }
    fclose(arqPro);

    arqPed = fopen("pedidos.bin", "rb");
    if (arqPed == NULL) { printf("\nErro ao abrir pedidos.bin"); return; }

    fread(&ped, sizeof(Pedido), 1, arqPed);
    while (!feof(arqPed)) {
        for (j = 0; j < total; j++) {
            if (ids[j] == ped.ip.idProduto) {
                qtds[j] += ped.ip.quant;
                break;
            }
        }
        fread(&ped, sizeof(Pedido), 1, arqPed);
    }
    fclose(arqPed);

    for (a = 0; a < total - 1; a++) {
        for (b = a + 1; b < total; b++) {
            if (qtds[b] > qtds[a]) {
                tmp = qtds[a]; qtds[a] = qtds[b]; qtds[b] = tmp;
                tmp = ids[a];  ids[a]  = ids[b];  ids[b]  = tmp;
            }
        }
    }

    system("cls");
    printf("\n========================================");
    printf("\n        PRODUTOS MAIS VENDIDOS          ");
    printf("\n========================================\n");

    exibe = (total < 5) ? total : 5;
    arqPro = fopen("produtos.bin", "rb");
    for (i = 0; i < exibe; i++) {
        if (qtds[i] == 0) break;
        rewind(arqPro);
        fread(&pro, sizeof(Produto), 1, arqPro);
        while (!feof(arqPro)) {
            if (pro.id == ids[i]) {
                printf("\n%d. %-30s Vendidos: %d", i + 1, pro.nomeProd, qtds[i]);
                break;
            }
            fread(&pro, sizeof(Produto), 1, arqPro);
        }
    }
    fclose(arqPro);

    printf("\n\n========================================");
    getchar(); getchar();
    system("cls");
}

void relatorioEstoqueBaixo() {
    FILE *arq;
    Produto p;
    int achou = 0;
    int limite = 10;

    arq = fopen("produtos.bin", "rb");
    if (arq == NULL) { printf("\nErro ao abrir produtos.bin"); return; }

    system("cls");
    printf("\n========================================");
    printf("\n      PRODUTOS COM ESTOQUE BAIXO        ");
    printf("\n========================================\n");

    fread(&p, sizeof(Produto), 1, arq);
    while (!feof(arq)) {
        if (p.estoque < limite) {
            printf("\nProduto:   %s", p.nomeProd);
            printf("\nCategoria: %s", p.c.nomeCat);
            printf("\nMarca:     %s", p.m.nomeMarca);
            printf("\nEstoque:   %d unidades", p.estoque);
            printf("\nPreco:     R$ %.2f", p.preco);
            printf("\n----------------------------------------\n");
            achou = 1;
        }
        fread(&p, sizeof(Produto), 1, arq);
    }

    if (!achou) printf("\nNenhum produto com estoque baixo.\n");
    fclose(arq);
    printf("\n========================================");
    getchar(); getchar();
    system("cls");
}

void relatorioProdutosPorCategoria() {
    FILE *arq;
    Produto p;
    char catVistas[100][50];
    int totalCats = 0, jaViu, i;

    arq = fopen("produtos.bin", "rb");
    if (arq == NULL) { printf("\nErro ao abrir produtos.bin"); return; }

    system("cls");
    printf("\n========================================");
    printf("\n        PRODUTOS POR CATEGORIA          ");
    printf("\n========================================\n");

    fread(&p, sizeof(Produto), 1, arq);
    while (!feof(arq)) {
        jaViu = 0;
        for (i = 0; i < totalCats; i++) {
            if (strcmp(catVistas[i], p.c.nomeCat) == 0) { jaViu = 1; break; }
        }
        if (!jaViu) {
            strcpy(catVistas[totalCats++], p.c.nomeCat);
            printf("\n\n=== %s ===\n", p.c.nomeCat);

            FILE *arq2 = fopen("produtos.bin", "rb");
            Produto p2;
            fread(&p2, sizeof(Produto), 1, arq2);
            while (!feof(arq2)) {
                if (strcmp(p2.c.nomeCat, p.c.nomeCat) == 0)
                    printf("  - %-30s Estoque: %3d  Preco: R$ %.2f\n", p2.nomeProd, p2.estoque, p2.preco);
                fread(&p2, sizeof(Produto), 1, arq2);
            }
            fclose(arq2);
        }
        fread(&p, sizeof(Produto), 1, arq);
    }

    fclose(arq);
    printf("\n========================================");
    getchar(); getchar();
    system("cls");
}

void relatorioProdutosPorMarca() {
    FILE *arq;
    Produto p;
    char marcasVistas[100][50];
    int totalMarcas = 0, jaViu, i;

    arq = fopen("produtos.bin", "rb");
    if (arq == NULL) { printf("\nErro ao abrir produtos.bin"); return; }

    system("cls");
    printf("\n========================================");
    printf("\n          PRODUTOS POR MARCA            ");
    printf("\n========================================\n");

    fread(&p, sizeof(Produto), 1, arq);
    while (!feof(arq)) {
        jaViu = 0;
        for (i = 0; i < totalMarcas; i++) {
            if (strcmp(marcasVistas[i], p.m.nomeMarca) == 0) { jaViu = 1; break; }
        }
        if (!jaViu) {
            strcpy(marcasVistas[totalMarcas++], p.m.nomeMarca);
            printf("\n\n=== %s ===\n", p.m.nomeMarca);

            FILE *arq2 = fopen("produtos.bin", "rb");
            Produto p2;
            fread(&p2, sizeof(Produto), 1, arq2);
            while (!feof(arq2)) {
                if (strcmp(p2.m.nomeMarca, p.m.nomeMarca) == 0)
                    printf("  - %-30s Estoque: %3d  Preco: R$ %.2f\n", p2.nomeProd, p2.estoque, p2.preco);
                fread(&p2, sizeof(Produto), 1, arq2);
            }
            fclose(arq2);
        }
        fread(&p, sizeof(Produto), 1, arq);
    }

    fclose(arq);
    printf("\n========================================");
    getchar(); getchar();
    system("cls");
}


int main() {
    int opcao;
    do {
        opcao = Menu();
        switch (opcao) {
            case 1: {
                int submenu;
                printf("\n1-Gerenciar Socio");
                printf("\n2-Fornecedores");
                printf("\n0-Voltar");
                printf("\nOpcao: ");
                scanf("%d", &submenu);

                switch (submenu) {
                    case 1: {
                        int opSocio;
                        do {
                            system("cls");
                            printf("\n=== GERENCIAR SOCIO ===\n");
                            printf("\n1-Cadastrar Socio");
                            printf("\n2-Listar Socios");
                            printf("\n3-Editar Socio");
                            printf("\n4-Excluir Socio");
                            printf("\n0-Voltar");
                            printf("\nOpcao: ");
                            scanf("%d", &opSocio);
                            switch (opSocio) {
                                case 1: Cadastro_socio();   break;
                                case 2: listarSocios();     break;
                                case 3: editaSocio();       break;
                                case 4: excluiSocio();      break;
                                default: if(opSocio!=0) printf("\nOpcao Invalida"); break;
                            }
                        } while (opSocio != 0);
                        break;
                    }
                    case 2: {
                        int opFornecedor;
                        do {
                            system("cls");
                            printf("\n=== GERENCIAR FORNECEDOR ===\n");
                            printf("\n1-Cadastrar Fornecedor");
                            printf("\n2-Listar Fornecedores");
                            printf("\n3-Editar Fornecedor");
                            printf("\n4-Excluir Fornecedor");
                            printf("\n0-Voltar");
                            printf("\nOpcao: ");
                            scanf("%d", &opFornecedor);
                            switch (opFornecedor) {
                                case 1: Cadastro_fornecedor();  break;
                                case 2: listarFornecedores();   break;
                                case 3: editaFornecedor();      break;
                                case 4: excluiFornecedor();     break;
                                default: if(opFornecedor!=0) printf("\nOpcao Invalida"); break;
                            }
                        } while (opFornecedor != 0);
                        break;
                    }
                    default: printf("\nOpcao invalida"); break;
                }
                break;
            }
            case 2: {
                int opProd;
                do {
                    system("cls");
                    printf("\n=== GERENCIAR PRODUTOS ===\n");
                    printf("1-Cadastrar produto\n");
                    printf("2-Listar produtos\n");
                    printf("3-Editar produto\n");
                    printf("4-Excluir produto\n");
                    printf("0-Voltar\n");
                    scanf("%d", &opProd);
                    switch (opProd) {
                        case 1: Cadastro_produto(); break;
                        case 2: listarProdutos();   break;
                        case 3: editaProduto();     break;
                        case 4: excluiProduto();    break;
                        default: if(opProd!=0) printf("\nOpcao Invalida"); break;
                    }
                } while (opProd != 0);
                break;
            }
            case 3: {
                int opPed;
                do {
                    system("cls");
                    printf("\n=== PEDIDOS ===\n");
                    printf("\n1-Efetuar pedido");
                    printf("\n2-Listar pedidos");
                    printf("\n3-Atualizar status do pedido");
                    printf("\n4-Cancelar pedido");
                    printf("\n0-Voltar\n");
                    scanf("%d", &opPed);
                    switch (opPed) {
                        case 1: cadastrosPedido();       break;
                        case 2: listarPedidos();         break;
                        case 3: atualizaStatus_pedido(); break;
                        case 4: excluiPedido();          break;
                        default: if(opPed!=0) printf("\nOpcao Invalida"); break;
                    }
                } while (opPed != 0);
                break;
            }
            case 4: {
                int opRel;
                do {
                    system("cls");
                    printf("\n=== RELATORIOS ===\n");
                    printf("\n1-Socios com assinatura vencendo");
                    printf("\n2-Produtos mais vendidos");
                    printf("\n3-Produtos com estoque baixo");
                    printf("\n4-Produtos por categoria");
                    printf("\n5-Produtos por marca");
                    printf("\n0-Voltar\n");
                    scanf("%d", &opRel);
                    switch (opRel) {
                        case 1: relatorioSociosVencendo();          break;
                        case 2: relatorioProdutosMaisVendidos();    break;
                        case 3: relatorioEstoqueBaixo();            break;
                        case 4: relatorioProdutosPorCategoria();    break;
                        case 5: relatorioProdutosPorMarca();        break;
                        default: if(opRel!=0) printf("\nOpcao Invalida"); break;
                    }
                } while (opRel != 0);
                break;
            }
            case 5:{
                printf("\nSaindo...");
                break;
            }
            default:
                printf("\nOpcao invalida, digite novamente");
                break;
        }
    } while (opcao != 0);
    return 0;
}