#include "Find.h"

// Функция формирования таблицы суффиксов
std::vector<int> prefix_func(const std::string& s)
{
	std::vector<int> p(s.length());

	int k = 0;
	p[0] = 0;
	for (int i = 1; i < s.length(); ++i) {
		while (k > 0 && s[k] != s[i]) {
			k = p[k - 1];
		}
		if (s[k] == s[i]) {
			++k;
		}
		p[i] = k;
	}
	return p;
}

int FindStr(std::string& s, std::string& t, int &shif)
{
	// s - Исходная строка
	// t - Искомая подстрока
	// shif - внешняя переменная для получения количества смещений
	if (s.length() < t.length()) {
		return -1;
	}

	if (!t.length()) {
		return s.length(); 
	}

	typedef std::unordered_map<char, int> TStopTable;
	typedef std::unordered_map<int, int> TSufficsTable;

	// Таблица стоп символом необходимая для реализации эвристики стоп-символа
	TStopTable stop_table;
	// Таблица стоп символом необходимая для реализации эвристики совпавшего суффикса
	TSufficsTable suffics_table;

	// формирование таблицы стоп-символов
	for (int i = 0; i < t.length(); ++i) {
		stop_table[t[i]] = i;
	}

	// формирование суффиксной таблицы
	std::string rt(t.rbegin(), t.rend());
	std::vector<int> p = prefix_func(t), pr = prefix_func(rt);
	for (int i = 0; i < t.length() + 1; ++i) {
		suffics_table[i] = t.length() - p.back();
	}
	for (int i = 1; i < t.length(); ++i) {
		int j = pr[i];
		suffics_table[j] = std::min(suffics_table[j], i - pr[i] + 1);
	}

	// Основной этап поиска
	for (int shift = 0; shift <= s.length() - t.length();) {
		int pos = t.length() - 1;
		int sum_pos_shift = pos + shift;

		// Проверка на совпадение последнего символа подстроки с соответсвующим ему по индексу символом 
		while (t[pos] == s[pos + shift]) {
			// По-символьная проверка на соответсвие искомой подстроки с найденой 
			if (pos == 0) {
				// sum_pos_shift  - позиция последнего символа искомой подстроки
					
				shif = shift;
				return sum_pos_shift;
			}
			--pos;
		}

		// Если не равны последний символ подстроки и соответсвующий ему по индексу символ, то 
		// начинает работать правило стоп-символа
		if (pos == t.length() - 1) {
			TStopTable::const_iterator stop_symbol = stop_table.find(s[pos + shift]);
			int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
			shift += stop_symbol_additional;
		}
		// Если последний или несколько последующих за ним символов подстроки равны соответсвующим им по индексу символам
		// основной строки, то начинает работать правило "хорошего" суффикса
		else {
			shift += suffics_table[t.length() - pos - 1];
		}
	}
	
	return -1;
}
