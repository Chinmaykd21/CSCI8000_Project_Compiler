int print(int   in, char *msg){
 if (in < 0){
 strcpy(msg, “The sum is below zero!”);
 } else if (in < 10){
 strcpy(msg, “The sum is a single digit numeric.”);
 } else {
 strcpy(msg, “The sum is large.”);
 }
 return 0;
}
int main(){
 int a, b, c;
 char e[100];
 scanf(“%d%d%f”, &a, &b, &c);
 int d = a + b + c;
 return print(d, e);
}

