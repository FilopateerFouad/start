#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FLUSH fflush(stdin)
#include <windows.h>
struct leaderboard{                                 //structure of each player//
    char name[50];
    float diff;
    char win;
    int number_ofmoves;
    int point;
};
    FILE *play;
    struct leaderboard A[50],temp;
void difficulty( void );
void beginner( void );
void intermediate( void );
void expert( void );
void minefield_generator( void );
void print_minefield( void );
void guess( void );
void boom( void );
void print_final_minefield( void );
void win( void );
void play_again( void );
void game_over( void );
int cnt;
int x, y;                                                     //user's coordinate inputs
int M, N;                                                    //m=col  , n=rows//
int total_mines = 0;
int mines = 0;
int minefield[30][30];                                      //2d array of operations of the game
int blank_minefield[30][30];                                //2d array that will be printed while playing
int final_minefield[30][30];                                //2d array that will be printed if you lose
int easy,medium,hard;                                          //counter for the levels

void  main()
{   play=fopen("score.txt","a");
    system("COLOR 74");
    printf("\t\tWelcome to Minesweeper\n");
    printf("\t\tPlease enter your name\n");
    scanf("%s",A[cnt].name);                                    //name of player//
    fprintf(play,"%s\t",A[cnt].name);
    difficulty();
}

void difficulty( void )                                     //Function for choosing the difficulty level//
{    play=fopen("score.txt","a");
    A[cnt].diff=0;
    while( ( A[cnt].diff != 1) && ( A[cnt].diff != 2) && ( A[cnt].diff != 3) && ( A[cnt].diff != 4))
    {
        printf("\t\tChoose a difficulty level(1-3) or 4 for a custom game:");
        scanf("%f", & A[cnt].diff);
         fprintf(play,"%.1f\t",A[cnt].diff);
        FLUSH;
        if( ( A[cnt].diff != 1) && ( A[cnt].diff != 2) && ( A[cnt].diff != 3) && ( A[cnt].diff != 4))         //wrong number of difficulty//
        {
            printf("\t\tPlease enter either 1, 2, 3 or 4\n");
        }
    }

    if(A[cnt].diff == 1 )
    {   easy++;
        beginner();
    }
    else if(A[cnt].diff == 2 )
    {   medium++;
        intermediate();
    }
    else if(A[cnt].diff == 3 )
    {   hard++;
        expert();
    }
    else if(A[cnt].diff == 4)
    {
        custom();
    }
}

void beginner( void )                                       //Gives the minefield the 'beginner' grid and mines
{
    M = 5;
    N = 5;
    total_mines = 7;
    minefield_generator();
    guess();
}

void intermediate( void )                                   //Gives the minefield the 'intermediate' grid and mines
{
    M = 9;
    N = 10;
    total_mines = 20;
    minefield_generator();
    guess();
}

void expert( void )                                         //Gives the minefield the 'expert' grid size and mines
{
    M = 10;
    N = 20;
    total_mines = 35;
    minefield_generator();
    guess();
}

void custom( void )
{
    M = 0;
    N = 0;
    total_mines = 0;
    printf("\t\tPlease enter the size of the dimensions you want\n");
    printf("\t\tFirst value:\n");
    scanf("%d", &M);
    printf("\t\tSecond value:\n");
    scanf("%d", &N);
    printf("\t\tNumber of mines you want to assign to the board:\n");
    scanf("%d", &total_mines);
    minefield_generator();
    guess();
}
void minefield_generator( void )                            //Function that generates the minefield
{
   srand( time( NULL ) );                                     //Starts the random no. generator
    int i = 0, j = 0;
    while( j < N )                                          //Nested loop for making the blank minefield and final minefield
    {
        while( i < M)
        {
            minefield[i][j] = '-';
            blank_minefield[i][j] = minefield[i][j];
            final_minefield[i][j] = minefield[i][j];
            i++;
        }
        i = 0;
        j++;
    }
    mines = 0;
    while( mines < total_mines )                            //Randomly generates the mines into the minefield
    {
        i = rand()%(M);
        j = rand()%(N);
        if( minefield[i][j] != '*')                         //If statement that checks if there is a mine already there and doesn't place a mine if there is
        {
            minefield[i][j] = '*';
            final_minefield[i][j] = minefield[i][j];
            mines++;
        }
    }
    i = 0;
    j = 0;

    while( j < N )                                          //While loop that generates the numbers for any adjacent mines
    {
        while( i < M)
        {
            if( minefield[i][j] != '*')
            {
                minefield[i][j] = 0;                             //blank number//
            }
            if((minefield[i-1][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i-1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i-1][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    i = 0;
    j = 0;
}
void print_minefield(void)                                  // This function prints the minefield
{
    int i = 0, j = 0, z = 0;
    while( z < M )                                          // This while loop prints out the line of co-ordinates along the x axis of the minefield
    {
        if( z == 0 )
        {
            printf("    ");
            printf("| %d | ", z);
            z++;
            continue;
        }
        printf("%d | ", z);
        z++;
    }
    printf("\n\n");

    while( j < N )                                          // Loop that prints out each character in the minefield
    {
        printf("| %d | ", j);
        while( i < M)
        {
            if( blank_minefield[i][j] == '-')
            {
                printf("%c ", blank_minefield[i][j]);
          }
            else if( minefield[i][j] == 0 )                 // This changes any spaces with values of zero to the character 'B'
            {
                blank_minefield[i][j] = 'B';
                printf("%c ", blank_minefield[i][j]);
            }
            else
            {
                printf("%d ", blank_minefield[i][j]);

            }
            i++;
            printf("| ");
        }
        printf("\n");
        i = 0;
        j++;
        for(int i=0;i<M;i++)
            printf("_____");
        printf("\n");
    }
}


void guess( void )
{
    print_minefield();
    int q = 0, i=0, j=0, match=0;
    while( j < N )                                          // While loop for testing whether or not the user has cleared the minefield
    {
        while( i < M )
        {
            if(minefield[i][j] == blank_minefield[i][j])
            {
                match++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    if( match == (( M * N ) - total_mines))                 // If the user has cleared the minefield, the win() function is run
    {   A[cnt].number_ofmoves++;
        win();
    }
    printf("\nEnter the x value, then a space, then the y value:");
    scanf("%d %d", &x, &y);                                 // Reading in the co-ordinates for the guess
    FLUSH;
    if( (x >= M) || (x < 0) || (y < 0) || (y >= N) )
    {
        printf("\nPlease enter a value inside the grid\n");
        guess();
    }
    if( minefield[x][y] == '*' )                            // Runs the boom() function if the user selects a mine
    {   A[cnt].number_ofmoves++;
        boom();
    }
    if( blank_minefield[x][y] != '-' )
    {
        printf("\nPlease enter a value that has not already been entered\n");
        guess();
    }
    else                                                // Checks if the adjacent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
    {
        blank_minefield[x][y] = minefield[x][y];
        if( minefield[x][y] == 0 )
        {
            if( minefield[x-1][y-1] == 0 )
            {
                blank_minefield[x-1][y] = minefield[x-1][y];
            }
            if( minefield[x-1][y] == 0 )
            {
                blank_minefield[x-1][y] = minefield[x-1][y];
            }
            if( minefield[x][y-1] == 0 )
            {
                blank_minefield[x][y-1] = minefield[x][y-1];
            }
            if( minefield[x-1][y+1] == 0 )
            {
                blank_minefield[x-1][y+1] = minefield[x-1][y+1];
            }
            if( minefield[x+1][y-1] == 0 )
            {
                blank_minefield[x+1][y-1] = minefield[x+1][y-1];
            }
            if( minefield[x+1][y] == 0 )
            {
                blank_minefield[x+1][y] = minefield[x+1][y];
            }
            if( minefield[x][y+1] == 0 )
            {
                blank_minefield[x][y+1] = minefield[x][y+1];
            }
            if( minefield[x+1][y+1] == 0 )
            {
                blank_minefield[x+1][y+1] = minefield[x+1][y+1];
            }
        }
        A[cnt].number_ofmoves++;
        guess();
    }
}
void boom( void )                                       // Runs the print_final_minefield function, then the play_again function
{  PlaySound(TEXT("BOOM.wav"),NULL,SND_SYNC);
    print_final_minefield();
    A[cnt].win='L';
    printf("\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
    play=fopen("score.txt","a");
    fprintf(play,"%d\t%c\n",A[cnt].number_ofmoves,A[cnt].win);
    calculator();
    play_again();
}

void print_final_minefield( void )                      // Prints the minefield, showing where all of the mines are placed
{
     int i = 0, j = 0, z = 0;
    while( z < M )                                          // This while loop prints out the line of co-ordinates along the x axis of the minefield
    {
        if( z == 0 )
        {
            printf("    ");
            printf("| %d | ", z);
            z++;
            continue;
        }
        printf("%d | ", z);
        z++;
    }
    printf("\n\n");

    while( j < N )                                          // Loop that prints out each character in the minefield
    {
        printf("| %d | ", j);
        while( i < M)
        {
                printf("%c ", final_minefield[i][j]);
          i++;
        printf("| ");
        }
        printf("\n");
        i = 0;
        j++;
        for(int i=0;i<M;i++)
            printf("_____");
        printf("\n");
    }
}
void win( void )                                        // Runs the play_again function
{
    printf("\n\n\n\t\t\tYOU WIN!!!!!\n\n\n");
     PlaySound(TEXT("winner.wav"),NULL,SND_SYNC);
    A[cnt].win='W';
     play=fopen("score.txt","a");
    fprintf(play,"%d\t%c\n",A[cnt].number_ofmoves,A[cnt].win);
    calculator();
    play_again();
}

void play_again( void )                                 // Gives the user the option to play again
{    play=fopen("score.txt","a");
    char option[2];
    printf("\n\t\tIS there any other player(Y/N)?:");
    scanf("%c", &option[0]);
    FLUSH;
    if((option[0] == 'Y') || (option[0] == 'y'))        // Restarts the program from after the welcome message
    {   cnt++;
        printf("\t\tPlease enter your name\n");
        scanf("%s",A[cnt].name);
        fprintf(play,"%s\t",A[cnt].name);
         A[cnt].number_ofmoves=0;
        difficulty();
    }
    else if( (option[0] == 'N') || (option[0] == 'n'))
    {
        game_over();
    }
    else
    {
        printf("Please enter either Y or N");
        play_again();
    }
}
void calculator(){                                                                          //function to calculate each user//
    if(A[cnt].diff==1){
        if(A[cnt].win=='L'){
            A[cnt].point=10+A[cnt].number_ofmoves;
        }
        else{
            A[cnt].point=50+A[cnt].number_ofmoves;
        }
    }
    else if(A[cnt].diff==2){
        if(A[cnt].win=='L'){
            A[cnt].point=20+A[cnt].number_ofmoves;
        }
        else{
            A[cnt].point=60+A[cnt].number_ofmoves;
        }
    }
    else if(A[cnt].diff==3){
          if(A[cnt].win=='L'){
                 A[cnt].point=30+A[cnt].number_ofmoves;
          }
          else{
            A[cnt].point=70+A[cnt].number_ofmoves;
          }
    }
    else if(A[cnt].diff==4){
        if(A[cnt].win=='L'){
                 A[cnt].point=M+N+A[cnt].number_ofmoves;
          }
          else{
            A[cnt].point=40+M+N+A[cnt].number_ofmoves;
          }
    }
}
void levels(void){
        int a=0,b=0,c=0,d=0;                                                                    //print the users according to the levels//
        printf("\t\tEasy Level:\n");
       while(a<cnt+1){
            if(A[a].diff==1){
                printf("\t%s\n",A[a].name);
            }
                a++;
        }
        printf("\t\tMedium Level:\n");
        while(b<cnt+1){
            if(A[b].diff==2){
                printf("\t%s\n",A[b].name);
            }
                b++;
        }
        printf("\t\tHard Level:\n");
        while(c<cnt+1){
            if(A[c].diff==3){
                printf("\t%s\n",A[c].name);
            }
                c++;
        }
        printf("\t\tCustom Level:\n");
         while(d<cnt+1){
            if(A[d].diff==4){
                printf("\t%s\n",A[d].name);
            }
                d++;
        }
}

void board(void){
    for(int i=0;i<cnt;i++){                                                               // sorting struct according to points
     for(int j=0;j<cnt-i;j++){
        if(A[j].point<A[j+1].point){
            temp=A[j];
            A[j]=A[j+1];
            A[j+1]=temp;
        }
    }
}
printf("\t\t\tThe final standings:\n");
for(int i=0;i<cnt+1;i++){
    printf("%s\t\t%d\n",A[i].name,A[i].point);
}
}

void game_over( void )                                  // Ends the program
{   levels();
    board();
    system("COLOR 08");
    PlaySound(TEXT("game over.wav"),NULL,SND_SYNC);
    printf("\n\n\t\tGame Over");
    fclose(play);
    exit(1);
}
