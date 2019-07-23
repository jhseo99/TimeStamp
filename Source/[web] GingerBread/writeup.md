# [web] GingerBread
- **출제의도**
    - base64 인코딩된 customer cookie를 baker의 쿠키로 변조하여 GingerBread를 제작한다. 

---

## 풀이과정  

메인 페이지에서 3개의 메뉴를 볼 수 있다.

![1st_web_gingerbread_01.png](/images/1st_web_gingerbread_01.PNG)

people 메뉴에서는 빵집에 있는 사람들을 볼 수 있다.

![1st_web_gingerbread_02.png](/images/1st_web_gingerbread_02.PNG)

bread 메뉴는 buy, bake, exit 중에서 선택 할 수 있다. 

![1st_web_gingerbread_03.png](/images/1st_web_gingerbread_03.PNG)

buy를 선택하면 gingerbread를 샀다는 문구를 볼 수 있다. bake를 선택하면 baker가 아니라서 살 수 없다고 나온다. 
exit은 다시 메인으로 돌아간다.

![1st_web_gingerbread_04.png](/images/1st_web_gingerbread_04.PNG)

![1st_web_gingerbread_05.png](/images/1st_web_gingerbread_05.PNG)


쿠키를 확인해보면 base64로 encode된 쿠키가 있다.

decode하면 customer가 나온다.

![1st_web_gingerbread_06.png](/images/1st_web_gingerbread_06.PNG)

baker를 base64로 encode하여 쿠키를 변조해준다.

![1st_web_gingerbread_07.png](/images/1st_web_gingerbread_07.PNG)

그리고 bake를 누르면 flag를 얻을 수 있다.

![1st_web_gingerbread_08.png](/images/1st_web_gingerbread_08.PNG)

해당문제 flag 내용은 `flag{giNg3R_is_N0t_de1iciouS_But_giNg3r_Bread_is_Yummy_yuMMy}` 이다.
