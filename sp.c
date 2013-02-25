#include <stdio.h>
#include <string.h>

#define cSep ',' //�ö�����Ϊһ���ַ������еķָ�������ÿ����֧��\,��ת��
#define _MAX_FILTER_KEYWORDS_COUNT 50 //����һ���ַ��������50���У���
#define _MAX_SEGMENT_LENGTH   512     //ÿ���ֶ������512���ֽڡ��������ֶ���

#define CRLF "\n"


int split_line(const char *str, char segs[_MAX_FILTER_KEYWORDS_COUNT][_MAX_SEGMENT_LENGTH]) {
	char *p = (char *)str;
	int i = 0, j = 0, k = 0;
	int escape = 0;

	if(!str)
		return 0;

	memset(segs, 0, _MAX_FILTER_KEYWORDS_COUNT*_MAX_SEGMENT_LENGTH);
	for(; i < _MAX_FILTER_KEYWORDS_COUNT && *p; p ++) {
		switch(*p) {
			case cSep:
				if(escape) {
					escape = 0;
					if(j < _MAX_SEGMENT_LENGTH - 2) {
						segs[i][j++] = '\\';
						segs[i][j++] = cSep;
					}
				}
				else {
					j = 0;
					i ++;
				}
				break;

			case '\\':
				if (escape) {
					escape = 0;
					if(j < _MAX_SEGMENT_LENGTH - 2) {
						segs[i][j++] = '\\';
						segs[i][j++] = '\\';
					}
				}
				else {
					escape = 1;
				}
				break;

			default:
				if(escape)
					escape  = 0;

				if(j < _MAX_SEGMENT_LENGTH - 1)
					segs[i][j++] = *p;

				break;
		}
	}

	return i + 1;
}

void print_segs(const char *line, const char *segs[_MAX_SEGMENT_LENGTH], int length) {
	int i = 0;
	char *p = (char *)segs;

	printf("split %s: %s", line, CRLF);
	for(; i < length; i ++) {
		printf("SEG %d: %s%s", i, p, CRLF);
		p += _MAX_SEGMENT_LENGTH;
	}
	printf("Total segs: %d%s%s", length, CRLF, CRLF);
}

void test_split_line(const char *line) {
	char segs[_MAX_FILTER_KEYWORDS_COUNT][_MAX_SEGMENT_LENGTH];
	int count;

	count = split_line(line, segs);
	print_segs(line, (const char **)segs, count);
}

void testcase() {
	char tests[][1024] = {  "123422,3gnet,www.baidu.com,/news.html",
							"123433, 3gnet, www\\,.sina.com, /sports.html",
							"12345323,cmnet\\,\\\\,\\,,\\\\\\\\\abcd",
							",,,",
							"\\,,\\,,\\,,",
							"\\\\,\\\\,\\\\,\\\\",
							"1234394,cmwap, u.cn, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaajjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkkkkkkkkkkkkkkkkkssssssssssssssssssssssssssssfffffffffffffffeeeeeeeeeeeeeeeeeeeewwwwwwwwwwwwwwwddddddddddddddddddddddddddddddddddddwwwnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
							""
							};

	char *line;

	line = tests[0];

	while(*line) {
		test_split_line((const char * )line);
		line += 1024;
	}
}

int main(int argc, char *argv[]) {

	testcase();

	return 0;
}


