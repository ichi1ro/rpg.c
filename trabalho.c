#include <stdio.h>
#include <stdlib.h>

struct tipo_jogador{
    char nome[100];
    int time;
    int chave;
};

struct tipo_celula{
    struct tipo_jogador jogador;
    struct tipo_celula *prox;
    struct tipo_celula *ant;
    int prioridade;
};

struct tipo_lista{
    struct tipo_celula *sent;
    struct tipo_celula *atual;
};

void inicializa(struct tipo_lista *l){
    l->sent = (struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    l->sent->prox = l->sent;
    l->sent->ant = l->sent;
    l->atual = l->sent;
}

int vazio(struct tipo_lista *l){
    return l->sent->prox == l->sent->ant;
}

void insere_jogador(struct tipo_lista *l, struct tipo_jogador x, int prioridade){
    struct tipo_celula *novo;
    novo = (struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->jogador = x;
    novo->prioridade = prioridade;
    novo->prox = l->sent;
    novo->ant = l->sent->ant;
    l->sent->ant->prox = novo;
    l->sent->ant = novo;
}

void lista_jogador(struct tipo_lista *l){
    struct tipo_celula *ptr;
    ptr = l->sent->prox;
    while(ptr!=l->sent){
        printf("\nJogador: %s | Time: %d | Prioridade: %d\n", ptr->jogador.nome, ptr->jogador.time, ptr->prioridade);
        ptr = ptr->prox;
    }
    printf("\n");
}

void lista_jogador2(struct tipo_lista *l){
    struct tipo_celula *ptr;
    ptr = l->sent->prox;
    while(ptr!=l->sent){
        printf("\n%d. Jogador: %s | Time: %d | Prioridade: %d\n",ptr->jogador.chave, ptr->jogador.nome, ptr->jogador.time, ptr->prioridade);
        ptr = ptr->prox;
    }
    printf("\n");
}

void lista_jogador3(struct tipo_lista *l){
    struct tipo_celula *ptr;
    ptr = l->sent->prox;
    while(ptr!=l->sent){
        printf("\nJogador: %s | Time: %d | (%d) \n ", ptr->jogador.nome, ptr->jogador.time, ptr->prioridade);
        ptr = ptr->prox;
    }
    if(l->atual == l->sent){
        l->atual = l->atual->prox;
    }
    printf("\nVez do jogador: %s\n", l->atual->jogador.nome);
}

struct tipo_celula *busca(struct tipo_lista *l, int chave){
    struct tipo_celula *ptr;
    ptr = l->sent->prox;
    while(ptr!=l->sent && chave!= ptr->jogador.chave){
        ptr = ptr->prox;
    }
    if(ptr!=l->sent){
        return ptr;
    }else{
        return NULL;
    }
    
}

int remove_jogador(struct tipo_lista *l, struct tipo_jogador *x, int *prioridade, struct tipo_jogador y){ 
    struct tipo_celula *del;
    del = busca(l,y.chave);
    if(del==NULL){
        return 0;
    }else{
        *x = del->jogador;
        *prioridade = del->prioridade;
        del->prox->ant = del->ant;
        del->ant->prox = del->prox;
        if(del==l->atual){
            l->atual = l->atual->prox;
        }
        free(del);
        return 1;
    }
    
    
}

struct tipo_celula *encontra_maior(struct tipo_lista *l){
    struct tipo_celula *ptr,*maior;
    maior=l->sent->prox;
    for(ptr=l->sent->prox; ptr!=l->sent; ptr=ptr->prox){
        if(ptr->prioridade > maior->prioridade)
            maior=ptr;
    }
    if(maior != l->sent)
        return maior;
    return NULL;
}

struct tipo_lista *conc(struct tipo_lista *l, struct tipo_lista *p){
    struct tipo_celula *maior;
    l->sent->prioridade = '!';
    while(l->sent->ant->prioridade!='!'){
        maior = encontra_maior(l);
        maior->ant->prox = maior->prox;
        maior->prox->ant = maior->ant;
        maior->ant = p->sent->ant;
        maior->prox = p->sent;
        p->sent->ant->prox = maior;
        p->sent->ant = maior;
    }
    if(!vazio(p)){
        return p;
    }
    return NULL;
}

void conc2(struct tipo_lista *l, struct tipo_lista *p){
    struct tipo_celula *ptr,*apt,*igual;
    ptr = l->sent->prox;
    if(ptr->prioridade > p->sent->prox->prioridade){
        ptr->ant->prox = ptr->prox;
        ptr->prox->ant = ptr->ant;
        ptr->prox = p->sent->prox;
        ptr->ant = p->sent;
        p->sent->prox->ant = ptr;
        p->sent->prox = ptr;
    }else{
        apt = p->sent->prox;
        while(apt!=p->sent && ptr->prioridade < apt->prox->prioridade){
            apt = apt->prox;
        }
        if(ptr->prioridade > apt->prox->prioridade){
            ptr->ant->prox = ptr->prox;
            ptr->prox->ant = ptr->ant;
            ptr->prox = apt->prox;
            ptr->ant = apt;
            apt->prox->ant = ptr;
            apt->prox = ptr;
        }
        igual = p->sent->prox;
        while(igual!=p->sent && ptr->prioridade != igual->prioridade){
            igual = igual->prox;
        }
        if(ptr->prioridade == igual->prioridade){
            ptr->ant->prox = ptr->prox;
            ptr->prox->ant = ptr->ant;
            ptr->prox = igual->prox;
            ptr->ant = igual;
            igual->prox->ant = ptr;
            igual->prox = ptr;
        }
    }
}

struct tipo_celula *passa_vez (struct tipo_lista *l){
    l->atual = l->atual->prox;
    return l->atual;
}

int verificar_time(struct tipo_lista *l){
    struct tipo_celula *ptr;
    int i=0,w=0;
    ptr = l->sent->prox;
    while(ptr!=l->sent){
        if(ptr->jogador.time == 1){
            i++;
        }
        if(ptr->jogador.time == 2){
            w++;
        }
        ptr = ptr->prox;
    }
    if((i>1 && w==0)||(i==0 && w>1)||(i==1 && w==0)||(i==0 && w==1)){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    struct tipo_lista *l;
    struct tipo_jogador y;
    int prioridade;
    y.chave = 1;
    l=(struct tipo_lista *)malloc(sizeof(struct tipo_lista));
    inicializa(l);
    int menu,menu2;
    do{
        printf("\nEstado de preparacao!\n1. Inserir jogador\n2. Listar jogadores\n3. Remover jogador\n4. Iniciar Partida\n5. Encerrar aplicacao\n\nDigite sua opcao: ");
        scanf("%d", &menu);
        switch(menu){
            case 1: 
                printf("Digite o jogador desejado: ");
                scanf("%s", y.nome);
                printf("Digite o seu time (1 ou 2): ");
                scanf("%d", &y.time);
                printf("Digite a sua prioridade: ");
                scanf("%d", &prioridade);
                insere_jogador(l,y,prioridade);
                y.chave++;
                break;
            case 2:
                lista_jogador(l);
                break;
            case 3: 
                lista_jogador2(l);
                printf("\nPara a remocao de um jogador, digite a sua chave: ");
                scanf("%d", &y.chave);
                remove_jogador(l,&y,&prioridade,y);
                printf("\nJogador removido: %s\n", y.nome);
                break;

            case 4:
                struct tipo_lista *p;
                p =(struct tipo_lista *)malloc(sizeof(struct tipo_lista));
                inicializa(p);
                if(verificar_time(l)){
                    printf("\nSo ha jogadores de um time!\n");
                    free(p);
                }else{
                    do{     
                        conc(l,p);
                        lista_jogador3(p);
                        if(p->atual==p->sent->prox){
                            printf("\nEstado de jogo!\n1. Encerrar a vez do jogador ativo\n2. Remover jogador\n3. Encerrar Jogo\n4. Inserir jogador\n\nDigite a sua opcao: ");
                            scanf("%d", &menu2);
                            switch(menu2){
                                case 1:
                                    passa_vez(p);
                                    break;
                                case 2:
                                    lista_jogador2(p);
                                    printf("\nPara a remocao de um jogador, digite a sua chave: ");
                                    scanf("%d", &y.chave);
                                    remove_jogador(p,&y,&prioridade,y);
                                    printf("\nJogador removido: %s\n", y.nome);
                                    break;
                                case 3:
                                    free(p);
                                    menu2=0;
                                    break;
                                case 4:
                                    printf("Digite o jogador desejado: ");
                                    scanf("%s", y.nome);
                                    printf("Digite o seu time (1 ou 2): ");
                                    scanf("%d", &y.time);
                                    printf("Digite a sua prioridade: ");
                                    scanf("%d", &prioridade);
                                    insere_jogador(l,y,prioridade);
                                    y.chave++;
                                    conc2(l,p);
                                break;
                            }
                        }else{
                            printf("\nEstado de jogo!\n1. Encerrar a vez do jogador ativo\n2. Remover jogador\n3. Encerrar Jogo\n\nDigite a sua opcao: ");
                            scanf("%d", &menu2);
                            switch(menu2){
                                case 1:
                                    passa_vez(p);
                                    break;
                                case 2:
                                    lista_jogador2(p);
                                    printf("\nPara a remocao de um jogador, digite a sua chave: ");
                                    scanf("%d", &y.chave);
                                    remove_jogador(p,&y,&prioridade,y);
                                    printf("\nJogador removido: %s\n", y.nome);
                                    break;
                                case 3:
                                    free(p);
                                    menu2=0;
                                    break;
                            }
                        }
                        if(verificar_time(p)){
                            printf("\nHa apenas jogadores de um time no jogo! Jogo encerrado\n");
                            free(p);
                            menu2=0;
                        }
                    }while(menu2!=0);
                } 
                break;
            case 5:
                menu = 0;
                break;
        }
    }while(menu!=0);
}