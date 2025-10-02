#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void oct_to_bin(const char*,char*);
void oct_to_hex(const char*,char*);
void hex_to_bin(const char*,char*);
void to_sign_magnitude(int32_t,char*);
void to_ones_complement(int32_t,char*);
void to_twos_complement(int32_t,char*);

typedef struct{char function_name[50];char input1[100];char expected[200];}TestCase;

int run_test(const TestCase*t){
    char actual[300]={0};
    if(strcmp(t->function_name,"oct_to_bin")==0)oct_to_bin(t->input1,actual);
    else if(strcmp(t->function_name,"oct_to_hex")==0)oct_to_hex(t->input1,actual);
    else if(strcmp(t->function_name,"hex_to_bin")==0)hex_to_bin(t->input1,actual);
    else if(strcmp(t->function_name,"to_sign_magnitude")==0){int32_t n=atoi(t->input1);to_sign_magnitude(n,actual);}
    else if(strcmp(t->function_name,"to_ones_complement")==0){int32_t n=atoi(t->input1);to_ones_complement(n,actual);}
    else if(strcmp(t->function_name,"to_twos_complement")==0){int32_t n=atoi(t->input1);to_twos_complement(n,actual);}
    else{printf("Unknown function: %s\n",t->function_name);return 0;}
    int pass=strcmp(actual,t->expected)==0;
    printf("%s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
        t->function_name,t->input1,t->expected,actual,pass?"PASS":"FAIL");
    return pass;
}

int main(){
    FILE*f=fopen("a2_test.txt","r");
    if(!f){perror("Cannot open a2_test.txt");return 1;}
    char line[512];int total=0,passed=0;
    while(fgets(line,sizeof(line),f)){
        if(line[0]=='#'||strlen(line)<=1)continue;
        TestCase t;memset(&t,0,sizeof t);
        char*fn=strtok(line," 	\n");
        if(!fn)continue;
        strcpy(t.function_name,fn);
        char*in1=strtok(NULL," 	\n");
        char*exp=strtok(NULL," 	\n");
        if(!in1||!exp)continue;
        strcpy(t.input1,in1);
        strcpy(t.expected,exp);
        total++;if(run_test(&t))passed++;
    }
    fclose(f);
    printf("Summary: %d/%d tests passed\n",passed,total);
    return 0;
}
