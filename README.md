# StudyTCP-IP
TCP/IP 학습 레포지토리

<br>

## 사용프로그램
- VMware Workstation 16 Player
- Ubuntu 64-bit
- PuTTY


## Day01
- 네트워크 프로그래밍에서 연결 요청을 허용하는 소켓의 생성과정
- 1단계) 소켓 생성 : socket() 함수호출
- 2단계) IP주소와 PORT번호 할당 : bind() 함수호출
- 3단계) 연결요청 가능상태로 변경 : listen() 함수호출
- 4단계) 연결요청에 대한 수락 : accept() 함수호출

## Day02
- Iterative 에코 서버, 에코 클라이언트
  - 하나의 서버가 하나의 클라이언트에게 서비스 제공
- echo_client.c 기존 코드(주석처리 한 부분)는 다음과 같은 잘못된 가정이 존재
  - read, write 함수가 호출될 때마다 문자열 단위로 셀제 입출력이 이루어짐
- 하지만 TCP는 데이터의 경계가 존재하지 않으므로 기존 클라이언트 코드는 둘 이상의 write 함수호출로 전달된 문자열 정보가 묶여서 한번에 서버로 전송될 수 있음
- 그러한 상황이 발생하면 클라이언트는 한번에 둘 이상의 문자열 정보를 서버로부터 되돌려받아, 원하는 결과를 얻지 못할 수 있음
- 다음과 같이 코드 수정
  - 전송한 데이터의 크기만큼 데이터를 수신하기 위해 read 함수 반복호출
  - 따라서 정확히 전송한 바이트 크기만큼 데이터 수신 가능
