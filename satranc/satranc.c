#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initializeTheBoard(char **, int, int);
void printScreen(char **, int, int);
void play(char **, int *);
int canMove(char **, int, int, int, int, int);
int pawnMove(char **, int, int, int, int, int);
int destinationCheck(char, int);
int isGameOver(char **, int, int);
int bishopMove(char **, int, int, int, int, int);
int rockMove(char **, int, int, int, int, int);
int knightMove(char **, int, int, int, int, int);
int queenMove(char **, int, int, int, int, int);
int kingMove(char **, int, int, int, int, int);
#define HEIGTH 8
#define WIDTH 8

int main()
{
    char **arr;
    int  i = 0, turn = 0, gameOver=0;

    //hafızadan alan al
    arr = malloc(sizeof(char *) * HEIGTH);
    for(; i<HEIGTH; i++)
    {
        arr[i] = malloc(sizeof(char) * WIDTH);
    }
    //tahtaya ilk halini ver
    initializeTheBoard(arr, HEIGTH, WIDTH);


    do
    {
        printScreen(arr, HEIGTH, WIDTH);
        play(arr, &turn);
    }while( (gameOver=isGameOver(arr, HEIGTH, WIDTH)) == 0);

    printf("%d player wins!", gameOver);
    //hafizayi geri bırak
    for(i=0;i<5;i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

//kullanıcıların ikisinin de sah tası mevcut mu
//eger oyleyse return 0
//eger 0. oyuncunun tasi yoksa 1 dondur
//eger 1. oyuncunun tasi yoksa 2 dondur
  int isGameOver(char ** arr, int nRows, int nCols )
// satır ve sütün hepsi kontrol edilsin diye for dögüsünde ilerlettik
//eger kucuk sah tası yoksa return 1 döncek buyuk sah tası yoksa return 2 donecek


{
 for(nRows=0;nRows<8;nRows++){
 for(nCols=0;nCols<8;nCols++){
 if(arr[nRows][nCols]=='S'){
 for(nRows=0;nRows<8;nRows++){
 for(nCols=0;nCols<8;nCols++){
 if(arr[nRows][nCols]=='s'){

    return 0;}}}

    return 1;}


 else if(arr[nRows][nCols]=='s'){
  for(nRows=0;nRows<8;nRows++){
 for(nCols=0;nCols<8;nCols++){
 if(arr[nRows][nCols]=='S'){

  return 0;}}}

  return 2;}

 }}
 return 0;}

//hareket edilecek hedef noktasindaki tas kimin
//eger siranin kendisindeki oyuncunun ise 0
//degilse 1 dondur
int destinationCheck(char destPiece, int turn)
{
    //turn 0 ise
    if ( (destPiece >= 'A' && destPiece <= 'Z') && turn == 0)
    {
        return 0;
    }
    //turn 1 ise
    if ( (destPiece >= 'a' && destPiece <= 'z') && turn == 1)
    {
        return 0;
    }
    return 1;
}
//piyon hareketi. hareket gecerliyse 1 degilse 0 dondurur
int pawnMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
{
    //hareket duz ise ilgili alan bos mu?
    if (eRow == sRow + direction && sCol== eCol)
    {
        if(arr[eRow][eCol] == ' ')
        {
            return 1;
        }
    }
    //hareket capraz ise hedef alan bos olmamalı
    else if (
              eRow == sRow + direction &&
              ( (sCol == eCol+1) || (sCol == eCol-1) )
             )
    {

        if (arr[eRow][eCol] != ' ')
        {
            return 1;
        }
    }
    //buraya ulastıysa yukaridaki returnlere ulasamamistir o yuzden 0 dondur
    return 0;
}int bishopMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
{
    //filin hareketi çaprazdır son haline gelmesi için başlangıç sütünüylr başlangıç satırı 1 er 2 şer  3 er gibi her iki tarafta artırılır.
    //gidicegi adımda önceki yerler bos mu diye kontrol ettik.
    // hem düz çapraz hem de ters çapraz gitmesini sağladık.
    if (   (eRow == sRow + direction+1 && sCol+1== eCol)
        || (eRow == sRow + direction+2 && sCol+2== eCol&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+3 && sCol+3== eCol&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+4 && sCol+4== eCol&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')
        &&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+5 && sCol+5== eCol&&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')
        &&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+6 && sCol+6== eCol&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+7 && sCol+7== eCol&&(arr[sRow+6][sCol+6]== ' ')&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+8 && sCol+8== eCol&&(arr[sRow+7][sCol+7]== ' ')&&(arr[sRow+6][sCol+6]== ' ')&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+1 && sCol-1== eCol)
        || (eRow == sRow + direction+2 && sCol-2== eCol&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+3 && sCol-3== eCol&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+4 && sCol-4== eCol&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+5 && sCol-5== eCol
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+6 && sCol-6== eCol&&(arr[sRow+5][sCol-5]== ' ')&&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')
        &&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+7 && sCol-7== eCol&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+5][sCol-5]== ' ')
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+8 && sCol-8== eCol&&(arr[sRow+7][sCol-7]== ' ')&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+5][sCol-5]== ' ')
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction-1 && sCol+1== eCol)
        || (eRow == sRow + direction-2 && sCol+2== eCol&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-3 && sCol+3== eCol&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-4 && sCol+4== eCol&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-5 && sCol+5== eCol&&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')
        &&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-6 && sCol+6== eCol&&(arr[sRow-5][sCol+5]== ' ')&&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')
        &&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-7 && sCol+7== eCol&&(arr[sRow-6][sCol+6]== ' ')&&(arr[sRow-5][sCol+5]== ' ')&&(arr[sRow-4][sCol+4]== ' ')
        &&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-8 && sCol+8== eCol&&(arr[sRow-7][sCol+7]== ' ')&&(arr[sRow-6][sCol+6]== ' ')&&(arr[sRow-5][sCol+5]== ' ')
        &&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-1 && sCol-1== eCol)
        || (eRow == sRow + direction-2 && sCol-2== eCol&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-3 && sCol-3== eCol&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-4 && sCol-4== eCol&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-5 && sCol-5== eCol &&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')
        &&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-6 && sCol-6== eCol&&(arr[sRow-5][sCol-5]== ' ')&&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')
        &&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-7 && sCol-7== eCol&&(arr[sRow-6][sCol-6]== ' ')&&(arr[sRow-5][sCol-5]== ' ')&&(arr[sRow-4][sCol-4]== ' ')
        &&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-8 && sCol-8== eCol&&(arr[sRow-7][sCol-7]== ' ')&&(arr[sRow-6][sCol-6]== ' ')&&(arr[sRow-5][sCol-5]== ' ')
        &&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' ')))
    {

        return 1;

    }

    return 0;
}
int rockMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
{
    // kalenin hareketi yana dogrudur ya da dikine dogrudur bunu icin sade sütün ya da satırı artıtdık.
    // kalenin gidecegi yerden önceki yerler bos mu diye kontrol ettik.

    if (
        (eRow == sRow + direction+1&& sCol== eCol)
        ||(eRow == sRow + direction+2&& sCol== eCol&&(arr[sRow+1][eCol]== ' '))
        ||(eRow == sRow + direction+3&& sCol== eCol&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+4&& sCol== eCol&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+5&& sCol== eCol&&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')
        &&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+6&& sCol== eCol&&(arr[sRow+5][eCol] == ' ')&&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')
        &&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+7&& sCol== eCol&&(arr[sRow+6][eCol] == ' ')&&(arr[sRow+5][eCol] == ' ')&&(arr[sRow+4][eCol] == ' ')
        &&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+8&& sCol== eCol&&(arr[sRow+7][eCol] == ' ')&&(arr[sRow+6][eCol] == ' ')&&(arr[sRow+5][eCol] == ' ')
        &&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction-1&& sCol== eCol)
        ||(eRow == sRow + direction-2&& sCol== eCol&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-3&& sCol== eCol&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-4&& sCol== eCol&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-5&& sCol== eCol&&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')
        &&(arr[sRow-1][eCol] == ' ') )
        ||(eRow == sRow + direction-6&& sCol== eCol&&(arr[sRow-5][eCol] == ' ')&&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')
        &&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-7&& sCol== eCol&&(arr[sRow-6][eCol] == ' ')&&(arr[sRow-5][eCol] == ' ')&&(arr[sRow-4][eCol] == ' ')
        &&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-8&& sCol== eCol&&(arr[sRow-7][eCol] == ' ')&&(arr[sRow-6][eCol] == ' ')&&(arr[sRow-5][eCol] == ' ')
        &&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction&& sCol+1== eCol)
        ||(eRow == sRow + direction&& sCol+2== eCol&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+3== eCol&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+4== eCol&&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+5== eCol&&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')
        &&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+6== eCol&&(arr[sRow][sCol+5] == ' ')&&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')
        &&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+7== eCol&&(arr[sRow][sCol+6] == ' ')&&(arr[sRow][sCol+5] == ' ')&&(arr[sRow][sCol+4] == ' ')
        &&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+8== eCol&&(arr[sRow][sCol+7] == ' ')&&(arr[sRow][sCol+6] == ' ')&&(arr[sRow][sCol+5] == ' ')
        &&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol-1== eCol)
        ||(eRow == sRow + direction&& sCol-2== eCol&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-3== eCol&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-4== eCol&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')
        &&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-5== eCol&&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')
        &&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-6== eCol&&(arr[sRow][sCol-5] == ' ')&&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')
        &&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-7== eCol&&(arr[sRow][sCol-6] == ' ')&&(arr[sRow][sCol-5] == ' ')&&(arr[sRow][sCol-4] == ' ')
        &&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-8== eCol&&(arr[sRow][sCol-7] == ' ')&&(arr[sRow][sCol-6] == ' ')&&(arr[sRow][sCol-5] == ' ')
        &&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' ')))
        {
            return 1;
        }



    return 0;
}
int knightMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)

// Atın hareketi l seklindedir ya 2 birim yana gidip 1 birim öne gider ya da 2 birim öne 1 birim yana gider.
//gidecegi yerden önceki yerlerin boş olup olmaması önemli degidir.
{if ((eRow == sRow + direction+2&& sCol-1== eCol)||(eRow == sRow + direction+2&& sCol+1== eCol)
     ||(eRow == sRow + direction+1&& sCol+2== eCol)||(eRow == sRow + direction+1&& sCol-2== eCol)
    ||(eRow == sRow + direction-2&& sCol-1== eCol)||(eRow == sRow + direction-2&& sCol+1== eCol)
    ||(eRow == sRow + direction-1&& sCol-2== eCol)||(eRow == sRow + direction-1&& sCol+2== eCol)
    )

        {
            return 1;
        }


    return 0;
}
int queenMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
//vezir kale ve filin birleşimi olan bir taştır
// vezirin gidecegi yerden oncekı yerler hareketini engelliyor mu onu kontrol ettik.
{
    if  (  (eRow == sRow + direction+1 && sCol+1== eCol)
        || (eRow == sRow + direction+2 && sCol+2== eCol&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+3 && sCol+3== eCol&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+4 && sCol+4== eCol&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')
        &&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+5 && sCol+5== eCol&&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')
        &&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+6 && sCol+6== eCol&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+7 && sCol+7== eCol&&(arr[sRow+6][sCol+6]== ' ')&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+8 && sCol+8== eCol&&(arr[sRow+7][sCol+7]== ' ')&&(arr[sRow+6][sCol+6]== ' ')&&(arr[sRow+5][sCol+5]== ' ')
        &&(arr[sRow+4][sCol+4]== ' ')&&(arr[sRow+3][sCol+3]== ' ')&&(arr[sRow+2][sCol+2]== ' ')&&(arr[sRow+1][sCol+1]== ' '))
        || (eRow == sRow + direction+1 && sCol-1== eCol)
        || (eRow == sRow + direction+2 && sCol-2== eCol&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+3 && sCol-3== eCol&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+4 && sCol-4== eCol&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+5 && sCol-5== eCol
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+6 && sCol-6== eCol&&(arr[sRow+5][sCol-5]== ' ')&&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')
        &&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+7 && sCol-7== eCol&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+5][sCol-5]== ' ')
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction+8 && sCol-8== eCol&&(arr[sRow+7][sCol-7]== ' ')&&(arr[sRow+6][sCol-6]== ' ')&&(arr[sRow+5][sCol-5]== ' ')
        &&(arr[sRow+4][sCol-4]== ' ')&&(arr[sRow+3][sCol-3]== ' ')&&(arr[sRow+2][sCol-2]== ' ')&&(arr[sRow+1][sCol-1]== ' '))
        || (eRow == sRow + direction-1 && sCol+1== eCol)
        || (eRow == sRow + direction-2 && sCol+2== eCol&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-3 && sCol+3== eCol&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-4 && sCol+4== eCol&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-5 && sCol+5== eCol&&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')
        &&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-6 && sCol+6== eCol&&(arr[sRow-5][sCol+5]== ' ')&&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')
        &&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-7 && sCol+7== eCol&&(arr[sRow-6][sCol+6]== ' ')&&(arr[sRow-5][sCol+5]== ' ')&&(arr[sRow-4][sCol+4]== ' ')
        &&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-8 && sCol+8== eCol&&(arr[sRow-7][sCol+7]== ' ')&&(arr[sRow-6][sCol+6]== ' ')&&(arr[sRow-5][sCol+5]== ' ')
        &&(arr[sRow-4][sCol+4]== ' ')&&(arr[sRow-3][sCol+3]== ' ')&&(arr[sRow-2][sCol+2]== ' ')&&(arr[sRow-1][sCol+1]== ' '))
        || (eRow == sRow + direction-1 && sCol-1== eCol)
        || (eRow == sRow + direction-2 && sCol-2== eCol&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-3 && sCol-3== eCol&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-4 && sCol-4== eCol&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-5 && sCol-5== eCol &&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')
        &&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-6 && sCol-6== eCol&&(arr[sRow-5][sCol-5]== ' ')&&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')
        &&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-7 && sCol-7== eCol&&(arr[sRow-6][sCol-6]== ' ')&&(arr[sRow-5][sCol-5]== ' ')&&(arr[sRow-4][sCol-4]== ' ')
        &&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        || (eRow == sRow + direction-8 && sCol-8== eCol&&(arr[sRow-7][sCol-7]== ' ')&&(arr[sRow-6][sCol-6]== ' ')&&(arr[sRow-5][sCol-5]== ' ')
        &&(arr[sRow-4][sCol-4]== ' ')&&(arr[sRow-3][sCol-3]== ' ')&&(arr[sRow-2][sCol-2]== ' ')&&(arr[sRow-1][sCol-1]== ' '))
        ||(eRow == sRow + direction+1&& sCol== eCol)
        ||(eRow == sRow + direction+2&& sCol== eCol&&(arr[sRow+1][eCol]== ' '))
        ||(eRow == sRow + direction+3&& sCol== eCol&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+4&& sCol== eCol&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+5&& sCol== eCol&&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')
        &&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+6&& sCol== eCol&&(arr[sRow+5][eCol] == ' ')&&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')
        &&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+7&& sCol== eCol&&(arr[sRow+6][eCol] == ' ')&&(arr[sRow+5][eCol] == ' ')&&(arr[sRow+4][eCol] == ' ')
        &&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction+8&& sCol== eCol&&(arr[sRow+7][eCol] == ' ')&&(arr[sRow+6][eCol] == ' ')&&(arr[sRow+5][eCol] == ' ')
        &&(arr[sRow+4][eCol] == ' ')&&(arr[sRow+3][eCol] == ' ')&&(arr[sRow+2][eCol] == ' ')&&(arr[sRow+1][eCol] == ' '))
        ||(eRow == sRow + direction-1&& sCol== eCol)
        ||(eRow == sRow + direction-2&& sCol== eCol&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-3&& sCol== eCol&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-4&& sCol== eCol&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-5&& sCol== eCol&&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')
        &&(arr[sRow-1][eCol] == ' ') )
        ||(eRow == sRow + direction-6&& sCol== eCol&&(arr[sRow-5][eCol] == ' ')&&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')
        &&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-7&& sCol== eCol&&(arr[sRow-6][eCol] == ' ')&&(arr[sRow-5][eCol] == ' ')&&(arr[sRow-4][eCol] == ' ')
        &&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction-8&& sCol== eCol&&(arr[sRow-7][eCol] == ' ')&&(arr[sRow-6][eCol] == ' ')&&(arr[sRow-5][eCol] == ' ')
        &&(arr[sRow-4][eCol] == ' ')&&(arr[sRow-3][eCol] == ' ')&&(arr[sRow-2][eCol] == ' ')&&(arr[sRow-1][eCol] == ' '))
        ||(eRow == sRow + direction&& sCol+1== eCol)
        ||(eRow == sRow + direction&& sCol+2== eCol&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+3== eCol&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+4== eCol&&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+5== eCol&&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')
        &&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+6== eCol&&(arr[sRow][sCol+5] == ' ')&&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')
        &&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+7== eCol&&(arr[sRow][sCol+6] == ' ')&&(arr[sRow][sCol+5] == ' ')&&(arr[sRow][sCol+4] == ' ')
        &&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol+8== eCol&&(arr[sRow][sCol+7] == ' ')&&(arr[sRow][sCol+6] == ' ')&&(arr[sRow][sCol+5] == ' ')
        &&(arr[sRow][sCol+4] == ' ')&&(arr[sRow][sCol+3] == ' ')&&(arr[sRow][sCol+2] == ' ')&&(arr[sRow][sCol+1] == ' '))
        ||(eRow == sRow + direction&& sCol-1== eCol)
        ||(eRow == sRow + direction&& sCol-2== eCol&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-3== eCol&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-4== eCol&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')
        &&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-5== eCol&&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')
        &&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-6== eCol&&(arr[sRow][sCol-5] == ' ')&&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')
        &&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-7== eCol&&(arr[sRow][sCol-6] == ' ')&&(arr[sRow][sCol-5] == ' ')&&(arr[sRow][sCol-4] == ' ')
        &&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' '))
        ||(eRow == sRow + direction&& sCol-8== eCol&&(arr[sRow][sCol-7] == ' ')&&(arr[sRow][sCol-6] == ' ')&&(arr[sRow][sCol-5] == ' ')
        &&(arr[sRow][sCol-4] == ' ')&&(arr[sRow][sCol-3] == ' ')&&(arr[sRow][sCol-2] == ' ')&&(arr[sRow][sCol-1] == ' ')) )
        {
            return 1;
        }



    return 0;

}
int kingMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
//sah taşı 1 er birim saga sola ileri ve geriye hareket eder ya da 1 birim çapraz gidebilir
{if ( (eRow == sRow + direction+1&& sCol== eCol+1)||(eRow == sRow + direction+1&& sCol== eCol-1)
    ||(eRow == sRow + direction-1&& sCol== eCol+1)||(eRow == sRow + direction-1&& sCol== eCol-1)
    ||(eRow == sRow + direction+1&& sCol+1== eCol)||(eRow == sRow + direction+1&& sCol-1== eCol)
    ||(eRow == sRow + direction-1&& sCol+1== eCol)||(eRow == sRow + direction-1&& sCol-1== eCol))

        {
            return 1;
        }


    //buraya ulastıysa yukaridaki returnlere ulasamamistir o yuzden 0 dondur
    return 0;
}

//tasın cinsine göre her tasi kontrol et fonksiyonlarını yaz
//destinationCheck fonksiyonu yukarıda yazılmıs ve hedef olarak gideceginiz
//noktadaki tasin kimin olduğuna bakar. Eğer sıranın kendindeki oyuncunun tası
//ise 0 dondurur. Değilse 1 dondurur. Boylece hem hareket fonksyionunda
//gelen deger 1 hem de destinationCheck fonksiyonundan donen deger 1 ise
//canMove fonksiyonu 1 dondurur. && ile bu durum kontrol edilebilir
int canMove(char **arr, int turn, int sRow, int sCol, int eRow, int eCol)
{
    char piece = arr[sRow][sCol];

    if (piece == 'P')
        // piyon için ekstaradan ilk hareketinde 2 birim ileri gitmesini sagladık
        // bunu başlagıç yatayını belirleyerek yaptık
    {
       return (pawnMove(arr, sRow, sCol, eRow, eCol, 1) && destinationCheck(arr[eRow][eCol], turn))
       ||(pawnMove(arr, sRow=1, sCol, eRow, eCol, 2) && destinationCheck(arr[eRow=3 ][eCol], turn));
    }
    else if ( piece == 'p')
    {
       return (pawnMove(arr, sRow, sCol, eRow, eCol, -1) && destinationCheck(arr[eRow][eCol], turn))
       ||(pawnMove(arr, sRow=6, sCol, eRow, eCol, -2) && destinationCheck(arr[eRow =4][eCol], turn ));
    }
    //buradan sonrası her tas icin fonksiyon yazacaksınız
    //fil hareketi icin yaz
    // turn u sıfır yaptık cunku terse giderken sıkıntı olmasın diye
    else if (piece == 'F'||piece == 'f')
     {
       return bishopMove(arr, sRow, sCol, eRow, eCol, 0) && destinationCheck(arr[eRow][eCol], turn);
     }

    //at hareketi icin yaz

   else if (piece == 'A'||piece == 'a')
     {
       return knightMove(arr, sRow, sCol, eRow, eCol, 0) && destinationCheck(arr[eRow][eCol], turn);
     }

    //kale icin yaz

     else if (piece == 'K'||piece == 'k' )
    {

    return rockMove(arr, sRow, sCol, eRow, eCol, 0) && destinationCheck(arr[eRow][eCol], turn);

    }

    else  if (piece == 'V'||piece == 'v' )
    {

      return queenMove(arr, sRow, sCol, eRow, eCol, 0) && destinationCheck(arr[eRow][eCol], turn);

    }
     else  if (piece == 'S'||piece == 's' )
    {

      return kingMove(arr, sRow, sCol, eRow, eCol, 0) && destinationCheck(arr[eRow][eCol], turn);

    }

    //vezir icin yaz

    //sah icin yaz

    //yukarıdaki kodlar yazıldığında buraya ulasamaz ama su anki halinde warning almamak icin yazıldı.
    //Tum kodu yazınca silebilirsiniz.
    return 0;

}

void play(char **arr, int *turn)
{
    char *sMove, *eMove;
    int sRow, sCol, eRow, eCol;
    sMove = malloc(sizeof(char) * 3);
    eMove = malloc(sizeof(char) * 3);
    do
    {
        printf("%d. player turn: ", *turn+1);
        scanf("%2s %2s", sMove, eMove);
        fflush(stdin);
        sRow = (int)(sMove[0] - 'A');
        sCol = (int)(sMove[1] - '1');
        eRow = (int)(eMove[0] - 'A');
        eCol = (int)(eMove[1] - '1');
        if(
            (sRow >= 0 && sRow <= 7) &&
            (sCol >= 0 && sCol <= 7) &&
            (eCol >= 0 && eCol <= 7) &&
            (eRow >= 0 && eRow <= 7)
           )
        {
            char piece = arr[sRow][sCol];
            //secilen tas sırası gelen kullanıcının mı
            if (
                 ( *turn == 0 && (piece >= 'A' && piece <= 'Z') )
                  ||
                 ( *turn == 1 && (piece >= 'a' && piece <= 'z') )
               )
            {
                //secilen tas hedef konuma gidebilir mi
                if( canMove(arr, *turn, sRow, sCol, eRow, eCol) == 1 )
                {
                    arr[eRow][eCol] = piece;
                    arr[sRow][sCol] = ' ';
                    *turn = (*turn + 1) % 2;
                    break;
                }
                //eger gidemiyorsa illegal move
                else
                {
                    printf("Illegal move. Try again.\n");
                }

            }
            //secilen tas kullanıcının degil
            else
            {
                printf("It's your opponent's piece\n");
            }
        }
        //istenen konumlar aralıkta girilmemis
        else
        {
            printf("Your move is out of boundary\n");
        }
    }while(1);//dogru hareket yapılana kadar devam eder. Dogru hareket yapıldıysa
              //yukarıdaki break bu while kosulunu kırar ve cıkılır.
}
//dizi iceriklerini ekrana yaz.
//her bir tas bir karenin icine girsin diye
//bir kac duzenleme yapildi
void printScreen(char ** arr, int nRows, int nCols)
{

    //ekranı her seferinde silip tekrar yazmak isterseniz.
    //aşagıdaki komutu aciniz
    system("@cls||clear");

    int i, j;

    printf("%s", " |");
    for(j=0;j<nCols;)
    {
        printf("  %d  |", ++j);
    }

    printf("\n--");

    for(j=0;j<nCols;j++)
    {
        printf("%s", "------");
    }

    printf("\n");

    for(i=0;i<nRows;i++)
    {
        printf("%c|", 'A'+i);

        for(j=0;j<nCols;j++)
        {
            printf("  %c  |", arr[i][j]);
        }

        printf("\n--");

        for(j=0;j<nCols;j++)
        {
            printf("%s", "------");
        }
        printf("\n");
    }
}
void initializeTheBoard(char **arr, int nRows, int nCols)
{
    int i, j;
    for(i=0;i<nRows-2;i++)
    {
        for(j=0;j<nCols;j++)
        {
            if (i == 0)
            {
                if (j == 0 || j==nCols-1)
                {
                    arr[i][j] = 'K';
                }

                else if (j == 1 || j==nCols-2)
                {
                    arr[i][j] = 'A';
                }

                else if (j == 2 || j==nCols-3)
                {
                    arr[i][j] = 'F';
                }
                else if (j == 3 )
                {
                    arr[i][j] = 'V';
                }
                else
                {
                    arr[i][j] = 'S';
                }
            }
            else if (i == 1)
            {
                arr[i][j] = 'P';
            }
            else
            {
                arr[i][j] = ' ';
            }
        }
    }
    //last 2 rows for opponent
    for(i=nRows-2; i<nRows;i++)
    {
        for(j=0;j<nCols;j++)
        {
            //add 32 to lower the opponent's character
            arr[i][j] = arr[nRows-i-1][j] + 32;
        }
    }
}

// ISA COLAKOGLU 160101022
// BATUHAN GORGEL 160101029
// MUHAREM ADEMOGLU 170101034