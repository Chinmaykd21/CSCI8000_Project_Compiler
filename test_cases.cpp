//below I have created several tests to determine if the proper syntax is followed
//during excecution, there are no errors, meaning that the incorrect syntax is accepted and not flagged/corrected


int print(int in, int fake, int bl, char *msg){
 if (in < 0){
 strcpy(msg bl, “The sum; it is below zero!”);
 } 
 if (in == 0 {  //the conditional statment lacks a ")" that indicates the end of the statement
 strcpy(msg, “The sum; it is zero!”);
 } 
 else if (in < 0)       //there are no "{}" to form the if else statement 
 strcpy(msg, “The sum; it is below zero!”);
 
 else if (in < 10)        //there is no "{" after the conditional statement to indicate the beginning of the else if statement
 strcpy(msg, “The sum is a single digit numeric.”); 
 } 
 else if in > 10  {       //there are no "()" enclosing the conditional statement
 strcpy(msg, “You now have two digits.”);
 } 
 else {
 strcpy(msg fake, “The sum is large.”); //there are two variables with no seperation
 }
 return 0;
}
int main(){
 int a, b, c ;
 char e[100];
 scanf(“%d%d%f”, &a, &b, &c);
 int d = a + b + c;
 return print(d, e fake ); //there are two variables with no seperation of ,’, ‘=’, ‘+’, ‘-’, ‘*’, ‘/’, ‘(’, and ‘)’ 
}






