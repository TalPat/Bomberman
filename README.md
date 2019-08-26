# Bomberman
3D adaption of the classic bomberman game
https://www.retrogames.cz/play_085-NES.php?emulator=js

This is currenly a POC branch for using conan.

### Pre-Install
This requires the c++ package manager conan and cmake. These are the install instructions I found the most convient. If you you like please visit https://conan.io/ for more information.

Please follow your platform specific instructions for installing cmake

#### Linux

```pip install conan```

#### OSX

```brew install conan```

#### Add remote repo
This will add the repo where sfml lives.

```conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```

### Install

```make```

### Running the Game

In the root of the project
```make run```
