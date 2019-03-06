for(k = 1; k <= n; k ++)
    for(i = 1; i <= n; i ++)
        for(j = 1; j <= n; j ++)
            if(e[i][j] > e[i][k] + e[k][j])
                e[i][j]=e[i][k]+e[k][j];