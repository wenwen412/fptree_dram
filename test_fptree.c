//
// Created by WenPan on 12/30/17.
//
#include <time.h>
#include "main.h"
extern bool verbose_output;
extern  int order;
extern node * queue;
// MAIN

int main( int argc, char ** argv ) {

    char * input_file;
    FILE * fp;
    node * root;
    int input, range2;
    char instruction;
    char license_part;

    root = NULL;
    verbose_output = false;

    if (argc > 1) {
        order = atoi(argv[1]);
        if (order < MIN_ORDER || order > MAX_ORDER) {
            fprintf(stderr, "Invalid order: %d .\n\n", order);
            usage_3();
            exit(EXIT_FAILURE);
        }
    }

    license_notice();
    usage_1();
    usage_2();

    if (argc > 2) {
        input_file = argv[2];
        fp = fopen(input_file, "r");
        if (fp == NULL) {
            perror("Failure to open input file.");
            exit(EXIT_FAILURE);
        }
//        while (!feof(fp)) {
//            fscanf(fp, "%d\n", &input);
//            root = insert(root, input, input);
//        }
    }

    int nums = 0;
    clock_t start, finish;
    double duration;
    char buf[512];
    start = clock();

    while (fgets(buf, sizeof buf, fp)) {
        nums++;
        fscanf(fp, "%d\n", &input);
        root = insert(root, input, input);
    }
    print_tree(root);

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "RART Insert spends %f seconds\n", duration );

    printf("> ");
    while (scanf("%c", &instruction) != EOF) {
        switch (instruction) {
            case 'd':
                scanf("%d", &input);
                root = delete(root, input);
                print_tree(root);
                break;
            case 'i':
                scanf("%d", &input);
                root = insert(root, input, input);
                print_tree(root);
                break;
            case 'f':
            case 'p':
                scanf("%d", &input);
                find_and_print(root, input, instruction == 'p');
                break;
            case 'r':
                scanf("%d %d", &input, &range2);
                if (input > range2) {
                    int tmp = range2;
                    range2 = input;
                    input = tmp;
                }
                find_and_print_range(root, input, range2, instruction == 'p');
                break;
            case 'l':
                print_leaves(root);
                break;
            case 'q':
                while (getchar() != (int)'\n');
                return EXIT_SUCCESS;
                break;
            case 't':
                print_tree(root);
                break;
            case 'v':
                verbose_output = !verbose_output;
                break;
            case 'x':
                if (root)
                    root = destroy_tree(root);
                print_tree(root);
                break;
            default:
                usage_2();
                break;
        }
        while (getchar() != (int)'\n');
        printf("> ");
    }
    printf("\n");

    return EXIT_SUCCESS;
}



/*
int main(int argc, char **argv) {
    clock_t start, finish;
    double duration;
    start = clock();

    char * filename = argv[1];

    //test_art_insert();
    //test_art_insert_verylong();
    test_art_insert_search(filename);
    //test_art_insert_delete();
    //test_art_insert_iter();

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
}

*/
/*
int test_FPTree(char * filename)
{
    node *root;
    clock_t start, finish;
    double duration;
    int len, nums, input;
    char buf[512];
    FILE *f = fopen(filename, "r");
    uint64_t line = 1;
    start = clock();

    while (fgets(buf, sizeof buf, f)) {
        nums++;
        fscanf(f, "%d\n", &input);
        root = insert(root, input, input);
        }
    uint64_t nlines = line - 1;

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "RART Insert spends %f seconds\n", duration );
    stats_report();
    printf( "Flush count is %d \n", extra_latency);
    fclose(f);
    print_tree(root);
}*/
