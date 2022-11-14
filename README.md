# minishell
## 작은 기능을 가지는 쉘 구현
### 구현
> 1. 사용자 입력을 받아 commandList를 Linkedlist형태의 데이터로 저장.
> 2. 부모 프로세스에서 실행할 커맨드(echo, cd, env, exit, pwd, unset...)와 자식프로세스에서 실행할 커맨드로 구분
> 3. 파이프나 redirection같은 stdin stdout 의 변경이 필요할 경우 알맞게 stdin과 stdout을 변경
> 4. 여러 커맨드가 존재할 경우 병렬처리
----------------
### 프로젝트를 하면서 알게 된것들
> 1. 표준입출력의 방향을 설정할수 있다
> 2. 파이프는 병렬처리와 표준입출력 설정이 핵심
> 3. 터미널도 조작이 가능
-----------------
### 병렬처리를 어떻게 처리하였나?
> 1. 부모 프로세서가 커맨드를 실행하고 끝나는것을 기다릴 자식프로세서를 생성
> 2. 생성된 자식 프로세서가 다시 자식프로세서를 생성하여 커맨드를 실행
> 3. 커맨드를 실행한 자식프로세서에게서 return이 돌아오면 그것을 부모 프로세서에 return
-------------------
### 왜 자식프로세서가 자식프로세서를 생성하여 처리했는가?
> - 곧바로 자식프로세서를 생성하여 실행을 맡겼을 경우 부모프로세서가 return값을 받길 기다릴때까지 병렬처리가 안되거나 병렬처리는 가능하나 커맨드들의 return값을 받을수 없음
----------------------
