#include "Find.h"

// ������� ������������ ������� ���������
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
	// s - �������� ������
	// t - ������� ���������
	// shif - ������� ���������� ��� ��������� ���������� ��������
	if (s.length() < t.length()) {
		return -1;
	}

	if (!t.length()) {
		return s.length(); 
	}

	typedef std::unordered_map<char, int> TStopTable;
	typedef std::unordered_map<int, int> TSufficsTable;

	// ������� ���� �������� ����������� ��� ���������� ��������� ����-�������
	TStopTable stop_table;
	// ������� ���� �������� ����������� ��� ���������� ��������� ���������� ��������
	TSufficsTable suffics_table;

	// ������������ ������� ����-��������
	for (int i = 0; i < t.length(); ++i) {
		stop_table[t[i]] = i;
	}

	// ������������ ���������� �������
	std::string rt(t.rbegin(), t.rend());
	std::vector<int> p = prefix_func(t), pr = prefix_func(rt);
	for (int i = 0; i < t.length() + 1; ++i) {
		suffics_table[i] = t.length() - p.back();
	}
	for (int i = 1; i < t.length(); ++i) {
		int j = pr[i];
		suffics_table[j] = std::min(suffics_table[j], i - pr[i] + 1);
	}

	// �������� ���� ������
	for (int shift = 0; shift <= s.length() - t.length();) {
		int pos = t.length() - 1;
		int sum_pos_shift = pos + shift;

		// �������� �� ���������� ���������� ������� ��������� � �������������� ��� �� ������� �������� 
		while (t[pos] == s[pos + shift]) {
			// ��-���������� �������� �� ����������� ������� ��������� � �������� 
			if (pos == 0) {
				// sum_pos_shift  - ������� ���������� ������� ������� ���������
					
				shif = shift;
				return sum_pos_shift;
			}
			--pos;
		}

		// ���� �� ����� ��������� ������ ��������� � �������������� ��� �� ������� ������, �� 
		// �������� �������� ������� ����-�������
		if (pos == t.length() - 1) {
			TStopTable::const_iterator stop_symbol = stop_table.find(s[pos + shift]);
			int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
			shift += stop_symbol_additional;
		}
		// ���� ��������� ��� ��������� ����������� �� ��� �������� ��������� ����� �������������� �� �� ������� ��������
		// �������� ������, �� �������� �������� ������� "��������" ��������
		else {
			shift += suffics_table[t.length() - pos - 1];
		}
	}
	
	return -1;
}
