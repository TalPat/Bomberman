# Bomberman
3D adaption of the classic bomberman game
https://www.retrogames.cz/play_085-NES.php?emulator=js

This is currenly a POC branch for using conan.

### Pre-Install
This requires the c++ package manager conan. These are the install instructions I found the most convient. If you you like please visit https://conan.io/ for more information.

#### Linux

```pip install conan```

#### OSX

```brew install conan```

#### Add remote repo
This will add the repo where sfml lives.
```conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```

### Install

```cd {BOMBERMAN_ROOT}```
```mkdir build && cd build```
```conan install ..```
```cmake ..```
```make```


### Running the Game

```./{BOMBERMAN_ROOT}/build/app/bomberman```
