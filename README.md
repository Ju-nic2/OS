# OS 
## introduction 
OS 공부 및 실습 코드 저장소     

## System_call_test
사용 커널 버전 : 5.11.22    

#### 구성요소 
System_call :  table file, header file, systemcall 함수 구현한 .c 파일 존재     
Makefile : 시스템콜 등록 후 동작 테스트용 실행파일 생성     
#### 실행 방법
커널 파일들    
1. 사용자 CPU archtecture 에 맞춰 .tlb file을 옮긴다.    
2. syscalls.h 파일은 {kernel sourse coude dir}/include/linux 에 옮긴다. 
3. {kernel sourse coude dir}/kernel에 sys_op_{연산이름} 파일을 옮긴다. 
4. {kernel sourse coude dir}/kernel에 make file 에 system_call 디렉토리 안 Makefile 을 옮긴다.     
5. 커널 컴파일 후 실행    
테스트 코드 실행법     
$> make   
$> ./syscall     
(수식 입력) 개행.
입력방법 :      
실행 파일 실행 후 “1+2” ,”1-2” 또는 “  1 +     2 “ 처럼 공백을 포함해도 상관 없다.     
입력의 끝은 개행으로 구분한다. 음수는 (-1) 과 같은 형태만 허용한다.      

## page_replacement     
page_repacement 기법 : 소스파일명   
FIFO : fifo.c    
Optimal : opt.c    
Least Recently Used : lru.c    
Second Chance : second-chance.c  
### 실행방법 
$>  make   
$> ./Replace < inputfile>  ( input file이 input.txt일 때 -> ./Replace input.txt )     

### 각 기법에 대해 입력으로 받을 수 있는 String     
Optimal Algorithm: “OPT” | “opt”    
FIFO Algorithm: “FIFO” | “fifo”     
Least Recently Uesd Algorithm: “LRU” | “lru”     
Second Chance Algorithm: “Second-Chance” | “second-chance”     
모든 알고리즘 출력: “all”   

### input file 형식   
page frame 수 (1 이상 , 4 이하)     
page reference string (공백으로 구분, 30개 이하)    
ex)
4
1 2 3 1 2 3 1 2 3 
