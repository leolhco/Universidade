#include <sys/types.h>
#include <sys/stat.h>

#include "btree.h"

#ifndef _BTREE_CPP
#define	_BTREE_CPP

bool fileExists(const char *filename) { struct stat statBuf; if (stat(filename,&statBuf) < 0) return false; return S_ISREG(statBuf.st_mode); }

btree::btree() {
    char nomearquivo[20] = "arvoreb.dat";

    // se arquivo ja existir, abrir e carregar cabecalho
    if (fileExists(nomearquivo)) {
        // abre arquivo
        arquivo = fopen(nomearquivo,"r+");
        leCabecalho();
    }
    // senao, criar novo arquivo e salvar o cabecalho
    else {
        // cria arquivo
        arquivo = fopen(nomearquivo,"w+");

        // atualiza cabecalho
        cabecalhoArvore.numeroElementos = 0;
        cabecalhoArvore.paginaRaiz = -1;
        salvaCabecalho();
    }
}

btree::~btree() {
    // fechar arquivo
    fclose(arquivo);
}

int btree::computarTaxaOcupacao() {
    return 0;
}

void btree::insereChave(int chave, int valor) {
    
    if (cabecalho.paginaRaiz == -1) {
        
        int npid;
        pagina* nR = criarPagina(&npid);
        
        if (!nR) 
            return;
        
        
        nR->chaves[0] = chave;
        nR->valores[0] = valor;
        nR->qtdElementos = 1;

        
        cabecalho.paginaRaiz = npid;
        cabecalho.altura = 1;
        cabecalho.totalChaves = 1;

       
        salvarPagina(npid, nR);
        delete nR;
        salvarCabecalho();
        
        return;
    
    }

    
    int chaveP;
    int paginaDP;
    
    
    int res = insereRecursivo(chave, valor, cabecalho.paginaRaiz, 1, 
                                   &chaveP, &paginaDP);

    
    if (res == SPLIT_OCORREU) {
        int npid;
        pagina* nR = criarPagina(&npid);
        if (!nR) 
            return;

        
        nR->qtdElementos = 1;
        nR->chaves[0] = chaveP;
        nR->valores[0] = cabecalho.paginaRaiz;
        nR->valores[1] = paginaDP;
        
        
        cabecalho.paginaRaiz = npid;
        cabecalho.altura++;
        
        
        salvarPagina(npid, nR);
        delete nR;
    }

    
    if(res != FALHA_INSERCAO) {
        cabecalho.totalChaves++;
        salvarCabecalho();
    }

}

int btree::insereRecursivo(int chave, int valor, int idP, int nivel, 
                           int* chaveP, int* paginaDP) {
    
    pagina* pag = lePagina(idP);
   
    if (pag == nullptr) 
        return -1; 

    
    int pos = 0;
   
    while(pos < pag->numeroElementos && chave > pag->chaves[pos]) {
        
        pos++;
   
    }

    if(nivel == cabecalhoArvore.alturaArvore) { 
        
        if(pos < pag->numeroElementos && chave == pag->chaves[pos]) {
            
            delete pag;
           
            return -1;
        
        }

        if(pag->numeroElementos < ORDEM - 1) { 
           
            insPag(pag, chave, valor, -1);
            salvaPagina(idP, pag);
            delete pag;
            
            return 0;
        
        } else { 
            
            divNo(pag, chave, valor, -1, chaveP, paginaDP);
            delete pag;
            
            return 1;

        }
    
    } else { 
        
        int pagF = pag->valores[pos];
        int result = insereRecursivo(chave, valor, pagF, nivel + 1, chaveP, paginaDP);

        if(result == 1) { 
             
            if(pag->numeroElementos < ORDEM - 1) { 
                
                insPag(pag, *chaveP, -1, *paginaDP);
                salvaPagina(idP, pag);
                delete pag;
                
                return 0;

             } else { 
                
                divNo(pag, *chaveP, -1, *paginaDP, chaveP, paginaDP);
                delete pag;
                
                return 1;
             
            }
        
        }
        
        delete pag;
        
        return 0;
    
    }

}

void btree::insPag(pagina *pag, int chave, int val, int dir) {
    
    int i = pag->numeroElementos;

    while(i > 0 && chave < pag->chaves[i-1]) {
        
        pag->chaves[i] = pag->chaves[i-1];
        
        if (dir == -1) {
             
            pag->valores[i] = pag->valores[i-1];
        
        } else {

            pag->valores[i+1] = pag->valores[i];
        
        }
        
        i--;
    }

    pag->chaves[i] = chave;

    if (dir == -1) {
        
        pag->valores[i] = val;
    
    } else {
        
        pag->valores[i+1] = dir;
    
    }
    
    pag->numeroElementos++;
}

void btree::divNo(pagina *pag, int chave, int val, int dir, int *chaveP, int *paginaDP) {
    
    int i;
    int xC[ORDEM];
    int xV[ORDEM + 1];

    for (i = 0; i < pag->numeroElementos; i++) {
        
        xC[i] = pag->chaves[i];
        xV[i] = pag->valores[i];
    
    }
    
    xV[pag->numeroElementos] = pag->valores[pag->numeroElementos];

    i = pag->numeroElementos;
    
    while(i > 0 && chave < xC[i-1]) {
        
        xC[i] = xC[i-1];
        
        if (dir == -1) {
            
            xV[i] = xV[i-1];

        } else {
            
            xV[i+1] = xV[i];
       
        }
        
        i--;
    }

    xC[i] = chave;

    if (dir == -1) {
        
        xV[i] = val;
    
    } else { 
        
        xV[i+1] = dir;
    
    }
    
    int nPid;
    pagina* nPg = novaPagina(&nPid);
    
    if(!nPg) 
        return;

    *paginaDP = nPid;
    int half = ORDEM / 2;
    int elem = pag->numeroElementos + 1;
    pag->numeroElementos = half;

    for(i = 0; i < half; i++) {
        
        pag->chaves[i] = xC[i];
        pag->valores[i] = xV[i];
    
    }

    if(dir == -1) {
        
        *chaveP = xC[half];
        nPg->numeroElementos = elem - half;
        
        for (i = 0; i < nPg->numeroElementos; i++) {
            
            nPg->chaves[i] = xC[half + i];
            nPg->valores[i] = xV[half + i];
        
        }
        
        pag->valores[half] = nPid; 
    
    } else { 
        
        *chaveP = xC[half]; 
        nPg->numeroElementos = elem - half - 1;

        for (i = 0; i < nPg->numeroElementos; i++) {
            
            nPg->chaves[i] = xC[half + 1 + i];
        
        }
        
        for (i = 0; i < nPg->numeroElementos + 1; i++) {
            
            nPg->valores[i] = xV[half + 1 + i];
        
        }
    
    }
    
    salvaPagina(pag->numeroPagina, pag);
    salvaPagina(nPg->numeroPagina, nPg);
    delete nPg;

}

void btree::removeChave(int chave) {
	// neste trabalho, não é necessário implementar a remoção!

    // se remover, atualizar cabecalho
    if (true) {
        cabecalhoArvore.numeroElementos--;
        salvaCabecalho();
    }
}

int btree::buscaChave(int chave) {
    
    if (cabecalhoArvore.paginaRaiz == -1) 
        return -1;
    

    int num = cabecalhoArvore.paginaRaiz;
    int nivel = 1;

    while (nivel <= cabecalhoArvore.alturaArvore) {
        
        pagina* pag = lePagina(num);
        
        if (pag == nullptr) 
            return -1; 
        

        int pos = 0;
        
        while (pos < pag->numeroElementos && chave > pag->chaves[pos]) {
            
            pos++;
        
        }

        if (pos < pag->numeroElementos && chave == pag->chaves[pos]) {
            
            if (nivel == cabecalhoArvore.alturaArvore) {
                
                int encontrou = pag->valores[pos];
                delete pag;
                return encontrou;
            
            } else {
                
                num = pag->valores[pos + 1];
            
            }
        
        } else {
            
            num = pag->valores[pos];
        
        }
        
        delete pag;
        nivel++;
    
    }

    return -1;
}

#endif	/* _BTREE_CPP */
