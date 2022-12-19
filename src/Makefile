# Определение операционной системы, имена программ и параметров
UNAME = $(shell uname -s)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
GCOVFLAGS:=--coverage
# macOS
ifeq ($(UNAME),Darwin)
	CHECK=-lcheck -lm -lpthread -fprofile-arcs
	OPEN = open
	MEMORY_TEST = leaks
# Ubuntu
else ifneq (,$(wildcard /etc/lsb-release))
	CHECK=-lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs
	OPEN = xdg-open
	MEMORY_TEST = valgrind
# Other linux
else ifeq ($(UNAME),Linux)
	CHECK=-lcheck -lm -lpthread -lrt -fprofile-arcs
	OPEN = xdg-open
	MEMORY_TEST = valgrind
endif

# Пути до используемых папок
OBJ_DIR = obj
TEST_DIR = tests
REPORT_DIR = report

# Списки различных файлов
SOURCES:= s21_*.c
TESTS:= $(TEST_DIR)/test*.c
LIB = s21_matrix.a

# Указываем список каталогов, в которых make выполняет поиск
vpath %.c $(SOURCES) : $(TESTS)
vpath %.o $(OBJ_DIR)

# ЦЕЛИ СБОРКИ

# Цель по-умолчанию: проверка стилей, запуск тестов, отчет и библиотека
all: style test gcov_report $(LIB)

# Запуск всех проверок
check: style cppcheck $(MEMORY_TEST)

# Проверка на Google-style
style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	rm .clang-format

# Автоматическое форматирование по Google-style
format:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c *.h
	rm .clang-format

# Проверка статическим анализатором кода
cppcheck:
	cppcheck *.c *.h
	
# Расширенная проверка статическим анализатором кода
cppcheck_all:
	cppcheck *.c *.h --enable=all

# Проверка на утечки памяти для macOS
leaks: clean test
	leaks -atExit -- ./test
	
# Проверка памяти для Linux
valgrind: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

# Сборка библиотеки для вертера без тестов и покрытия кода
s21_matrix.a: $(OBJ_DIR)
	@for f in $(SOURCES); do $(CC) $(CFLAGS) -c $$f -o $(OBJ_DIR)/$$f.o; done;
	ar rcs $(LIB) $(addprefix $(OBJ_DIR)/, s21_*.o)

# Сборка приложения для запуска тестов
test: clean $(OBJ_DIR)
	@for f in $(SOURCES); do $(CC) $(CFLAGS) -c --coverage $$f -o $(OBJ_DIR)/$$f.o; done;
	@for f in $(TESTS); do $(CC) $(CFLAGS) -c $$f -o $(OBJ_DIR)/$$f.o; done;
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/s21_*.o $(OBJ_DIR)/$(TEST_DIR)/test*.o $(CHECK)
	./$@

# Подготовка отчетов через gcovr
gcov_report: test $(REPORT_DIR)
	gcovr -r . --html --html-details -o $(REPORT_DIR)/report.html
	$(OPEN) $(REPORT_DIR)/report.html

# Подготовка докера для его работы на goinfre
init_docker:
	rm -rf ~/Library/Containers/com.docker.docker
	mkdir -p ~/goinfre/Docker/Data
	ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker

# Запуск мини-вертера (проверка на стили и корректность сборки Makefile)
docker: $(LIB)
	cd ../materials/build && sh run.sh

# Запуск докера с тестами и valgrind
docker_test: clean
	cd docker && sh run.sh

# Пересборка проекта (при этом не изменившиеся модули не пересобираются)
rebuild:
	make -B

# Создание временной папки для .o-файлов
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(TEST_DIR)

# Создание временной папки для отчетов
$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)

# Удаление временных файлов и папок
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f test
	rm -f *.a
	rm -f *.o
	rm -f $(TEST_DIR)/*.o
	rm -f *.gc*
	rm -f *.log

 # Перечисление целей, которые не являются названиями файлов
.PHONY: all check style cppcheck cppcheck_all leaks format valgrind s21_verter test gcov_report init_docker docker docker_test rebuild clean
