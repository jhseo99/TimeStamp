# 경력기술서

--------

## 와이키키소프트 (2020.01 ~ )

<br>

### __1. FIDO2 및 U2F 인증장치(HID) 개발__

- __개발스택__
  - C++
  - Keil
  - Fido2
  - U2F
  - CBOR

- __업무담당__
  - 인증장치 소프트웨어 개발
  - 인터뷰 진행
  - 인증장치 스펙 문서 작성

- __업무내용__
  - C++ 언어를 사용하여 Fido2 및 U2F 프로토콜 개발
  - FIDO2 프로토콜 스펙에 맞게 기존 소스코드 수정
  - FIDO2 프로토콜 옵션 기능 추가
  - HID 메세지를 파싱하여 U2F 프로토콜 메세지로 변환
  - U2F 메세지를 CBOR 메세지로 변환
  - U2F version, register, authenticate 등의 U2F 스펙 개발
  - Fido conformance Tool Test 및 MSTest 통과
  - 개발한 인증장치의 스펙 관련 산출물 문서 작성
  - FIDO Alliance 인증장치 등록 및 인증장치 관련 인터뷰 진행

<br>

### __2. Fido2 Windows Library 개발__

- __개발스택__
  - C++
  - Visual Studio
  - mbedTLS
  - cpprest
  - Fido2
  - json

- __업무담당__
  - Fido 라이브러리 유지보수 및 신규 기능 추가 개발
  - 고객사 배포

- __업무내용__
  - C++ 언어를 사용하여 기존에 개발 되어있던 라이브러리 유지보수 및 신규 기능 추가
  - 에러코드 정리 및 분류
  - 기존 소스파일 코드 정리
  - Windows 버전에 따른 Webauthn API 호출 및 오프라인 API 개발
  - cpprest를 사용하여 json 파싱 및 생성
  - Windows 하위 버전에서 개발한 API를 통해 Fido Register 및 Authenticate 실행
  - 자사 모바일 앱의 서버와 연동하여 모바일 푸쉬 기능 개발
  - 개발된 라이브러리를 dll 형식으로 고객사에 배포

<br>

--------

## 블랙펄시큐리티 (2018.03 ~ 2018.12)

<br>

### __1. 국제해킹대회 Codegate 2018 문제 출제 및 운영__

- __개발스택__
  - C
  - C++
  - Visual Studio
  - VS Code
  - Docker

- __업무담당__
  - 해킹 대회 문제 출제
  - 해킹 대회 운영진으로 참여

- __업무내용__
  - 출제된 문제이름: Shall we dance
    - C++ 언어로 mp3 플레이어 개발
    - Windows PE 리버싱 문제
    - mp3 플레이어를 리버싱 분석하여 손상된 mp3 PE 파일을 복구하는 문제
  - 출제된 문제이름: DaysNote
    - C 언어로 윤년의 개념을 활용한 노트 개발
    - 윤년인 해는 366 Byte 만큼을 Write 할 수 있고, 윤년이 아닌 해는 365 Byte 만큼을 Write 할 수 있게 구현
    - 위 개념을 활용하여 1 Byte Buffer Overflow 취약점 삽입
    - Shellcode 작성시 \\x0b 문자를 우회
  - Amazon AWS 서버에 Docker를 사용하여 문제마다 각각의 컨테이너 생성
  - 대회 현장 WIFI 네트워크 IP 대역 세팅 지원
  - 대회 현장 서버 로그 감시

<br>

### __2. 2018 사이버가디언즈리그 문제 출제 및 운영__

- __개발스택__
  - C
  - C++
  - HTML
  - PHP
  - Apache
  - MySQL
  - Visual Studio
  - VS Code
  - AWS
  - Docker

- __업무담당__
  - 해킹 대회 문제 출제
  - 해킹 대회 운영진으로 참여

- __업무내용__
  - 고등학생을 대상으로 진행되는 리그 형식의 해킹 대회
  - UAF(Use-After-Free) 취약점을 사용한 시스템 해킹 문제 출제
  - Random seed를 이용한 문제 출제
  - Linux 명령어를 이용한 문제 출제
  - Web Cookie 및 Base64를 이용한 문제 출제
  - Web URL Redirection 취약점을 이용한 문제 출제
  - 이외에 비교적 가벼운 난이도의 다양한 해킹 문제 출제
  - Amazon AWS 서버에 Docker를 사용하여 문제마다 각각의 컨테이너 생성
  - 대회 현장 WIFI 네트워크 IP 대역 세팅
  - Amazon AWS EC2 포트 IP 대역 필터링 설정
  - Amazon AWS EC2 포트 오픈 역할 수행
  - 대회 현장 서버 로그 감시

<br>

### __3. 보안 API 및 특허 모듈 개발__

- __개발스택__
  - C
  - VS Code
  - OpenSSL

- __업무담당__
  - Java 개발된 보안 API C로 포팅
  - 특허 모듈 개발
  - 특허 모듈 산출물 작성

- __업무내용__
  - 시큐어 코딩 가이드를 따라 Java로 제작된 보안 API C언어로 포팅
  - XSS 필터링, URL 필터링, File Path 검사, 특수문자 치환 등과 같은 API 개발
  - OpenSSL을 사용하여 MD5 단방향 해쉬 및 AES 양방향 암호화 API 개발
  - C언어를 사용하여 TCP/IP 소켓 프로그래밍으로 특허모듈 개발
  - 소켓 통신을 통해 여러 임베디드 디바이스 간의 연결
  - 디바이스의 파일들을 자체 알고리즘과 RSA로 암호화하여 바이너리 형식으로 저장하도록 개발
  - 여러 대의 연결된 디바이스가 상호 작용을 통해 위변조 여부 검사 및 자가 백업하도록 개발
  - FTP 프로토클을 사용해 파일 백업
  - 개발된 모듈 산출물 작성

<br>

--------
