#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "grades.h"
#include "linked-list.h"


#define MAX_GRADE 100
#define ERROR 1
#define FAIL -1

struct grades{
    struct list *students_list;
};

struct student{
    char *name;
    int id;
    struct list *student_courses;
};

struct course{
    char *course_name;
    int grade;
};

/* My user functions*/
int clone_student(void *element, void **output);
void destroy_student(void *element);
int clone_course(void *element, void **output);
void course_destroy(void *element);

/* Private functions for this module */
static struct iterator* list_find_id(struct list *students_list, const int id);
static struct iterator* list_find_course(struct list *student_courses,
                                         const char *name);

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init(){
    struct grades *new_grades = (struct grades*)malloc(sizeof(struct grades));
    if(new_grades == NULL){
        free(new_grades);
        return NULL;
    }
    new_grades->students_list = list_init(clone_student, destroy_student);
    if(new_grades->students_list == NULL){
        free(new_grades);
        return NULL;
    }
    return new_grades;
}
/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
    if(grades == NULL){
        return;
    }
    list_destroy(grades->students_list);
    free(grades);
    return;
}
/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
    if(grades == NULL || list_find_id(grades->students_list, id) != NULL){
        return ERROR;
    }
    struct student *new_student;
    new_student = (struct student*)malloc(sizeof(struct student));
    if(new_student == NULL){
        free(new_student);
        return ERROR;
    }
    new_student->id = id;
    new_student->name = malloc(sizeof(char)*(strlen(name)+1));
    if(new_student->name == NULL){
        free(new_student->name);
        free(new_student);
        return ERROR;
    }
    strcpy(new_student->name, name);
    new_student->student_courses = list_init(clone_course, course_destroy);
    if(new_student->student_courses == NULL){
        free(new_student->name);
        free(new_student);
        return ERROR;
    }
    if(list_push_back(grades->students_list, new_student) != 0){
        destroy_student(new_student);
        return ERROR;
    }
    destroy_student(new_student);
    return 0;
}
/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
 int grades_add_grade(struct grades *grades,
                      const char *name,
                      int id,
                      int grade){

    if(grades == NULL || grade < 0 || grade > MAX_GRADE){
        return ERROR;
    }
    struct iterator *current_student = list_find_id(grades->students_list, id);
    if(current_student ==  NULL){
        return ERROR;
    }
    struct student *student_data = (struct student*)list_get(current_student);
    if(list_find_course(student_data->student_courses, name) != NULL){
        return ERROR;
    }

    struct course *new_course=(struct course*)malloc(sizeof(struct course));
    if(new_course == NULL){
        free(new_course);
        return ERROR;
    }
    new_course->course_name = malloc(sizeof(char)*(strlen(name)+1));
    if(new_course->course_name == NULL){
        free(new_course->course_name);
        free(new_course);
        return ERROR;
    }
    strcpy(new_course->course_name, name);
    new_course->grade = grade;

    if(list_push_back(student_data->student_courses, new_course) != 0){
        course_destroy(new_course);
        return ERROR;
    }
    course_destroy(new_course);
    return 0;
}
/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out){
    struct iterator *student_data = list_find_id(grades->students_list, id);
    if(grades == NULL || student_data == NULL){
        *out = NULL;
        return FAIL;
    }

    struct student *calc_student = (struct student*)list_get(student_data);
    char *student_name = malloc(sizeof(char)*(strlen(calc_student->name)+1));
    if(student_name == NULL){
        free(student_name);
        *out = NULL;
        return FAIL;
    }

    strcpy(student_name,calc_student->name);
    *out = student_name;

    struct iterator *course_data = list_begin(calc_student->student_courses);
    size_t list_len = list_size(calc_student->student_courses);
    float avg = 0.0;
    if(course_data == NULL){
        return avg;
    }
    for(size_t i = 0; i < list_len; i++){
        struct course *current_course = (struct course*)list_get(course_data);
        avg += current_course->grade;
        course_data = list_next(course_data);
    }
    avg = avg/list_len;
    return avg;
}
/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
    struct iterator *student_data = list_find_id(grades->students_list, id);
    if(grades == NULL || student_data == NULL){
        return ERROR;
    }

    struct student *print_student = (struct student*)list_get(student_data);
    printf("%s %d:", print_student->name, print_student->id);

    if(print_student->student_courses == NULL){
        printf("\n");
        return 0;
    }

    struct iterator *course_data = list_begin(print_student->student_courses);
    size_t list_len = list_size(print_student->student_courses);
    for(size_t i = 0; i < list_len; i++){
        struct course *current_course = (struct course*)list_get(course_data);
        printf(" %s %d", current_course->course_name, current_course->grade);
        if(i != list_len - 1){
            printf(",");
        }
        course_data = list_next(course_data);
    }
    printf("\n");
    return 0;
}
/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
    struct iterator *current_student = list_begin(grades->students_list);
    if(grades == NULL){
        return ERROR;
    }
    size_t list_len = list_size(grades->students_list);
    for(size_t i = 0; i < list_len; i++){
        struct student *student_data;
        student_data = (struct student*)list_get(current_student);
        grades_print_student(grades, student_data->id);
        current_student = list_next(current_student);
    }
    return 0;
}



/* User functions for Using The linked list ADT*/
int clone_student(void *element, void **output){
    struct student *student_data = (struct student*)element;
    struct student *new_student;
    new_student = (struct student*)malloc(sizeof(struct student));
    if(new_student == NULL){
        free(new_student);
        return ERROR;
    }
    new_student->id = student_data->id;
    new_student->name = malloc(sizeof(char)*(strlen(student_data->name)+1));
    if(new_student->name == NULL){
        free(new_student->name);
        return ERROR;
    }
    strcpy(new_student->name, student_data->name);
    new_student->student_courses = list_init(clone_course, course_destroy);
    *output = (void*)new_student;
    return 0;
}


void destroy_student(void *element){
    struct student *rm_student = (struct student*)element;
    list_destroy(rm_student->student_courses);
    free(rm_student->name);
    free(rm_student);
}


int clone_course(void *element, void **output){
    struct course *course_data = (struct course*)element;
    struct course *new_course = (struct course*)malloc(sizeof(struct course));
    if(new_course == NULL){
        free(new_course);
        return ERROR;
    }
    int len_name = strlen(course_data->course_name) + 1;
    new_course->course_name = malloc(sizeof(char)*len_name);
    if(new_course->course_name == NULL){
        free(new_course->course_name);
        return ERROR;
    }
    strcpy(new_course->course_name,course_data->course_name);
    new_course->grade = course_data->grade;
    *output = (void*)new_course;
    return 0;
}


void course_destroy(void *element){
    struct course *rm_course = (struct course*)element;
    free(rm_course->course_name);
    free(rm_course);
}


static struct iterator* list_find_id(struct list *students_list, const int id){

    struct iterator *current_student = list_begin(students_list);
    size_t list_len = list_size(students_list);
    for(size_t i = 0; i < list_len; i++){
        struct student *student_data;
        student_data = (struct student*)list_get(current_student);
        if(student_data->id == id){
            return current_student;
        }
    current_student = list_next(current_student);
    }
    return NULL;
}


static struct iterator* list_find_course(struct list *student_courses,
                                         const char *name){

    struct iterator *current_course = list_begin(student_courses);
    size_t list_len = list_size(student_courses);
    for(size_t i = 0; i < list_len; i++){
        struct course *course_data = (struct course*)list_get(current_course);
        if(strcmp(course_data->course_name, name) == 0){
            return current_course;
        }
        current_course = list_next(current_course);
    }
    return NULL;
}
