/**
 * @file my_string.c
 * @author Andrew Jones
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2021-06-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"
#include <stdio.h>
static double PI = 3.1415;


char * returnSomeLetters(char *str) {
  char result[4];
  for(int n = 0; n < 3; n++) {
    result[n] = str[n];
  }
  result[3] = '\0';
  return result;
}

void func(int a, int *b, int *c) {
  a++;
  c = b;
  *b = a + 7;
  (*c)++;
}

int main(void) {
  int a = 12;
  int b = 9;
  int c = 36;
  func(a, &b, &c);
  printf("A: %d\n", a);
  printf("A: %d\n", b);
  printf("A: %d\n", c);
  printf("Hello Quiz 4"); 


  char string[] = "cswiurfbwfnrjsbfnw;nbf";
  char *result = returnSomeLetters(string);
  printf("%s", result);

  return 0;
}
/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  //UNUSED_PARAM(s);
  int n = 0;
  while (*s != 0) {
	  n++;
	  s++;
  }

  return n;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  //UNUSED_PARAM(s1);
  //UNUSED_PARAM(s2);
  //UNUSED_PARAM(n); a byte is 8bits
	//int c = 0;
  if(*s1 == '\0' && *s2 != '\0') {
    return -1;
  } else if(*s1 != '\0' && *s2 == '\0') {
    return 1;
  }

  
	while (n != 0 && (*s1 != 0 || *s2 != 0)) {
		if (*s1 > *s2) {
			return 1;                                    //updated this to change the difference by how significant the byte is
		}
		else if (*s1 < *s2) {
			return -1;                                  //same^^
		}
		s1++;
		s2++;
		n--;
	}
  return 0;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  //UNUSED_PARAM(dest);
  //UNUSED_PARAM(src);
  //UNUSED_PARAM(n);
  //printf("first dest: %s\n", dest);
  //printf("first src: %s\n", src);
  char *d = dest;
	while (n > 0) {
		*dest = *src;
    if(*dest == '\0') {
      return d;
    }
		src++;
		dest++;
		n--;
	}

  // *dest = '\0';
  //printf("final dest: %s\n", d);
  return (d);
  /*
  char *d = dest;
  while (n > 0 && *src != '\0') {
    *dest = *src;
    src++;
    dest++;
    n--;
  }
  *dest = *src;
  //printf("final dest: %s\n", d);
  return (d);*/
}
