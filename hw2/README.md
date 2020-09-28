# ДЗ №2

#### 1. Реализовать на языке C/C++ классические операции перемножения квадратных матриц и умножения матрицы на вектор (3 балла)

Реализовывал перемножение матриц. Для умножения матрицы на вектор, чтобы не повторяться, просто отнаследовался от класса матрицы и сделал 2 класса: вектор-строка и вектор-столбец, где они внутри представленны как матрица 1хN и Nх1 соответственно. 

#### 2. Разделить программу на несколько модулей и провести сборку через статическую линковку (2 балла)

Собираю классы и методы в библиотеку, потом через статическую линковку собираю эту библиотеку и main.cpp в исполняемый файл. Makefile лежит в репозитории.

#### 3. Подготовьте две сборки с флагами -g и  -O3 и измерьте времена выполнения операций с N = 512, 1024..., 4096 (3 балла)

Сделал сборку с разными флагами и тестировани умножения матриц через bash скрипт. Нужно просто запустить speed_test.sh, он соберет проект с разными флагами и протестирует каждый вариант со всеми нужными размерами матриц.

#### 4. Измерить времена выполнения программ в виртуальной машине, реальной ОС и (опционально) в докере (3 балла + 0.5 балла за докер)

Измерить времена выполнения программ на локальной машине на своем маке, в docker и в виртуалке Parallels Desktop с Ubuntu. Виртуализация в Parallels, как я понял, очень эффективная и не самая тривиальная, поэтому просадки по скорости практически не было. 

**Локальная машина:**

*Compilation flag -O3:*

Duration: 698 ms | n=512 | Dot product type: simple  
Duration: 470 ms | n=512 | Dot product type: Strassen  
Duration: 9003 ms | n=1024 | Dot product type: simple  
Duration: 3385 ms | n=1024 | Dot product type: Strassen  
Duration: 121246 ms | n=2048 | Dot product type: simple  
Duration: 23754 ms | n=2048 | Dot product type: Strassen  
Duration: 1149452 ms | n=4096 | Dot product type: simple  
Duration: 160188 ms | n=4096 | Dot product type: Strassen  


*Compilation flag -g:*

Duration: 1323 ms | n=512 | Dot product type: simple  
Duration: 1077 ms | n=512 | Dot product type: Strassen  
Duration: 20703 ms | n=1024 | Dot product type: simple    
Duration: 7373 ms | n=1024 | Dot product type: Strassen  
Duration: 287497 ms | n=2048 | Dot product type: simple  
Duration: 56019 ms | n=2048 | Dot product type: Strassen  
Duration: 2535337 ms | n=4096 | Dot product type: simple  
Duration: 395614 ms | n=4096 | Dot product type: Strassen  

**Docker:**

*Compilation flag -O3:*

Duration: 689 ms | n=512 | Dot product type: simple  
Duration: 462 ms | n=512 | Dot product type: Strassen  
Duration: 8689 ms | n=1024 | Dot product type: simple  
Duration: 3178 ms | n=1024 | Dot product type: Strassen  
Duration: 122948 ms | n=2048 | Dot product type: simple  
Duration: 23458 ms | n=2048 | Dot product type: Strassen  
Duration: 1348667 ms | n=4096 | Dot product type: simple  
Duration: 162824 ms | n=4096 | Dot product type: Strassen  

*Compilation flag -g:*

Duration: 1490 ms | n=512 | Dot product type: simple  
Duration: 1026 ms | n=512 | Dot product type: Strassen  
Duration: 25361 ms | n=1024 | Dot product type: simple  
Duration: 7824 ms | n=1024 | Dot product type: Strassen  
Duration: 301908 ms | n=2048 | Dot product type: simple  
Duration: 54134 ms | n=2048 | Dot product type: Strassen  
Duration: 3273444 ms | n=4096 | Dot product type: simple  
Duration: 378682 ms | n=4096 | Dot product type: Strassen  


**Parallels Desktop VM (MacOS):**

*Compilation flag -O3:*

Duration: 787 ms | n=512 | Dot product type: simple  
Duration: 509 ms | n=512 | Dot product type: Strassen  
Duration: 9470 ms | n=1024 | Dot product type: simple  
Duration: 3053 ms | n=1024 | Dot product type: Strassen  
Duration: 128537 ms | n=2048 | Dot product type: simple  
Duration: 23176 ms | n=2048 | Dot product type: Strassen  
Duration: 1273396 ms | n=4096 | Dot product type: simple  
Duration: 155585 ms | n=4096 | Dot product type: Strassen  

*Compilation flag -g:*

Duration: 1307 ms | n=512 | Dot product type: simple  
Duration: 970 ms | n=512 | Dot product type: Strassen  
Duration: 24255 ms | n=1024 | Dot product type: simple  
Duration: 7531 ms | n=1024 | Dot product type: Strassen  
Duration: 332521 ms | n=2048 | Dot product type: simple  
Duration: 52909 ms | n=2048 | Dot product type: Strassen  
Duration: 3219988 ms | n=4096 | Dot product type: simple  
Duration: 354638 ms | n=4096 | Dot product type: Strassen  


#### 5. Реализовать базовые скрипты bash, перечисленные на лекции (1.5 балла)
Скрипты лежат в отдельной папке, на каждую задачу - отдельный скрипт.

Бонусы:

#### 6. Дополнительные баллы за использование функций BLAS/cBLAS (1.5 балла)

Умножение с cBLAS в отдельном файлике cblas_text.cpp. Матрицы умножаются просто нереально быстро, прирост скорости на матрицах 4096х4096 по сравнению с самописным методом Штрассена - примерно в 35 раз, а с обычным умножением - в районе 80-90 раз!

Duration: 41 ms | n=512 | Dot product type: cblas
Duration: 198 ms | n=1024 | Dot product type: cblas
Duration: 882 ms | n=2048 | Dot product type: cblas
Duration: 4278 ms | n=4096 | Dot product type: cblas

#### 7. Дополнительные баллы за вызов теста LINPACK на вашем компьютере (1.5 балла)

На маке так и не удалось его собрать, пришлось воспользоваться уже готовым docker-контейнером. 

![Linpack_results](/hw2/Linpack_results.png)

#### 8. Супербонус: реализовать метод Штрассена перемножения квадратных матриц (3 балла)

Закодил в файлике dot_product_strassen.cpp. Прирост скорости получается в несколько раз для больших матриц.


