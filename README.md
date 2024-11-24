# SpaceStation

## Описание

Добро пожаловать в проект SpaceStation! Этот проект на языке программирования C++ с использованием CMake, Google Test.

## Проверка необходимых утилит
- **cmake** - для автоматизации сборки
- **ninja** - генератор

Установите **ninja**, используя команды:

На Ubuntu/Debian:
```
sudo apt update
sudo apt install ninja-build
```
На macOS:
```
brew install ninja
```
или подходящие для вашей системы.

- **g++/clang** - компилятор

### Необязательные:
- **clang-tidy**

На Ubuntu/Debian:
```
sudo apt update
sudo apt install clang-tidy
```
На MacOS:
```
brew install llvm
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

- **clang-format**

На Ubuntu/Debian:
```
sudo apt update
sudo apt install clang-format
```
На MacOS:
```
brew install clang-format
```

## Сборка и запуск

1. Перейдите в корневую директорию проекта (по умолчанию SpaceStation)
   ```
   cd SpaceStation/
   ```

2. Сконфигурируйте проект:
   ```
   cmake --preset release
   ```

3. Запустите сборку приложения:
   ```
   cmake --build --preset release
   ```
   и тестов:
   ```
   cmake --build --preset test
   ```

4. Запустите сервер и клиента в разных окнах терминала:
   ```
   ./build/release/bin/server
   ```
   ```
   ./build/release/bin/client
   ```


5. Запустите тесты:
   ```
   ./build/release/bin/test_lib
   ```
   ```
   ctest --preset test
   ```

## Настройка форматирования

Проект использует [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) для автоматического форматирования кода. Конфигурация форматирования находится в файле .clang-format.

## Структура проекта

```
SpaceStation/
├── build/                        # Папка для файлов сборки
├── external/                     # Подмодули и сторонние библиотеки
│   ├── CMakeLists.txt            # CMakeLists для сборки
│   └── gtest/                    # Подмодуль Google Test
│       └── CMakeLists.txt        # CMakeLists для сборки библиотеки
├── include/                      # Заголовочные файлы проекта
│   └── libspace/                 # Папка для библиотеки
│       └── libspace.hpp          # Заголовочный файл
├── src/                          # Исходные файлы проекта
│   ├── app/                      # Папка исходных файлов для программы
│   │   ├── CMakeLists.txt        # CMakeLists для сборки
│   │   ├── server.cc             # Исходный файл части сервера
│   │   └── client.cc             # Исходный файл части клиента
│   ├── libspace/                 # Папка исходных файлов для программы
│   │   ├── CMakeLists.txt        # CMakeLists для сборки
│   │   ├── spacemodule.cc        # Исходный файл библиотеки
│   │   └── spacestation.cc       # Исходный файл библиотеки
│   └── CMakeLists.txt            # CMakeLists для сборки
├── tests/                        # Тестовые файлы проекта
│   ├── CMakeLists.txt            # CMakeLists для сборки библиотеки
│   └── test.cc                   # Тестовый файл
├── CMakeLists.txt                # Основной файл CMake
├── CMakePresets.json             # Пресеты для CMake
├── .clang-format                 # Файл конфигурации ClangFormat
├── .gitignore                    # Файл git ignore
├── README_ENG.md                 # Версия README.md на английском
└── README.md                     # Этот файл
```

