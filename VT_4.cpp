#include <iostream>
/*
1) Необходимо подсчитать количество чисел на промежутке от -128 до 127, 
соответствующих  условию (Х * У – (X div 2)) = 0 
2) Найти и вывести на экран двухсотую
пару чисел X и У соответствующих заданному условию. 

Если таких чисел меньше двухсот, 
то вывести об этом сообщение на экран. 
 */


/*На промежутке от -128 до 127. 
Подсчитать количество таких пар чисел X и У, что (Х * У – (X div 2)) = 0. Ответ вывести на экран.*/
int main()
{
    unsigned count = 0;
    signed _int16 X, Y;
    _asm 
    {
        
        mov X, 126 // X = [-128; 127]
        M1:
           

            mov Y, 126 // Y = [-128; 127]
            M2:
                mov bx, 2; // для (X / ->_2_)
                mov ax, word ptr[X] // X(byte) 
                mov edx, dword ptr[X] // для (X % 2)
                
                
                imul [Y] // ax * Y(word) => dx:ax
                push ax // сохраняем (X * Y)
                mov eax, edx // X
                idiv bx // AX = EAX / BX
                
                mov bx, ax // bx = (X % 2)
                pop ax // pop (X * Y)
                sub ax, bx // (Х * У) – (X div 2)
                cmp ax, 0
                jne M3
                    inc count
                    
                M3:

                
                inc Y
            cmp Y, 127
            jle M2
              
            
            inc X
        cmp X, 127
        jle M1
    }
    std::cout << count;
    return 0;
}
