#include <stdio.h>

extern "C"{
struct string_type{
    long length;
    char* str;
} ;


int 输出(char* a){
   return printf("%s",a) ;
}

int 输出整数(int a){
    return printf("%d\n",a);
}

}