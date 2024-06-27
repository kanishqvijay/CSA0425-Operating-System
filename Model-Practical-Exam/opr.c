#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int search(int key, int* fr, int fn)
{
    for (int i = 0; i < fn; i++)
        if (fr[i] == key)
            return 1;
    return 0;
}

int predict(int* pg, int* fr, int pn, int index, int fn)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimalPage(int* pg, int pn, int fn)
{
    int* fr = (int*)calloc(fn, sizeof(int));
    int hit = 0;
    int index = 0;

    for (int i = 0; i < pn; i++) {
        if (search(pg[i], fr, fn)) {
            hit++;
            continue;
        }

        if (index < fn)
            fr[index++] = pg[i];
        else {
            int j = predict(pg, fr, pn, i + 1, fn);
            fr[j] = pg[i];
        }

        printf("Page %d -> Frame: ", pg[i]);
        for (int k = 0; k < fn; k++)
            printf("%d ", fr[k]);
        printf("\n");
    }
    printf("Hits: %d\n", hit);
    printf("Misses: %d\n", pn - hit);

    free(fr);
}

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int page_count = sizeof(pages) / sizeof(pages[0]);
    int frame_count = 4;

    printf("Page Reference Sequence:\n");
    for (int i = 0; i < page_count; i++)
        printf("%d ", pages[i]);
    printf("\n\n");

    optimalPage(pages, page_count, frame_count);

    return 0;
}