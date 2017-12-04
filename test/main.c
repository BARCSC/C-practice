#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SSIZE 500
typedef int elemtype;
typedef struct _stack {
elemtype element[SSIZE];
int top;
}stack;
char ch[] = "+-*/()#"; //�±꼴���������ġ���Ӧ�����֡�
int f1[] = {3, 3, 5, 5, 1, 6, 0};//ջ��Ԫ�����ȼ�
int f2[] = {2, 2, 4, 4, 6, 1, 0};//ջ��Ԫ�����ȼ�
void initstack(stack* s) //��ʼ����ջ
{
s->top = -1;
}
int isempty(stack* s) //�пղ���
{
if(s->top < 0) return 1;
return 0;
}
int push(stack* s, elemtype value) {//��ջ����,�ɹ�����1,����0
if(s->top >= SSIZE - 1) return 0;
s->element[++s->top] = value;
return 1;
}
elemtype gettop(stack* s) {//ȡջ��Ԫ��
return s->element[s->top];
}
elemtype pop(stack* s) {//��ջ����,���س�ջԪ��
return s->element[s->top--];
}
elemtype cton(char c) {//�������ת��Ϊ����ch�е��±�
switch(c) {
case '+': return 0;
case '-': return 1;
case '*': return 2;
case '/': return 3;
case '(': return 4;
case ')': return 5;
default: return 6;
}
}
char compare(char c1, char c2) //�Ƚ���������������ȼ�,
{ //����ʹ��switch���
int i1 = cton(c1);
int i2 = cton(c2);
if(f1[i1] > f2[i2]) return '>';
else if(f1[i1] < f2[i2]) return '<';
else return '=';
}
int operate(elemtype a, elemtype t, elemtype b) //������������,
{ //������������
int sum;
switch(t) {
case 0: sum = a + b; break;
case 1: sum = a - b; break;
case 2: sum = a * b; break;
default:sum = a / b;
}
return sum;
}
int evaluate(char *d) {//ͨ������ǰ��ĺ���,����������ʽ������
char c;
int i = 0, sum = 0,j=-1;
elemtype x, t, a, b;
stack optr, opnd;
initstack(&optr);
push(&optr, cton('#'));
initstack(&opnd);
c=d[++j];
while((c != '#') || (ch[gettop(&optr)] != '#')) {
if(isdigit(c)) {
sum = 0;
while(isdigit(c)) {
sum = sum * 10 + (c - '0');
c =d[++j];
}
push(&opnd, sum);
}
else {
switch(compare(ch[gettop(&optr)], c)) {
case '<': push(&optr, cton(c)); //ջ����������ȼ�
c = d[++j];
break;
case '=': x = pop(&optr); //ջ�к�ջ�����������ȼ�һ����
c = d[++j];
break;
case '>': t = pop(&optr); //ջ�ڵ���������ȼ���,��ʼ����
b = pop(&opnd);
a = pop(&opnd);
push(&opnd, operate(a, t, b));
break;
}
}
}
return (gettop(&opnd));
}
int main() {
    char m,d[SSIZE];
    int k=0;
    printf("�������������ʽ(��#����):");
    while(m!='#')
    {
        k++;
        m=getchar();
        if(m==' ') m=getchar();
        if(m=='\n') m='#';
        d[k]=m;
    }
int result = evaluate(d);
printf("������Ϊ: %d", result);
return 0;
}
