### 목적 : 몇가지 내장 Shell 기능을 포함하는 간단한 유닉스 명령줄 프로그램을 만듭니다

| 명령어 | 기능 | 구현 여부 |
| --- | --- | --- |
| cd | 디렉토리를 변경합니다 | O |
| echo | 표준 출력에 인수를 씁니다 | O |
| env | 환경변수를 출력합니다 | O |
| setenv | 환경변수를 설정합니다 | O |
| unsetenv | 환경변수를 해제합니다 | O |
| exit | 미니쉘을 종료합니다 | O |

### 사용 언어

- C

### 추가 기능

- 신호 처리(ctrl-C, ctrl-D).
- 다중 명령 지원(separated by ;).
- Single quotes('), Double quotes(")에 따른 올바른 따옴표 관리
- 올바른 에러처리를 위한 errono 관리

<aside>
💡 모든 기능은 42의 코딩 표준인 Norm에 따라 작성되었습니다.
</aside>

### 프로젝트를 하면서 알게 된것들

> 표준입출력의 방향을 설정할수 있다  
> 파이프는 병렬처리와 표준입출력 설정이 핵심  
> 터미널도 조작이 가능시그널 처리
---

### 구현

> 사용자 입력을 받아 commandList를 Linkedlist형태의 데이터로 저장.  
> 부모 프로세스에서 실행할 커맨드(echo, cd, env, exit, pwd, unset...)와 자식프로세스에서 실행할 커맨드로 구분  
> 파이프나 redirection같은 stdin stdout 의 변경이 필요할 경우 알맞게 stdin과 stdout을 변경여러 커맨드가 존재할 경우 병렬처리
---

## 문제 해결 사례

### 문제

다중 명령어를 입력하는 경우 병렬 처리가 되지 않고, 직렬 처리가 되고있음.

### 원인

쉘 커맨드를 입력하는 경우 각 명령어의  return값을 얻고자 할때 minishell 메인 프로세스가 return값을 기다리면 병렬처리가 안되고 병렬처리를 하면 return값을 얻을 수 없음
![미니쉘 구조(완)](https://user-images.githubusercontent.com/57505385/201668170-f172611c-3fab-4440-a368-acbadd24fcdd.png)
### 해결
![미니쉘 구조(미완)](https://user-images.githubusercontent.com/57505385/201668174-09f7bc6a-5a5c-4518-8293-6ac8b7e196cb.png)
executer를 생성하는 자식프로세서를 하나 더 둠으로써 minishell은 해당 명령어를 실행할 자식프로세서들만을 생성하고 return값이 다 오기를 대기하고, 자식프로세서들은 명령어를 실제 처리할 자식프로세서를 생성하여 return값을 돌려주는 방식의 구조로 변경

