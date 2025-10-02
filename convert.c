#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

void oct_to_bin(const char *oct, char *out) {
    out[0] = '\0';
    for (int i = 0; oct[i]; i++) {
        int d = oct[i] - '0';
        char bits[4];
        bits[0] = ((d >> 2) & 1) + '0';
        bits[1] = ((d >> 1) & 1) + '0';
        bits[2] = (d & 1) + '0';
        bits[3] = '\0';
        strcat(out, bits);
    }
}

void oct_to_hex(const char *oct, char *out) {
    char bin[512] = {0};
    oct_to_bin(oct, bin);
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[520] = {0};
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded+pad, bin);
    int plen = strlen(padded);
    out[0] = '\0';
    for (int i=0;i<plen;i+=4){
        int val=0;
        for(int j=0;j<4;j++) val = (val<<1) | (padded[i+j]-'0');
        char digit = val<10 ? '0'+val : 'A'+(val-10);
        strncat(out, &digit, 1);
    }
    char *p = out;
    while (*p=='0' && *(p+1)!='\0') p++;
    if (p!=out) memmove(out,p,strlen(p)+1);
}

void hex_to_bin(const char *hex, char *out) {
    out[0]='\0';
    for(int i=0;hex[i];i++){
        char c=toupper((unsigned char)hex[i]);
        int v;
        if(c>='0'&&c<='9') v=c-'0';
        else if(c>='A'&&c<='F') v=10+(c-'A');
        else continue;
        char bits[5];
        for(int b=3;b>=0;b--) bits[3-b]=((v>>b)&1)+'0';
        bits[4]='\0';
        strcat(out,bits);
    }
}

static void to_binary32(uint32_t val,char*out){
    for(int i=31;i>=0;i--) *out++=((val>>i)&1)?'1':'0';
    *out='\0';
}

void to_sign_magnitude(int32_t n,char*out){
    if(n>=0){to_binary32((uint32_t)n,out);}
    else{
        uint32_t mag=(uint32_t)(-n);
        to_binary32(mag,out);
        out[0]='1';
    }
}

void to_ones_complement(int32_t n,char*out){
    if(n>=0){to_binary32((uint32_t)n,out);}
    else{
        uint32_t mag=(uint32_t)(-n);
        to_binary32(mag,out);
        for(int i=0;i<32;i++) out[i]=out[i]=='0'?'1':'0';
    }
}

void to_twos_complement(int32_t n,char*out){
    to_binary32((uint32_t)n,out);
}
