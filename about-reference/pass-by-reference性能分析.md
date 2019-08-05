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

![左:传引用 右:传值](/images/传值与传引用-结构体较小.jpg)

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

![左传引用,右传值](/images/传值与传引用-结构体较大.jpg)


通常建议优化的地方有参数传递和返回值.现在全用上,作为对比:

```C++
class A
{
    char chars[1024*8+1]={'\0'};// x86-64 gcc 9.1环境，此边界值为触发 memset 和 memcpy 的临界值，可能与 page 有关
};

A callee(A a)
{
    return a;
}

void caller()
{
    A _a;
    callee(_a);
}
```

参数和返回值传值:

```asm
callee(A):
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov QWORD PTR [rbp-8], rdi
  mov rax, QWORD PTR [rbp-8]
  mov rcx, rax
  lea rax, [rbp+16]
  mov edx, 8193
  mov rsi, rax
  mov rdi, rcx
  call memcpy
  mov rax, QWORD PTR [rbp-8]
  leave
  ret
caller():
  push rbp
  mov rbp, rsp
  push rbx
  sub rsp, 16424
  mov QWORD PTR [rbp-16432], 0
  mov QWORD PTR [rbp-16424], 0
  lea rdx, [rbp-16416]
  mov eax, 0
  mov ecx, 1022
  mov rdi, rdx
  rep stosq
  mov rdx, rdi
  mov BYTE PTR [rdx], al
  add rdx, 1
  lea rbx, [rbp-8224]
  sub rsp, 8
  sub rsp, 8200
  mov rax, rsp
  mov rcx, rax
  lea rax, [rbp-16432]
  mov edx, 8193
  mov rsi, rax
  mov rdi, rcx
  call memcpy
  mov rdi, rbx
  call callee(A)
  add rsp, 8208
  nop
  mov rbx, QWORD PTR [rbp-8]
  leave
  ret
```

参数传引用,返回值传值:

```asm
callee(A&):
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov QWORD PTR [rbp-8], rdi
  mov QWORD PTR [rbp-16], rsi
  mov rdx, QWORD PTR [rbp-8]
  mov rax, QWORD PTR [rbp-16]
  mov rcx, rdx
  mov edx, 8193
  mov rsi, rax
  mov rdi, rcx
  call memcpy
  mov rax, QWORD PTR [rbp-8]
  leave
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 16416
  mov QWORD PTR [rbp-16416], 0
  mov QWORD PTR [rbp-16408], 0
  lea rdx, [rbp-16400]
  mov eax, 0
  mov ecx, 1022
  mov rdi, rdx
  rep stosq
  mov rdx, rdi
  mov BYTE PTR [rdx], al
  add rdx, 1
  lea rax, [rbp-8208]
  lea rdx, [rbp-16416]
  mov rsi, rdx
  mov rdi, rax
  call callee(A&)
  nop
  leave
  ret
```

参数传值,返回值传引用(实际不可这样写,因为返回了局部变量的引用)

```asm
callee(A):
  push rbp
  mov rbp, rsp
  mov eax, 0
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 8208
  mov QWORD PTR [rbp-8208], 0
  mov QWORD PTR [rbp-8200], 0
  lea rdx, [rbp-8192]
  mov eax, 0
  mov ecx, 1022
  mov rdi, rdx
  rep stosq
  mov rdx, rdi
  mov BYTE PTR [rdx], al
  add rdx, 1
  sub rsp, 8200
  mov rax, rsp
  mov rcx, rax
  lea rax, [rbp-8208]
  mov edx, 8193
  sub rsp, 8
  mov rsi, rax
  mov rdi, rcx
  call memcpy
  add rsp, 8
  call callee(A)
  add rsp, 8200
  nop
  leave
  ret
```

参数和返回值均传引用:

```asm
callee(A&):
  push rbp
  mov rbp, rsp
  mov QWORD PTR [rbp-8], rdi
  mov rax, QWORD PTR [rbp-8]
  pop rbp
  ret
caller():
  push rbp
  mov rbp, rsp
  sub rsp, 8208
  mov QWORD PTR [rbp-8208], 0
  mov QWORD PTR [rbp-8200], 0
  lea rdx, [rbp-8192]
  mov eax, 0
  mov ecx, 1022
  mov rdi, rdx
  rep stosq
  mov rdx, rdi
  mov BYTE PTR [rdx], al
  add rdx, 1
  lea rax, [rbp-8208]
  mov rdi, rax
  call callee(A&)
  nop
  leave
  ret
```

对比:

![参数和返回值传递方式对比](/images/传值与传引用-参数和返回值对比.jpg)

可见,传值竟然比传引用多出一堆指令+两个 memcpy!

经过测试,在结构体或类较大的情况下,通常会有 1.5~2 倍的性能差距!