#include <iostream>

using namespace std;

typedef struct tupla
{
    int valor1;
    int valor2;

}tupla;

int EncontraMin(int **matriz, int n_cidades)
{
    int i, j, min = 99999999, I_backup, J_backup;

    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            if (matriz[i][j] != -1 && matriz[i][j] < min)
            {
                min = matriz[i][j];
                I_backup = i;
                J_backup = j;
            }
        }
    }
    matriz[I_backup][J_backup] = -1;

    return min;
}

bool EncontraCaminho(int **matriz, int inicial, int final, int n_cidades, int n_caminhos)
{
    int n_usados = 0, i = 0, j = 0, count = 0,i_anterior=-1,valor=0;
    bool usado[n_cidades];

    int sequencia[n_cidades];


    for (i = 0; i < n_cidades; i++)
    {
        usado[i] = false;
    }

    i = inicial;
    usado[inicial] = true;
    sequencia[valor]=i;    
    j=0;
    while (n_usados < n_cidades)
    {
        
        if (matriz[i][j] != -1 && j>=0 && n_cidades>j)
        {
            
            
            if (usado[j] == false)
            {
                count++;
                valor++;

                if (valor>=n_cidades)
                {
                    break;
                }

                if (j == final)
                {
                    return true;
                }
                sequencia[valor]=i;
                
                i = j;

                usado[j] = true;
                n_usados++;
                j = -1;
            }

        }

        else if (matriz[i][j] == -1 && j + 1 >= n_cidades)
        {
            
            valor--;

            if (valor == -1)
            {
                
                break;
            }

            
            i = sequencia[valor+1];
            
            j = -1;
        }

        j++;
        
        //cout<<j<<endl;

        if (count == n_caminhos||j>=n_caminhos)
        {
            break;
        }
    }
    delete(sequencia);
    delete(usado);

    return false;
}







void EncontraMaiorCaminho(int **matriz, int inicial, int final, int n_cidades, int n_caminhos)
{
    int i=0, j=0, minimo = 0;
    int **matrizaux;

    matrizaux = new int *[n_cidades];

    for (i = 0; i < n_cidades; i++)
    {
        matrizaux[i] = new int[n_cidades];
    }

    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            matrizaux[i][j] = matriz[i][j];
        }
    }

    while (EncontraCaminho(matrizaux, inicial, final, n_cidades, n_caminhos))
    {
        minimo = EncontraMin(matrizaux, n_cidades);
        
    }

    delete(matrizaux);
    for (i = 0; i < n_cidades; i++)
    {
        delete(matrizaux[i]);
    }
     delete(matrizaux);
    cout << minimo << endl;
}


void pesquisas(int **matriz,int n_cidades,int caminhos,int consultas)
{
    int count=0;

    tupla vetorconsultas[consultas];

    
    while(count<consultas)
    {
       cin>>vetorconsultas[count].valor1;
       cin>>vetorconsultas[count].valor2;
       count++;
    }

    count=0;
    while(count<consultas)
    {
        
       EncontraMaiorCaminho(matriz,vetorconsultas[count].valor1-1,vetorconsultas[count].valor2-1, n_cidades, caminhos);
       count++;
    }


}
-------------------------------------------------------------------------------------------------------------------------------------------------

void inicializamatriz(int **matriz, int n_cidades)
{
    int i = 0, j = 0;
    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            matriz[i][j] = -1;
        }
    }
}

void preeencheMatriz(int *matriz[], int caminhos)
{
    int i = 0, valor1=0, valor2=0, distancia=0;
    while (i < caminhos)
    {
        cin >> valor1 >> valor2 >> distancia;
        matriz[valor1 - 1][valor2 - 1] = distancia;
        i++;
    }
}


--------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    int i = 0; 
    int n_cidades, caminhos, consultas;

    cin >> n_cidades >> caminhos >> consultas;
  
    int **matriz;

    matriz = new int *[n_cidades];

    for (i = 0; i < n_cidades; i++)
    {
        matriz[i] = new int[n_cidades];
    }

    inicializamatriz(matriz, n_cidades);

    preeencheMatriz(matriz, caminhos);

    pesquisas(matriz,n_cidades,caminhos,consultas);

}