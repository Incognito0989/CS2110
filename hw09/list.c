/**
 * CS 2110 - Fall 2021 - Homework 9
 *
 * @author Andrew Jones
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return FAILURE if
 * the function returns an int).
 */

// Do not add ANY additional includes!!!
#include "list.h"
#include <stdio.h>
/* You should NOT have any global variables. */

static struct user *create_user(char *name, enum user_type type, union user_data data);
static int create_student(int num_classes, double *grades, struct student *dataOut); //completed for you
static int create_instructor(double salary, struct instructor *dataOut); //completed for you
static int user_equal(const struct user *user1, const struct user *user2);

/** create_user
 *
 * Helper function that creates a struct user by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the data union. This means malloc'ing space for copies of each field.
 *
 * If malloc returns NULL, you should return NULL as well.
 *
 * If creating a student/instructor fails, you must free everything you've allocated
 * and return NULL
 *
 * You should call create_student() or create_instructor() in this function
 * to create a deep copy of the union user_data depending on the enum user_type
 *
 * (hint: you cannot just assign the parameter data to the data part of user)
 *
 * Remember to set the next pointer to NULL.
 *
 * @param the fields of the struct user struct
 * @return a struct user, return NULL if malloc fails
 */
static struct user *create_user(char *name, enum user_type type, union user_data data)
{
    //UNUSED(name);
    //UNUSED(type);
    //UNUSED(data);
    //UNUSED(create_student);
    //UNUSED(create_instructor);
    //printf("CCCCCCCC%d\n", 0);
    struct user *u;
    //printf("CCCCCCCC%d\n", 1);
    if((u = malloc(sizeof(struct user))) == NULL) {
    	//free(u);
    	return NULL;
    }
    //printf("CCCCCCCC%d\n", 2);
    
    
    if(name == NULL) {
    	//printf("CCCCCCCC%d\n", 20);

    	u->name = NULL;
    	//printf("CCCCCCCC%d\n", 21);
    } else {
    	//u->name = (char *) malloc(sizeof(name));
    	//printf("CCCCCCCC%d\n", 22);
    	if((u->name = (char *) malloc(strlen(name) + 1)) == NULL) {
    		//printf("CCCCCCCC%d\n", 23);
    		free(u);
    		//printf("CCCCCCCC%d\n", 24);
    		return NULL;
    	}
    	//printf("CCCCCCCC%d\n", 25);
	    strncpy(u->name, name, strlen(name) + 1);
	    //printf("CCCCCCCC%d\n", 250);	
    }

    //printf("CCCCCCCC%d\n", 3);

    	u->type = type;
	    u->next = NULL;
    
	//printf("CCCCCCCC%d\n", 4);
    if(type == STUDENT) {
    	if(create_student(data.student.num_classes, data.student.grades, &(u->data.student)) == FAILURE) {
    		free(u->name);
    		free(u);
    		return NULL;
    	}
    	//create_student(data.student.num_classes, data.student.grades, &(u->data.student));
    } else if(type == INSTRUCTOR) {
    	if(create_instructor(data.instructor.salary, &(u->data.instructor)) == FAILURE) {
    		free(u->name);
    		free(u);
    		return NULL;
    	}
    	//create_instructor(data.instructor.salary, &(u->data.instructor));
    }

    return u;
}

/** create_student
 *
 * Helper function that creates a struct student and allocates memory for the grade array on the heap.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the student struct, and an existing pointer to a student
 * @return FAILURE if malloc fails, SUCCESS otherwise.
 */
static int create_student(int num_classes, double *grades, struct student *dataOut)
{
    /***do not change anything in this function***/
    dataOut->num_classes = num_classes;
    dataOut->grades = NULL;
    if (grades != NULL) {
        if (!(dataOut->grades = (double *) malloc(sizeof(double)*num_classes))) return FAILURE;
        memcpy(dataOut->grades, grades, sizeof(double)*num_classes);
    }
    return SUCCESS;
}

/** create_instructor
 *
 * Helper function that creates an struct instructor.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the struct instructor, and an existing pointer to an instructor
 * @return always SUCCESS, since there is no malloc call
 */
static int create_instructor(double salary, struct instructor *dataOut)
{
    /***do not edit anything in this function***/
    dataOut->salary = salary; //yes that's all this function does
    return SUCCESS;
}

/** student_equal
 *
 * Helper function to compare two struct students. You may find it useful to call this helper
 * function from the user_equal function that you have to implement.
 *
 * @param the two student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const struct student *student1, const struct student *student2)
{
    if (student1->num_classes != student2->num_classes) return 0;
    if (student1->grades != student2->grades)
    {
        if (student1->grades == NULL || student2->grades == NULL) return 0;
        if (memcmp(student1->grades, student2->grades,
                student1->num_classes * sizeof(double)))
        {
            return 0;
        }
    }
    return 1;
}

/** user_equal
 * Helper function to help you compare two user structs.
 *
 * If the name, type, and union fields are all equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null!
 * If two users both have null for a certain pointer, the pointers are
 * considered equal.
 * However, if either of the input users is NULL, you should return 0.
 *
 * You may find it useful to call the student_equal function defined above.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two struct user structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int user_equal(const struct user *user1, const struct user *user2)
{
    //UNUSED(user1);
    //UNUSED(user2);
    //UNUSED(student_equal);
    //printf("DDDDDDDD%d\n", 0);
    if(user1 == NULL || user2 == NULL) {
    	return 0;
    }
    //printf("DDDDDDDD%d\n", 1);
    if(((user1->name == NULL) && (user2->name != NULL)) || ((user1->name != NULL) && (user2->name == NULL))) {
    	return 0;
    }
    //printf("DDDDDDDD%d\n", 2);
    if(user1->type == STUDENT && user2->type == STUDENT) {
    	//printf("DDDDDDDD%d\n", 3);
    	if((user1->name == NULL && user2->name == NULL) || strcmp(user1->name, user2->name) == 0) {
    		const struct student *s1 = &(user1->data.student);
    		const struct student *s2 = &(user2->data.student);
    		//printf("DDDDDDDD%d\n\n", 30);
			return student_equal(s1, s2);
    	}
    	//printf("DDDDDDDD%d\n", 4);
    } else if(user1->type == user2->type) {
    	//printf("DDDDDDDD%d\n", 5);
    	if(user1->data.instructor.salary == user1->data.instructor.salary) {
			//printf("DDDDDDDD%d\n", 6);
			if(user1->name == NULL && user2->name == NULL) {
				//printf("DDDDDDDD%d\n\n", 7);
				return 1;
			}
			//printf("DDDDDDDD%d\n\n", 8);
			return strcmp(user1->name, user2->name) + 1;
    	}
    }
    //printf("DDDDDDDD%d\n\n", 9);
    return 0;
}

/** create_list
 *
 * Creates a struct user_list by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
struct user_list *create_list(void)
{
	struct user_list *l;
	l = malloc(sizeof(struct user_list));
	if(l == NULL) {
		return NULL;
	}
	//l->head = (struct user *) malloc(sizeof(struct user));
	l->size = 0;
	l->head = NULL;
    return l;
}

/** push_front
 *
 * Adds the element at the front of the struct user_list.
 *
 * @param list a pointer to the struct user_list structure.
 * @param      the fields of the struct user struct
 * @return FAILURE if the struct user_list is NULL or if allocating the new user fails,
 * SUCCESS if successful.
 */
int push_front(struct user_list *list, char *name, enum user_type type, union user_data data)
{
    //UNUSED(list);
    //UNUSED(name);
    //UNUSED(type);
    //UNUSED(data);
    //UNUSED(create_user);
    /*if(type == STUDENT) {

    	printf("XXXXXXXXXXXX%d ||  %d  ||  %d\n", 0, type, data.student.num_classes);
    }
    if(type == INSTRUCTOR) {
    	printf("XXXXXXXXXXXX%d ||  %d  ||  %f\n", 0, type, data.instructor.salary);

    }*/

    if(list == NULL) {
    	return FAILURE;
    }
	//printf("XXXXXXXXXXXX%d\n", 1);

	struct user *p = create_user(name, type , data);
	
	//printf("XXXXXXXXXXXX%d\n", 2);

	if(p == NULL) {
		return FAILURE;
	}
	//printf("XXXXXXXXXXXX%d\n", 3);
	p->next = list->head;
	//printf("XXXXXXXXXXXX%d\n", 4);

	list->head = p;
	//printf("XXXXXXXXXXXX%d\n", 5);

	list->size += 1;
	//printf("XXXXXXXXXXXX%d\n\n", 6);

	//printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX%s || %d  ||  %d\n", list->head->name, list->head->type, type);
    return SUCCESS;
}

/** push_back
 *
 * Adds the element to the back of the struct user_list.
 *
 * @param list a pointer to the struct user_list structure.
 * @param      the fields of the struct user struct
 * @return FAILURE if the index is out of bounds or the struct user_list is NULL
 *         or malloc fails (do not add the data in this case)
 *         otherwise return SUCCESS
 */
int push_back(struct user_list *list, char *name, enum user_type type, union user_data data)
{
    //UNUSED(list);
    //UNUSED(name);
    //UNUSED(type);
    //UNUSED(data);
    //UNUSED(create_user);
    if(list == NULL) {
    	return FAILURE;
    }
    if(list->size == 0) {
    	struct user *temp = create_user(name, type, data);
    	if((temp == NULL)) {
    		//free(temp);
    		return FAILURE;
    	}
    	list->head = temp;
    	list->size += 1;

    } else {
    	struct user *next = list->head;

    	while(next->next != NULL) {
    		next = next->next;
    	}
    	next->next = create_user(name, type, data);
    	if(next->next == NULL) {
    		free(next);
    		return FAILURE;
    	}

    	list->size += 1;
    }
    return SUCCESS;
}

/** add_at_index
 *
 * Add the element at the specified index in the struct user_list. This index must lie in
 * the inclusive range [0,size].
 * For example, if you have no elements in the struct user_list,
 * you should be able to add to index 0 but no further.
 * If you have two elements in the struct user_list,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the struct user_list structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the struct user struct
 * @return FAILURE if the index is out of bounds or the struct user_list is NULL
 *         or malloc fails (do not add the data in this case)
 *         otherwise return SUCCESS
 */
int add_at_index(struct user_list *list, int index, char *name, enum user_type type, union user_data data)
{
    //UNUSED(list);
    //UNUSED(index);
    //UNUSED(name);
    //UNUSED(type);
    //UNUSED(data);
    //UNUSED(create_user);
	//printf("XXXXXXX%d  ||  index: %d  ||  size: %d\n", 0, index, list->size);
    if(list == NULL || list->size < index || index < 0 || (&data.instructor == NULL && &data.student == NULL)) {
    	return FAILURE;
    }
    //printf("XXXXXXX%d\n", 1);
    if(index == 0) {
    	//printf("RETURN%d  ||  %d\n", 10, data.student.num_classes);
    	return push_front(list, name, type, data);
    }
    //printf("XXXXXXX%d\n", 2);
    if(index == list->size) {
    	//printf("RETURN%d\n", 20);
    	return push_back(list, name, type, data);
    }
    //printf("XXXXXXX%d\n", 3);
    struct user *p = create_user(name, type, data);
    //printf("XXXXXXX%d\n", 4);
    if(p == NULL) {
    	//printf("RETURN%d\n", 40);
    	return FAILURE;
    }
    //printf("XXXXXXX%d\n", 5);
    struct user *next = list->head;
    //printf("XXXXXXX%d\n", 6);
    for(int n = 0; n < index - 1; n += 1) {
    	//printf("XXXXXXX%d\n", (6*10) + n);
    	next = next->next;
    }
    //printf("XXXXXXX%d\n", 7);
    //struct user *nextt = next->next;
    //printf("XXXXXXX%d\n", 8);
    p->next = next->next;
    next->next = p;
    //printf("XXXXXXX%d\n", 9);
    //p->next = nextt;
    //printf("XXXXXXX%d\n", 10);
    list->size += 1;
    //printf("XXXXXXX%d  ||  %s\n", 11, p->next->name);
    //printf("RETURN%d\n", 110);

    return SUCCESS;
}

/** get
 *
 * Gets the data at the specified index in the struct user_list
 *
 * @param list a pointer to the struct user_list structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the struct user_list or NULL on failure.
 * @return FAILURE if dataOut is NULL or index is out of range of the struct user_list or
 *         the struct user_list is NULL, SUCCESS otherwise
 */
int get(struct user_list *list, int index, struct user **dataOut)
{
    //UNUSED(list);
    //UNUSED(index);
    //UNUSED(dataOut);
    //printf("%s\n", list->head->name);
    if(list == NULL || index >= list->size || index < 0 || list->size == 0 || dataOut == NULL) {
    	return FAILURE;
    }
    struct user *next = list->head;
    for(int n = 0; n < index; n++) {
    	next = next->next;
    }
    *dataOut = next;

    return SUCCESS;
}

/** contains
  *
  * Traverses the struct user_list, trying to see if the struct user_list contains some
  * data. We say the list contains some input if there exists some user with
  * equal data as the input.
  *
  * You should use 'user_equal' here to compare the data. Note that pointers are
  * allowed to be null!
  *
  * If there are multiple pieces of data in the struct user_list which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the struct user_list structure
  * @param data The data, to see if it exists in the struct user_list
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the struct user_list or NULL on failure
  * @return int    FAILURE if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else SUCCESS
  */
int contains(struct user_list *list, struct user *data, struct user **dataOut)
{
    //UNUSED(list);
    //UNUSED(data);
    //UNUSED(dataOut);
    //UNUSED(user_equal);
    if(dataOut == NULL) {
    	return FAILURE;
    }
    if(list == NULL || list->size == 0 || data == NULL) {
    	*dataOut = NULL;
    	return FAILURE;
    }

    struct user *p = list->head;
    for(int n = 0; n < list->size; n++) {
    	//XXXXXXXXXX  possibly something wrong w my equal method
    	if(user_equal(p, data) == 1) {
    		*dataOut = p;
    		return SUCCESS;
    	}
    	p = p->next;
    }
    *dataOut = NULL;
    return FAILURE;
}

/** pop_front
  *
  * Removes the user at the front of the struct user_list, and returns its data.
  *
  * @param list a pointer to the struct user_list.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                struct user or NULL if the struct user_list is NULL or empty
  * @return FAILURE if dataOut is NULL (the struct user_list is NULL or empty),
  *         else SUCCESS
  */
int pop_front(struct user_list *list, struct user **dataOut)
{
    //UNUSED(list);
    //UNUSED(dataOut);
    if(dataOut == NULL || list == NULL || list->size == 0) {
    	return FAILURE;
    }
    //struct user *p = list->head;
    //UNUSED(p);
    *dataOut = list->head;
    //free(p->name);
    //free(p);
    list->head = list->head->next;
    list->size -= 1;
    return SUCCESS;
}

/** pop_back
  *
  * Removes the user at the back of the struct user_list, and returns its data.
  *
  * @param list a pointer to the struct user_list.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                struct user or NULL if the struct user_list is NULL or empty
  * @return FAILURE if dataOut is NULL (the struct user_list is NULL or empty),
  *         else SUCCESS
  */
int pop_back(struct user_list *list, struct user **dataOut)
{
    //UNUSED(list);
    //UNUSED(dataOut);
    if(list == NULL || dataOut == NULL || list->size == 0) {
    	return FAILURE;
    }
    if(list->size == 1) {
    	return pop_front(list, dataOut);
    }
    struct user *next = list->head;
    struct user *prev;
    for(int n = 0; n < list->size - 1; n++) {
    	prev = next;
    	next = next->next;
    }
    prev->next = NULL;
    *dataOut = next;
    //free(next->name);
    //free(next);
    list->size -= 1;
    return SUCCESS;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the struct user_list.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to a pointer used to return the data in the 
 *                struct user at index or NULL if the struct user_list is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return FAILURE if the index is out of bounds, the struct user_list is NULL or
 *         the dataOut is NULL
 *         otherwise return SUCCESS
 */
int remove_at_index(struct user_list *list, struct user **dataOut, int index)
{
    //UNUSED(list);
    //UNUSED(index);
    //UNUSED(dataOut);
    if(list == NULL || dataOut == NULL || index >= list->size || index < 0) {
    	return FAILURE;
    }
    if(list->size == 1 || index == 0) {
    	return pop_front(list, dataOut);
    }
    struct user *cur = list->head;
    for(int n = 0; n < index - 1; n++) {
    	cur = cur->next;
    }
    //struct user *prev = cur->next;
    *dataOut = cur->next;
    //free(prev->name);
    //free(prev);
    if(cur->next->next == NULL) {
    	cur->next = NULL;
    } else {
    	cur->next = cur->next->next;
    }
    list->size -= 1;
    return SUCCESS;
}

/** empty_list
 *
 * Empties the struct user_list. After this is called, the struct user_list should be
 * empty. This does NOT free the struct user_list struct itself, just all users and
 * data within. Make sure to check that the list is not NULL before
 * using it.
 *
 * Once again, the things that need to be freed after this function are:
 * - the user structs
 * - all pointers in the user struct (and the union within)
 *
 * However, if you're using other functions you've written (which you should be),
 * those functions might take care of some of the freeing for you.
 *
 * You may call free on a char pointer as well as a struct pointer.
 *
 * If 'list' is NULL, don't do anything.
 *
 * @param list a pointer to the struct user_list structure
 */
void empty_list(struct user_list *list)
{
   // UNUSED(list);
	if(list == NULL || list->size == 0) {
		return;
	}
	struct user **p = (struct user **) malloc(sizeof(struct user));
	if(p == NULL) {
		return;
	}
	while(list->size > 0) {
		pop_front(list, p);
		free((*p)->name);
		if((**p).type == STUDENT) {
			free((**p).data.student.grades);
		}
		free(*p);
	}
	free(p);
	list->head = NULL;
	list->size = 0;
}

/** get_highest_paid
 *
 * Traverses the struct user_list, determining the highest of all instructor salaries and
 * returning the struct user corresponding to the highest paid instructor.
 *
 * If there are multiple highest paid instructors in the list, return the one that shows up
 * earlier in the list (closer to head).
 *
 * You should make sure your code only looks at instructors, as students do not have salaries!
 *
 * If there are no instructors in the list, place NULL at dataOut.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to pointer to struct user used to return the highest paid instructor.
 *                  or NULL if there are no instructors or the list is NULL or empty
 * @return FAILURE if the struct user_list is NULL or empty, else SUCCESS
 */
int get_highest_paid(struct user_list *list, struct user **dataOut)
{
    //UNUSED(list);
    //UNUSED(dataOut);
    if(dataOut == NULL) {
    	return FAILURE;
    }
    if(list == NULL || list->size == 0) {
    	*dataOut = NULL;
    	return FAILURE;
    }
    struct user *p = list->head;
    struct user *max = NULL;
    
    for(int n = 0; n < list->size; n++) {
    	
    	if(p->type == INSTRUCTOR) {
    		if(max == NULL) {
    			max = p;
    		} else if(p->data.instructor.salary > max->data.instructor.salary) {
    			max = p;
    		}
    	}
    	p = p->next;

    }

    if(max == NULL) {
    	*dataOut = NULL;
    	return SUCCESS;
    }
    *dataOut = max;
    return SUCCESS;
}


/** is_passing_all_classes
 *
 * Traverses the struct user_list, finding the student with the given name and 
 * determining whether they're passing all their classes.
 * 
 * We say a student is passing a class if their grade is greater than 
 * or equal to 60.
 *
 * You should make sure your code only considers students, even if there is 
 * an instructor of the same name!
 *
 * If a student is not taking any classes, they are NOT considered to be passing.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to int used to return whether or not the student 
 *                is passing their classes. Insert 1 if they are passing, 
 *                0 if they are not, or -1 if the user_list is NULL or empty 
 *                or does not contain the student with the given name.
 * @return FAILURE if the struct user_list is NULL or empty or does not contain
 *                 the student named, else SUCCESS
 */
int is_passing_all_classes(struct user_list *list, char *name, int *dataOut)
{
    //UNUSED(list);
    //UNUSED(name);
    //UNUSED(dataOut);
    if(list == NULL || list->size == 0) {
    	*dataOut = -1;
    	return FAILURE;
    }
    if(dataOut == NULL) {
    	return FAILURE;
    }
    struct user *p = list->head;
    for(int n = 0; n < list->size; n++) {
    	if(p->type == STUDENT) {
    		if(strcmp(name, p->name) == 0) {
    			if(p->data.student.num_classes == 0) {
			    	*dataOut = 0;
			    	return SUCCESS;
    			}
			    for(int j = 0; j < p->data.student.num_classes; j++) {
					if(*((p->data.student.grades) + j) < 60.0) {
						*dataOut = 0;
						return SUCCESS;
					}
    			}
    			*dataOut = 1;
    			return SUCCESS;
    		}
    	}
    	p = p->next;
    }
	*dataOut = -1;
	return FAILURE;
}

/** end_semester
 *
 * Traverses the struct user_list, performing an operation on each user.
 *
 * For students:
 *    - All classes should be dropped (num_classes = 0)
 *    - The grades array should be updated accordingly (set to NULL)
 *    - You should not leak memory while doing this
 * For instructors:
 *    - You should add 10000 to their current salary.
 *
 * @param list a pointer to the struct user_list structure
 * @return FAILURE if the struct user_list is NULL or empty,
 *                else SUCCESS
 */
int end_semester(struct user_list *list)
{
    //UNUSED(list);
    if(list == NULL || list->size == 0) {
    	return FAILURE;
    }
    struct user *p = list->head;
    for(int n = 0; n < list->size; n++) {
    	if(p->type == STUDENT) {
    		if(p->data.student.num_classes > 0) {
				free(p->data.student.grades);
    			p->data.student.grades = NULL;
    			p->data.student.num_classes = 0;
    		}    		
    	} else {
    		p->data.instructor.salary += 10000;
    	}
    	p = p->next;
    }
    return SUCCESS;
}