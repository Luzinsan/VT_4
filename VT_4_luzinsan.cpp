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
    _int16 count = 0; 
    signed _int8 X, Y;
    signed _int8 X_r, Y_r;
    bool flag = false;
    const char* msg = "\n\tThe number of pairs is less than 200";
    _asm 
    {
        
        mov X, -128 // X = [-128; 127]
        M1:
            
            mov Y, -128 // Y = [-128; 127]  
            M2:
                
                mov al, X   // для (->_X_ div    2 )
                cbw
                mov dl, 2;           // для (   X  div ->_2_)
                idiv dl             // (even part)AL = AX / DL---> AL (X div 2)
                cbw
                // сохраняем (X div 2)
                push ax     // --------------------------> AX (X div 2)
               
                mov al, X // X(byte) 
                cbw
                imul Y // AL * Y(byte) => AX
                pop dx // pop (X div 2)
                //sub ax, dx
                sub al, dl // (Х * У) – (X div 2)
                sbb ah, dh
                cmp ax, 0
                jne M3
                    inc count
                    cmp count, 200
                    jne M3
                        cmp flag, 1
                        je M3
                            mov flag, 1
                            mov al, X
                            mov X_r, al
                            mov al, Y
                            mov Y_r, al
                M3:
                
            inc Y
            cmp Y, -128
                jne M2
              
        inc X
        cmp X, -128
        jne M1

    }

    std::cout << "\n\tNumber of pairs: " << static_cast<int>(count);
    if (flag)
        std::cout << "\n\t200-th pair\n\t ( x = " << static_cast<int>(X_r) << "; y = " << static_cast<int>(Y_r) << ' )' << std::endl;
    else
        std::cout << msg;
    




    bool tflag = false;
    int counter = 0, RX, RY;
    for (int iii = -128; iii < 128; ++iii)
        for (int jjj = -128; jjj < 128; ++jjj)
            if ((iii * jjj - (iii / 2)) == 0)
            {
                counter++;
                std::cout << "\n\tThe "<< counter <<"-th pair\t(x = " << iii << "; y = " << jjj << ')' << std::endl;
                if (counter == 200 && tflag == false)
                {
                    tflag = true;
                    RX = iii; RY = jjj;
                }
            }

    std::cout << "\n\tNumber of pairs: " << counter;
    if (tflag)
        std::cout << "\n\t200-th pair\n\t ( x = " << RX << "; y = " << RY << ')' << std::endl;
    else
        std::cout << msg;

    return 0;
}
