#include "tools.h"
#include <stdlib.h>
static int reverse(int num);
char* itc(int num){
	if(num < 0){
		exit(EXIT_FAILURE);
	}
	if(num == 0){
		return "0";
	}
	num = reverse(num);
	char* str = (char*)malloc(sizeof(char)*32);
	int i = 0;
	while(num){
		str[i++] = num%10 + '0';
		num/=10;
	}
	return str;
}
static int reverse(int num){
	int temp = 0;
	while(num){
		temp+=temp*10+num%10;
		num/=10;
	}
	return temp;
}
