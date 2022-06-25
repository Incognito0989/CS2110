/**
 * @file hw7.c
 * @author Andrew Jones
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2021-10-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of pokemon structs
struct pokemon pokedex[MAX_POKEDEX_SIZE];

int size = 0;

/** catchPokemon
 *
 * @brief creates a new pokemon struct and adds it to the array of pokemon structs, "pokedex"
 *
 *
 * @param "nickname" nickname of the pokemon being created and added
 *               NOTE: if the length of the nickname (including the null terminating character)
 *               is above MAX_NICKNAME_SIZE, truncate nickname to MAX_NICKNAME_SIZE. If the length
 *               is below MIN_NICKNAME_SIZE, return FAILURE.  
 *               
 * @param "pokedexNumber" pokedexNumber of the pokemon being created and added
 * @param "powerLevel" power level of the pokemon being created and added
 * @param "speciesName" species name of the pokemon being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "nickname" is less than MIN_NICKNAME_SIZE
 *         (2) a pokemon with the same already exits in the array "pokedex"
 *         (3) adding the new pokemon would cause the size of the array "pokedex" to
 *             exceed MAX_POKEDEX_SIZE
 */
int catchPokemon(const char *nickname, int pokedexNumber, double powerLevel, const char *speciesName)
{
   /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  //UNUSED_PARAM(nickname);
  //UNUSED_PARAM(pokedexNumber);
  //UNUSED_PARAM(powerLevel);
  //UNUSED_PARAM(speciesName);
	printf("nick: %s species: %s\n", nickname, speciesName);
	//failure if nickname is less than min size or adding pokemon exceeds pokedex max size
	if ((my_strlen(nickname) < MIN_NICKNAME_SIZE) || (MAX_POKEDEX_SIZE <= size + 1) || (my_strlen(speciesName) < MIN_SPECIESNAME_SIZE)) {
			printf("nick1: %s species: %s\n", nickname, speciesName);

		return FAILURE;
	}
	//failure if duplicate
	for(int n = 0; n < size; n++) {
		if(my_strncmp(pokedex[n].nickname, nickname, my_strlen(nickname)) == 0) {
				printf("nick2: %s species: %s\n", pokedex[n].nickname, nickname);

			return FAILURE;
		}
	}

	struct pokemon *myStruct = &pokedex[size];

	my_strncpy(myStruct->nickname, nickname, MAX_NICKNAME_SIZE - 1);			//minus one to have space for the null terminator
	if(my_strlen(myStruct->nickname) > MAX_NICKNAME_SIZE - 1) {
		myStruct->nickname[MAX_NICKNAME_SIZE - 1] = '\0';
	}

	myStruct->pokedexNumber = pokedexNumber;
	myStruct->powerLevel = powerLevel;

	my_strncpy(myStruct->speciesName, speciesName, MAX_SPECIESNAME_SIZE - 1);	//minus one to have space for the null terminator
	if(my_strlen(myStruct->speciesName) > MAX_SPECIESNAME_SIZE - 1) {
		myStruct->speciesName[MAX_SPECIESNAME_SIZE - 1] = '\0';
	}
	size++;
	for(int n = 0; n < size; n++) {
		printf("second: %s species: %s\n", pokedex[n].nickname, pokedex[n].speciesName);
	}
	//pokedex[pokedexNumber] = newStruct;

  return SUCCESS;
}

/** updatePokemonNickname
 *
 * @brief updates the nickname of an existing pokemon in the array of pokemon structs, "pokedex"
 *
 * @param "s" pokemon struct that exists in the array "pokedex"
 * @param "nickname" new nickname of pokemon "s"
 *               NOTE: if the length of nickname (including the null terminating character)
 *               is above MAX_NICKNAME_SIZE, truncate nickname to MAX_NICKNAME_SIZE
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the pokemon struct "s" can not be found in the array "pokedex"
 */
int updatePokemonNickname(struct pokemon s, const char *nickname)
{
  //UNUSED_PARAM(s);
  //UNUSED_PARAM(nickname);
	for(int n = 0; n < size; n++) {
		if(my_strncmp(pokedex[n].nickname, s.nickname, my_strlen(s.nickname)) == 0) {
			my_strncpy(pokedex[n].nickname, nickname, MAX_NICKNAME_SIZE - 1);
			if(my_strlen(pokedex[n].nickname) > MAX_NICKNAME_SIZE - 1) {
				pokedex[n].nickname[MAX_NICKNAME_SIZE - 1] = '\0';
			}
			return SUCCESS;
		}
	}

  return FAILURE;
}

/** swapPokemon
 *
 * @brief swaps the position of two pokemon structs in the array of pokemon structs, "pokedex"
 *
 * @param "index1" index of the first pokemon struct in the array "pokedex"
 * @param "index2" index of the second pokemon struct in the array "pokedex"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "pokedex"
 */
int swapPokemon(int index1, int index2)
{
  //UNUSED_PARAM(index1);
  //UNUSED_PARAM(index2);
	if(index1 < 0 || index2 < 0 || index1 >= size || index2 >= size) {
		return FAILURE;
	}
	struct pokemon myStruct = pokedex[index1];
	pokedex[index1] = pokedex[index2];
	pokedex[index2] = myStruct;
  return SUCCESS;
}

/** releasePokemon
 *
 * @brief removes pokemon in the array of pokemon structs, "pokedex", that has the same nickname
 *
 * @param "s" pokemon struct that exists in the array "pokedex"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the pokemon struct "s" can not be found in the array "pokedex"
 */
int releasePokemon(struct pokemon s)
{
  //UNUSED_PARAM(s);
	for(int n = 0; n < size; n++) {
		if(my_strncmp(pokedex[n].nickname, s.nickname, my_strlen(s.nickname)) == 0) {
			for(int i = n; i < size; i++) {
				swapPokemon(i, i + 1);
			}
			size--;
			return SUCCESS;
		}
	}
  return FAILURE;
}

/** comparePokemon
 *
 * @brief compares the two pokemons' pokedex number and names (using ASCII)
 *
 * @param "s1" pokemon struct that exists in the array "pokedex"
 * @param "s2" pokemon struct that exists in the array "pokedex"
 * @return negative number if s1 is less than s2, positive number if s1 is greater
 *         than s2, and 0 if s1 is equal to s2
 */
int comparePokemon(struct pokemon s1, struct pokemon s2)
{
  //UNUSED_PARAM(s1);
  //UNUSED_PARAM(s2);
	//printf("ComparePokemon\n");
	//printf("powerlevels: %f : %f\n", s1.powerLevel, s2.powerLevel);
	if(s1.pokedexNumber > s2.pokedexNumber) {
		//printf("Returning 1\n");
		return 1;
	} else if (s1.pokedexNumber < s2.pokedexNumber) {
		//printf("Returning -1\n");
		return -1;
	} else {
		//printf("NAME: %s  :  %s\n", s1.nickname, s2.nickname);
		//printf("Returning %d\n", my_strncmp(s1.nickname, s2.nickname, MAX_NICKNAME_SIZE));
		return my_strncmp(s1.nickname, s2.nickname, MAX_NICKNAME_SIZE);
	}
}

/** sortPokemon
 *
 * @brief using the comparePokemon function, sort the pokemons in the array of
 * pokemon structs, "pokedex," by the pokedex number and nicknames
 *
 * @param void
 * @return void
 */
void sortPokemon(void)
{
	for(int n = 0; n < size - 1; n++) {
		//printf("notsorted(%d)%s\n", n, pokedex[n].nickname);
		int min = n;
		for(int i = n + 1; i < size; i++) {
			//printf("%d \n", comparePokemon(pokedex[i], pokedex[n]));
			if(comparePokemon(pokedex[i], pokedex[min]) < 0) {
				min = i;;
			}
		}
		swapPokemon(n, min);
		//printf("sort(%d)%s\n", n, pokedex[n].nickname);
	}
}