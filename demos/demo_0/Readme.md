# IORacer  
## demo_0
SFML & Box2D demonstration project.

#### Building (Ubuntu)
    1.  Install SFML library
        - sudo apt-get install libsfml-dev
    2.  Install Box2D library
        - cd [path]
        - git clone https://github.com/erincatto/Box2D.git
        - cd [path]/Box2D/Box2D
        - Open CMakeLists.txt and add line before add_subdirectory: set(CMAKE_CXX_STANDARD 11)
          This fixes nullptr error.
        - cd Build
        - cmake -DBOX2D_BUILD_EXAMPLES=OFF -DBOX2D_BUILD_SHARED=ON -DBOX2D_INSTALL=ON ..
        - make
        - sudo make install
    3.  Build demo_0
        - mkdir debug
        - cd debug
        - cmake .. && make && make install
     4. Run demo_0: 
        - ./demo_0