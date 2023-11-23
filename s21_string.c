#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index)
{
  char *res = NULL;
  if (src && str && s21_strlen(src) >= start_index)
  {
    res = malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (res)
    {
      s21_strncpy(res, src, start_index);
      *(res + start_index) = '\0';
      s21_strcat(res, str);
      s21_strcat(res, src + start_index);
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n)
{
  s21_size_t i = 0;
  char *char_dest = (char *)dest;
  char *char_src = (char *)src;
  for (i = 0; i < n; i++)
  {
    char_dest[i] = char_src[i];
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n)
{
  char *pd = (char *)dest;
  const char *ps = (const char *)src;
  if (dest < src)
  {
    while (n-- > 0)
    {
      *pd++ = *ps++;
    }
  }
  else
  {
    pd = pd + n;
    ps = ps + n;
    while (n-- > 0)
    {
      *--pd = *--ps;
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n)
{
  unsigned char *p = str;
  while (n > 0)
  {
    *p = c;
    p++;
    n--;
  }
  return (str);
}

char *s21_strcat(char *dest, const char *src)
{
  char *flag;
  char *start = dest;
  while (*start != '\0')
  {
    start++;
  }
  while (*src != '\0')
  {
    *start++ = *src++;
  }
  *start = '\0';
  flag = dest;
  return flag;
}

char *s21_strchr(const char *str, int c)
{
  char *s = (char *)str;
  unsigned char b = (char)c;
  char *res;
  while (*s != '\0' &&
         *s != b)
  { // проходимся по строке до конца или до первого вхождения
    s++;
  }
  if (*s == '\0' && b != '\0')
  { // если не нашли - нулл
    res = s21_NULL;
  }
  else
  {
    res = s; // если нашли возвращаем указатель
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2)
{
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  int res = 1;
  while (*s1 == *s2)
  {
    if (*s1 == '\0')
    {
      res = 0;
      break;
    }
    ++s1;
    ++s2;
  }
  if (res != 0)
  {
    res = *s1 - *s2;
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src)
{
  char *flag;
  int i = 0;
  while (src[i] != '\0')
  {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  flag = dest;
  return flag;
}

s21_size_t s21_strcspn(const char *str1, const char *str2)
{
  s21_size_t i = 0;
  while (str1[i] && !s21_strchr(str2, str1[i]))
    i++;
  return i;
}

char *s21_strerror(int errnum)
{
  char *ERRORS[] = ERR_LIST;
  char *error = s21_NULL;
  static char buf[100];
  if (errnum >= 0 && errnum < N)
  {
    error = ERRORS[errnum];
  }
  else
  {
    if (std == 0)
    {
      char *undef = "Unknown error ";
      s21_sprintf(buf, "%s%d", undef, errnum);
    }
    else if (std == 1)
    {
      char *undef = "Unknown error: ";
      s21_sprintf(buf, "%s%d", undef, errnum);
    }
  }
  return error == s21_NULL ? buf : error;
}

s21_size_t s21_strlen(const char *str)
{
  s21_size_t size = 0;
  while (str[size])
  {         // пока индекс строки действителен
    ++size; // увеличиваем счетчик размера
  }
  return size; // возвращаем размер
}

char *s21_strncat(char *dest, const char *src, s21_size_t count)
{
  char *p = dest + s21_strlen(dest);
  while (*src != '\0' && count--)
  {
    *p++ = *src++;
  }
  *p = '\0';
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n)
{
  int flag = 0;
  while (n--)
  {
    if (*str1 != *str2)
    {
      flag = *str1 - *str2;
    }
    else
    {
      ++str1;
      ++str2;
    }
  }
  return flag;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n)
{
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++)
  {
    dest[i] = src[i];
  }
  while (i < n)
  {
    dest[i] = '\0';
    i++;
  }
  return dest;
}

char *s21_strpbrk(const char *str1, const char *str2)
{
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  int size = s21_strlen(str2);
  int flag = 1;
  char *res = s21_NULL;
  while (*s1 != '\0' && flag == 1)
  {
    for (int i = 0; size > i && flag == 1; i++)
    {
      if (*s1 == s2[i])
      {
        flag = 0;
        res = s1;
      }
    }
    s1++;
  }
  return res;
}

char *s21_strrchr(const char *str, int c)
{
  const char *res = s21_NULL;
  if (str != s21_NULL)
  {
    do
    {
      if (*str == (char)c)
      {
        res = str;
      }
    } while (*str++);
  }
  return (char *)res;
}

s21_size_t s21_strspn(const char *str1, const char *str2)
{
  s21_size_t i = 0;
  while (str1[i] && s21_strchr(str2, str1[i]))
    i++;
  return i;
}

char *s21_strstr(const char *haystack, const char *needle)
{
  char *p = (char *)haystack;
  int size = s21_strlen(needle);
  int flag = 1;
  char *res = s21_NULL;
  while (*p != '\0' && flag == 1)
  {
    if (s21_strncmp(p, needle, size) == 0)
    {
      flag = 0;
      res = p;
    }
    else
    {
      p++;
    }
  }
  return res;
}

char *s21_strtok(char *str, const char *delim)
{
  static char *result = s21_NULL;
  if (str)
  {
    result = str;
    while (*result && s21_strchr(delim, *result))
      *result++ = '\0';
  }
  if (result != NULL)
  {
    if (*result != '\0')
    {
      str = result;
      while (*result && !s21_strchr(delim, *result))
        ++result;
      while (*result && s21_strchr(delim, *result))
        *result++ = '\0';
    }
    else
    {
      str = s21_NULL;
    }
  }
  else
  {
    str = s21_NULL;
  }
  return str;
}

void *s21_to_lower(const char *str)
{
  char *res = NULL;
  if (str)
  {
    res = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (res)
    {
      s21_strcpy(res, str);
      for (char *tmp_str = res; *tmp_str; tmp_str++)
      {
        if (*tmp_str >= 'A' && *tmp_str <= 'Z')
        {
          *tmp_str += 32;
        }
      }
    }
  }
  return res;
}

void *s21_to_upper(const char *str)
{
  char *res = NULL;
  if (str)
  {
    res = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (res != NULL)
    {
      s21_strcpy(res, str);
      for (char *tmp_str = res; *tmp_str; tmp_str++)
      {
        if (*tmp_str >= 'a' && *tmp_str <= 'z')
        {
          *tmp_str -= 32;
        }
      }
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars)
{
  char *res = NULL;
  if (src && trim_chars)
  {
    char *ptr_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++)
      ;
    for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
         end_str--)
      ;
    res = (char *)malloc((end_str - ptr_str + 1) * sizeof(char));
    if (res)
    {
      s21_strncpy(res, ptr_str, end_str - ptr_str);
      *(res + (end_str - ptr_str)) = '\0';
    }
  }
  return res;
}
