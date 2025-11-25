#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int n, H, W;
static char *g;
static unsigned char *vis;

static void shuffle(int d[4])
{
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = d[i]; d[i] = d[j]; d[j] = t;
    }
}

static void breakWall(int r1, int c1, int r2, int c2)
{
    int gr1 = 2 * r1 + 1, gc1 = 2 * c1 + 1;
    int gr2 = 2 * r2 + 1, gc2 = 2 * c2 + 1;
    int wr = (gr1 + gr2) / 2;
    int wc = (gc1 + gc2) / 2;
    g[wr * (W + 1) + wc] = '.';
}

static void dfs(int r, int c)
{
    vis[r * n + c] = 1;

    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs);

    for (int i = 0; i < 4; i++) {
        int nr = r, nc = c;
        if (dirs[i] == 0) nr--;
        if (dirs[i] == 1) nr++;
        if (dirs[i] == 2) nc--;
        if (dirs[i] == 3) nc++;

        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (vis[nr * n + nc]) continue;

        breakWall(r, c, nr, nc);
        dfs(nr, nc);
    }
}

int main(void)
{
    n = 6;
    H = 2 * n + 1;
    W = 2 * n + 1;

    srand((unsigned)time(NULL));

    g = malloc((size_t)H * (size_t)(W + 1));
    vis = calloc((size_t)n * n, 1);

    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) g[r * (W + 1) + c] = '#';
        g[r * (W + 1) + W] = '\0';
    }

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            g[(2 * r + 1) * (W + 1) + (2 * c + 1)] = '.';

    dfs(0, 0);

    for (int r = 0; r < H; r++) puts(&g[r * (W + 1)]);

    free(g);
    free(vis);
    return 0;
}
