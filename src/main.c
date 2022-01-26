#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>

#define ROWS 200
#define COLS 200
#define WORDBANK 200
FILE* filestream;
char puzzle[ROWS][COLS];
int puzzleAnswers[ROWS][COLS];
char words[WORDBANK][ROWS];
char fileName[25];
char buf;
int sumKata, lengthKata;
int row = 0;
int col = 0;
int prevCol = 0;
int i, j, k, l, m, n, o;
int compared = 0;

void proccessFile(){
    char dir[30] = {'.', '.', '/', 't', 'e','s','t','/'};
	printf("Input File Name: ");
    gets(fileName);

    strcat(dir, fileName);
	filestream = fopen(dir, "r");
	if (filestream == NULL) {
		printf("File open error \n");
	}else{
        while(!feof(filestream)) {
            buf = fgetc(filestream); 
            
            if (buf == '\n'){
                if(col == 0){
                    break;
                }else{
                    row++;
                    prevCol = col;
                    col = 0;
                }
            }
            else if(isalnum(buf)) {
                puzzle[col][row] = toupper(buf);
                puzzleAnswers[col][row] = 9;
                col++;
            }
        }

        sumKata = 0;
        lengthKata = 0;
        while(!feof(filestream)) {
            buf = fgetc(filestream); 
            if(buf == '\n'){
                words[sumKata][lengthKata] = '.';
                sumKata = sumKata + 1;
                lengthKata = 0;
            }else if(isalnum(buf)){
                words[sumKata][lengthKata] = toupper(buf);
                lengthKata++;
            }
        }
        words[sumKata][lengthKata] = '.';
        sumKata ++;
        printf("\n---P U Z Z L E  A N S W E R---\n\n");
    }
}

int findWord(int rowKata, int baris, int kolom, int a, int b){
    int found = 0;
    int colorCode;
    m = 0;
    n = baris; o = kolom;
    while((words[rowKata][m] != '.') && found == 0){
        if(words[rowKata][m] == puzzle[o][n]){
            compared=compared+1;
            n = n + a;
            o = o + b;
            m = m + 1;
        }else{
            compared=compared+1;
            found = 1;
            break;
        }
    }
    m = 0;
    n = baris; o = kolom;
    if(found == 0){
        while((words[rowKata][m] != '.')){
            colorCode = rowKata % 6;
            puzzleAnswers[o][n] = colorCode;
            n = n + a;
            o = o + b;
            m = m + 1;
        }
    }
    return found;
}

void printf_COLOR(const char *s, int code){
    if(code == 0){
        printf("\033[0m\033[1;31m%s\033[0m", s);
    }else if(code == 1){
        printf("\033[0m\033[1;32m%s\033[0m", s);
    }else if(code == 2){
        printf("\033[0m\033[1;33m%s\033[0m", s);
    }else if(code == 3){
        printf("\033[0m\033[1;34m%s\033[0m", s);
    }else if(code == 4){
        printf("\033[0m\033[1;35m%s\033[0m", s);
    }else if(code == 5){
        printf("\033[0m\033[1;36m%s\033[0m", s);
    }
}

void printResult(){
    int colorCode;
    m = 0;
    n = 0;
    for(m=0; m < row; m++){
        for(n=0; n < prevCol; n++){
            if(puzzleAnswers[n][m] != 9){
                if(n == 0 && m != 0){
                    printf("\n");
                    buf = puzzle[n][m];
                    colorCode = puzzleAnswers[n][m] % 6;
                    printf_COLOR(&buf, colorCode); printf(" ");
                }else{
                    buf = puzzle[n][m];
                    colorCode = puzzleAnswers[n][m] % 6;
                    printf_COLOR(&buf, colorCode); printf(" ");
                }   
            }else{
                if(n == 0){
                    printf("\n");
                    printf("%c", puzzle[n][m]); printf(" ");
                }else{
                    printf("%c", puzzle[n][m]); printf(" ");
                }
            }
        }
    }
}

int main() {
    int found;
    struct timeval start, end;

    proccessFile(); 
    gettimeofday(&start, NULL);

    for(i=0; i < sumKata; i++){
        found = 0;
        k = 0;
        while(k < row && found == 0){
            j = 0; 
            while(j < prevCol && found == 0){
                if(words[i][0] == puzzle[j][k]){
                    if(findWord(i,k,j,0,1) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,0,-1) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,-1,0) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,1,0) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,-1,1) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,-1,-1) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,1,1) == 0){
                        found = 1;
                    }else if(findWord(i,k,j,1,-1) == 0){
                        found = 1;
                    }
                }else{
                    compared++;
                }
                j++;
            }
            k++;
        }
    }

    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    printResult();
    printf("\n\n**The execution time is %d seconds and %d microseconds\n", seconds, micros);
    printf("**Terdapat %d kali perbandingan", compared);
   
    return 0;
}