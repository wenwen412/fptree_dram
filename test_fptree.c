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
    //char * input, range2;
    char input[24], range2[24];
    int num_input;
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
    }

    int nums = 0, line =0;
    clock_t start, finish;
    double duration;
    record * r;
    char buf[512];
    start = clock();
    int len = 0;

    while (fgets(buf, sizeof buf, fp)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        root = insert(root, (char*)buf, nums);
        nums++;
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "FPTree Insert spends %f seconds\n", duration );


    /* Range scan
     */
    start = clock();
    char start_key[100];
    if(strcmp(input_file,"words2.txt") == 0)
        strcpy(start_key, "aplitic");
    else if (strcmp(input_file,"seq_nums.txt") == 0)
        strcpy(start_key, "1500000");
    else if (strcmp(input_file,"rd_string_1m.txt") == 0)
        strcpy(start_key, "SjoaTJY");
    /* int array_size = key_end - key_start + 1;
    * We temporarily set array size to MAX_RANGE*/
    int array_size = MAX_RANGE;
    char * returned_keys[array_size];
    void * returned_pointers[array_size];
    int num_found = find_range2( root, start_key, 10000, false,
                                returned_keys, returned_pointers );
    if (!num_found)
        printf("None found.\n");
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "FPTree range scan spends %f seconds\n", duration );

    /* rebuild
     */
    /*
    start = clock();
    node * new_root = rebuild();
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "FPTree rebuild spends %f seconds\n", duration );
    */



    /* Search */
    fseek(fp, 0, SEEK_SET);
    line = 1;
    start = clock();
    while (fgets(buf, sizeof buf, fp)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        r = find(root, buf, false, NULL);
        line++;
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "FPTree search spends %f seconds\n", duration );


    /* delete */
    line = 1;
    fseek(fp, 0, SEEK_SET);
    start = clock();
    while (fgets(buf, sizeof buf, fp)) {
        len = strlen(buf);
        buf[len-1] = '\0';
        root = delete(root, buf);
        line++;
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "RART deletion spends %f seconds\n", duration );


    printf("> ");
    while (scanf("%c", &instruction) != EOF) {
        switch (instruction) {
            case 'd':
                scanf("%s", input);
                root = delete(root, input);
                // print_tree(root);
                break;
            case 'i':
                scanf("%s", &input);
                root = insert(root, input, input);
                print_tree(root);
                break;
            case 'f':
            case 'p':
                scanf("%s", &input);
                find_and_print(root, input, instruction == 'p');
                break;
            case 'r':
                scanf("%s %d", &input, &range2);
                if (input > range2) {
                    int tmp = range2;
                    // range2 = input;
                    // input = tmp;
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
