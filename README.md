# StudyTCP-IP
TCP/IP 학습 레포지토리



## 사용프로그램
- VMware Workstation 16 Player
- Ubuntu 64-bit
- PuTTY

<br>

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

## Day03
- UDP 기반 에코 서버/클라이언트
 - TCP에서는 소켓-소켓 1:1관계 -> 서버에서 여러 개의 클라이언트에게 서비스 제공하려면 서버소켓 이외에 추가로 클라 갯수만큼의 소켓 필요
 - UDP는 하나의 소켓만으로 둘 이상의 호스트와 통신 가능
 - TCP와 달리 연결요청 및 수락 과정이 존재하지 않아 서버/클라 표현이 적절치 않을 수도 있지만, 비스를 제공한다는  측면에서 서버라고 칭함
 - sendto 함수 호출시 IP와 PORT번호가 자동으로 할당 -> UDP 클라이언트 프로그램에서는 주소정보 할당 과정 불필요
 - 데이터의 경계가 존재하는 프로토콜이므로 데이터 송수신 과정에서 호출하는 입출력함수의 호출횟수가 완벽히 일치해야 송신된 데이터 전부를 수신 가능
 
 ## Day04
 - DNS(Domain Name System) : IP주소와 도메인 이름 사이에서의 변환을 수행하는 시스템
   - 도메인 이름 : 인테넷에서 서비스를 제공하는 서버는 IP주소로 구분하지만 기억하기 쉽지 않음 -> 기억하기도 좋고 표현하기도 좋은 형태의 도메인 이름을 부여
   - 도메인 이름으로 웹 페이지 접속시 : 도메인이름 -> DNS서버가 변환 -> IP주소 반환
   - gethostbyname.c : 도메인 이름을 이용해서 IP주소 얻어오기
   - gethostbyadr.c :  IP주소를 이용해서 도메인 정보 얻어오기
 
 - 소켓의 다양한 옵션
   - sock_type.c : 프로토콜 레벨이 SOL_SOCKET이고 이름이 SO_TYPE인 옵션을 이용해서 소켓의 타입 정보(TCP인지 UDP인지) 확인
   - get_buf.c : 소켓 생성시 기본적으로 만들어지는 입출력 버퍼 크기 확인
   - set_buf.c : 입출력 버퍼 임의로 변경 -> setsockopt 함수호출을 통해 전달한 버퍼의 크기가 나름대로 반영은 되지만(?) 정확히 맞춰지지는 않음 
   - reuseadr_eserver.c : 주석처리된 채 실행 -> 서버, 클라이언트 연결 상태에서 서버 프로그램 강제종료 시키면 서버 재실행에 문제 발생 : //설명을 못 적겠다.
   
 ## Day05(금)
 - 멀티프로세스 기반의 서버구현
 
 ## Day06(월)
 -
 
 ## Day07(화)
 
 ## Day08(수)
 - 멀티쓰레드 기반의 서버구현
