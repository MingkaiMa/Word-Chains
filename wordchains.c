#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "WGraph.h"

#define TRUE 1
#define FALSE 0
#define WORD_NUMBER 1000
#define CHAR_NUMBER 19
#define INF 10000


int isOneDiffer(char *a, char *b){
  int length_word1 = strlen(a);
  int length_word2 = strlen(b);
  
  if(abs(length_word1 - length_word2) > 1)
    return FALSE;

  int counter = 0;
  int i = 0;
  int j = 0;

  while(i < length_word1 && j < length_word2){

    if(a[i] != b[j]){
      if(counter == 1){
	return FALSE;
      }

      if(length_word1 > length_word2){
	i = i + 1;
      }else if(length_word1 < length_word2){
	j = j + 1;
      }else {
	i = i + 1;
	j = j + 1;
      }

      counter = counter + 1;

    } else {
      i = i + 1;
      j = j + 1;
    }

  }

  if(i < length_word1 || j < length_word2){
    counter++;
  }
  return (counter == 1);
}



void longest_path(int nV, int **matrix, char **word_list){

  int D_Matrix[nV][nV];
  int P_Matrix[nV][nV];
  int chain_nb = 0;
  //int S_Matrix[nV][nV];
  

  for(int nb = 0; nb < nV; nb++){

    int start_node = nb;
    
    int D[nV];
    //D = malloc(sizeof(int) * nV);
    int P[nV];
    int S[nV];
    int k = nV;
  
    for(int i = 0; i < nV; i++){
      D[i] = INF;
      P[i] = -1;
      S[i] = 0;
    }
 
    for(int i = 0; i < nV; i++){
      D[i] = matrix[start_node][i];
      if(D[i] != INF)
	P[i] = start_node;
    }
    
    S[start_node] = 1;
    
    for(int i = 0; i < nV; i++){
      
      int min_value = INF;
      for(int j = 0; j < nV; j++){
	if(!S[j] && D[j] < min_value){
	  min_value = D[j];
	  k = j;
	}
      }
      
      if(k == nV){
	break;
      }
      
      S[k] = 1;
      
      for(int j = 0; j < nV; j++){
	
	if(!S[j] && D[j] > D[k] + matrix[k][j]){
	  
	  D[j] = D[k] + matrix[k][j];
	  P[j] = k;
	}
	
      }
    
    }

    for(int i = 0; i < nV; i++){
      if(chain_nb > D[i])
	chain_nb = D[i];
      
      D_Matrix[nb][i] = D[i];
      P_Matrix[nb][i] = P[i];
    }
   
  }

  printf("\nMaximum chain length: %d\n", (abs(chain_nb) + 1));

  
  int search[abs(chain_nb) + 1];


  printf("Maximal chains: \n");
  for(int i = 0; i < nV; i++){
    for(int j = 0; j < nV; j++){
      if(D_Matrix[i][j] == chain_nb){
	search[0] = j;
	int m = j;
	for(int k = 1; k < (abs(chain_nb) + 1); k++){
	  search[k] = P_Matrix[i][m];
	  m = P_Matrix[i][m];
	}

	for(int k = abs(chain_nb); k >= 0; k--){
	  printf("%s ", word_list[search[k]]);
	  if(k != 0)
	    printf("-> ");
	}
	printf("\n");
      }
    }
  }
   
}


int main(){
  
  printf("Enter a number: ");
  int nV;
  scanf("%d", &nV);

  Graph g = newGraph(nV);
  //char word_list[nV][19];

  char **word_list = malloc(sizeof(char *) * nV);
  assert(word_list != NULL);
  for(int i = 0; i < nV; i++){
    word_list[i] = calloc(19, sizeof(char));
    assert(word_list[i] != NULL);
  }
  for(int i = 0; i < nV; i++){
    printf("Enter word: ");
    scanf("%s", word_list[i]);      
  }


  //  isOneDiffer("cast", "cat");

  
  for(int i = 0; i < nV; i++){
    for(int j = i; j < nV; j++){
      if(i == j) {
	Edge e;
	e.v = i;
	e.w = j;
	e.weight = 0;
	insertEdge(g, e);
      }else if(isOneDiffer(word_list[i], word_list[j])){
	Edge e;
	e.v = i;
	e.w = j;
	e.weight = -1;
	insertEdge(g, e);
      } else {
	Edge e;
	e.v = i;
	e.w = j;
	e.weight = INF;
	insertEdge(g, e);
      }

    }
    
    }

  printf("\n");
  
  int **Matrix = getMatrix(g);
  for(int i = 0; i < nV; i++){
    printf("%s: ", word_list[i]);
    for(int j = 0; j < nV; j++){
      if(Matrix[i][j] == -1){
	printf("%s ", word_list[j]);
      }
    }
    printf("\n");
  }


  longest_path(nV, Matrix, word_list);

  

  //free word_list

  for(int i = 0; i < nV; i++)
      free(word_list[i]);
  free(word_list);

  //free graph
  freeGraph(g);
  
}
