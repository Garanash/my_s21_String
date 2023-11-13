#include "s21_string.h"

void write_percent(char *str, int *n, struct_format form);

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "");
  setlocale(LC_ALL, "en_US.UTF-8");
  int n = 0;
  struct_format form;
  va_list arg;
  va_start(arg, format);
  int format_length = s21_strlen(format);
  for (int i = 0; i < format_length; i++) {
    if (format[i] == '%') {
      form.minus = -1;
      form.plus = -1;
      form.space = -1;
      form.width = -1;
      form.accuracy = -1;
      form.accuracy_length = -1;
      form.length_h = -1;
      form.length_l = -1;
      form.zero = -1;
      int flag = 1;
      while (flag) {
        i++;
        if (format[i] == '-') {
          form.minus = 1;
        } else if (format[i] == '+') {
          form.plus = 1;
        } else if (format[i] == ' ') {
          form.space = 1;
        } else if (format[i] == '.') {
          i = i + 1;
          form.accuracy = 1;
          form.accuracy_length = length_of_accuracy_or_width(format, &i);
        } else if (format[i] == 'h') {
          form.length_h = 1;
        } else if (format[i] == 'l') {
          form.length_l = 1;
          if (format[i + 1] == 'l') {
            form.length_l = 2;
          }
        } else if (format[i] == '0' && format[i - 1] != '-') {
          form.zero = 1;
        } else {
          if (format[i] >= '0' && format[i] <= '9') {
            form.width = length_of_accuracy_or_width(format, &i);
          } else {
            flag = 0;
          }
        }
      }
      form.specifier = format[i];
      check_specificator(str, &n, form, arg);
    } else {
      str[n] = format[i];
      n++;
    }
  }
  str[n] = '\0';
  va_end(arg);
  return n;
}

int length_of_accuracy_or_width(const char *format, int *i) {
  int length = 0;
  if (format[*i] >= 48 && format[*i] <= 57) {
    length = 0;
    for (int y = 0; format[*i] >= 48 && format[*i] <= 57; y++) {
      length = (length * 10) + format[*i] - 48;
      (*i)++;
    }
  }
  (*i)--;
  return length;
}

int check_specificator(char *str, int *n, struct_format form, va_list arg) {
  if (form.specifier == 'c') {
    write_c(str, n, form, arg);
  } else if (form.specifier == 'd') {
    write_d(str, n, form, arg);
  } else if (form.specifier == 'i') {
    write_i(str, n, form, arg);
  } else if (form.specifier == 'f') {
    write_f(str, n, form, arg);
  } else if (form.specifier == 's') {
    write_s(str, n, form, arg);
  } else if (form.specifier == 'u') {
    write_u(str, n, form, arg);
  } else if (form.specifier == '%') {
    write_percent(str, n, form);
  }
  return *n;
}

void write_c(char *str, int *n, struct_format form, va_list arg) {
  if (form.length_l == 1) {
    wchar_t arg_char_l = (wchar_t)va_arg(arg, wchar_t);
    write_wide_char(str, n, form, arg_char_l);
  } else {
    char arg_char = va_arg(arg, int);
    write_char(str, n, form, arg_char);
  }
}

void write_char(char *str, int *n, struct_format form, char arg) {
  if (form.minus == -1 && form.width != -1) {
    write_space(str, n, 1, form);
  }
  str[*n] = arg;
  (*n)++;
  if (form.minus == 1 && form.width != -1) {
    write_space(str, n, 1, form);
  }
}

void write_wide_char(char *str, int *n, struct_format form, wchar_t arg) {
  char *memory = s21_NULL;
  memory = (char *)calloc(arg, sizeof(wchar_t));
  if (memory == s21_NULL) {
    exit(0);
  }
  wctomb(memory, arg);
  *(memory + s21_strlen(memory)) = '\0';
  if (form.minus == -1 && form.width != -1) {
    write_space(str, n, s21_strlen(memory), form);
  }
  int i = 0;
  while (memory[i] != '\0') {
    str[*n] = memory[i++];
    (*n)++;
  }
  if (form.minus == 1 && form.width != -1) {
    write_space(str, n, s21_strlen(memory), form);
  }
  if (memory) {
    free(memory);
  }
}

void write_d(char *str, int *n, struct_format form, va_list arg) {
  if (form.length_h == 1) {
    short int arg_d_h = (long long int)(short int)va_arg(arg, int);
    write_int(str, n, form, arg_d_h);
  } else if (form.length_l == 1) {
    long int arg_d_l = (long long int)va_arg(arg, long int);
    write_int(str, n, form, arg_d_l);
  } else if (form.length_l == 2) {
    long long int arg_d_ll = (long long int)va_arg(arg, long long int);
    write_int(str, n, form, arg_d_ll);
  } else {
    int arg_d = va_arg(arg, int);
    write_int(str, n, form, arg_d);
  }
}

void write_i(char *str, int *n, struct_format form, va_list arg) {
  if (form.length_h == 1) {
    long long int arg_i_h = (long long int)(short int)va_arg(arg, int);
    write_int(str, n, form, arg_i_h);
  } else if (form.length_l == 1) {
    long long int arg_i_l = (long long int)va_arg(arg, long int);
    write_int(str, n, form, arg_i_l);
  } else if (form.length_l == 2) {
    long long int arg_i_ll = (long long int)va_arg(arg, long long int);
    write_int(str, n, form, arg_i_ll);
  } else {
    long long int arg_i = va_arg(arg, int);
    write_int(str, n, form, arg_i);
  }
}

void write_u(char *str, int *n, struct_format form, va_list arg) {
  unsigned long long int arg_u = 0;
  if (form.length_h == 1) {
    arg_u = (unsigned long long int)(unsigned short int)va_arg(arg, int);
    write_unsigned_i(str, n, form, arg_u);
  } else if (form.length_l == 1) {
    arg_u = (unsigned long long int)va_arg(arg, unsigned long int);
    write_unsigned_i(str, n, form, arg_u);
  } else if (form.length_l == 2) {
    arg_u = (unsigned long long int)va_arg(arg, unsigned long long int);
    write_int(str, n, form, arg_u);
  } else {
    arg_u = (unsigned long long int)va_arg(arg, unsigned int);
    write_unsigned_i(str, n, form, arg_u);
  }
}

void write_f(char *str, int *n, struct_format form, va_list arg) {
  double arg_f = va_arg(arg, double);
  double temp_arg_f = arg_f;
  int length_int_kost = length_of_arg((int)round(arg_f));
  if (temp_arg_f < 0) {
    temp_arg_f = -temp_arg_f;
  }
  int length_int = length_of_arg((int)arg_f);
  if (form.accuracy_length == -1) {
    form.accuracy_length = 6;
  }
  int full_len;
  if (form.accuracy == 1 && form.accuracy_length == 0) {
    if (length_int_kost > length_int) length_int = length_int_kost;
    full_len = length_int;
  } else {
    full_len = length_int + 1 + form.accuracy_length;
  }
  char *memory_before_dot = s21_NULL;
  char *memory_after_dot = s21_NULL;
  memory_before_dot = (char *)calloc(1024, sizeof(char));
  memory_after_dot = (char *)calloc(1024, sizeof(char));
  if (memory_before_dot == s21_NULL && memory_after_dot == s21_NULL) {
    exit(0);
  }
  int sign_len = count_sign_len(form, (int)arg_f);
  if (form.minus == 1) {
    if (signbit(arg_f)) {
      str[*n] = '-';
      (*n)++;
    }
    write_sign_float(str, n, form, arg_f);
    write_fl(str, n, memory_before_dot, memory_after_dot, form, temp_arg_f);
    write_space(str, n, full_len + sign_len, form);
  } else {
    write_space(str, n, full_len + sign_len, form);
    if (signbit(arg_f)) {
      str[*n] = '-';
      (*n)++;
    }
    write_sign_float(str, n, form, arg_f);
    write_fl(str, n, memory_before_dot, memory_after_dot, form, temp_arg_f);
  }
  if (memory_before_dot && memory_after_dot) {
    free(memory_before_dot);
    free(memory_after_dot);
  }
}

void write_fl(char *str, int *n, char *mem_bef_dot, char *mem_aft_dot,
              struct_format form, double arg) {
  if (form.accuracy_length != 0) {
    arg = round_arg(form, arg);
    double num_bef_dot = 0.0;
    long double num_aft_dot = 0.0;
    double num_ceil = 0.0;
    num_aft_dot = modf(arg, &num_bef_dot);
    number_of_int(mem_bef_dot, num_bef_dot);
    int y = s21_strlen(mem_bef_dot) - 1;
    while (y >= 0) {
      str[*n] = mem_bef_dot[y--];
      (*n)++;
    }
    str[*n] = '.';
    (*n)++;
    for (int i = 0; i < form.accuracy_length; i++) {
      num_aft_dot = (num_aft_dot * 10.) + (5 * pow(10, -form.accuracy_length));
      modf(num_aft_dot, &num_ceil);
      if (i > 20) {
        num_aft_dot = num_aft_dot + (0 * pow(10, -i));
      }
      if (i == form.accuracy_length - 1) {
        num_ceil = round(num_ceil);
        mem_aft_dot[i] = num_ceil + '0';
      } else {
        mem_aft_dot[i] = num_ceil + '0';
        num_aft_dot = num_aft_dot - num_ceil;
      }
    }
    for (int i = 0; i < form.accuracy_length; i++) {
      str[*n] = mem_aft_dot[i];
      (*n)++;
    }
  } else {
    arg = round(arg);
    number_of_int(mem_bef_dot, (long long)arg);
    int x = s21_strlen(mem_bef_dot) - 1;
    while (x >= 0) {
      str[*n] = mem_bef_dot[x];
      x--;
      (*n)++;
    }
  }
}

double round_arg(struct_format form, double number) {
  double whole;
  double m = modf(number, &whole) * pow(10.0, form.accuracy_length);
  double mod = fmod(m, pow(10.0, form.accuracy_length));
  if (mod == 50) {
    m = round(m + 1) / pow(10.0, form.accuracy_length);
  } else {
    m = round(m) / pow(10.0, form.accuracy_length);
  }
  number = whole + m;
  return number;
}

void write_s(char *str, int *n, struct_format form, va_list arg) {
  if (form.length_l == 1) {
    wchar_t *arg_s_l = (wchar_t *)va_arg(arg, wchar_t *);
    if (arg_s_l == s21_NULL) {
      arg_s_l = L"(null)";
    }
    write_str_l(str, n, form, arg_s_l);
  } else {
    char *arg_s = va_arg(arg, char *);
    if (arg_s == s21_NULL) {
      arg_s = "(null)";
    }
    write_str(str, n, form, arg_s);
  }
}

void write_str(char *str, int *n, struct_format form, char *arg_s) {
  int length = s21_strlen(arg_s);
  if (form.accuracy_length != -1) {
    if (length > form.accuracy_length) {
      length = form.accuracy_length;
    }
  }
  if (form.minus == 1) {
    for (int i = 0; i < length; i++) {
      str[*n] = arg_s[i];
      (*n)++;
    }
    write_space(str, n, length, form);
  } else {
    write_space(str, n, length, form);
    for (int i = 0; i < length; i++) {
      str[*n] = arg_s[i];
      (*n)++;
    }
  }
}

void write_str_l(char *str, int *n, struct_format form, wchar_t *arg_s_l) {
  int length = len_of_wchar(arg_s_l);
  char *memory = s21_NULL;
  memory = (char *)calloc(1024, sizeof(char));
  if (memory == s21_NULL) {
    exit(0);
  }
  wcstombs(memory, arg_s_l, length * sizeof(wchar_t));
  int full_len = s21_strlen(memory);
  if (form.accuracy_length != -1) {
    if (full_len > form.accuracy_length) {
      full_len = form.accuracy_length;
    }
  }
  if (form.minus == 1) {
    for (int i = 0; i < full_len; i++) {
      str[*n] = memory[i];
      (*n)++;
    }
    write_space(str, n, full_len, form);
    str[*n] = '\0';
  } else {
    write_space(str, n, full_len, form);
    for (int i = 0; i < full_len; i++) {
      str[*n] = memory[i];
      (*n)++;
    }
    str[*n] = '\0';
  }
  if (memory) {
    free(memory);
  }
}

void write_int(char *str, int *n, struct_format form, long long arg) {
  long long tmp_arg = arg;
  if (tmp_arg < 0) {
    tmp_arg = -tmp_arg;
  }
  int len_accuracy_length = 0;
  char *memory_char = s21_NULL;
  memory_char = (char *)calloc(2000, sizeof(char));
  if (memory_char == s21_NULL) {
    exit(0);
  }
  number_of_int(memory_char, tmp_arg);
  int length = s21_strlen(memory_char);
  if (form.accuracy_length != -1 && form.accuracy_length > length) {
    len_accuracy_length = form.accuracy_length - length;
  }
  int len_sign = count_sign_len(form, arg);
  if (form.accuracy == 1 && form.accuracy_length == 0 && arg == 0 &&
      form.width != -1) {
    for (int i = 0; i < (form.width); i++) {
      str[*n] = ' ';
      (*n)++;
    }
  }
  if (arg != 0 ||
      (form.accuracy = 1 && form.accuracy_length != 0 && arg == 0)) {
    if (form.minus == 1) {
      if (arg < 0) {
        str[*n] = '-';
        (*n)++;
      }
      write_sign(str, n, form, arg);
      write_zero(str, n, length, form);
      int i = s21_strlen(memory_char) - 1;
      while (i >= 0) {
        str[*n] = memory_char[i--];
        (*n)++;
      }
      write_space(str, n, len_accuracy_length + length + len_sign, form);
    } else {
      write_space(str, n, len_accuracy_length + length + len_sign, form);
      if (arg < 0) {
        str[*n] = '-';
        (*n)++;
      }
      write_sign(str, n, form, arg);
      write_zero(str, n, length, form);
      int i = s21_strlen(memory_char) - 1;
      while (i >= 0) {
        str[*n] = memory_char[i--];
        (*n)++;
      }
    }
  }
  free(memory_char);
}

void number_of_int(char *memory_str, long long arg) {
  int i = 0;
  if (arg == LONG_MIN) {
    arg = 922337203685477580;
    memory_str[i] = '8';
    i++;
  }
  while (arg > 9) {
    memory_str[i] = (arg % 10) + 48;
    arg = arg / 10;
    i++;
  }
  memory_str[i] = (arg % 10) + 48;
}

int length_of_arg(long long num) {
  int l = 1;
  if (num < 0) {
    num = -num;
  }
  while (num > 9) {
    l++;
    num = num / 10;
  }
  return l;
}

void write_sign(char *str, int *n, struct_format form, long long arg) {
  if (form.plus == 1 && arg >= 0) {
    str[*n] = '+';
    (*n)++;
  } else {
    if (form.space == 1 && arg >= 0) {
      str[*n] = ' ';
      (*n)++;
    }
  }
}

void write_sign_float(char *str, int *n, struct_format form, long double arg) {
  if (form.plus == 1 && !signbit(arg)) {
    str[*n] = '+';
    (*n)++;
  } else {
    if (form.space == 1 && !signbit(arg)) {
      str[*n] = ' ';
      (*n)++;
    }
  }
}

void write_zero(char *str, int *n, int len, struct_format form) {
  for (int i = 0; i < (form.accuracy_length - len); i++) {
    str[*n] = '0';
    (*n)++;
  }
}

int count_sign_len(struct_format form, long long arg) {
  int sign_len = 0;
  if ((form.space == 1 && arg >= 0) || (form.plus == 1 && arg >= 0) ||
      arg < 0) {
    if (form.width != -1) {
      sign_len = 1;
    }
  }
  return sign_len;
}

void write_space(char *str, int *n, int length, struct_format form) {
  if (form.zero == 1 && form.accuracy_length == -1) {
    for (int i = 0; i < (form.width - length); i++) {
      str[*n] = '0';
      (*n)++;
    }
  } else {
    for (int i = 0; i < (form.width - length); i++) {
      str[*n] = ' ';
      (*n)++;
    }
  }
}

void write_unsigned_i(char *str, int *n, struct_format form,
                      unsigned long long arg) {
  char *memory_char = s21_NULL;
  memory_char = (char *)calloc(1024, sizeof(char));
  if (memory_char == s21_NULL) {
    exit(0);
  }
  unsigned_num(memory_char, (unsigned long long)arg);
  int length = s21_strlen(memory_char);
  int len_accuracy_length = 0;
  if (form.accuracy_length != -1 && form.accuracy_length > length) {
    len_accuracy_length = form.accuracy_length - length;
  }
  if (form.accuracy == 1 && form.accuracy_length == 0 && arg == 0 &&
      form.width != -1) {
    for (int i = 0; i < (form.width); i++) {
      str[*n] = ' ';
      (*n)++;
    }
  }
  int i = s21_strlen(memory_char) - 1;
  if (arg != 0 ||
      (form.accuracy = 1 && form.accuracy_length != 0 && arg == 0)) {
    if (form.minus == 1) {
      write_zero(str, n, length, form);
      while (i >= 0) {
        str[*n] = memory_char[i--];
        (*n)++;
      }
      write_space(str, n, len_accuracy_length + length, form);
    } else {
      write_space(str, n, len_accuracy_length + length, form);
      write_zero(str, n, length, form);
      while (i >= 0) {
        str[*n] = memory_char[i--];
        (*n)++;
      }
    }
  }
  free(memory_char);
}

int len_of_wchar(wchar_t *arg_s_l) {
  s21_size_t size = 0;
  while (arg_s_l[size]) {
    ++size;
  }
  return size;
}

void unsigned_num(char *memory_str, unsigned long long arg) {
  int i = 0;
  if (arg == ULONG_MAX) {
    arg = 1844674407370955161;
    memory_str[i] = '5';
    i++;
  }
  while (arg > 9) {
    memory_str[i++] = (arg % 10) + 48;
    arg = arg / 10;
  }
  memory_str[i] = (arg % 10) + 48;
}

void write_percent(char *str, int *n, struct_format form) {
  int length = 1;
  if (form.minus == 1) {
    str[*n] = '%';
    (*n)++;
    write_space(str, n, length, form);
  } else {
    write_space(str, n, length, form);
    str[*n] = '%';
    (*n)++;
  }
}