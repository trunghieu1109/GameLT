**XQuest**

This is a game created in 2 months for Advanced Programming Major Assignment using C++ and SDL2. It's the first time I created a game, so please leave your thoughs and I will learn from them.
In this game, the character need collecting the diamond, combat against all the boss.s

**Demo**

![Imgur](https://i.imgur.com/i7f4DND.png)

**Game Scece**

![Imgur](https://i.imgur.com/VggNEMq.png)

![Imgur](https://i.imgur.com/LDrTV7I.png)


**Prerequisites**

After downloading this file, ensure you meet the following requirements:
* You have installed C++11 or more.
* You have installed SDL2 and some extend libraries: SDL_image, SDL_ttf and SDL_mixer.
* Your computer should be 64 bits.

If you can't install SDL2, SDL_image or other extend libraries, you can refer some videos:
* https://www.youtube.com/watch?v=DoRyZaFZekQ&ab_channel=Tr%E1%BA%A7nTh%E1%BB%8BMinhCh%C3%A2u
* https://www.youtube.com/watch?v=kxi0TMXEG3g&ab_channel=Tr%E1%BA%A7nTh%E1%BB%8BMinhCh%C3%A2u

**How to run/compile this game ?**

After you install everything in Prerequisites, execute the following command in the project's directory: 
* g++ -c head/*.cpp -std=c++14 -O3 -Wall -m64 -I include -ID:\NewSDL\SDL2_ttf\x86_64-w64-mingw32\include\SDL2 -ID:\NewSDL\SDL2_mixer\x86_64-w64-mingw32\include\SDL2 -ID:\NewSDL\SDL2_image\x86_64-w64-mingw32\include\SDL2 -ID:\NewSDL\SDL2\x86_64-w64-mingw32\include\SDL2 && g++ obj/Release/head/*.o -o Run -s -L D:\NewSDL\SDL2\x86_64-w64-mingw32\lib -L D:\NewSDL\SDL2_image\x86_64-w64-mingw32\lib -L D:\NewSDL\SDL2_mixer\x86_64-w64-mingw32\lib -L D:\NewSDL\SDL2_ttf\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && start Run
- Another way is clicking to file [XQuest.exe] directly.

**How to use it ?**

- To play this game in perfect way, you need to focus on this instruction:
* Press [LEFT_ARROW] to move left.
* Press [RIGHT_ARROW] to move right.
* Press [v] to jump. If you hold that button, the character will jump higher.
* Press [c] to shot. If you hold that button more than 1s, the character will shot a powerful energy ball.
* Press [x] to dash. If you hold that button, the character will dash farther.
* Press [z] to dash with damage. The character will be covered with energy and cause damage to surrounding enemies. This skill is
* Press [o] to dash in lava. Press[UP_ARROW/DOWN_ARROW] to adjust the sliding angle.
* Press [p] to pause game. Press [p] again to continue game.
* Press [X] to quit and save game.
* In this game, you default health is 150. You must find the heart in the map to increase your max health. 1 heart = 20 health.
* When you have max health, if you collect the health diamond, you can store health in a equipment. But you must find it so you can store your health. Mana is the similar to health. You can use these equipments by pausing the game and clicking to button with healthStoreIcon and manaStoreIcon.
* Your mission is collecting the point diamonds, more than 60% of total point diamonds, so combating against the boss and going to next round by passing through the portal.

**Member**
* Nguyen Trung Hieu

**Source Texture & Mix**

* https://www.spriters-resource.com/
* https://www.sounds-resource.com/ 






