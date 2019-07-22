![Image Error](./castle.jpg)

Hacker School FC3
=================

<br>Hacker School FC3는 Hacker School에서 제공하는 War game 문제로 FTZ, LOB의 다음 단계이다. 이전의 문제들과는 다르게 Red_Hat이 아닌 Fedora 환경에서 문제를 진행하며 다양한 메모리 보호 기법이 적용되어 있다.

---

사전지식
========

<br>본격적으로 문제를 풀기에 앞서 서버의 환경을 알아보자. 현재 FC3 서버에는 'DEP / NX, ASLR, ASCII Armor'라는 보호 기법이 기본적으로 적용되어 있다.

<br>앞으로 문제를 풀어나가는데에 있어 조금이라도 더 수월하게 이 기법들에 대해 미리 알아보고 대처 할 수 있도록 하자.

---

DEP / NX
--------

<br>DEP / NX는 stack이나 heap과 같은 데이터 영역에 실행 권한을 없애는 것이다.

<br>쉽게 말해 공격자가 buffer overflow 공격을 통해 ret를 쉘 코드로 변조하였다고 가정하면 DEP가 적용되기 전에는 스택에 실행 권한이 있기 때문에 그대로 쉘이 실행 되었다. 하지만 DEP가 적용되어 있으면 데이터 영역에서의 실행 권한이 없기 때문에 쉘이 실행되지 않고 예외 처리가 되고 프로그램이 종료된다.

---

ASLR
----

<br>ASLR은 공격자가 메모리 주소에 접근 하는 것을 어렵게 하기 위해 스택이나, 힙, 라이브러리 영역 등의 주소를 랜덤으로 배치시켜 실행 할 때마다 데이터의 주소가 달라지게 하는 것을 말한다.

<br>실행 할 때마다 데이터의 주소가 달라지기 때문에 공격자가 원하는 데이터의 주소를 얻어 공격을 시도하여도 데이터의 주소가 달라지기 때문에 공격에 실패하게 될 확률이 높다.

<br>※현재 FC3에는 스택 영역에만 ASLR이 적용되어 있다.

---

ASCII Armor
-----------

<br>ASCII Armor는 공유 라이브러리 영역의 주소 값을 16MB이하로 만들어 주소 값을 0x00으로 시작하게 만드는 것이다.

<br>0x00은 NULL 값을 뜻한다. 이로 인해 공유 라이브러리 영역을 참조하는 공격을 시도하게 되면 주소 대신 NULL이 삽입되기 때문에 공유 라이브러리 영역에 쉽게 접근 할 수 없다.

---

<br>위 보호기법들이 FC3에 적용된 보호기법이다. 한 눈에 봐도 난이도가 이전에 비해 올라간 것 같다. 이제 본격적으로 문제를 풀어보자.

---

iron_golem
==========

<br>![Image Error](./iron_golem//source.jpg)

<br>첫 번째 문제라 그런지 코드가 간단하다. 힌트부터 살펴보면 FEBP 기법을 사용하라고 말하는 것 같다. 코드는 실행 인자를 받아 buffer에 저장하는 것이다. 역시나 길이 제한이 없어 overflow가 발생한다.

<br>![Image Error](./iron_golem/gdb_stack.jpg)

<br>gdb를 이용해 열어본 결과 스택에 0x108 byte를 할당 한 것을 볼 수 있다. 0x108은 10진수로 264에 해당하는 값이다. buffer는 256 byte이므로 8 byte의 dummy가 있다는 것을 확인하였다.

<br>![Image Error](./iron_golem/stack.jpg)

<br>얻은 정보를 바탕으로 구성한 스택이다.

<br>어떻게 쉘을 실행 시킬지부터 생각해보자. DEP가 적용되어 쉘 코드는 사용이 불가능 하다. 그렇다면 함수를 이용해 쉘을 실행시켜야 한다.

<br>방법은 간단하다. 첫 번째 인자를 실행하는 execl() 함수를 이용하자. FEBP 기법을 이용해 ebp를 변경 시키고 ebp+4 지점인 ret에 execl() 함수의 주소를 적어주면 될 것이다. 하지만, 한 가지 주목해야 할 점이 있다. 현재 fake ebp로 이동한 지점의 위에 ret를 담는 것이기 때문에 execl()의 함수 프롤로그가 실행되면 push ebp; mov ebp, esp에 의해 다시 ebp가 원상복구 되어 버린다. 그렇기 때문에 프롤로그가 끝난 지점을 ret로 주어야한다. 이 지점의 주소를 알아내자.

<br>![Image Error](./iron_golem/execl.jpg)

<br>gdb를 통해 본 결과, execl+3 지점인 0x007a5723을 ret로 사용하면 될 것 같다. 그리고 ASCII Armor 기법이 적용되어 주소가 0x00으로 시작하는 모습도 구경해 볼 수 있다.

<br>다음으로 ebp+8 지점에는 execl의 첫 번째 인자가 들어가야 한다. 즉, 쉘을 실행 시킬 수 있어야 한다. DEP로 인해 쉘 코드는 사용 할 수 없기 때문에 쉘을 실행시키는 프로그램을 작성하여 인자로 넘겨주어야 할 것 같다.

<br>프로그램을 어떻게 담을 수 있을까? 우선 ASLR을 우회해야 하기 때문에 ASLR의 영향을 받지 않는 바이너리 쪽의 got를 사용하기로 하자.

<br>got(Global Offset Table)는 함수들의 실제 주소를 담고 있는 곳이다. 우리가 함수를 호출하게 되면 보통 바로 함수를 호출하는 것이 아니라 plt(Procedure Linkage Table)라는 곳을 호출한다. 그리고 plt는 got로 연결을 돌려주는 역할을 하고 got에 쓰여진 진짜 함수 주소를 읽어온다. 그리고 그 함수의 주소를 통해 함수를 실행한다. 즉, 우리가 함수를 호출하게 되면 got에 기록된 함수의 주소를 호출하는 것과 같다.

<br>그럼, got 영역 중에서 프로그램을 담기 적당한 곳이 있는지 찾아보자.

<br>![Image Error](./iron_golem/got.jpg)

<br>objdump와 grep을 이용해서 got의 위치를 찾고 gdb로 got를 살펴보았다. 0x08049618에는 단지, "\\001" 문자가 들어있어 덮어써도 상관 없을 것 같다. 이 곳에 프로그램을 담자. 프로그램 이름을 "\\x001"로 하게되면 got는 우리가 만든 파일을 실행하게 될 것이다.

<br>여기서 현재 상황을 보자. 우리는 fake ebp를 통해 어딘가로 이동 할 것이다. 이동한 곳의 ebp+4 지점에는 execl()+3의 주소가 있어야한다. 그리고 ebp+8 지점의 주소는 0x08049618이 되어야 한다. 그 말은 즉, ebp는 0x08049618에서 8을 뺀 0x08049610이 되어야 한다.

<br>이제 필요한 것이 모두 준비되었다. 정리해보자.

<li>fake ebp : 0x08049610</li><li>ret : 0x007a5723</li><li>ebp+8 : 0x08049618</li>

<br>우리가 전달 해주어야 할 값은 fake ebp와 ret 뿐이다. ebp+8은 execl 함수가 알아서 인자를 참조 할 것이기 때문이다.

<br>이제 공격을 시도해보자.

<br>![Image Error](./iron_golem/sh01.jpg)

<br>/etc/passwd 파일을 열어 iron_golem의 권한 값을 얻어내고 이를 이용해 iron_golem 권한의 쉘을 실행시키는 코드를 작성하였다. 파일 이름은 "\\x01"로 하여 0x08049618에 들어가게 해주었다.

<br>![Image Error](./iron_golem/success.jpg)

<br>buffer(256 byte) + dummy(8 byte)를 채워주고 fake ebp로 0x08049610을, ret로 0x007a5723의 execl() 지점을 주었다. 그 결과 깔끔하게 공격에 성공하였다.

---

dark_eyes
=========

<br>![Image Error](./dark_eyes/source.jpg)

<br>코드를 보면 이전에 사용하였던 FEBP 기법을 막아놓았고 나머지는 전과 동일한 모습이다.

<br>그러나 우리는 FEBP 기법을 사용 할 것이다. 방법은 간단하다. 지금부터 잘 따라오길 바란다.

<br>SFP를 바꿀 수 없는데 어떻게 FEBP 기법을 사용할까? 바로 이동하는 SFP에 저장된 곳으로 이동하는 ebp를 따라가서 우리가 원하는 값을 집어 넣어 fake ebp로 만들어 버리는 것이다.

<br>그러기 위해서는 현재 main의 스택 프레임을 잃어버리면 안된다. 그렇기 때문에 ret를 leave 명령으로 덮어 mov esp, ebp; pop ebp를 수행한다. 그렇게 되면 ebp는 SFP에 저장된 곳이 되고 mov esp, ebp 명령에 의해 esp는 ebp와 같아진다. pop ebp 명령어에 의해 ebp+4, ebp+8에 각각 ret와 인자가 제대로 위치 할 수 있게 된다. 남은 문제는 간단하다. ebp를 쫓아가기 위해 ebp가 이동한 거리를 알아내어 그 만큼 dump 시켜주면 된다.

<br>![Image Error](./dark_eyes/stack.jpg)

<br>이해를 돕기 위해 그림을 보면서 알아보자. ebp는 1번에서 1번에 들어있는 Fake ebp's Address의 값을 따라 2번으로 이동 할 것이다. 이동 되는 위치는 우리가 바꿀 수 없다. 하지만 들어 있는 정보는 바꿀 수 있다. ret를 leave 명령으로 바꿔 ebp를 유지시키고 ?의 거리를 알아내어 Fake ebp를 우리가 원하는 값으로 dump 시켜버리면 진짜 fake ebp가 되는 것이다.

<br>?의 거리를 알아내는 것은 간단하다. 2번 주소 - 1번 주소 - Fake ebp's Address(4 byte) - RET(4 byte)를 해주면 된다.

<br>![Image Error](./dark_eyes/leave_addr.jpg)

<br>우선, ebp 위치를 유지시키기 위해 필요한 주소인 leave 명령어의 주소를 얻었다.

<br>![Image Error](./dark_eyes/ebp.jpg)

<br>main이 종료되기 직전에 break point를 걸고 실행시켜 ebp의 위치를 확인했다. ebp는 0xfef54d28에 위치하고 있고 0xfef54d88로 이동한다.

<br>이로써 ?의 크기를 알아 낼 수 있게 되었다.

> 0xfef54d88 - 0xfef54d28 - SFP(4 byte) - RET(4 byte) = 0x58(88)

<br>거리를 알아내었기 때문에 ASLR의 영향도 받지 않는다. 88 byte 만큼을 dump 시켜주면 ebp를 fake ebp로 만들 수 있을 것이다.

<br>이제는 fake ebp에 들어갈 값을 찾아보자. 이전과 마찬가지로 got 영역을 사용한다.

<br>![Image Error](./dark_eyes/got.jpg)

<br>0x08049690에는 ebp+8 인자가 들어가야 함으로 0x08049690 - 8을 해서 0x08049688을 fake ebp로 사용하고 쉘 프로그램 이름을 "\\x001"로 링크 해주면 될 것 같다.

<br>![Image Error](./dark_eyes/execl.jpg)

<br>execl() 함수의 프롤로그가 끝난 지점인 0x007a5723의 ret도 구했다.

<br>이제 쉘을 실행하는 프로그램을 작성하여 이름을 "\\x01"로 링크 하는 일만 남았다.

<br>![Image Error](./dark_eyes/sh.jpg)

<br>모든 준비가 끝났다.

<br>마지막으로 한 번 정리해보자.

<br>우선, buffer(256 byte) + dummy(8 byte) + SFP(4 byte) = 268 byte 만큼을 dump 하여 ret에 도달한다. ret는 leave 명령어가 위치한 주소로 덮어쓴다. ebp는 fake ebp에 가게 되고 88 byte를 dump하여 ebp를 따라간다. fake ebp를 만들어주기 위해 인자가 저장된 곳 -8 지점으로 dump한다. ret는 execl+3의 위치로 덮어쓴다.

<br>여기까지가 모든 과정이다. 공격을 시도해보자.

<br>![Image Error](./dark_eyes/success.jpg)

<br>공격에 성공하였다.

---

hell_fire
=========

<br>![Image Error](./hell_fire/source.jpg)

<br>코드는 전과 다른 것이 거의 없고 힌트를 보면 BOF가 Remote 중이라고 한다.

<br>![Image Error](./hell_fire/bof.jpg)

<br>서비스를 확인 해 본 결과 tcp/7777 포트로 서비스 중인 것을 확인하였다.

<br>이는 xinetd 슈퍼 데몬으로 실행되는데 슈퍼 데몬은 따로 remote 할 필요 없이 쉘만 실행 시키면 쉘을 얻을 수 있다고 한다.

<br>그렇다면 쉘을 실행 시키기 위해서 system() 함수 내부의 do_system() 함수를 이용 할 것이다. do_system()에 있는 execve()를 호출 하는 것만으로도 쉘을 획득 할 수 있다.

<br>![Image Error](./hell_fire/execve.jpg)

<br>gdb를 사용하여 do_system을 disassemble 하여 0x007a5490에 execve() 함수가 위치한 것을 확인했다. 하지만, 이 주소만으로는 함수가 실행되지 않으므로 인자를 세팅하는 <do_system+1124> 지점부터 ret로 덮어쓰면 된다. 이제 buffer(4 byte) + dummy(4 byte) + SFP(4 byte) = 268 byte를 dump 하고 ret를 0x00750784로 덮어쓰면 쉘을 얻을 수 있다.

<br>![Image Error](./hell_fire/success.jpg)

<br>netcat으로 localhost의 7777번 포트를 열어 본 결과이다. do_system() 덕분에 아주 간단하게 공격에 성공하였다.

---

evil_wizard
===========

<br>![Image Error](./evil_wizard/source.jpg)

<br>이번 단계는 GOT Overwrite라는 기법이 사용된다.

---

GOT Overwrite
=============

<br>GOT Overwrite에 대해 알아보자.

<br>GOT Overwrite는 이전에 말한 got 영역을 덮어쓰는 것을 얘기한다.

<br>전에 얘기 하였듯이 함수를 호출하게 되면 함수를 바로 호출 하는 것이 아니라 사실은 plt를 호출 하게 된다. 그리고 plt는 실제 함수의 주소를 담고 있는 got에 연결을 시켜준다. plt는 got로 연결시켜주는 명령어로 이루어진 테이블이다. plt 명령에 따라 got에 연결되어 실제 함수 주소를 얻고 got에 있는 함수의 주소를 호출하는 것이 함수의 동작 방식이다.

<br만약, got 영역에 있는 printf() 함수의 주소를 system() 함수의 주소로 overwrite 하면 어떻게 될까? printf() 함수를 호출 하면 plt에 연결되고 plt는 got으로 jmp 되어 got에 있는 printf 주소를 얻을 것이다. 하지만 이 주소는 system() 함수의 주소이기 때문에 system() 함수가 실행 된다. 이 것이 GOT Overwrite 기법이다.

---

<br>그렇다면 got을 어떻게 덮어 쓸 수 있을까? 바로 RTL과 gadget(가젯)을 이용하여 덮어쓴다.

---

RTL
===

<br>RTL은 Return To Library 기법으로 ret를 우리가 원 하는 함수의 주소로 덮어쓰면 그 함수가 실행 되게끔 하는 것이라고 앞에서 배웠다.

<br>![Image Error](./evil_wizard/rtl_stack.jpg)

<br>그 과정에서 함수에 올바른 인자를 전달하기 위해 스택을 위와 같이 구성해야 한다. 스택의 흐름에 따라 function() 함수가 실행 될 것이고 다시 function()'s ret를 따라가서 ret가 가리키는 곳이 실행 될 것이다. 이 때 function()'s ret를 또 다른 인자가 있는 함수의 실행 점으로 바꾸려고 한다. 이 때는 단지 인자만 위에 쌓아주면 함수가 정상적으로 동작 할 것이다. 하지만, 만약 함수 여러개를 실행하려고 하거나 혹은 인자가 여러 개일 경우에는 어떻게 될까?

<br>![Image Error](./evil_wizard/rtl_stack2.jpg)

<br>함수 여러 개를 실행 시키기 위해 스택을 위와 같이 만들어주어야 한다. 이 함수들이 인자가 없다면 원하는대로 올바른 동작을 하겠지만 인자가 존재한다면 인자가 들어가야 할 곳에 ret가 들어가기 때문에 원하는대로 동작하지 않게 되는 것이다.

<br>그렇다면 ret 대신 인자를 넣으면 어떻게 될까? 이번에는 ret가 들어가야 할 곳에 인자가 들어가 있기 때문에 우리가 원하는 함수들은 맨 첫 번째 함수를 제외하고는 실행되지 않을 것이다.

<br>이 같은 문제를 해결하기 위해 가젯을 사용한다.

---

gadget
======

<br>가젯은 ret 명령어로 끝나는 코드 조각들을 말한다. 그리고 이 코드 조각들은 함수의 인자들을 정리해야 할 때 사용된다.

<br>좀 더 정확한 표현으로는 ret를 올바른 곳에 위치시키기 위해 사용되었던 인자들을 스택에서 정리 해주는 것이다. 어떤 코드 조각들이 스택을 정리하는가? pop 명령어이다.

<br>![Image Error](./evil_wizard/gadget.jpg)

<br>위 스택이 가젯을 사용한 스택이다. 위 가젯은 이번 문제에 소스 코드에 존재하는 ppr 가젯이다. pop pop ret 명령을 수행하기 때문에 줄여서 ppr 이라고 한다. 먼저, RET를 따라 함수가 실행되고 함수는 parameter 1과 parameter2에 위치한 값 2개를 인자로 갖는다. 이후 함수의 ret에 위치한 주소를 따라가는데 여기에는 가젯이 들어있다. 가젯을 따라 pop eax; pop eax; 명령을 수행하게 되면 스택에서 parameter 1과 parameter2가 제거되게 된다. 그럼 next ret가 gadget의 바로 위에 존재하게 된다. 그리고 가젯의 마지막 명령어 ret를 사용하면 ret(pop eip) 명령에 따라서 eip는 next ret를 가리키게 되는 것이다.

<br>결론적으로 ppr 가젯을 활용해 우리가 원하는 함수를 원하는 만큼 원하는 대로 인자를 넣을 수 있다는 말이다.

---

<br>일단, 여기까지가 GOT Overwrite를 위해 필요한 사전 지식이다. 위 정보가 왜 필요한지는 문제를 풀면서 좀 더 자세히 배워보자.

<br>우선, 이번 문제를 풀기 위해 필요한 정보들이다.

<li>strcpy() 함수의 plt 주소</li><li>printf() 함수의 plt, got 주소</li><li>system() 함수의 주소</li><li>"/bin/sh"의 주소</li><li>ppr 가젯의 주소</li>

<br>이번 단계에서는 setreuid()와 setregid() 함수를 통해 권한을 제공 받기 때문에 system() 함수를 이용하여 쉘을 띄우기만 하면 된다. 그러기 위해 printf() 함수를 GOT Overwrite 하여 system() 함수로 덮어 쓸 것이다. 그리고 system()의 인자로 "/bin/sh"을 주기 위해서 "/bin/sh"의 주소 또한 필요하다. strcpy() 함수와 ppr 가젯은 printf() 함수의 got를 덮어 쓸 때 사용된다.

<br>우리의 계획은 이렇다. 목표는 printf() 함수의 got를 덮어써 system() 함수를 호출 하는 것이고, 이 때 인자로 "/bin/sh"이 전달 되어야 한다. 그리고 printf() 함수의 got를 덮어 쓸 때 strcpy() 함수를 이용해서 system() 함수의 주소를 덮어주면 된다.

<br>필요한 정보들을 하나씩 얻어보자.

<br>![Image Error](./evil_wizard/strcpy.jpg)

<br>우선, strcpy() 함수의 plt 주소이다. 0x08048494에 strcpy@plt가 위치한 것을 확인하였다.

<br>![Image Error](./evil_wizard/printf.jpg)

<br>printf() 함수의 plt와 got 주소이다. plt는 0x08048424인 것을 볼 수 있고 got 주소는 0x08049884이다. 앞에서 plt는 got에 있는 함수의 실제 주소로 연결 시켜준다고 하였으니 plt에서 jmp 명령어를 통해 이동하는 곳이 실제 주소인 것이다.

<br>![Image Error](./evil_wizard/system.jpg)

<br>system() 함수의 주소 0x007507c0도 얻었다.

<br>![Image Error](./evil_wizard/bin_sh.jpg)

<br>"/bin/sh"이 위치한 곳은 0x00833603이다.

<br>![Image Error](./evil_wizard/ppr.jpg)

<br>마지막으로 ppr 가젯이 위치한 곳을 찾아주자. pop 명령어를 검색하여 ppr 가젯의 첫 번째 명령어인 pop %eax를 찾아주었다. 이 곳 0x0804854f가 ppr 가젯의 시작 위치이다.

<br>이제 printf() 함수의 got를 system() 함수의 주소로 덮어주기만 하면 된다. 이제 왜 우리가 strcpy()와 ppr 가젯이 필요했는지 알게 될 것이다.

<br>![Image Error](./evil_wizard/system_data.jpg)

<br>objdump릁 통해 system() 함수의 주소 값이 스택 어디에도 존재 하지 않는다는 것을 확인하였다. 그럼 어떻게 printf@got를 덮을 수 있을까? 바로 system() 함수의 주소를 1 byte씩 분리하여 덮어쓰는 것이다. 총 4번 strcpy()를 호출하여 printf@got를 1 byte씩 덮어주면 된다. 이 과정에서 strcpy() 함수를 여러번 호출하기 때문에 각각의 인자를 정리해주는 ppr 가젯이 필요하게 된다.

<br>그럼, system() 함수의 주소 값을 1 byte씩 나눠 스택에서 찾으면 된다.

<br>little endian 정렬 방식에 의해 끝에서부터 덮어줘야 하기 때문에 c0부터 찾아보자.

<br>![Image Error](./evil_wizard/c0.jpg)

<br>c0은 0x08048420에 위치하고 있는 것을 알아냈다. 많은 c0 값이 있는데 printf@got 주소를 1 byte씩 증가시키며 값을 덮어 쓸 것이기 때문에 c0이 가장 뒤에 있는 값을 찾으면 된다.

<br>![Image Error](./evil_wizard/07.jpg)

<br>역시나 가장 뒤에 07이 위치하고 있는 0x08048154를 사용하면 된다.

<br>![Image Error](./evil_wizard/75.jpg)

<br>75 값 또한, 0x080482c8에 있는 값을 사용하면 된다.

<br>이제 마지막으로 00 값을 찾아주면 되는데 c0을 찾을 때 0x080481ec의 값의 가장 끝이 00인 것을 볼 수 있다. 이 곳을 사용하면 00 값으로 사용하면 된다.

<br>지금까지 정보를 스택에 정리해보자.

<br>![Image Error](./evil_wizard/last_stack.jpg)

<br>스택은 위와 같다. 정리하면 ret에 위치한 strcpy@plt를 따라 strcpy() 함수가 실행되고 인자로 printf@got의 주소와 c0이 위치한 곳의 주소를 넘겨준다. printf@got의 가장 끝 1 byte가 c0으로 덮어졌다.

<br>이후 ret에 위치한 PPR Gadget을 실행한다. pop eax; pop eax; ret에 의해서 printf@got+0's address와 c0 data's address가 pop 되고 ret 명령에 의해 두 번째 strcpy@plt를 실행한다.

<br>strcpy() 함수가 실행 되고 이번에는 printf@got 주소에 +1을 하여 printf@got의 끝에서 두 번째 자리를 07로 덮는다.

<br>그리고 또 다시 ret에 PPR Gadget을 실행 시켜 인자를 정리하고 다음 strcpy@plt를 실행 할 것이다.

<br>이런 식으로 printf@got를 모두 덮는 것이다.

<br>그렇게 되면 printf() 함수를 실행하면 system() 함수가 실행 될 것이다. 이 말은 즉, printf("/bin/sh")을 실행 하면 system("/bin/sh")이 실행 되는 것과 마찬가지라는 것이다. 그러므로 최종적으로는 ret를 printf@plt로 주어 printf() 함수를 실행하고 ebp+8 지점의 인자에는 "/bin/sh"의 주소가 들어있으면 정상적으로 우리가 원하는 동작을 할 수 있다.

<br>![Image Error](./evil_wizard/payload.jpg)

<br>위 과정에 맞는 페이로드를 python으로 작성하여 좀 더 편하게 공격 할 수 있게 하였다. 주석을 참고하여 스택 그림과 코드를 비교하며 보면 이해하기 어렵지 않을 것이다.

<br>![Image Error](./evil_wizard/failed.jpg)

<br>위 페이로드로 공격을 시도하였지만 실패하였다. 알아보니 strcpy() 함수를 사용하여 printf@got을 dump 할 때 전달 해 준 값에 문제가 있었다. strcpy() 함수는 NULL byte를 문자열의 끝으로 인식하여 그 만큼을 덮어 쓰는데 우리가 전해준 값 중 c0과 NULL byte의 값이 너무 멀어 overflow를 일으킨 것 같다. 좀 더 NULL과 가까운 값을 사용해주면 된다.

<br>![Image Error](./evil_wizard/c0_2.jpg)

<br>위 값들 중 NULL과 가까운 0x0804852c에 있는 c0 값을 사용해서 코드를 수정하고 다시 공격을 시도하자.

<br>![Image Error](./evil_wizard/success.jpg)

<br>코드의 system_c0을 0x0804852c로 고쳐주고 다시 공격을 시도하였더니 공격에 성공하였다.

---

dark_stone
==========

<br>![Image Error](./dark_stone/source.jpg)

<br>이전과 코드가 동일하다. 단지, remote 환경의 차이인 것 같다. 이전 단계에서 사용했던 공격 방법을 그대로 사용하여 remote 접속만 해주면 될 것 같다.

<br>필요한 정보들을 모두 얻어보자.

<br>![Image Error](./dark_stone/strcpy.jpg)

<br>strcpy@plt의 주소는 0x08048438이다.

<br>![Image Error](./dark_stone/printf.jpg)

<br>printf@plt와 printf@got의 주소는 각각 0x08048408, 0x0804984c이다.

<br>![Image Error](./dark_stone/system.jpg)

<br>system() 함수의 주소는 0x007507c0이다.

<br>![Image Error](./dark_stone/bin_sh.jpg)

<br>"/bin/sh"의 주소 또한 0x00833603으로 구해주었다.

<br>![Image Error](./dark_stone/ppr.jpg)

<br>ppr 가젯은 0x080484f3에 있다.

<br>이제 system() 함수의 주소 값들을 스택에서 뽑아내자.

<br>![Image Error](./dark_stone/c0.jpg)

<br>c0은 이전 단계에서 교훈을 얻었으니 NULL과 가까운 0x080484d0을 사용하고, 00도 0x08048344에서 찾아주었다.

<br>![Image Error](./dark_stone/07.jpg)

<br>07은 0x0804817c에 있다.

<br>![Image Error](./dark_stone/75.jpg)

<br>마지막으로 75는 0x080482b4에 위치해있다.

<br>얻은 정보를 모두 정리해보자.

<li>strcpy@plt - 0x08048438</li><li>printf@plt - 0x08048408</li><li>printf@got - 0x0804984c</li><li>system() - 0x007507c0</li><li>"/bin/sh" - 0x00833603</li><li>PPR Gadget - 0x080484f3</li><li>c0 - 0x080484d0</li><li>07 - 0x0804817c</li><li>75 - 0x080482b4</li><li>00 - 0x08048344</li>

<br>이 정보들을 바탕으로 이전과 똑같은 페이로드를 짜주면 된다.

<br>![Image Error](./dark_stone/payload.jpg)

<br>얻은 정보들을 모두 넣고 페이로드를 구성했다. 이제 remote 서버에 접속하여 공격을 시도하자.

<br>![Image Error](./dark_stone/success.jpg)

<br>역시나 깔끔하게 공격에 성공하였다.

---

clear
=====

<br>![Image Error](./clear.jpg)

<br>여기까지가 Hacker School FC3의 과정이다. 문제 수에 비해 많은 정보를 얻고 공부 할 수 있었다.

---
