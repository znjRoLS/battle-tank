/**
 *  @file highscores.c
 *  @brief - Implementacije funkcija za rad sa listom najboljih rezultata.
 */
 #include "global.h"

void clear_high_scores ( int difficulty )
{
    int i;
    char temp[42];
    FILE * f;
    strcpy(temp, "high_scores");
    switch ( difficulty )
    {
    case 0:
        strcat(temp, "_easy.txt");
        break;
    case 1:
        strcat(temp, "_medium.txt");
        break;
    case 2:
        strcat(temp, "_hard.txt");
        break;
    }
    f = fopen ( temp, "w" );
    for ( i = 0; i < 20; i++ ) fprintf ( f, "0 jovanaETF\n" );
    fclose ( f );
    encrypt ( difficulty );
}

void check_high_scores ( void )
{
    check ( 0 );
    check ( 1 );
    check ( 2 );
}

void update_high_scores (char name[20], int score, int difficulty)
{
     check_high_scores ( );
     int i,n,j;
     char names[21][20], t[20];
     char temp[42];
     strcpy(temp, "high_scores");
     switch ( difficulty )
     {
     case 0:
         strcat(temp, "_easy.txt");
         break;
     case 1:
         strcat(temp, "_medium.txt");
         break;
     case 2:
         strcat(temp, "_hard.txt");
         break;
     }
     int scores[21];
     FILE *high_scores;
     high_scores = fopen(temp, "r");
     if ( high_scores == NULL )
     {
        clear_high_scores ( difficulty );
        high_scores = fopen ( temp, "r" );
     }
     n=0;
     while (fscanf(high_scores,"%d",&scores[n])!=EOF)
     {
         fscanf(high_scores," %s", names[n]);
         n++;
     }
     fclose (high_scores);
     scores[n]=score;
     strcpy(names[n],name);
     i=n;
     while ((i>0)&&(scores[i]>scores[i-1]))
     {
        strcpy(t,names[i]);
        strcpy(names[i],names[i-1]);
        strcpy(names[i-1],t);
        j=scores[i];
        scores[i]=scores[i-1];
        scores[i-1]=j;
        i--;
     }
     while ((i>0)&&(scores[i]==scores[i-1])&&(strcmp(names[i],names[i-1])<0))
     {
        strcpy(t,names[i]);
        strcpy(names[i],names[i-1]);
        strcpy(names[i-1],t);
        j=scores[i];
        scores[i]=scores[i-1];
        scores[i-1]=j;
        i--;
     }
     if (n<20) n++;
     i=0;
     high_scores = fopen(temp, "w");
     while (i<n)
     {
         fprintf(high_scores, "%d %s\n", scores[i], names[i]);
         i++;
     }
     fclose (high_scores);
     encrypt ( difficulty );
}
