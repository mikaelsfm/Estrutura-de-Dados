#include <stdio.h>

int f(){
    int k, r;
    r = 0;
    for (k = 0; k<5; k++){
        if ((k%3)==1){
            r = r+k;
        }
        else{
            r = r+1;
        }
    }
    return r;
}

int main(){
    int a;
    a = f();
    printf("%d", a);
}