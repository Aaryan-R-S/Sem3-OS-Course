#include<stdio.h>

int main(int argc, char* argv[]){
    FILE *ptr1, *ptr2;

    char buffer[1000000];
    int a, b;

    if(argc!=3){
        printf("[INVALID ARGUMENTS] Enter the arguments in the following form: ./main srcFilePath destFilePath\n");
        return 1;
    }

    ptr1 = fopen(argv[1], "rb");

    if(ptr1!=NULL){
        ptr2 = fopen(argv[2], "wb");
        if(ptr2!=NULL){
            while(feof(ptr1)==0){
                if((a = fread(buffer,1,100,ptr1)) != 100){
                    if(ferror(ptr1)!=0){
                        printf("Error while reading the file!\n");
                        return 1;
                    }
                }
                if((b = fwrite(buffer,1,a,ptr2)) != a){
                    printf("Error while writing the file!\n");
                    return 1;
                }
            }
            printf("Done copying!\n");
            fclose(ptr1);
            fclose(ptr2);
        }
        else{
            printf("[ERROR] Cannot open file %s \n", argv[2]);
            fclose(ptr1);
            return 1;
        }
    }
    else{
        printf("[ERROR] Cannot open file %s \n", argv[1]);
        return 1;
    }
    
    return 0;
}