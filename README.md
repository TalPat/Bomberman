# Bomberman
3D adaption of the classic bomberman game
https://www.retrogames.cz/play_085-NES.php?emulator=js

This is currenly a POC branch for using conan.

### Pre-Install

#### Linux

```pip install conan```

#### OSX

```brew install conan```


### Install

```cd {BOMBERMAN_ROOT}```
```mkdir build && cd build```
```conan install ..```
```cmake ..```
```make```


### Running the Game

```./{BOMBERMAN_ROOT}/build/app/bomberman```
