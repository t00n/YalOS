#include "string.h"

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

int strdiff(const char* s1, const char* s2)
{
	int diff = 0;
	int len = strlen(s1);
	int len2 = strlen(s2);
	if (len2 < len)
	{
		int tmp = len;
		len = len2;
		len2 = tmp;
	}
	for (int i = 0; i < len; ++i)
	{
		if (s1[i] != s2[i])
		{
			++diff;
		}
	}
	diff += len2-len;
	return diff;
}

int strcmp(const char* s1, const char* s2)
{
	int i;
	for (i = 0; s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i]; ++i)
	{}
	if (s1[i] == s2[i]) // s1=s2
	{
		return 0;
	}
	++i;
	if (s2[i] >= s1[i])
	{
		i = -i-1;
	}
	return i;
}

char** strsplit(const char* s, char limit)
{
	int count = 0;
	char** ret = malloc(sizeof(char*)*10);
	char* storage = malloc(sizeof(char)*10);
	int storage_i = 0;
	int len = strlen(s);
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == limit)
		{
			if (strlen(storage) > 0)
			{
				ret[count] = storage;
				++count;
				storage = malloc(sizeof(char)*10);
				storage_i = 0;
			}
		}
		else
		{
			storage[storage_i] = s[i];
			++storage_i;
		}
	}
	ret[count] = 0;
	return ret;
}
