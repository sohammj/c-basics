#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define SUBJECTS 5
#define DATA_FILE "gradebook.txt"

struct Student {
    int roll;
    char name[NAME_LEN];
    float marks[SUBJECTS];
    float total;
    float average;
    char grade;
};


void addStudent(struct Student db[], int *n);
void listStudents(struct Student db[], int n);
int  findByRoll(struct Student db[], int n, int roll);
void updateMarks(struct Student db[], int n);
void deleteStudent(struct Student db[], int *n);
void computeResult(struct Student *s);
void saveToFile(struct Student db[], int n);
int  loadFromFile(struct Student db[], int *n);

int main(void) {
    struct Student db[MAX_STUDENTS];
    int count = 0;
    loadFromFile(db, &count);

    int ch;
    do {
        printf("\n=== Gradebook ===\n");
        printf("1 Add   2 List   3 Search   4 Update   5 Delete   6 Save   7 Load   0 Exit\n");
        printf("Choice: ");
        if (scanf("%d", &ch) != 1) break;

        switch (ch) {
            case 1:
                addStudent(db, &count);
                break;

            case 2:
                listStudents(db, count);
                break;

            case 3: {
                int r;
                printf("Roll: ");
                scanf("%d", &r);
                int i = findByRoll(db, count, r);
                if (i == -1) printf("Not found.\n");
                else {
                    printf("Roll=%d Name=%s ", db[i].roll, db[i].name);
                    for (int k = 0; k < SUBJECTS; k++)
                        printf("M%d=%.2f ", k + 1, db[i].marks[k]);
                    printf("Total=%.2f Avg=%.2f Grade=%c\n",
                           db[i].total, db[i].average, db[i].grade);
                }
                break;
            }

            case 4:
                updateMarks(db, count);
                break;

            case 5:
                deleteStudent(db, &count);
                break;

            case 6:
                saveToFile(db, count);
                break;

            case 7:
                if (loadFromFile(db, &count)) printf("Loaded.\n");
                else printf("Load failed.\n");
                break;

            case 0:
                break;

            default:
                printf("Invalid.\n");
                break;
        }
    } while (ch != 0);

    saveToFile(db, count);
    printf("Bye.\n");
    return 0;
}



void computeResult(struct Student *s) {
    s->total = 0.0f;
    for (int i=0; i<SUBJECTS; i++) s->total += s->marks[i];
    s->average = s->total / SUBJECTS;

    if      (s->average >= 90) s->grade = 'A';
    else if (s->average >= 75) s->grade = 'B';
    else if (s->average >= 60) s->grade = 'C';
    else if (s->average >= 40) s->grade = 'D';
    else                       s->grade = 'F';
}

int findByRoll(struct Student db[], int n, int roll) {
    for (int i=0; i<n; i++) if (db[i].roll == roll) return i;
    return -1;
}

void addStudent(struct Student db[], int *n) {
    if (*n >= MAX_STUDENTS) { printf("Full.\n"); return; }

    struct Student s;
    printf("Roll: ");  scanf("%d", &s.roll);
    if (findByRoll(db, *n, s.roll) != -1) { printf("Duplicate roll.\n"); return; }

    printf("Name (no spaces): "); scanf("%49s", s.name);
    for (int i=0; i<SUBJECTS; i++) {
        printf("Marks %d: ", i+1);
        scanf("%f", &s.marks[i]);
    }
    computeResult(&s);

    db[*n] = s;
    (*n)++;
    printf("Added.\n");
}

void listStudents(struct Student db[], int n) {
    if (n == 0) { printf("No records.\n"); return; }
    for (int i=0; i<n; i++) {
        printf("Roll=%d Name=%s ", db[i].roll, db[i].name);
        for (int j=0; j<SUBJECTS; j++) printf("M%d=%.2f ", j+1, db[i].marks[j]);
        printf("Total=%.2f Avg=%.2f Grade=%c\n",
               db[i].total, db[i].average, db[i].grade);
    }
}

void updateMarks(struct Student db[], int n) {
    int r; printf("Roll to update: "); scanf("%d", &r);
    int i = findByRoll(db, n, r);
    if (i == -1) { printf("Not found.\n"); return; }

    for (int k=0; k<SUBJECTS; k++) {
        printf("New Marks %d: ", k+1);
        scanf("%f", &db[i].marks[k]);
    }
    computeResult(&db[i]);
    printf("Updated.\n");
}

void deleteStudent(struct Student db[], int *n) {
    int r; printf("Roll to delete: "); scanf("%d", &r);
    int i = findByRoll(db, *n, r);
    if (i == -1) { printf("Not found.\n"); return; }

    for (int k=i; k<*n-1; k++) db[k] = db[k+1];
    (*n)--;
    printf("Deleted.\n");
}




void saveToFile(struct Student db[], int n) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) { printf("Save failed.\n"); return; }

    for (int i=0; i<n; i++) {
        fprintf(fp, "%d %s", db[i].roll, db[i].name);
        for (int j=0; j<SUBJECTS; j++) fprintf(fp, " %.2f", db[i].marks[j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Saved %d.\n", n);
}



int loadFromFile(struct Student db[], int *n) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) return 0;

    *n = 0;
    while (*n < MAX_STUDENTS) {
        struct Student s;
        int read = fscanf(fp, "%d %49s %f %f %f %f %f",
                          &s.roll, s.name,
                          &s.marks[0], &s.marks[1], &s.marks[2],
                          &s.marks[3], &s.marks[4]);
        if (read != 7) break;
        computeResult(&s);
        db[*n] = s;
        (*n)++;
    }
    fclose(fp);
    return 1;
}
