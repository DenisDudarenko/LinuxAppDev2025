# numberstat

Учебный проект (Linux Application Development): библиотека + утилита, локализация, unit-тесты, manpage, Doxygen, install/uninstall.
Программа numberstat показывает число в виде римскиого, двоичного и других представлений. При передаче определенного флага она выводит только ответ выбранного формата

## Сборка
```bash
cmake -S . -B build
cmake --build build
```

## Запуск
После сборки (без установки):
```bash
./build/src/numberstat 12
```

После установки в /tmp/qq:
```bash
/tmp/qq/bin/numberstat 12
```

## Тесты
```bash
cmake --build build --target run_tests
```

## Документация (Doxygen)
После сборки (если установлен doxygen):
- `build/doc/html/index.html`

## Manpage
После установки:
```bash
man numberstat
```

## Установка без root (в /tmp/qq)
```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/tmp/qq
cmake --build build
cmake --install build
MANPATH=/tmp/qq/share/man man numberstat
```

## Установка в систему (root)
```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build
su -c "cmake --install build"
man numberstat
```

## Деинсталляция
```bash
cmake --build build --target uninstall
```

## Локали
```bash
LANG=ru_RU.UTF-8 numberstat 12
LANG=C numberstat 12
```
