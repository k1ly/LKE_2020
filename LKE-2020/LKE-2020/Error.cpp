#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "|SYSTEM| Недопустимый код ошибки"),
		ERROR_ENTRY(1, "|SYSTEM| Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY(10, "|SYSTEM| Параметр -in должен быть задан"),
		ERROR_ENTRY(11, "|SYSTEM| Превышена длина параметра -in"),
		ERROR_ENTRY(12, "|SYSTEM| Ошибка при создании файла протокола"),
		ERROR_ENTRY(13, "|SYSTEM| Ошибка при открытии исходного кода"),
		ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15), ERROR_ENTRY_NODEF(16),
		ERROR_ENTRY_NODEF(17), ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),

		ERROR_ENTRY(20, "|SYSTEM| Ошибка при создании выходного файла"),
		ERROR_ENTRY(21, "|SYSTEM| Превышен допустимый размер таблицы лексем"),
		ERROR_ENTRY(22, "|SYSTEM| Превышен допустимый размер таблицы идентификаторов"),
		ERROR_ENTRY(23, "|SYSTEM| Лексема не найдена в таблице"),
		ERROR_ENTRY(24, "|SYSTEM| Идентификатор не найден в таблице"),
		ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26), ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "|Lexical| Недопустимый символ в исходном коде"),
		ERROR_ENTRY(101, "|Lexical| Недопустимый символ в строковом литерале"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "|Lexical| Лексема не найдена"),
		ERROR_ENTRY(111, "|Lexical| Превышена длина строкового литерала"),
		ERROR_ENTRY(112, "|Semantic| Дублирование функции main"),
		ERROR_ENTRY(113, "|Semantic| Требуется объявление функции main"),
		ERROR_ENTRY(114, "|Semantic| Неверно задана директива"),
		ERROR_ENTRY(115, "|Semantic| Повторное использование директивы"),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120, "|Semantic| Объявление вложенной функции"),
		ERROR_ENTRY(121, "|Semantic| Требуется объявление функции"),
		ERROR_ENTRY(122, "|Semantic| Использование вложенного цикла недопустимо"),
		ERROR_ENTRY(123, "|Lexical| Переменная не объявлена"),
		ERROR_ENTRY(124, "|Lexical| Неверно задан тип данных"),
		ERROR_ENTRY(125, "|Lexical| Неверно объявлена функция"),
		ERROR_ENTRY(126, "|Semantic| Повторное объявление переменной"),
		ERROR_ENTRY(127, "|Semantic| Повторное объявление функции"),
		ERROR_ENTRY(128, "|Semantic| Некорректно задан размер массива"),
		ERROR_ENTRY(129, "|Semantic| Требуется объявление массива"),

		ERROR_ENTRY(130, "|Lexical| Превышено допустимое целочисленное значение"),
		ERROR_ENTRY(131, "|Lexical| Слишком много значений инициализатора"),
		ERROR_ENTRY(132, "|Lexical| Неверная инициализация массива"),
		ERROR_ENTRY(133, "|Semantic| Размер массива должен иметь целочисленный тип"),
		ERROR_ENTRY(134, "|Semantic| Требуется имя файла"),
		ERROR_ENTRY(135, "|Semantic| Неверное использование имени файла"),
		ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200, "|Syntax| Неверная структура программы"),
		ERROR_ENTRY(201, "|Syntax| Ошибка в инструкции языка"),
		ERROR_ENTRY(202, "|Syntax| Ошибка в условном блоке"),
		ERROR_ENTRY(203, "|Syntax| Ошибка в условной инструкции"),
		ERROR_ENTRY(204, "|Syntax| Ошибка в операндах"),
		ERROR_ENTRY(205, "|Syntax| Ошибка в арифметической операции"),
		ERROR_ENTRY(206, "|Syntax| Ошибка в операции сравнения"),
		ERROR_ENTRY(207, "|Syntax| Ошибка в параметрах функции"),
		ERROR_ENTRY(208, "|Syntax| Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),

		ERROR_ENTRY(300, "|Semantic| Несовпадение типов операндов"),
		ERROR_ENTRY(301, "|Semantic| Присваивание недопустимого типа"),
		ERROR_ENTRY(302, "|Semantic| Несовпадение типов параметров функции"),
		ERROR_ENTRY(303, "|Semantic| Несовпадение количества параметров функции"),
		ERROR_ENTRY(304, "|Semantic| Тип возвращаемого значения не соответствует типу функции"),
		ERROR_ENTRY(305, "|Semantic| Не удается открыть файл"),
		ERROR_ENTRY(306, "|Semantic| Требуется подключение стандартной библиотеки"),
		ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308), ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500), ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR* e = new ERROR;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			*e = errors[0];
		else
			*e = errors[id];
		return *e;
	}
	ERROR geterrorpos(int id, int line, int col)
	{
		ERROR* e = new ERROR;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			*e = errors[0];
		else
		{
			*e = errors[id];
			e->inext.line = line;
			e->inext.col = col;
		}
		return *e;
	}
}