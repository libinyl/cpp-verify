当结构体或类的大小较小时, pass by reference 会减少执行的指令,但比较有限:

```C++
// pass by value
class A
{
    int v[100] ={1};
    char m[1024]={'m'}; 
};

void callee(A a)// 改为&a即为 pass by reference
{

}

void caller()
{
    A _a;
    callee(_a);
}
```


对应汇编:

```asm
callee(A):
  push rbp
  mov rbp, rsp
  nop
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 1424
  lea rdx, [rbp-1424]
  mov eax, 0
  mov ecx, 178
  mov rdi, rdx
  rep stosq
  mov DWORD PTR [rbp-1424], 1
  mov QWORD PTR [rbp-1024], 109
  mov QWORD PTR [rbp-1016], 0
  lea rdx, [rbp-1008]
  mov eax, 0
  mov ecx, 126
  mov rdi, rdx
  rep stosq
  sub rsp, 1424
  mov rax, rsp
  mov rdi, rax
  lea rax, [rbp-1424]
  mov edx, 178
  mov rsi, rax
  mov rcx, rdx
  rep movsq
  call callee(A)
  add rsp, 1424
  nop
  leave
  ret
```


```
callee(A&):
  push rbp
  mov rbp, rsp
  mov QWORD PTR [rbp-8], rdi
  nop
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 1424
  lea rdx, [rbp-1424]
  mov eax, 0
  mov ecx, 178
  mov rdi, rdx
  rep stosq
  mov DWORD PTR [rbp-1424], 1
  mov QWORD PTR [rbp-1024], 109
  mov QWORD PTR [rbp-1016], 0
  lea rdx, [rbp-1008]
  mov eax, 0
  mov ecx, 126
  mov rdi, rdx
  rep stosq
  lea rax, [rbp-1424]
  mov rdi, rax
  call callee(A&)
  nop
  leave
  ret
```

对比:

![左:传引用 右:传值](images/传值与传引用-结构体较小.jpg)

在结构体或类的大小较大时,调用了memcpy,此时会有性能差距:

```C++
class A
{
    char chars[1024*1024]={'\0'}; 
};

void callee(A a)// 改为&a即为 pass by reference
{

}

void caller()
{
    A _a;
    callee(_a);
}
```

传值:

```
callee(A):
  push rbp
  mov rbp, rsp
  nop
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 1048576
  mov QWORD PTR [rbp-1048576], 0
  mov QWORD PTR [rbp-1048568], 0
  lea rax, [rbp-1048560]
  mov edx, 1048560
  mov esi, 0
  mov rdi, rax
  call memset
  sub rsp, 1048576
  mov rax, rsp
  mov rcx, rax
  lea rax, [rbp-1048576]
  mov edx, 1048576
  mov rsi, rax
  mov rdi, rcx
  call memcpy
  call callee(A)
  add rsp, 1048576
  nop
  leave
  ret
```

传引用:

```asm
callee(A&):
  push rbp
  mov rbp, rsp
  mov QWORD PTR [rbp-8], rdi
  nop
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 1048576
  mov QWORD PTR [rbp-1048576], 0
  mov QWORD PTR [rbp-1048568], 0
  lea rax, [rbp-1048560]
  mov edx, 1048560
  mov esi, 0
  mov rdi, rax
  call memset
  lea rax, [rbp-1048576]
  mov rdi, rax
  call callee(A&)
  nop
  leave
  ret
```

对比:

![左传引用,右传值](images/传值与传引用-结构体较大.jpg)