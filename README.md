# The-quadratic-equation
Данный репозиторий предназначен для решения квадратного уравнения по введённым коэффициентам
## Задача
Написать программу для решения уравнения вида a*x^2 + b*x + c = 0
## Сборка
Выполните `make` в директории проекта для сборки решения  
## Функции
`int isZero(float nmb)` проверяет, является ли переданное число нулевым  
`void print_solution(int QoS, float sol_1, float sol_2)` выводит переданные решения  
`int solveQuad(float a, float b, float c, float *sol_1, float *sol_2)` решает квадратное уравнение  
`char* get_err_codes(int e_no)` определяет ошибку по коду
## Ввод
Вводится три вещественных числа, являющихся коэффициентами уравнения вида `a*x^2 + b*x + c = 0`
Ввод осуществляется в следующем порядке: `a` `b` `c`
## Вывод
При отсутствии решений уравнения выводится текст "No solutions"  
При наличии одного или двух решений в каждой строке выводится по одному вещественному числу, являющемуся решением данного уравнения  
## Тестирование
Решение оснащено двумя видами тестов:  
1. Unit-тесты. Для запуска в файле main.c определите `TESTS_ON`;  
2. Shell-тесты. Для запуска соберите решение и запустите скрипт `quadtests.sh`  
## Котик
........................／＞　 フ.....................  
　　　　　| 　_　 _|  
　 　　　／`ミ _x 彡  
　　 　 /　　　 　 |  
　　　 /　 ヽ　　 ﾉ  
　／￣|　　 |　|　|  
　| (￣ヽ＿_ヽ_)_)  
　＼二つ  
